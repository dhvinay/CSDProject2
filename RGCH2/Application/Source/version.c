/**
 *  @file   version.c
 */

#include "Eos.h"
#include "version.h"

const uint8 applVersion_acu8[21] __attribute__ ((section (".appl_version"))) = applVersion_value;
const uint8 applGNumber_acu8[20] __attribute__ ((section (".appl_g_nr")))    = applGNumber_value;
const uint8 applDate_acu8[3]     __attribute__ ((section (".appl_date")))    = applDate_value;
const uint8 applTime_acu8[3]                                                 = applTime_value;
