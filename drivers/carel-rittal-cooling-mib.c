/* carel-rittal-cooling-mib.c - subdriver to monitor carel-rittal-cooling SNMP devices with NUT
 *
 *  Copyright (C)
 *  2011 - 2016	Arnaud Quette <arnaud.quette@free.fr>
 *  2020    	Eaton (Arnaud Quette <ArnaudQuette@Eaton.com>)
 *
 *  Note: this subdriver was initially generated as a "stub" by the
 *  gen-snmp-subdriver script. It must be customized!
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

#include "carel-rittal-cooling-mib.h"

#define CAREL_RITTAL_COOLING_MIB_VERSION    "0.1"

#define CAREL_RITTAL_COOLING_DEVICE_SYSOID  ".1.3.6.1.4.1.8072.3.2.10" //".1.3.6.1.4.1.9839"

#define CAREL_RITTAL_COOLING_OID_MODEL_NAME ".1.3.6.1.4.1.9839.1.2.0"

static info_lkp_t device_agent_info[] = {
	{ 2, "Generic cooling with Carel Rittal communication" }, /* "Code of the Agent. 2=pCOWeb." */
	{ 0, NULL }
};

/* CAREL_RITTAL_COOLING Snmp2NUT lookup table */
static snmp_info_t carel_rittal_cooling_mib[] = {

	/* Device collection */
	{ "device.mfr", ST_FLAG_STRING, SU_INFOSIZE, NULL, "Generic",
		SU_FLAG_STATIC | SU_FLAG_ABSENT | SU_FLAG_OK, NULL },
	/* agentCode.0 = INTEGER: 2 */
	{ "device.model", ST_FLAG_STRING, SU_INFOSIZE,
		CAREL_RITTAL_COOLING_OID_MODEL_NAME,
		"Generic cooling Carel/Rittal", SU_FLAG_STATIC | SU_FLAG_OK, &device_agent_info[0] },
	/* agentRelease.0 = INTEGER: 3 */
	{ "device.firmware", 0, 1,
		".1.3.6.1.4.1.9839.1.1.0",
		NULL, SU_FLAG_SEMI_STATIC | SU_FLAG_OK, NULL },
	{ "device.type", ST_FLAG_STRING, SU_INFOSIZE, NULL, "cooling",
		SU_FLAG_STATIC | SU_FLAG_ABSENT | SU_FLAG_OK, NULL },

	/* Machine status */
	/* stato-macchina.0 = INTEGER: 1 */
//?	{ "device.status", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.1.0", NULL, SU_FLAG_OK, &status_info[0] },


	/* Output collection */
	/* LCP Server IN? */
	/* b1-value.0 = INTEGER: 0 */
	/* { "unmapped.b1-value", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.1.0", NULL, SU_FLAG_OK, NULL }, */
	/* LCP Server IN #1 */
	/* b2-value.0 = INTEGER: 244 */
	{ "output.1.temperature", 0, 0.1, ".1.3.6.1.4.1.9839.2.1.2.2.0", NULL, SU_FLAG_OK, NULL },
	/* LCP Server IN #1 */
	/* b3-value.0 = INTEGER: 236 */
	{ "output.2.temperature", 0, 0.1, ".1.3.6.1.4.1.9839.2.1.2.3.0", NULL, SU_FLAG_OK, NULL },
	/* LCP Server IN #1 */
	/* b4-value.0 = INTEGER: 257 */
	{ "output.3.temperature", 0, 0.1, ".1.3.6.1.4.1.9839.2.1.2.4.0", NULL, SU_FLAG_OK, NULL },
	/* setpoint-lcp.0 = INTEGER: 230 */
	{ "output.temperature.nominal", ST_FLAG_RW, 0.1, ".1.3.6.1.4.1.9839.2.1.2.48.0", NULL, SU_FLAG_OK, NULL },

	/* Input collection */
	/* Server out? */
	/* b5-value.0 = INTEGER: 0 */
	/* { "unmapped.b5-value", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.5.0", NULL, SU_FLAG_OK, NULL }, */
	/* Server out #1 */
	/* b6-value.0 = INTEGER: 297 */
	{ "input.1.temperature", 0, 0.1, ".1.3.6.1.4.1.9839.2.1.2.6.0", NULL, SU_FLAG_OK, NULL },
	/* Server out #2 */
	/* b7-value.0 = INTEGER: 294 */
	{ "input.2.temperature", 0, 0.1, ".1.3.6.1.4.1.9839.2.1.2.7.0", NULL, SU_FLAG_OK, NULL },
	/* Server out #3 */
	/* b8-value.0 = INTEGER: 310 */
	{ "input.3.temperature", 0, 0.1, ".1.3.6.1.4.1.9839.2.1.2.8.0", NULL, SU_FLAG_OK, NULL },


	/* Cooling collection */
	/* evap-temp.0 = INTEGER: 104 */
	{ "cooling.evaporation.temperature", 0, 0.1, ".1.3.6.1.4.1.9839.2.1.2.13.0", NULL, SU_FLAG_OK, NULL },
	/* b12-value.0 = INTEGER: 68 */
	/* FIXME: to be verified!!! */
	{ "cooling.evaporation.pressure", 0, 0.1, ".1.3.6.1.4.1.9839.2.1.2.12.0", NULL, SU_FLAG_OK, NULL },
	/* cond-temp.0 = INTEGER: 375 */
	{ "cooling.condensation.temperature", 0, 0.1, ".1.3.6.1.4.1.9839.2.1.2.14.0", NULL, SU_FLAG_OK, NULL },
	/* b11-value.0 = INTEGER: 217 */
	/* FIXME: to be verified!!! */
	{ "cooling.condensation.pressure", 0, 0.1, ".1.3.6.1.4.1.9839.2.1.2.11.0", NULL, SU_FLAG_OK, NULL },
	/* rotor-speed-rps.0 = INTEGER: 1099 */
	{ "cooling.compressor.speed", 0, 0.1, ".1.3.6.1.4.1.9839.2.1.2.45.0", NULL, SU_FLAG_OK, NULL },
	/* motor-current.0 = INTEGER: 55 */
	{ "cooling.compressor.current", 0, 0.1, ".1.3.6.1.4.1.9839.2.1.2.46.0", NULL, SU_FLAG_OK, NULL },
	/* valve-steps.0 = INTEGER: 480 */
	{ "cooling.valve.position", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.17.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.30.0 = INTEGER: 100 */
	{ "cooling.valve.opening", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.30.0", NULL, SU_FLAG_OK, NULL },

	/* y3-AOut3.0 = INTEGER: 488 */
	{ "cooling.fan.speed.percent", 0, 0.1, ".1.3.6.1.4.1.9839.2.1.3.18.0", NULL, SU_FLAG_OK, NULL },
	/* Note: no per-fan RPM speed found! */

/* Needs

Temperature																									UNIT °C
X	In	+	x3	(LCP, server in)			output.{,1-3}.temperature
X	Out	+	x3	(server out) 			input.{,1-3}.temperature
X	Evaporation						cooling.temperature.evaporation?		1.3.6.1.4.1.9839.2.1.2.13
X	Condensation						cooling.temperature.condensation?	1.3.6.1.4.1.9839.2.1.2.14
X	Setpoint						output.temperature.nominal

Fan speed
	%							cooling.fan.{,1-6}.speed.{percent,rpm}
	+ RPM per fan																							UNIT RPM

X	cooling.fan.speed.percent -- 1.3.6.1.4.1.9839.2.1.3.18													UNIT percent

Electronic Valve
X	Opening 	%					cooling.valve.opening
X	Steps Position		1.3.6.1.4.1.9839.2.1.3.17	cooling.valve.position									UNIT steps

Compressor
X	Inverter speed						cooling.compressor.inverter.speed OR cooling.compressor.speed		UNIT RPM
X	Motor current						cooling.compressor.motor.current  OR cooling.compressor.current		UNIT Amps

Pressure
X	Evaporation						cooling.pressure.evaporation?	1.3.6.1.4.1.9839.2.1.2.12?				UNIT bar
X	Condensation					cooling.pressure.condensation?	1.3.6.1.4.1.9839.2.1.2.11?				UNIT bar

1.3.6.1.4.1.9839.2.1.2.1.0|2|0
1.3.6.1.4.1.9839.2.1.2.2.0|2|223
1.3.6.1.4.1.9839.2.1.2.3.0|2|190
1.3.6.1.4.1.9839.2.1.2.4.0|2|159
1.3.6.1.4.1.9839.2.1.2.5.0|2|0
1.3.6.1.4.1.9839.2.1.2.6.0|2|296
1.3.6.1.4.1.9839.2.1.2.7.0|2|263
1.3.6.1.4.1.9839.2.1.2.8.0|2|232
1.3.6.1.4.1.9839.2.1.2.9.0|2|656
1.3.6.1.4.1.9839.2.1.2.10.0|2|164
1.3.6.1.4.1.9839.2.1.2.11.0|2|249
1.3.6.1.4.1.9839.2.1.2.12.0|2|99
1.3.6.1.4.1.9839.2.1.2.13.0|2|104
1.3.6.1.4.1.9839.2.1.2.14.0|2|429
1.3.6.1.4.1.9839.2.1.2.15.0|2|62
1.3.6.1.4.1.9839.2.1.2.16.0|2|60
1.3.6.1.4.1.9839.2.1.2.17.0|2|150
1.3.6.1.4.1.9839.2.1.2.18.0|2|-500
1.3.6.1.4.1.9839.2.1.2.19.0|2|20
1.3.6.1.4.1.9839.2.1.2.20.0|2|900
1.3.6.1.4.1.9839.2.1.2.21.0|2|263
1.3.6.1.4.1.9839.2.1.2.22.0|2|190

*/


#if 0
	/* agentRelease.0 = INTEGER: 3 */
	{ "unmapped.agentRelease", 0, 1, ".1.3.6.1.4.1.9839.1.1.0", NULL, SU_FLAG_OK, NULL },
	/* agentCode.0 = INTEGER: 2 */
	{ "unmapped.agentCode", 0, 1, ".1.3.6.1.4.1.9839.1.2.0", NULL, SU_FLAG_OK, NULL },
	/* systm.3.1.1.0 = STRING: "DEBUT d'alarme" */
	{ "unmapped.systm", ST_FLAG_STRING, SU_INFOSIZE, ".1.3.6.1.4.1.9839.1.3.1.1.0", NULL, SU_FLAG_OK, NULL },
	/* systm.3.1.2.0 = STRING: "FIN d'alarme" */
	{ "unmapped.systm", ST_FLAG_STRING, SU_INFOSIZE, ".1.3.6.1.4.1.9839.1.3.1.2.0", NULL, SU_FLAG_OK, NULL },
	/* pCOId1-Status.0 = INTEGER: 2 */
	{ "unmapped.pCOId1-Status", 0, 1, ".1.3.6.1.4.1.9839.2.0.10.1.0", NULL, SU_FLAG_OK, NULL },
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
	/* din5.0 = INTEGER: 0 */
	{ "unmapped.din5", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.5.0", NULL, SU_FLAG_OK, NULL },
	/* din6.0 = INTEGER: 0 */
	{ "unmapped.din6", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.6.0", NULL, SU_FLAG_OK, NULL },
	/* din7.0 = INTEGER: 0 */
	{ "unmapped.din7", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.7.0", NULL, SU_FLAG_OK, NULL },
	/* din8.0 = INTEGER: 0 */
	{ "unmapped.din8", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.8.0", NULL, SU_FLAG_OK, NULL },
	/* din9.0 = INTEGER: 1 */
	{ "unmapped.din9", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.9.0", NULL, SU_FLAG_OK, NULL },
	/* din10.0 = INTEGER: 0 */
	{ "unmapped.din10", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.10.0", NULL, SU_FLAG_OK, NULL },
	/* dobj11.0 = INTEGER: 0 */
	{ "unmapped.dobj11", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.11.0", NULL, SU_FLAG_OK, NULL },
	/* dobj12.0 = INTEGER: 0 */
	{ "unmapped.dobj12", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.12.0", NULL, SU_FLAG_OK, NULL },
	/* dobj13.0 = INTEGER: 0 */
	{ "unmapped.dobj13", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.13.0", NULL, SU_FLAG_OK, NULL },
	/* dobj14.0 = INTEGER: 0 */
	{ "unmapped.dobj14", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.14.0", NULL, SU_FLAG_OK, NULL },
	/* dobj15.0 = INTEGER: 0 */
	{ "unmapped.dobj15", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.15.0", NULL, SU_FLAG_OK, NULL },
	/* dobj16.0 = INTEGER: 0 */
	{ "unmapped.dobj16", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.16.0", NULL, SU_FLAG_OK, NULL },
	/* dout1.0 = INTEGER: 1 */
	{ "unmapped.dout1", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.17.0", NULL, SU_FLAG_OK, NULL },
	/* dout2.0 = INTEGER: 0 */
	{ "unmapped.dout2", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.18.0", NULL, SU_FLAG_OK, NULL },
	/* dout3.0 = INTEGER: 1 */
	{ "unmapped.dout3", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.19.0", NULL, SU_FLAG_OK, NULL },
	/* dout4.0 = INTEGER: 0 */
	{ "unmapped.dout4", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.20.0", NULL, SU_FLAG_OK, NULL },
	/* dout5.0 = INTEGER: 0 */
	{ "unmapped.dout5", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.21.0", NULL, SU_FLAG_OK, NULL },
	/* dout6.0 = INTEGER: 0 */
	{ "unmapped.dout6", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.22.0", NULL, SU_FLAG_OK, NULL },
	/* dout7.0 = INTEGER: 1 */
	{ "unmapped.dout7", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.23.0", NULL, SU_FLAG_OK, NULL },
	/* dout8.0 = INTEGER: 0 */
	{ "unmapped.dout8", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.24.0", NULL, SU_FLAG_OK, NULL },
	/* dout9.0 = INTEGER: 0 */
	{ "unmapped.dout9", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.25.0", NULL, SU_FLAG_OK, NULL },
	/* dout10.0 = INTEGER: 0 */
	{ "unmapped.dout10", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.26.0", NULL, SU_FLAG_OK, NULL },
	/* dout11.0 = INTEGER: 0 */
	{ "unmapped.dout11", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.27.0", NULL, SU_FLAG_OK, NULL },
	/* dout12.0 = INTEGER: 0 */
	{ "unmapped.dout12", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.28.0", NULL, SU_FLAG_OK, NULL },
	/* bms-res-alarm.0 = INTEGER: 0 */
	{ "unmapped.bms-res-alarm", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.29.0", NULL, SU_FLAG_OK, NULL },
	/* al-envelope.0 = INTEGER: 0 */
	{ "unmapped.al-envelope", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.30.0", NULL, SU_FLAG_OK, NULL },
	/* al-start-fail-lock.0 = INTEGER: 0 */
	{ "unmapped.al-start-fail-lock", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.31.0", NULL, SU_FLAG_OK, NULL },
	/* mal-start-failure-msk.0 = INTEGER: 0 */
	{ "unmapped.mal-start-failure-msk", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.32.0", NULL, SU_FLAG_OK, NULL },
	/* mal-discharge-ht.0 = INTEGER: 0 */
	{ "unmapped.mal-discharge-ht", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.33.0", NULL, SU_FLAG_OK, NULL },
	/* dobj34.0 = INTEGER: 0 */
	{ "unmapped.dobj34", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.34.0", NULL, SU_FLAG_OK, NULL },
	/* mal-dp-startup.0 = INTEGER: 0 */
	{ "unmapped.mal-dp-startup", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.35.0", NULL, SU_FLAG_OK, NULL },
	/* mal-dp-lubrification-oil.0 = INTEGER: 0 */
	{ "unmapped.mal-dp-lubrification-oil", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.36.0", NULL, SU_FLAG_OK, NULL },
	/* mal-b1.0 = INTEGER: 0 */
	{ "unmapped.mal-b1", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.37.0", NULL, SU_FLAG_OK, NULL },
	/* mal-b2.0 = INTEGER: 0 */
	{ "unmapped.mal-b2", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.38.0", NULL, SU_FLAG_OK, NULL },
	/* mal-b3.0 = INTEGER: 0 */
	{ "unmapped.mal-b3", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.39.0", NULL, SU_FLAG_OK, NULL },
	/* mal-b4.0 = INTEGER: 0 */
	{ "unmapped.mal-b4", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.40.0", NULL, SU_FLAG_OK, NULL },
	/* mal-b5.0 = INTEGER: 0 */
	{ "unmapped.mal-b5", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.41.0", NULL, SU_FLAG_OK, NULL },
	/* mal-b6.0 = INTEGER: 0 */
	{ "unmapped.mal-b6", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.42.0", NULL, SU_FLAG_OK, NULL },
	/* mal-b7.0 = INTEGER: 0 */
	{ "unmapped.mal-b7", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.43.0", NULL, SU_FLAG_OK, NULL },
	/* mal-b8.0 = INTEGER: 0 */
	{ "unmapped.mal-b8", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.44.0", NULL, SU_FLAG_OK, NULL },
	/* mal-b9.0 = INTEGER: 0 */
	{ "unmapped.mal-b9", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.45.0", NULL, SU_FLAG_OK, NULL },
	/* mal-b10.0 = INTEGER: 0 */
	{ "unmapped.mal-b10", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.46.0", NULL, SU_FLAG_OK, NULL },
	/* mal-b11.0 = INTEGER: 0 */
	{ "unmapped.mal-b11", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.47.0", NULL, SU_FLAG_OK, NULL },
	/* mal-b12.0 = INTEGER: 0 */
	{ "unmapped.mal-b12", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.48.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.49.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.49.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.50.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.50.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.51.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.51.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.52.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.52.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.53.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.53.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.54.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.54.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.55.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.55.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.56.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.56.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.57.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.57.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.58.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.58.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.59.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.59.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.60.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.60.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.61.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.61.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.62.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.62.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.63.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.63.0", NULL, SU_FLAG_OK, NULL },
	/* digitalObjects.64.0 = INTEGER: 0 */
	{ "unmapped.digitalObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.1.64.0", NULL, SU_FLAG_OK, NULL },
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
	/* b9-value.0 = INTEGER: 897 */
	{ "unmapped.b9-value", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.9.0", NULL, SU_FLAG_OK, NULL },
	/* b10-value.0 = INTEGER: 289 */
	{ "unmapped.b10-value", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.10.0", NULL, SU_FLAG_OK, NULL },
	/* b11-value.0 = INTEGER: 217 */
	{ "unmapped.b11-value", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.11.0", NULL, SU_FLAG_OK, NULL },
	/* b12-value.0 = INTEGER: 68 */
	{ "unmapped.b12-value", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.12.0", NULL, SU_FLAG_OK, NULL },

	/* aobj15.0 = INTEGER: 296 */
	{ "unmapped.aobj15", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.15.0", NULL, SU_FLAG_OK, NULL },
	/* aobj16.0 = INTEGER: 60 */
	{ "unmapped.aobj16", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.16.0", NULL, SU_FLAG_OK, NULL },
	/* aobj17.0 = INTEGER: 150 */
	{ "unmapped.aobj17", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.17.0", NULL, SU_FLAG_OK, NULL },
	/* aobj18.0 = INTEGER: -300 */
	{ "unmapped.aobj18", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.18.0", NULL, SU_FLAG_OK, NULL },
	/* aobj19.0 = INTEGER: 20 */
	{ "unmapped.aobj19", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.19.0", NULL, SU_FLAG_OK, NULL },
	/* aobj20.0 = INTEGER: 900 */
	{ "unmapped.aobj20", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.20.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.21.0 = INTEGER: 300 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.21.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.22.0 = INTEGER: 245 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.22.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.23.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.23.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.24.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.24.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.25.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.25.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.26.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.26.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.27.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.27.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.28.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.28.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.29.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.29.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.30.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.30.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.31.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.31.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.32.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.32.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.33.0 = INTEGER: 0 */
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
	/* rotor-speed-rps.0 = INTEGER: 1099 */
	{ "unmapped.rotor-speed-rps", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.45.0", NULL, SU_FLAG_OK, NULL },
	/* motor-current.0 = INTEGER: 55 */
	{ "unmapped.motor-current", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.46.0", NULL, SU_FLAG_OK, NULL },
	/* aobj47.0 = INTEGER: 0 */
	{ "unmapped.aobj47", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.47.0", NULL, SU_FLAG_OK, NULL },

	/* analogObjects.49.0 = INTEGER: 380 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.49.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.50.0 = INTEGER: 150 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.50.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.51.0 = INTEGER: 320 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.51.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.52.0 = INTEGER: 500 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.52.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.53.0 = INTEGER: 500 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.53.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.54.0 = INTEGER: 750 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.54.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.55.0 = INTEGER: 850 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.55.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.56.0 = INTEGER: 1400 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.56.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.57.0 = INTEGER: 50 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.57.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.58.0 = INTEGER: 30 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.58.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.59.0 = INTEGER: 350 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.59.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.60.0 = INTEGER: 50 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.60.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.61.0 = INTEGER: 70 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.61.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.62.0 = INTEGER: 40 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.62.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.63.0 = INTEGER: 30 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.63.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.64.0 = INTEGER: 120 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.64.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.65.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.65.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.66.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.66.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.67.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.67.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.68.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.68.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.69.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.69.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.70.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.70.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.71.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.71.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.72.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.72.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.73.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.73.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.74.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.74.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.75.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.75.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.76.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.76.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.77.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.77.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.78.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.78.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.79.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.79.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.80.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.80.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.81.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.81.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.82.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.82.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.83.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.83.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.84.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.84.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.85.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.85.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.86.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.86.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.87.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.87.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.88.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.88.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.89.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.89.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.90.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.90.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.91.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.91.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.92.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.92.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.93.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.93.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.94.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.94.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.95.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.95.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.96.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.96.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.97.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.97.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.98.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.98.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.99.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.99.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.100.0 = INTEGER: 0 */
	{ "unmapped.analogObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.2.100.0", NULL, SU_FLAG_OK, NULL },
	/* analogObjects.101.0 = INTEGER: 0 */
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
	{ "unmapped.analogObjects", 0, 1, ".1.3rotor-speed-hz.6.1.4.1.9839.2.1.2.124.0", NULL, SU_FLAG_OK, NULL },
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
	/* rotor-speed-hz.0 = INTEGER: 3299 */
	{ "unmapped.rotor-speed-hz", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.1.0", NULL, SU_FLAG_OK, NULL },
	/* drive-status.0 = INTEGER: 1 */
	{ "unmapped.drive-status", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.2.0", NULL, SU_FLAG_OK, NULL },
	/* error-code.0 = INTEGER: 0 */
	{ "unmapped.error-code", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.3.0", NULL, SU_FLAG_OK, NULL },
	/* drive-temp.0 = INTEGER: 48 */
	{ "unmapped.drive-temp", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.4.0", NULL, SU_FLAG_OK, NULL },
	/* bus-voltage.0 = INTEGER: 541 */
	{ "unmapped.bus-voltage", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.5.0", NULL, SU_FLAG_OK, NULL },
	/* motor-voltage.0 = INTEGER: 269 */
	{ "unmapped.motor-voltage", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.6.0", NULL, SU_FLAG_OK, NULL },
	/* power-req-0-1000-after-envelope.0 = INTEGER: 846 */
	{ "unmapped.power-req-0-1000-after-envelope", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.7.0", NULL, SU_FLAG_OK, NULL },
	/* current-hour.0 = INTEGER: 12 */
	{ "unmapped.current-hour", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.8.0", NULL, SU_FLAG_OK, NULL },
	/* current-minute.0 = INTEGER: 51 */
	{ "unmapped.current-minute", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.9.0", NULL, SU_FLAG_OK, NULL },
	/* current-month.0 = INTEGER: 12 */
	{ "unmapped.current-month", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.10.0", NULL, SU_FLAG_OK, NULL },
	/* current-weekday.0 = INTEGER: 6 */
	{ "unmapped.current-weekday", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.11.0", NULL, SU_FLAG_OK, NULL },
	/* current-year.0 = INTEGER: 17 */
	{ "unmapped.current-year", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.12.0", NULL, SU_FLAG_OK, NULL },
	/* on-off-BMS.0 = INTEGER: 1 */
	{ "unmapped.on-off-BMS", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.13.0", NULL, SU_FLAG_OK, NULL },
	/* envelope-zone.0 = INTEGER: 1 */
	{ "unmapped.envelope-zone", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.14.0", NULL, SU_FLAG_OK, NULL },
	/* ht-zone.0 = INTEGER: 1 */
	{ "unmapped.ht-zone", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.15.0", NULL, SU_FLAG_OK, NULL },
	/* cooling-capacity-after-envelope.0 = INTEGER: 84 */
	{ "unmapped.cooling-capacity-after-envelope", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.16.0", NULL, SU_FLAG_OK, NULL },

	/* integerObjects.19.0 = INTEGER: 2 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.19.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.20.0 = INTEGER: 300 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.20.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.21.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.21.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.22.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.22.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.23.0 = INTEGER: 5 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.23.0", NULL, SU_FLAG_OK, NULL },
	/* y4-AOut4.0 = INTEGER: 488 */
	{ "unmapped.y4-AOut4", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.24.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.25.0 = INTEGER: 260 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.25.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.26.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.26.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.27.0 = INTEGER: 29 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.27.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.28.0 = INTEGER: 48 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.28.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.29.0 = INTEGER: 1776 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.29.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.31.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.31.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.32.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.32.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.33.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.33.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.34.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.34.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.35.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.35.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.36.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.36.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.37.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.37.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.38.0 = INTEGER: 161 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.38.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.39.0 = INTEGER: 7 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.39.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.40.0 = INTEGER: 768 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.40.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.41.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.41.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.42.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.42.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.43.0 = INTEGER: 7 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.43.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.44.0 = INTEGER: 768 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.44.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.45.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.45.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.46.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.46.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.47.0 = INTEGER: 5 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.47.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.48.0 = INTEGER: 80 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.48.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.49.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.49.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.50.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.50.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.51.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.51.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.52.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.52.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.53.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.53.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.54.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.54.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.55.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.55.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.56.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.56.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.57.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.57.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.58.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.58.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.59.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.59.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.60.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.60.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.61.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.61.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.62.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.62.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.63.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.63.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.64.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.64.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.65.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.65.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.66.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.66.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.67.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.67.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.68.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.68.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.69.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.69.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.70.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.70.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.71.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.71.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.72.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.72.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.73.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.73.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.74.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.74.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.75.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.75.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.76.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.76.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.77.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.77.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.78.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.78.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.79.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.79.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.80.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.80.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.81.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.81.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.82.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.82.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.83.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.83.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.84.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.84.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.85.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.85.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.86.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.86.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.87.0 = INTEGER: 0 */
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
	/* integerObjects.93.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.93.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.94.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.94.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.95.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.95.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.96.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.96.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.97.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.97.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.98.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.98.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.99.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.99.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.100.0 = INTEGER: 890 */
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
	/* integerObjects.107.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.107.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.108.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.108.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.109.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.109.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.110.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.110.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.111.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.111.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.112.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.112.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.113.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.113.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.114.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.114.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.115.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.115.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.116.0 = INTEGER: 0 */
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
	/* integerObjects.125.0 = INTEGER: 17 */
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
	/* integerObjects.146.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.146.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.147.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.147.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.148.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.148.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.149.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.149.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.150.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.150.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.151.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.151.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.152.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.152.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.153.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.153.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.154.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.154.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.155.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.155.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.156.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.156.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.157.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.157.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.158.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.158.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.159.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.159.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.160.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.160.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.161.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.161.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.162.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.162.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.163.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.163.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.164.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.164.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.165.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.165.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.166.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.166.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.167.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.167.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.168.0 = INTEGER: 0 */
	{ "unmapped.integerObjects", 0, 1, ".1.3.6.1.4.1.9839.2.1.3.168.0", NULL, SU_FLAG_OK, NULL },
	/* integerObjects.169.0 = INTEGER: 0 */
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
	/* integerObjects.201.0 = INTEGER: 2017 */
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

mib2nut_info_t	carel_rittal_cooling = { "carel_rittal_cooling", CAREL_RITTAL_COOLING_MIB_VERSION, NULL, NULL, carel_rittal_cooling_mib, CAREL_RITTAL_COOLING_DEVICE_SYSOID };
