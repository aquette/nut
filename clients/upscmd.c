/* upscmd - simple "client" to test instant commands via upsd

   Copyright (C)
     2000  Russell Kroll <rkroll@exploits.org>
     2019  EATON (author: Arnaud Quette <ArnaudQuette@eaton.com>)

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*/

#include "common.h"
#include "nut_platform.h"

#include <pwd.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include "upsclient.h"

static char			*upsname = NULL, *hostname = NULL;
static UPSCONN_t	*ups = NULL;
static int			status_info = 0;

struct list_t {
	char	*name;
	struct list_t	*next;
};

static void usage(const char *prog)
{
	printf("Network UPS Tools upscmd %s\n\n", UPS_VERSION);
	printf("usage: %s [-h]\n", prog);
	printf("       %s [-l <ups>]\n", prog);
	printf("       %s [-u <username>] [-p <password>] [-w] <ups> <command> [<value>]\n\n", prog);
	printf("Administration program to initiate instant commands on UPS hardware.\n");
	printf("\n");
	printf("  -h		display this help text\n");
	printf("  -l <ups>	show available commands on UPS <ups>\n");
	printf("  -u <username>	set username for command authentication\n");
	printf("  -p <password>	set password for command authentication\n");
	printf("  -w            wait for the completion of command by the driver\n");
	printf("                and return its actual result from the device\n");
	printf("\n");
	printf("  <ups>		UPS identifier - <upsname>[@<hostname>[:<port>]]\n");
	printf("  <command>	Valid instant command - test.panel.start, etc.\n");
	printf("  [<value>]	Additional data for command - number of seconds, etc.\n");
}

static void print_cmd(char *cmdname)
{
	int		ret;
	unsigned int	numq, numa;
	const char	*query[4];
	char		**answer;

	query[0] = "CMDDESC";
	query[1] = upsname;
	query[2] = cmdname;
	numq = 3;

	ret = upscli_get(ups, numq, query, &numa, &answer);

	if ((ret < 0) || (numa < numq)) {
		printf("%s\n", cmdname);
		return;
	}

	/* CMDDESC <upsname> <cmdname> <desc> */
	printf("%s - %s\n", cmdname, answer[3]);
}

static void listcmds(void)
{
	int		ret;
	unsigned int	numq, numa;
	const char	*query[4];
	char		**answer;
	struct list_t	*lhead = NULL, *llast = NULL, *ltmp, *lnext;

	query[0] = "CMD";
	query[1] = upsname;
	numq = 2;

	ret = upscli_list_start(ups, numq, query);

	if (ret < 0) {

		/* old upsd = no way to continue */
		if (upscli_upserror(ups) == UPSCLI_ERR_UNKCOMMAND) {
			fatalx(EXIT_FAILURE, "Error: upsd is too old to support this query");
		}

		fatalx(EXIT_FAILURE, "Error: %s", upscli_strerror(ups));
	}

	while (upscli_list_next(ups, numq, query, &numa, &answer) == 1) {

		/* CMD <upsname> <cmdname> */
		if (numa < 3) {
			fatalx(EXIT_FAILURE, "Error: insufficient data (got %d args, need at least 3)", numa);
		}

		/* we must first read the entire list of commands,
		   before we can start reading the descriptions */

		ltmp = xcalloc(1, sizeof(*ltmp));
		ltmp->name = xstrdup(answer[2]);

		if (llast) {
			llast->next = ltmp;
		} else {
			lhead = ltmp;
		}

		llast = ltmp;
	}

	/* walk the list and try to get descriptions, freeing as we go */
	printf("Instant commands supported on UPS [%s]:\n\n", upsname);

	for (ltmp = lhead; ltmp; ltmp = lnext) {
		lnext = ltmp->next;

		print_cmd(ltmp->name);

		free(ltmp->name);
		free(ltmp);
	}
}

