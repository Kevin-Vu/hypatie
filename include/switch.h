/* ------------------ */
/* ---- switch.h ---- */
/* ------------------ */
/* ---------------------------------------------------------------------------------------------------- */
/* Adapted from :																						*/
/* Sources : alk https://stackoverflow.com/questions/17984628/switch-statement-using-string-on-an-array */
/* ---------------------------------------------------------------------------------------------------- */

#ifndef SWITCH_
#define SWITCH_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Only add new main command between FIRST_CMD and LAST_CMD */
enum Command_id { NO_COMMAND, FIRST_CMD, NEW, READ, ADD, REMOVE, REPLACE, PASSWORD, HELP, LAST_CMD, SIMPLE, SPECIAL };
struct Command_info{ const char * command; enum Command_id id; };

extern struct Command_info command_infos[];

int cmp_command_infos(const void * pvCI1, const void* pvCI2);
int readCommand(const char * command);

#endif