/* carel-bluebox-cooling-mib.c - subdriver to monitor Carel-BlueBox-cooling SNMP devices with NUT
 *
 *  Copyright (C)
 *  2011 - 2020	Arnaud Quette <arnaud.quette@free.fr>
 *  2020    	Eaton (Arnaud Quette <ArnaudQuette@Eaton.com>)
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include "carel-bluebox-cooling-mib.h"

#define CAREL_BLUEBOX_COOLING_MIB_VERSION  "0.1"

/* sysOIDs found on the Carel Bluebox version */
#define CAREL_BLUEBOX_COOLING_DEVICE_SYSOID ".1.3.6.1.4.1"

#define CAREL_BLUEBOX_COOLING_OID_MODEL_NAME ".1.3.6.1.4.1.9839.1.2.0"

/* other definitions */
/* FIXME: doubt on the values! */
#define DO_OFF 0
#define DO_ON  1

static info_lkp_t status_info[] = {
	{ 0, "on" },
	{ 1, "off" },
	{ 2, "off" },     /* off from digital input */
	{ 3, "off" },     /* off from superv */
	{ 4, "off" },     /* off from alarm */
	{ 5, "standby" },
	{ 0, NULL }
};

static info_lkp_t device_agent_info[] = {
	{ 2, "Generic cooling with Carel Bluebox communication" }, /* "Code of the Agent. 2=pCOWeb." */
	{ 0, NULL }
};