static void do_cmd(char **argv, const int argc)
{
	int		cmd_complete = 0;
	char	buf[SMALLBUF];
	char	status_id[37]; /* UUID4_LEN */

	if (argc > 1) {
		snprintf(buf, sizeof(buf), "INSTCMD %s %s %s\n", upsname, argv[0], argv[1]);
	} else {
		snprintf(buf, sizeof(buf), "INSTCMD %s %s\n", upsname, argv[0]);
	}

	if (upscli_sendline(ups, buf, strlen(buf)) < 0) {
		fatalx(EXIT_FAILURE, "Can't send instant command: %s", upscli_strerror(ups));
	}

	if (upscli_readline(ups, buf, sizeof(buf)) < 0) {
		fatalx(EXIT_FAILURE, "Instant command failed: %s", upscli_strerror(ups));
	}

	/* verify answer */
	if (strncmp(buf, "OK", 2) != 0) {
		fatalx(EXIT_FAILURE, "Unexpected response from upsd: %s", buf);
	}

	/* check for status tracking id */
	if (status_info) {
		/* sanity check on the size: "OK " + UUID4_LEN */
		if (strlen(buf) == 39) {
			snprintf(status_id, sizeof(status_id), "%s", buf+3);

			/* send status tracking request, looping if status is PENDING */
			/* FIXME: consider adding a timeout! */
			while (!cmd_complete) {

				snprintf(buf, sizeof(buf), "GET CMDSET_STATUS %s\n", status_id);

				if (upscli_sendline(ups, buf, strlen(buf)) < 0) {
					fatalx(EXIT_FAILURE, "Can't send status tracking request: %s", upscli_strerror(ups));
				}

				/* and get status tracking reply */
				if (upscli_readline(ups, buf, sizeof(buf)) < 0) {
					fatalx(EXIT_FAILURE, "Can't receive status tracking information: %s", upscli_strerror(ups));
				}

				if (strncmp(buf, "PENDING", 7) != 0)
					cmd_complete = 1;

				/* wait a second before retrying */
				sleep (1);
			}
		}
	}
	/* reply as usual */
	fprintf(stderr, "%s\n", buf);
}

static void clean_exit(void)
{
	if (ups) {
		upscli_disconnect(ups);
	}

	free(upsname);
	free(hostname);
	free(ups);
}

int main(int argc, char **argv)
{
	int	i, ret, port;
	int	have_un = 0, have_pw = 0, cmdlist = 0;
	char	buf[SMALLBUF], username[SMALLBUF], password[SMALLBUF];
	const char	*prog = xbasename(argv[0]);

	while ((i = getopt(argc, argv, "+lhu:p:wV")) != -1) {

		switch (i)
		{
		case 'l':
			cmdlist = 1;
			break;

		case 'u':
			snprintf(username, sizeof(username), "%s", optarg);
			have_un = 1;
			break;

		case 'p':
			snprintf(password, sizeof(password), "%s", optarg);
			have_pw = 1;
			break;

		case 'w':
			status_info = 1;
			break;

		case 'V':
			fatalx(EXIT_SUCCESS, "Network UPS Tools upscmd %s", UPS_VERSION);

		case 'h':
		default:
			usage(prog);
			exit(EXIT_SUCCESS);
		}
	}

	argc -= optind;
	argv += optind;

	if (argc < 1) {
		usage(prog);
		exit(EXIT_SUCCESS);
	}

	/* be a good little client that cleans up after itself */
	atexit(clean_exit);

	if (upscli_splitname(argv[0], &upsname, &hostname, &port) != 0) {
		fatalx(EXIT_FAILURE, "Error: invalid UPS definition.  Required format: upsname[@hostname[:port]]");
	}

	ups = xcalloc(1, sizeof(*ups));

	if (upscli_connect(ups, hostname, port, 0) < 0) {
		fatalx(EXIT_FAILURE, "Error: %s", upscli_strerror(ups));
	}

	if (cmdlist) {
		listcmds();
		exit(EXIT_SUCCESS);
	}

	if (argc < 2) {
		usage(prog);
		exit(EXIT_SUCCESS);
	}

	/* also fallback for old command names */
	if (!strchr(argv[1], '.')) {
		fatalx(EXIT_FAILURE, "Error: old command names are not supported");
	}

	if (!have_un) {
		struct passwd	*pw;

		memset(username, '\0', sizeof(username));
		pw = getpwuid(getuid());

		if (pw) {
			printf("Username (%s): ", pw->pw_name);
		} else {
			printf("Username: ");
		}

		if (!fgets(username, sizeof(username), stdin)) {
			fatalx(EXIT_FAILURE, "Error reading from stdin!");
		}

		/* deal with that pesky newline */
		if (strlen(username) > 1) {
			username[strlen(username) - 1] = '\0';
		} else {
			if (!pw) {
				fatalx(EXIT_FAILURE, "No username available - even tried getpwuid");
			}

			snprintf(username, sizeof(username), "%s", pw->pw_name);
		}
	}

	/* getpass leaks slightly - use -p when testing in valgrind */
	if (!have_pw) {
		/* using getpass or getpass_r might not be a
		   good idea here (marked obsolete in POSIX) */
		char	*pwtmp = GETPASS("Password: ");

		if (!pwtmp) {
			fatalx(EXIT_FAILURE, "getpass failed: %s", strerror(errno));
		}

		snprintf(password, sizeof(password), "%s", pwtmp);
	}

	snprintf(buf, sizeof(buf), "USERNAME %s\n", username);

	if (upscli_sendline(ups, buf, strlen(buf)) < 0) {
		fatalx(EXIT_FAILURE, "Can't set username: %s", upscli_strerror(ups));
	}

	ret = upscli_readline(ups, buf, sizeof(buf));

	if (ret < 0) {
		if (upscli_upserror(ups) != UPSCLI_ERR_UNKCOMMAND) {
			fatalx(EXIT_FAILURE, "Set username failed: %s", upscli_strerror(ups));
		}

		fatalx(EXIT_FAILURE,
			"Set username failed due to an unknown command.\n"
			"You probably need to upgrade upsd.");
	}

	snprintf(buf, sizeof(buf), "PASSWORD %s\n", password);

	if (upscli_sendline(ups, buf, strlen(buf)) < 0) {
		fatalx(EXIT_FAILURE, "Can't set password: %s", upscli_strerror(ups));
	}

	if (upscli_readline(ups, buf, sizeof(buf)) < 0) {
		fatalx(EXIT_FAILURE, "Set password failed: %s", upscli_strerror(ups));
	}

	/* enable status tracking ID */
	if (status_info) {

		snprintf(buf, sizeof(buf), "SET CMDSET_STATUS ON\n");

		if (upscli_sendline(ups, buf, strlen(buf)) < 0) {
			fatalx(EXIT_FAILURE, "Can't enable command status tracking: %s", upscli_strerror(ups));
		}

		if (upscli_readline(ups, buf, sizeof(buf)) < 0) {
			fatalx(EXIT_FAILURE, "Enabling command status tracking failed: %s", upscli_strerror(ups));
		}
		else if (strncmp(buf, "OK", 2) != 0) { /* Verify the result */
			fatalx(EXIT_FAILURE, "Enabling command status tracking failed. upsd answered: %s", buf);
		}
	}

	do_cmd(&argv[1], argc - 1);

	exit(EXIT_SUCCESS);
}


/* Formal do_upsconf_args implementation to satisfy linker on AIX */
#if (defined NUT_PLATFORM_AIX)
void do_upsconf_args(char *upsname, char *var, char *val) {
        fatalx(EXIT_FAILURE, "INTERNAL ERROR: formal do_upsconf_args called");
}
#endif  /* end of #if (defined NUT_PLATFORM_AIX) */