/* CAREL_COOLING Snmp2NUT lookup table */
static snmp_info_t carel_bluebox_cooling_mib[] = {

/*
https://github.com/librenms/librenms/blob/master/mibs/carel/KELVIN-pCOWeb-Chiller-MIB

Supported devices:
* CRAC mitsubishi i-NEXT_DX (Carel Bluebox DBBB0mcbMF)
	For the air conditioning system NutKao use:
	https://library.mitsubishielectric.co.uk/pdf/book/i-NEXT_DX_Installation__Use_and_Maintenance_Manual__Z_18_7_EN#page-1


*/

	/* Device collection */
	{ "device.mfr", ST_FLAG_STRING, SU_INFOSIZE, NULL, "Generic",
		SU_FLAG_STATIC | SU_FLAG_ABSENT | SU_FLAG_OK, NULL },
	/* agentCode.0 = INTEGER: 2 */
	{ "device.model", ST_FLAG_STRING, SU_INFOSIZE,
		CAREL_BLUEBOX_COOLING_OID_MODEL_NAME,
		"Generic cooling Carel/Bluebox", SU_FLAG_STATIC | SU_FLAG_OK, &device_agent_info[0] },
	/* agentRelease.0 = INTEGER: 4 */
	{ "device.firmware", 0, 1,
		".1.3.6.1.4.1.9839.1.1.0",
		NULL, SU_FLAG_SEMI_STATIC | SU_FLAG_OK, &device_agent_info[0] },
	{ "device.type", ST_FLAG_STRING, SU_INFOSIZE, NULL, "cooling",
		SU_FLAG_STATIC | SU_FLAG_ABSENT | SU_FLAG_OK, NULL },

	/* Machine status */
	/* stato-macchina.0 = INTEGER: 1 */
	{ "device.status", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.1.0", NULL, SU_FLAG_OK, &status_info[0] },

	/* UPS collection */
	/* FIXME: Rittal
	{ "device.status", ST_FLAG_STRING, SU_INFOSIZE, ".1.3.6.1.4.1.9839.2.0.10.1.0", NULL,
		SU_FLAG_OK, &status_info[0] },
	*/

/*
1.3.6.1.4.1.9839.2.1.2.2.0|2|218	"temperatura acqua Ingresso Circuito 1" / water temperature Circuit 1 input	/ UNITS "C x10"
1.3.6.1.4.1.9839.2.1.2.3.0|2|0		"temperatura acqua Ingresso Circuito 2" / water temperature Circuit 2 input	/ UNITS "C x10"
1.3.6.1.4.1.9839.2.1.2.4.0|2|0
1.3.6.1.4.1.9839.2.1.2.5.0|2|0
1.3.6.1.4.1.9839.2.1.2.6.0|2|0
1.3.6.1.4.1.9839.2.1.2.7.0|2|0
1.3.6.1.4.1.9839.2.1.2.8.0|2|0
1.3.6.1.4.1.9839.2.1.2.9.0|2|217	R/W	"Setpoint temperatura aria mandata" / Supply air temperature setpoint	/ UNITS "C x10"
1.3.6.1.4.1.9839.2.1.2.10.0|2|0
1.3.6.1.4.1.9839.2.1.2.11.0|2|0
1.3.6.1.4.1.9839.2.1.2.12.0|2|0
1.3.6.1.4.1.9839.2.1.2.13.0|2|0
1.3.6.1.4.1.9839.2.1.2.14.0|2|0
1.3.6.1.4.1.9839.2.1.2.15.0|2|0
1.3.6.1.4.1.9839.2.1.2.16.0|2|0
1.3.6.1.4.1.9839.2.1.2.17.0|2|0
1.3.6.1.4.1.9839.2.1.2.18.0|2|0
1.3.6.1.4.1.9839.2.1.2.19.0|2|0
1.3.6.1.4.1.9839.2.1.2.20.0|2|0
1.3.6.1.4.1.9839.2.1.2.21.0|2|400		R/W	"Regolazione Motocondensante su temp. aria mandata -Cut off-"
										Condensing unit regulation on temp. supply air -Cut off
1.3.6.1.4.1.9839.2.1.2.22.0|2|220		R/W	"Differenziale termoregolazione su temp. aria mandata"
										Thermoregulation differential on temp. supply air
1.3.6.1.4.1.9839.2.1.2.23.0|2|0
1.3.6.1.4.1.9839.2.1.2.24.0|2|25		"temperatura evaporazione EVD EVO"
1.3.6.1.4.1.9839.2.1.2.25.0|2|50		"Pressione evaporazione EVD EVO"
1.3.6.1.4.1.9839.2.1.2.26.0|2|100		"Surriscaldamento Aspirazione EVD EVO"
1.3.6.1.4.1.9839.2.1.2.27.0|2|217		"Surriscaldamento Scarico EVD EVO"
1.3.6.1.4.1.9839.2.1.2.28.0|2|225		"temperatura Scarico EVD EVO" / EVD EVO Exhaust temperature
1.3.6.1.4.1.9839.2.1.2.29.0|2|249		"Pressione Condensazione EVD EVO"
1.3.6.1.4.1.9839.2.1.2.30.0|2|0
1.3.6.1.4.1.9839.2.1.2.31.0|2|227		"percentuale Apertura Valvola EVD EVO"
1.3.6.1.4.1.9839.2.1.2.32.0|2|546		"temperatura Liquido EVD EVO"
1.3.6.1.4.1.9839.2.1.2.33.0|2|24
*/
	/* Input collection */
	/* Water temperature IN */
	/* FIXME: return air temp. below should be prefered, but it's empty! */
	/* temp-acqua-in1-cb.0 = INTEGER: 218 */
	{ "input.temperature", 0, 0.1, ".1.3.6.1.4.1.9839.2.1.2.2.0", NULL, SU_FLAG_ZEROINVALID | SU_FLAG_OK, NULL },
	/* FIXME: can be indexed, with the above as .1 and the below as .2 */
	/* temp-acqua-in2-cb.0 = INTEGER: 0 */
	/* { "input.temperature", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.3.0", NULL, SU_FLAG_ZEROINVALID | SU_FLAG_OK, NULL }, */
	/* Return air temperature */
	/* temp-aria.0 = INTEGER: 0 */
	{ "input.temperature", 0, 0.1, ".1.3.6.1.4.1.9839.2.1.2.1.0", NULL, SU_FLAG_ZEROINVALID | SU_FLAG_OK, NULL },

	/* Output collection */
	/* Water temperature OUT */
	/* FIXME: supply air temp. below should be prefered, but it's empty! */
	/* temp-acqua-out-cm.0 = INTEGER: 257 */
	{ "output.temperature", 0, 0.1, ".1.3.6.1.4.1.9839.2.1.2.4.0", NULL, SU_FLAG_ZEROINVALID | SU_FLAG_OK, NULL },
	/* Return air temperature */
	/* temp-mand-cb.0 = INTEGER: 0 */
	{ "output.temperature", 0, 0.1, ".1.3.6.1.4.1.9839.2.1.2.10.0", NULL, SU_FLAG_ZEROINVALID | SU_FLAG_OK, NULL },

	/* cb-set-aria-mand.0 = INTEGER: 217 */
	/* Supply air temperature Setpoint */
	{ "output.temperature.nominal", ST_FLAG_RW, 0.1, ".1.3.6.1.4.1.9839.2.1.2.9.0", NULL, SU_FLAG_OK, NULL },

	/* Alarms count:
	 * FIXME: this should be renamed to "device.alarm.count" for genericity and agnostic processing */
/*
	{ "ups.alarms", 0, 1.0, ".1.3.6.1.4.1.9839.2.1.1.50.0", NULL, SU_FLAG_OK, NULL },
*/

	/* Commands */
	/* Supervision On/off
	/* on-off-sup.0 = INTEGER: 0 */
	{ "device.on", 0, DO_ON, ".1.3.6.1.4.1.9839.2.1.1.12.0", NULL, SU_TYPE_CMD, NULL, NULL },
	{ "device.off", 0, DO_OFF, ".1.3.6.1.4.1.9839.2.1.1.12.0", NULL, SU_TYPE_CMD, NULL, NULL },

#if 0
	/* prIndex.1 = INTEGER: 1 */
	{ "unmapped.prIndex", 0, 1, ".1.3.6.1.4.1.2021.2.1.1.1", NULL, SU_FLAG_OK, NULL },
	/* prIndex.2 = INTEGER: 2 */
	{ "unmapped.prIndex", 0, 1, ".1.3.6.1.4.1.2021.2.1.1.2", NULL, SU_FLAG_OK, NULL },
	/* prNames.1 = STRING: "pcod" */
	{ "unmapped.prNames", ST_FLAG_STRING, SU_INFOSIZE, ".1.3.6.1.4.1.2021.2.1.2.1", NULL, SU_FLAG_OK, NULL },
	/* prNames.2 = STRING: "thttpd" */
	{ "unmapped.prNames", ST_FLAG_STRING, SU_INFOSIZE, ".1.3.6.1.4.1.2021.2.1.2.2", NULL, SU_FLAG_OK, NULL },
	/* prMin.1 = INTEGER: 1 */
	{ "unmapped.prMin", 0, 1, ".1.3.6.1.4.1.2021.2.1.3.1", NULL, SU_FLAG_OK, NULL },
	/* prMin.2 = INTEGER: 1 */
	{ "unmapped.prMin", 0, 1, ".1.3.6.1.4.1.2021.2.1.3.2", NULL, SU_FLAG_OK, NULL },
	/* prMax.1 = INTEGER: 0 */
	{ "unmapped.prMax", 0, 1, ".1.3.6.1.4.1.2021.2.1.4.1", NULL, SU_FLAG_OK, NULL },
	/* prMax.2 = INTEGER: 0 */
	{ "unmapped.prMax", 0, 1, ".1.3.6.1.4.1.2021.2.1.4.2", NULL, SU_FLAG_OK, NULL },
	/* prCount.1 = INTEGER: 1 */
	{ "unmapped.prCount", 0, 1, ".1.3.6.1.4.1.2021.2.1.5.1", NULL, SU_FLAG_OK, NULL },
	/* prCount.2 = INTEGER: 1 */
	{ "unmapped.prCount", 0, 1, ".1.3.6.1.4.1.2021.2.1.5.2", NULL, SU_FLAG_OK, NULL },
	/* prErrorFlag.1 = INTEGER: 0 */
	{ "unmapped.prErrorFlag", 0, 1, ".1.3.6.1.4.1.2021.2.1.100.1", NULL, SU_FLAG_OK, NULL },
	/* prErrorFlag.2 = INTEGER: 0 */
	{ "unmapped.prErrorFlag", 0, 1, ".1.3.6.1.4.1.2021.2.1.100.2", NULL, SU_FLAG_OK, NULL },
	/* prErrMessage.1 = "" */
	{ "unmapped.prErrMessage", 0, 1, ".1.3.6.1.4.1.2021.2.1.101.1", NULL, SU_FLAG_OK, NULL },
	/* prErrMessage.2 = "" */
	{ "unmapped.prErrMessage", 0, 1, ".1.3.6.1.4.1.2021.2.1.101.2", NULL, SU_FLAG_OK, NULL },
	/* prErrFix.1 = INTEGER: 0 */
	{ "unmapped.prErrFix", 0, 1, ".1.3.6.1.4.1.2021.2.1.102.1", NULL, SU_FLAG_OK, NULL },
	/* prErrFix.2 = INTEGER: 0 */
	{ "unmapped.prErrFix", 0, 1, ".1.3.6.1.4.1.2021.2.1.102.2", NULL, SU_FLAG_OK, NULL },
	/* prErrFixCmd.1 = "" */
	{ "unmapped.prErrFixCmd", 0, 1, ".1.3.6.1.4.1.2021.2.1.103.1", NULL, SU_FLAG_OK, NULL },
	/* prErrFixCmd.2 = "" */
	{ "unmapped.prErrFixCmd", 0, 1, ".1.3.6.1.4.1.2021.2.1.103.2", NULL, SU_FLAG_OK, NULL },
	/* dlmodNextIndex.0 = INTEGER: 2 */
	{ "unmapped.dlmodNextIndex", 0, 1, ".1.3.6.1.4.1.2021.13.14.1.0", NULL, SU_FLAG_OK, NULL },
	/* dlmodName.1 = STRING: "carelPcoEth" */
	{ "unmapped.dlmodName", ST_FLAG_STRING, SU_INFOSIZE, ".1.3.6.1.4.1.2021.13.14.2.1.2.1", NULL, SU_FLAG_OK, NULL },
	/* dlmodPath.1 = STRING: "/usr/local/lib/carelPcoEth.so" */
	{ "unmapped.dlmodPath", ST_FLAG_STRING, SU_INFOSIZE, ".1.3.6.1.4.1.2021.13.14.2.1.3.1", NULL, SU_FLAG_OK, NULL },
	/* dlmodError.1 = "" */
	{ "unmapped.dlmodError", 0, 1, ".1.3.6.1.4.1.2021.13.14.2.1.4.1", NULL, SU_FLAG_OK, NULL },
	/* dlmodStatus.1 = INTEGER: 1 */
	{ "unmapped.dlmodStatus", 0, 1, ".1.3.6.1.4.1.2021.13.14.2.1.5.1", NULL, SU_FLAG_OK, NULL },

	/* systm.3.1.1.0 = STRING: "alarm fired" */
	{ "unmapped.systm", ST_FLAG_STRING, SU_INFOSIZE, ".1.3.6.1.4.1.9839.1.3.1.1.0", NULL, SU_FLAG_OK, NULL },
	/* systm.3.1.2.0 = STRING: "alarm reentered" */
	{ "unmapped.systm", ST_FLAG_STRING, SU_INFOSIZE, ".1.3.6.1.4.1.9839.1.3.1.2.0", NULL, SU_FLAG_OK, NULL },
	/* pCOId1-ErrorsNumber.0 = INTEGER: 0 */
	{ "unmapped.pCOId1-ErrorsNumber", 0, 1, ".1.3.6.1.4.1.9839.2.0.11.1.0", NULL, SU_FLAG_OK, NULL },
	/* din1.0 = INTEGER: 0 */
	{ "unmapped.din1", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.1.0", NULL, SU_FLAG_OK, NULL },
	/* din2.0 = INTEGER: 0 */
	{ "unmapped.din2", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.2.0", NULL, SU_FLAG_OK, NULL },
	/* din3.0 = INTEGER: 0 */
	{ "unmapped.din3", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.3.0", NULL, SU_FLAG_OK, NULL },
	/* din4.0 = INTEGER: 0 */
	{ "unmapped.din4", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.4.0", NULL, SU_FLAG_OK, NULL },
	/* din6.0 = INTEGER: 1 */
	{ "unmapped.din6", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.6.0", NULL, SU_FLAG_OK, NULL },
	/* dout-1.0 = INTEGER: 0 */
	{ "unmapped.dout-1", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.7.0", NULL, SU_FLAG_OK, NULL },
	/* dout-2.0 = INTEGER: 1 */
	{ "unmapped.dout-2", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.8.0", NULL, SU_FLAG_OK, NULL },
	/* dout-3.0 = INTEGER: 1 */
	{ "unmapped.dout-3", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.9.0", NULL, SU_FLAG_OK, NULL },
	/* dout-4.0 = INTEGER: 1 */
	{ "unmapped.dout-4", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.10.0", NULL, SU_FLAG_OK, NULL },
	/* dout-5.0 = INTEGER: 0 */
	{ "unmapped.dout-5", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.11.0", NULL, SU_FLAG_OK, NULL },

	/* qal-flux-acq-util.0 = INTEGER: 0 */
	{ "unmapped.qal-flux-acq-util", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.13.0", NULL, SU_FLAG_OK, NULL },
	/* qal-filtro-aria-cb.0 = INTEGER: 0 */
	{ "unmapped.qal-filtro-aria-cb", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.16.0", NULL, SU_FLAG_OK, NULL },
	/* qal-term-vent-cb.0 = INTEGER: 0 */
	{ "unmapped.qal-term-vent-cb", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.17.0", NULL, SU_FLAG_OK, NULL },
	/* qal-term-pompa2-cm.0 = INTEGER: 1 */
	{ "unmapped.qal-term-pompa2-cm", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.20.0", NULL, SU_FLAG_OK, NULL },
	/* qal-lim-max-in-acq.0 = INTEGER: 1 */
	{ "unmapped.qal-lim-max-in-acq", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.21.0", NULL, SU_FLAG_OK, NULL },
	/* qal-s-umid-aria-cm.0 = INTEGER: 0 */
	{ "unmapped.qal-s-umid-aria-cm", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.22.0", NULL, SU_FLAG_OK, NULL },
	/* qal-s-temp-aria.0 = INTEGER: 0 */
	{ "unmapped.qal-s-temp-aria", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.23.0", NULL, SU_FLAG_OK, NULL },
	/* qal-s-temp-out-cm.0 = INTEGER: 0 */
	{ "unmapped.qal-s-temp-out-cm", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.24.0", NULL, SU_FLAG_OK, NULL },
	/* qal-s-temp-in-cm.0 = INTEGER: 0 */
	{ "unmapped.qal-s-temp-in-cm", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.25.0", NULL, SU_FLAG_OK, NULL },
	/* qal-s-temp-in2-cb.0 = INTEGER: 0 */
	{ "unmapped.qal-s-temp-in2-cb", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.27.0", NULL, SU_FLAG_OK, NULL },
	/* qal-ore-unita-cb.0 = INTEGER: 1 */
	{ "unmapped.qal-ore-unita-cb", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.28.0", NULL, SU_FLAG_OK, NULL },
	/* qal-s-temp-aria-mand.0 = INTEGER: 0 */
	{ "unmapped.qal-s-temp-aria-mand", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.35.0", NULL, SU_FLAG_OK, NULL },
	/* qal-forz-off-valv1.0 = INTEGER: 0 */
	{ "unmapped.qal-forz-off-valv1", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.36.0", NULL, SU_FLAG_OK, NULL },
	/* qal-forz-off-valv2.0 = INTEGER: 1 */
	{ "unmapped.qal-forz-off-valv2", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.37.0", NULL, SU_FLAG_OK, NULL },
	/* qal-offline-plan.0 = INTEGER: 0 */
	{ "unmapped.qal-offline-plan", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.38.0", NULL, SU_FLAG_OK, NULL },
	/* cb-en-2sonde-acq.0 = INTEGER: 0 */
	{ "unmapped.cb-en-2sonde-acq", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.39.0", NULL, SU_FLAG_OK, NULL },
	/* cb-abil-mandata.0 = INTEGER: 0 */
	{ "unmapped.cb-abil-mandata", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.40.0", NULL, SU_FLAG_OK, NULL },
	/* qal-motocond-cbx.0 = INTEGER: 0 */
	{ "unmapped.qal-motocond-cbx", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.41.0", NULL, SU_FLAG_OK, NULL },
	/* cbx-en-reg-ripr.0 = INTEGER: 0 */
	{ "unmapped.cbx-en-reg-ripr", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.42.0", NULL, SU_FLAG_OK, NULL },
	/* en-evd-1.0 = INTEGER: 0 */
	{ "unmapped.en-evd-1", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.43.0", NULL, SU_FLAG_OK, NULL },
	/* al-offline-evd-1.0 = INTEGER: 0 */
	{ "unmapped.al-offline-evd-1", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.44.0", NULL, SU_FLAG_OK, NULL },
	/* al-s1-evd-1.0 = INTEGER: 0 */
	{ "unmapped.al-s1-evd-1", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.45.0", NULL, SU_FLAG_OK, NULL },
	/* al-s2-evd-1.0 = INTEGER: 0 */
	{ "unmapped.al-s2-evd-1", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.46.0", NULL, SU_FLAG_OK, NULL },
	/* al-s3-evd-1.0 = INTEGER: 0 */
	{ "unmapped.al-s3-evd-1", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.47.0", NULL, SU_FLAG_OK, NULL },
	/* al-s4-evd-1.0 = INTEGER: 0 */
	{ "unmapped.al-s4-evd-1", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.48.0", NULL, SU_FLAG_OK, NULL },
	/* al-low-sh-a-evd-1.0 = INTEGER: 0 */
	{ "unmapped.al-low-sh-a-evd-1", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.49.0", NULL, SU_FLAG_OK, NULL },
	/* al-mop-a-evd-1.0 = INTEGER: 0 */
	{ "unmapped.al-mop-a-evd-1", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.51.0", NULL, SU_FLAG_OK, NULL },
	/* al-eev-a-evd-1.0 = INTEGER: 0 */
	{ "unmapped.al-eev-a-evd-1", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.52.0", NULL, SU_FLAG_OK, NULL },
	/* al-lowsuct-a-evd-1.0 = INTEGER: 0 */
	{ "unmapped.al-lowsuct-a-evd-1", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.53.0", NULL, SU_FLAG_OK, NULL },
	/* al-hit-cond-evd-1.0 = INTEGER: 0 */
	{ "unmapped.al-hit-cond-evd-1", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.54.0", NULL, SU_FLAG_OK, NULL },
	/* al-eeprom-evd-1.0 = INTEGER: 0 */
	{ "unmapped.al-eeprom-evd-1", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.55.0", NULL, SU_FLAG_OK, NULL },
	/* al-batt-evd-1.0 = INTEGER: 0 */
	{ "unmapped.al-batt-evd-1", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.56.0", NULL, SU_FLAG_OK, NULL },
	/* al-fw-compatiberr-evd-1.0 = INTEGER: 0 */
	{ "unmapped.al-fw-compatiberr-evd-1", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.57.0", NULL, SU_FLAG_OK, NULL },
	/* al-configerr-evd-1.0 = INTEGER: 0 */
	{ "unmapped.al-configerr-evd-1", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.58.0", NULL, SU_FLAG_OK, NULL },
	/* din-1-evd-1.0 = INTEGER: 0 */
	{ "unmapped.din-1-evd-1", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.59.0", NULL, SU_FLAG_OK, NULL },
	/* din-2-evd-1.0 = INTEGER: 0 */
	{ "unmapped.din-2-evd-1", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.60.0", NULL, SU_FLAG_OK, NULL },
	/* cb-en-distribuito.0 = INTEGER: 0 */
	{ "unmapped.cb-en-distribuito", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.61.0", NULL, SU_FLAG_OK, NULL },
	/* cb-en-valvola.0 = INTEGER: 0 */
	{ "unmapped.cb-en-valvola", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.62.0", NULL, SU_FLAG_OK, NULL },
	/* cb-abil-valv2.0 = INTEGER: 0 */
	{ "unmapped.cb-abil-valv2", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.63.0", NULL, SU_FLAG_OK, NULL },
	/* res-allarmi-sup.0 = INTEGER: 0 */
	{ "unmapped.res-allarmi-sup", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.64.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.65.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.65.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.66.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.66.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.67.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.67.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.68.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.68.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.69.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.69.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.70.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.70.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.71.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.71.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.72.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.72.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.73.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.73.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.74.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.74.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.75.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.75.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.76.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.76.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.77.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.77.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.78.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.78.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.79.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.79.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.80.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.80.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.81.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.81.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.82.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.82.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.83.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.83.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.84.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.84.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.85.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.85.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.86.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.86.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.87.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.87.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.88.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.88.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.89.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.89.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.90.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.90.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.91.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.91.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.92.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.92.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.93.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.93.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.94.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.94.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.95.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.95.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.96.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.96.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.97.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.97.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.98.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.98.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.99.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.99.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.100.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.100.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.101.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.101.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.102.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.102.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.103.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.103.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.104.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.104.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.105.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.105.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.106.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.106.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.107.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.107.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.108.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.108.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.109.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.109.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.110.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.110.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.111.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.111.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.112.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.112.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.113.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.113.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.114.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.114.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.115.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.115.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.116.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.116.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.117.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.117.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.118.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.118.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.119.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.119.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.120.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.120.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.121.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.121.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.122.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.122.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.123.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.123.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.124.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.124.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.125.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.125.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.126.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.126.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.127.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.127.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.128.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.128.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.129.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.129.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.130.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.130.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.131.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.131.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.132.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.132.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.133.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.133.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.134.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.134.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.135.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.135.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.136.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.136.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.137.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.137.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.138.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.138.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.139.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.139.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.140.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.140.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.141.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.141.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.142.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.142.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.143.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.143.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.144.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.144.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.145.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.145.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.146.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.146.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.147.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.147.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.148.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.148.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.149.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.149.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.150.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.150.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.151.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.151.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.152.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.152.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.153.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.153.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.154.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.154.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.155.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.155.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.156.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.156.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.157.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.157.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.158.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.158.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.159.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.159.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.160.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.160.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.161.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.161.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.162.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.162.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.163.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.163.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.164.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.164.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.165.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.165.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.166.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.166.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.167.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.167.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.168.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.168.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.169.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.169.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.170.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.170.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.171.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.171.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.172.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.172.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.173.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.173.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.174.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.174.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.175.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.175.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.176.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.176.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.177.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.177.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.178.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.178.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.179.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.179.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.180.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.180.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.181.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.181.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.182.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.182.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.183.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.183.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.184.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.184.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.185.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.185.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.186.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.186.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.187.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.187.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.188.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.188.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.189.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.189.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.190.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.190.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.191.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.191.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.192.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.192.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.193.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.193.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.194.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.194.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.195.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.195.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.196.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.196.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.197.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.197.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.198.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.198.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.199.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.199.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.200.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.200.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.201.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.201.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.202.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.202.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.203.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.203.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.204.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.204.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.205.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.205.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.206.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.206.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.207.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.207.0", NULL, SU_FLAG_OK, NULL },

	/* temp-acqua-in1-cb.0 = INTEGER: 218 */
	{ "unmapped.temp-acqua-in1-cb", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.2.0", NULL, SU_FLAG_OK, NULL },
	/* temp-acqua-in2-cb.0 = INTEGER: 0 */
	{ "unmapped.temp-acqua-in2-cb", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.3.0", NULL, SU_FLAG_OK, NULL },
	/* temp-acqua-out-cm.0 = INTEGER: 0 */
	{ "unmapped.temp-acqua-out-cm", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.4.0", NULL, SU_FLAG_OK, NULL },
	/* temp-acqua-in-cm.0 = INTEGER: 0 */
	{ "unmapped.temp-acqua-in-cm", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.5.0", NULL, SU_FLAG_OK, NULL },
	/* vis-set-calc.0 = INTEGER: 0 */
	{ "unmapped.vis-set-calc", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.6.0", NULL, SU_FLAG_OK, NULL },
	/* cb-set-aria.0 = INTEGER: 0 */
	{ "unmapped.cb-set-aria", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.7.0", NULL, SU_FLAG_OK, NULL },
	/* cm-offset.0 = INTEGER: 0 */
	{ "unmapped.cm-offset", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.8.0", NULL, SU_FLAG_OK, NULL },
	/* cb-set-aria-mand.0 = INTEGER: 217 */
	{ "unmapped.cb-set-aria-mand", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.9.0", NULL, SU_FLAG_OK, NULL },

	/* temp-aria-calc.0 = INTEGER: 0 */
	{ "unmapped.temp-aria-calc", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.11.0", NULL, SU_FLAG_OK, NULL },
	/* temp-mand-cb-calc.0 = INTEGER: 0 */
	{ "unmapped.temp-mand-cb-calc", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.12.0", NULL, SU_FLAG_OK, NULL },
	/* media-temp-aria.0 = INTEGER: 0 */
	{ "unmapped.media-temp-aria", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.13.0", NULL, SU_FLAG_OK, NULL },
	/* media-temp-aria-mand.0 = INTEGER: 0 */
	{ "unmapped.media-temp-aria-mand", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.14.0", NULL, SU_FLAG_OK, NULL },
	/* cbx-lim-min-set-aria.0 = INTEGER: 0 */
	{ "unmapped.cbx-lim-min-set-aria", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.15.0", NULL, SU_FLAG_OK, NULL },
	/* cbx-lim-max-set-aria.0 = INTEGER: 0 */
	{ "unmapped.cbx-lim-max-set-aria", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.16.0", NULL, SU_FLAG_OK, NULL },
	/* cbx-cutoff-aria.0 = INTEGER: 0 */
	{ "unmapped.cbx-cutoff-aria", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.17.0", NULL, SU_FLAG_OK, NULL },
	/* cbx-diff-aria.0 = INTEGER: 0 */
	{ "unmapped.cbx-diff-aria", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.18.0", NULL, SU_FLAG_OK, NULL },
	/* cbx-lim-min-set-aria-mand.0 = INTEGER: 0 */
	{ "unmapped.cbx-lim-min-set-aria-mand", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.19.0", NULL, SU_FLAG_OK, NULL },
	/* cbx-lim-max-set-aria-mand.0 = INTEGER: 0 */
	{ "unmapped.cbx-lim-max-set-aria-mand", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.20.0", NULL, SU_FLAG_OK, NULL },
	/* cbx-cutoff-aria-mand.0 = INTEGER: 400 */
	{ "unmapped.cbx-cutoff-aria-mand", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.21.0", NULL, SU_FLAG_OK, NULL },
	/* cbx-diff-aria-mand.0 = INTEGER: 220 */
	{ "unmapped.cbx-diff-aria-mand", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.22.0", NULL, SU_FLAG_OK, NULL },
	/* sucttemp-a-evd-1.0 = INTEGER: 0 */
	{ "unmapped.sucttemp-a-evd-1", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.23.0", NULL, SU_FLAG_OK, NULL },
	/* evaptemp-a-evd-1.0 = INTEGER: 25 */
	{ "unmapped.evaptemp-a-evd-1", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.24.0", NULL, SU_FLAG_OK, NULL },
	/* evapP-a-evd-1.0 = INTEGER: 50 */
	{ "unmapped.evapP-a-evd-1", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.25.0", NULL, SU_FLAG_OK, NULL },
	/* sh-a-evd-1.0 = INTEGER: 100 */
	{ "unmapped.sh-a-evd-1", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.26.0", NULL, SU_FLAG_OK, NULL },
	/* dscgSH-evd-1.0 = INTEGER: 217 */
	{ "unmapped.dscgSH-evd-1", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.27.0", NULL, SU_FLAG_OK, NULL },
	/* dscgtemp-evd-1.0 = INTEGER: 225 */
	{ "unmapped.dscgtemp-evd-1", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.28.0", NULL, SU_FLAG_OK, NULL },
	/* condp-evd-1.0 = INTEGER: 249 */
	{ "unmapped.condp-evd-1", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.29.0", NULL, SU_FLAG_OK, NULL },
	/* condtemp-evd-1.0 = INTEGER: 0 */
	{ "unmapped.condtemp-evd-1", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.30.0", NULL, SU_FLAG_OK, NULL },
	/* evd-1-pisition-percent.0 = INTEGER: 227 */
	{ "unmapped.evd-1-pisition-percent", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.31.0", NULL, SU_FLAG_OK, NULL },
	/* s4-prbval-evd-1.0 = INTEGER: 546 */
	{ "unmapped.s4-prbval-evd-1", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.32.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.33.0 = INTEGER: 24 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.33.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.34.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.34.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.35.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.35.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.36.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.36.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.37.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.37.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.38.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.38.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.39.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.39.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.40.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.40.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.41.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.41.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.42.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.42.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.43.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.43.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.44.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.44.0", NULL, SU_FLAG_OK, NULL },
	/* rotor-speed-rps.0 = INTEGER: 0 */
	{ "unmapped.rotor-speed-rps", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.45.0", NULL, SU_FLAG_OK, NULL },
	/* motor-current.0 = INTEGER: 0 */
	{ "unmapped.motor-current", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.46.0", NULL, SU_FLAG_OK, NULL },
	/* aobj47.0 = INTEGER: 10 */
	{ "unmapped.aobj47", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.47.0", NULL, SU_FLAG_OK, NULL },
	/* setpoint-lcp.0 = INTEGER: 10 */
	{ "unmapped.setpoint-lcp", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.48.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.49.0 = INTEGER: 20 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.49.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.50.0 = INTEGER: 2 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.50.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.51.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.51.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.52.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.52.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.53.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.53.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.54.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.54.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.55.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.55.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.56.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.56.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.57.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.57.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.58.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.58.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.59.0 = INTEGER: 49 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.59.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.60.0 = INTEGER: 116 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.60.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.61.0 = INTEGER: 70 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.61.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.62.0 = INTEGER: 5 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.62.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.63.0 = INTEGER: 140 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.63.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.64.0 = INTEGER: 20 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.64.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.65.0 = INTEGER: 20 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.65.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.66.0 = INTEGER: 30 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.66.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.67.0 = INTEGER: 15 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.67.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.68.0 = INTEGER: 180 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.68.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.69.0 = INTEGER: 400 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.69.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.70.0 = INTEGER: 20 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.70.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.71.0 = INTEGER: 100 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.71.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.72.0 = INTEGER: 20 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.72.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.73.0 = INTEGER: 10 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.73.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.74.0 = INTEGER: 20 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.74.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.75.0 = INTEGER: 30 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.75.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.76.0 = INTEGER: 30 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.76.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.77.0 = INTEGER: 20 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.77.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.78.0 = INTEGER: 60 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.78.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.79.0 = INTEGER: 400 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.79.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.80.0 = INTEGER: 450 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.80.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.81.0 = INTEGER: 450 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.81.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.82.0 = INTEGER: 50 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.82.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.83.0 = INTEGER: 220 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.83.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.84.0 = INTEGER: 185 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.84.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.85.0 = INTEGER: 210 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.85.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.86.0 = INTEGER: 250 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.86.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.87.0 = INTEGER: 190 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.87.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.88.0 = INTEGER: 270 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.88.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.89.0 = INTEGER: 320 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.89.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.90.0 = INTEGER: 40 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.90.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.91.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.91.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.92.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.92.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.93.0 = INTEGER: 20 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.93.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.94.0 = INTEGER: -20 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.94.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.95.0 = INTEGER: 280 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.95.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.96.0 = INTEGER: 140 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.96.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.97.0 = INTEGER: 180 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.97.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.98.0 = INTEGER: 10 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.98.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.99.0 = INTEGER: 20 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.99.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.100.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.100.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.101.0 = INTEGER: 20 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.101.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.102.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.102.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.103.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.103.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.104.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.104.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.105.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.105.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.106.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.106.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.107.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.107.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.108.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.108.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.109.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.109.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.110.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.110.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.111.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.111.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.112.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.112.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.113.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.113.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.114.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.114.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.115.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.115.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.116.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.116.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.117.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.117.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.118.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.118.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.119.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.119.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.120.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.120.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.121.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.121.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.122.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.122.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.123.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.123.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.124.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.124.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.125.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.125.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.126.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.126.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.127.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.127.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.128.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.128.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.129.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.129.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.130.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.130.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.131.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.131.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.132.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.132.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.133.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.133.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.134.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.134.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.135.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.135.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.136.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.136.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.137.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.137.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.138.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.138.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.139.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.139.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.140.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.140.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.141.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.141.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.142.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.142.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.143.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.143.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.144.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.144.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.145.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.145.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.146.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.146.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.147.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.147.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.148.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.148.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.149.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.149.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.150.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.150.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.151.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.151.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.152.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.152.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.153.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.153.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.154.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.154.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.155.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.155.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.156.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.156.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.157.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.157.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.158.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.158.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.159.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.159.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.160.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.160.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.161.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.161.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.162.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.162.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.163.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.163.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.164.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.164.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.165.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.165.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.166.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.166.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.167.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.167.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.168.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.168.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.169.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.169.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.170.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.170.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.171.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.171.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.172.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.172.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.173.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.173.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.174.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.174.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.175.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.175.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.176.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.176.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.177.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.177.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.178.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.178.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.179.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.179.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.180.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.180.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.181.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.181.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.182.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.182.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.183.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.183.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.184.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.184.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.185.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.185.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.186.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.186.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.187.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.187.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.188.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.188.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.189.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.189.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.190.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.190.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.191.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.191.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.192.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.192.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.193.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.193.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.194.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.194.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.195.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.195.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.196.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.196.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.197.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.197.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.198.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.198.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.199.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.199.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.200.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.200.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.201.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.201.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.202.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.202.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.203.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.203.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.204.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.204.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.205.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.205.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.206.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.206.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.207.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.207.0", NULL, SU_FLAG_OK, NULL },

	/* cb-vis-ext-signal.0 = INTEGER: 0 */
	{ "unmapped.cb-vis-ext-signal", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.2.0", NULL, SU_FLAG_OK, NULL },
	/* cm-vis-umid-aria.0 = INTEGER: 0 */
	{ "unmapped.cm-vis-umid-aria", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.3.0", NULL, SU_FLAG_OK, NULL },
	/* cb-vis-vent-mod.0 = INTEGER: 0 */
	{ "unmapped.cb-vis-vent-mod", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.4.0", NULL, SU_FLAG_OK, NULL },
	/* cm-vis-valv.0 = INTEGER: 0 */
	{ "unmapped.cm-vis-valv", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.5.0", NULL, SU_FLAG_OK, NULL },
	/* cm-vis-out-set-ch.0 = INTEGER: 1450 */
	{ "unmapped.cm-vis-out-set-ch", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.6.0", NULL, SU_FLAG_OK, NULL },
	/* cb-avv-tot-unita-h.0 = INTEGER: 0 */
	{ "unmapped.cb-avv-tot-unita-h", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.7.0", NULL, SU_FLAG_OK, NULL },
	/* cb-avv-tot-unita-l.0 = INTEGER: 1444 */
	{ "unmapped.cb-avv-tot-unita-l", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.8.0", NULL, SU_FLAG_OK, NULL },
	/* cb-avv-tot-vent-h.0 = INTEGER: 0 */
	{ "unmapped.cb-avv-tot-vent-h", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.9.0", NULL, SU_FLAG_OK, NULL },
	/* cb-avv-tot-vent-l.0 = INTEGER: 0 */
	{ "unmapped.cb-avv-tot-vent-l", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.10.0", NULL, SU_FLAG_OK, NULL },
	/* cm-avv-tot-pompa1-h.0 = INTEGER: 0 */
	{ "unmapped.cm-avv-tot-pompa1-h", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.11.0", NULL, SU_FLAG_OK, NULL },
	/* cm-avv-tot-pompa1-l.0 = INTEGER: 0 */
	{ "unmapped.cm-avv-tot-pompa1-l", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.12.0", NULL, SU_FLAG_OK, NULL },
	/* cm-avv-tot-pompa2-h.0 = INTEGER: 18 */
	{ "unmapped.cm-avv-tot-pompa2-h", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.13.0", NULL, SU_FLAG_OK, NULL },
	/* cm-avv-tot-pompa2-l.0 = INTEGER: 29267 */
	{ "unmapped.cm-avv-tot-pompa2-l", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.14.0", NULL, SU_FLAG_OK, NULL },
	/* cb-ore-tot-unita-h.0 = INTEGER: 17 */
	{ "unmapped.cb-ore-tot-unita-h", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.15.0", NULL, SU_FLAG_OK, NULL },
	/* cb-ore-tot-unita-l.0 = INTEGER: 4 */
	{ "unmapped.cb-ore-tot-unita-l", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.16.0", NULL, SU_FLAG_OK, NULL },
	/* cb-ore-tot-vent-h.0 = INTEGER: 17 */
	{ "unmapped.cb-ore-tot-vent-h", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.17.0", NULL, SU_FLAG_OK, NULL },
	/* cb-ore-tot-vent-l.0 = INTEGER: 4 */
	{ "unmapped.cb-ore-tot-vent-l", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.18.0", NULL, SU_FLAG_OK, NULL },
	/* cm-ore-tot-pompa1-h.0 = INTEGER: 19 */
	{ "unmapped.cm-ore-tot-pompa1-h", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.19.0", NULL, SU_FLAG_OK, NULL },
	/* cm-ore-tot-pompa1-l.0 = INTEGER: 0 */
	{ "unmapped.cm-ore-tot-pompa1-l", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.20.0", NULL, SU_FLAG_OK, NULL },
	/* cm-ore-tot-pompa2-h.0 = INTEGER: 0 */
	{ "unmapped.cm-ore-tot-pompa2-h", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.21.0", NULL, SU_FLAG_OK, NULL },
	/* cm-ore-tot-pompa2-l.0 = INTEGER: 0 */
	{ "unmapped.cm-ore-tot-pompa2-l", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.22.0", NULL, SU_FLAG_OK, NULL },
	/* cb-vis-valv.0 = INTEGER: 0 */
	{ "unmapped.cb-vis-valv", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.23.0", NULL, SU_FLAG_OK, NULL },
	/* cb-vis-valv2.0 = INTEGER: 0 */
	{ "unmapped.cb-vis-valv2", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.24.0", NULL, SU_FLAG_OK, NULL },
	/* cb-funz-valvole.0 = INTEGER: 0 */
	{ "unmapped.cb-funz-valvole", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.25.0", NULL, SU_FLAG_OK, NULL },
	/* cbx-vis-motocond-mod.0 = INTEGER: 0 */
	{ "unmapped.cbx-vis-motocond-mod", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.26.0", NULL, SU_FLAG_OK, NULL },
	/* cbx-pwr-min-aria.0 = INTEGER: 0 */
	{ "unmapped.cbx-pwr-min-aria", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.27.0", NULL, SU_FLAG_OK, NULL },
	/* cbx-pwr-max-aria.0 = INTEGER: 0 */
	{ "unmapped.cbx-pwr-max-aria", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.28.0", NULL, SU_FLAG_OK, NULL },
	/* cbx-pwr-min-aria-mand.0 = INTEGER: 0 */
	{ "unmapped.cbx-pwr-min-aria-mand", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.29.0", NULL, SU_FLAG_OK, NULL },
	/* cbx-pwr-max-aria-mand.0 = INTEGER: 0 */
	{ "unmapped.cbx-pwr-max-aria-mand", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.30.0", NULL, SU_FLAG_OK, NULL },
	/* tipo-unita.0 = INTEGER: 0 */
	{ "unmapped.tipo-unita", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.31.0", NULL, SU_FLAG_OK, NULL },
	/* evd-1-pisition-steps.0 = INTEGER: 0 */
	{ "unmapped.evd-1-pisition-steps", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.32.0", NULL, SU_FLAG_OK, NULL },
	/* evd-1-reg-status.0 = INTEGER: 0 */
	{ "unmapped.evd-1-reg-status", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.33.0", NULL, SU_FLAG_OK, NULL },
	/* cb-diff-vent.0 = INTEGER: 0 */
	{ "unmapped.cb-diff-vent", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.34.0", NULL, SU_FLAG_OK, NULL },
	/* cb-lim-max-in-acq.0 = INTEGER: 524 */
	{ "unmapped.cb-lim-max-in-acq", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.35.0", NULL, SU_FLAG_OK, NULL },
	/* cm-rit-lim-max-t.0 = INTEGER: 0 */
	{ "unmapped.cm-rit-lim-max-t", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.36.0", NULL, SU_FLAG_OK, NULL },
	/* cb-sg-max-valvola-1.0 = INTEGER: 0 */
	{ "unmapped.cb-sg-max-valvola-1", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.37.0", NULL, SU_FLAG_OK, NULL },
	/* cb-sg-max-valvola-2.0 = INTEGER: 0 */
	{ "unmapped.cb-sg-max-valvola-2", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.38.0", NULL, SU_FLAG_OK, NULL },
	/* cb-vis-vent-mod2.0 = INTEGER: 100 */
	{ "unmapped.cb-vis-vent-mod2", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.39.0", NULL, SU_FLAG_OK, NULL },
	/* cbx-vis-motocond-mod2.0 = INTEGER: 0 */
	{ "unmapped.cbx-vis-motocond-mod2", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.40.0", NULL, SU_FLAG_OK, NULL },
	/* cb-tipo-valvola2.0 = INTEGER: 0 */
	{ "unmapped.cb-tipo-valvola2", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.41.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.42.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.42.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.43.0 = INTEGER: 524 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.43.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.44.0 = INTEGER: 120 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.44.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.45.0 = INTEGER: 15 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.45.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.46.0 = INTEGER: 120 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.46.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.47.0 = INTEGER: 180 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.47.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.48.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.48.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.49.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.49.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.50.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.50.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.51.0 = INTEGER: 40 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.51.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.52.0 = INTEGER: 100 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.52.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.53.0 = INTEGER: 50 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.53.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.54.0 = INTEGER: 240 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.54.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.55.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.55.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.56.0 = INTEGER: 120 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.56.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.57.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.57.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.58.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.58.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.59.0 = INTEGER: 240 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.59.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.60.0 = INTEGER: 1 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.60.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.61.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.61.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.62.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.62.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.63.0 = INTEGER: 30 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.63.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.64.0 = INTEGER: 60 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.64.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.65.0 = INTEGER: 20 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.65.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.66.0 = INTEGER: 2 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.66.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.67.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.67.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.68.0 = INTEGER: 120 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.68.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.69.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.69.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.70.0 = INTEGER: 50 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.70.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.71.0 = INTEGER: 120 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.71.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.72.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.72.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.73.0 = INTEGER: 2000 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.73.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.74.0 = INTEGER: 800 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.74.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.75.0 = INTEGER: 2000 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.75.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.76.0 = INTEGER: 800 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.76.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.77.0 = INTEGER: 30 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.77.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.78.0 = INTEGER: 70 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.78.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.79.0 = INTEGER: 50 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.79.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.80.0 = INTEGER: 90 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.80.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.81.0 = INTEGER: 10 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.81.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.82.0 = INTEGER: 90 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.82.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.83.0 = INTEGER: 120 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.83.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.84.0 = INTEGER: 3800 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.84.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.85.0 = INTEGER: 40 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.85.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.86.0 = INTEGER: 600 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.86.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.87.0 = INTEGER: 50 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.87.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.88.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.88.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.89.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.89.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.90.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.90.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.91.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.91.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.92.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.92.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.93.0 = INTEGER: 7 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.93.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.94.0 = INTEGER: 539 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.94.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.95.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.95.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.96.0 = INTEGER: 25 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.96.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.97.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.97.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.98.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.98.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.99.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.99.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.100.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.100.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.101.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.101.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.102.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.102.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.103.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.103.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.104.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.104.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.105.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.105.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.106.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.106.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.107.0 = INTEGER: 6 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.107.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.108.0 = INTEGER: 246 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.108.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.109.0 = INTEGER: 4 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.109.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.110.0 = INTEGER: 613 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.110.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.111.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.111.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.112.0 = INTEGER: 654 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.112.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.113.0 = INTEGER: 15 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.113.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.114.0 = INTEGER: 119 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.114.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.115.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.115.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.116.0 = INTEGER: 922 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.116.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.117.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.117.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.118.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.118.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.119.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.119.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.120.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.120.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.121.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.121.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.122.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.122.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.123.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.123.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.124.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.124.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.125.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.125.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.126.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.126.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.127.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.127.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.128.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.128.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.129.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.129.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.130.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.130.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.131.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.131.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.132.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.132.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.133.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.133.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.134.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.134.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.135.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.135.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.136.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.136.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.137.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.137.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.138.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.138.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.139.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.139.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.140.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.140.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.141.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.141.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.142.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.142.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.143.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.143.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.144.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.144.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.145.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.145.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.146.0 = INTEGER: 100 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.146.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.147.0 = INTEGER: 120 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.147.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.148.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.148.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.149.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.149.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.150.0 = INTEGER: 15 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.150.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.151.0 = INTEGER: 37 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.151.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.152.0 = INTEGER: 37 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.152.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.153.0 = INTEGER: 37 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.153.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.154.0 = INTEGER: 37 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.154.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.155.0 = INTEGER: 37 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.155.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.156.0 = INTEGER: 37 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.156.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.157.0 = INTEGER: 37 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.157.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.158.0 = INTEGER: 37 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.158.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.159.0 = INTEGER: 37 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.159.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.160.0 = INTEGER: 201 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.160.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.161.0 = INTEGER: 113 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.161.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.162.0 = INTEGER: 78 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.162.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.163.0 = INTEGER: 61 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.163.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.164.0 = INTEGER: 37 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.164.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.165.0 = INTEGER: 37 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.165.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.166.0 = INTEGER: 201 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.166.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.167.0 = INTEGER: 113 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.167.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.168.0 = INTEGER: 76 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.168.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.169.0 = INTEGER: 201 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.169.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.170.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.170.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.171.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.171.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.172.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.172.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.173.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.173.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.174.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.174.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.175.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.175.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.176.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.176.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.177.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.177.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.178.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.178.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.179.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.179.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.180.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.180.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.181.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.181.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.182.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.182.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.183.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.183.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.184.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.184.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.185.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.185.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.186.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.186.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.187.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.187.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.188.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.188.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.189.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.189.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.190.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.190.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.191.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.191.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.192.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.192.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.193.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.193.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.194.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.194.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.195.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.195.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.196.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.196.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.197.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.197.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.198.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.198.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.199.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.199.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.200.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.200.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.201.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.201.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.202.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.202.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.203.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.203.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.204.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.204.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.205.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.205.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.206.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.206.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.207.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.207.0", NULL, SU_FLAG_OK, NULL },
#endif
	/* end of structure. */
	{ NULL, 0, 0, NULL, NULL, 0, NULL }
};

/* FIXME: this may not be a 0/1 - no alarm/alarm, as in standard MIBs, but a value mapping
 * 'UNKNOWN'  => '-1'
 * 'OK'       => '0'
 * 'WARNING'  => '1,		# warning might not ever happen..?
 * 'CRITICAL' => '2'
 *
 * Ref: https://github.com/fenrus/nagioschecks_carel/blob/master/check_carel_alarm.pl
 * FIXME: seems not applicable to Carel *Bluebox*
 */
static alarms_info_t carel_bluebox_cooling_alarms[] = {
/*
	14 => 'Air flow switch',
	15 => 'Emergency chiller',
	18 => 'Maintenance alarm',
	19 => 'Phase-sequency-alarm',
	26 => 'Prealarm high temp ambient air',
	29 => 'High pressure from pressure switch',
	30 => 'Low pressure from pressure switch',
	31 => 'Resistor overheating',
	32 => 'Air filter',
	33 => 'High temp ambient air',
	34 => 'Low temp ambient air',
*/
	/* din5.0 = INTEGER: 1 */
	{ ".1.3.6.1.4.1.9839.2.1.1.5.0", "TEST", "Testalarm" },
	/* qal-flux-aria-cb.0 = INTEGER: 0 */
	{ ".1.3.6.1.4.1.9839.2.1.1.14.0", "", "Testalarm" },
	/* qal-flux-acq-aux-cm.0 = INTEGER: 0 */
	{ ".1.3.6.1.4.1.9839.2.1.1.15.0", NULL, NULL },
	/* qal-allagamento-cb.0 = INTEGER: 1 */
	{ ".1.3.6.1.4.1.9839.2.1.1.18.0", NULL, NULL },
	/* qal-term-pompa1-cm.0 = INTEGER: 0 */
	{ ".1.3.6.1.4.1.9839.2.1.1.19.0", NULL, NULL },
	/* qal-s-temp-in1-cb.0 = INTEGER: 0 */
	{ ".1.3.6.1.4.1.9839.2.1.1.26.0", NULL, NULL },
	/* qal-ore-vent-cb.0 = INTEGER: 0 */
	{ ".1.3.6.1.4.1.9839.2.1.1.29.0", NULL, NULL },
	/* qal-ore-pompa1-cm.0 = INTEGER: 0 */
	{ ".1.3.6.1.4.1.9839.2.1.1.30.0", NULL, NULL },
	/* qal-ore-pompa2-cm.0 = INTEGER: 0 */
	{ ".1.3.6.1.4.1.9839.2.1.1.31.0", NULL, NULL },
	/* qal-clock.0 = INTEGER: 0 */
	{ ".1.3.6.1.4.1.9839.2.1.1.32.0", NULL, NULL },
	/* qal-perm-mem.0 = INTEGER: 1 */
	{ ".1.3.6.1.4.1.9839.2.1.1.33.0", NULL, NULL },
	/* qal-offline-bms.0 = INTEGER: 1 */
	{ ".1.3.6.1.4.1.9839.2.1.1.34.0", NULL, NULL },


	/* end of structure. */
	{ NULL, NULL, NULL }
} ;

mib2nut_info_t	carel_bluebox_cooling = { "carel_bluebox_cooling", CAREL_BLUEBOX_COOLING_MIB_VERSION, NULL, CAREL_BLUEBOX_COOLING_OID_MODEL_NAME, carel_bluebox_cooling_mib, CAREL_BLUEBOX_COOLING_DEVICE_SYSOID, carel_bluebox_cooling_alarms };
