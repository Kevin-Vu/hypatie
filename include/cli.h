/* --------------- */
/* ---- cli.h ---- */
/* --------------- */

#ifndef CLI_
#define CLI_

#include "switch.h"
#include "parse_prop.h"
#include "util_string.h"
#include "openssl.h"

#define BUFFERSIZE 		100
#define DO_EXIT			1
#define DO_NOT_EXIT		0

#define HYPATIE_VER		((const char *)"v1.0")

/* ---------------------------------------------------------------------------------------- */
/* ----------------------------------- retrieve command ----------------------------------- */
void action(int command);
/* ---------------------------------------------------------------------------------------- */
void retrieveInput(char * input, char * message);
/* ----------------------------------- execute command ------------------------------------ */
void printNewPassword(const char * option, const char * length);
void printPassword(P_PROP * p, int length);
void addPassword(char * key, char * iv);
void removePassword(P_PROP * p, int length, char * key, char * iv);
void replacePassword(P_PROP * p, int length, char * key, char * iv);
void changeMasterPassword(P_PROP * p, int length);
void printHelp();
/* ---------------------------------------------------------------------------------------- */
void printBanner();
void displayArray(P_PROP * p, int length);
/* ---------------------------------------------------------------------------------------- */
int createFileIfNotExist(char * master, int command);
void encryptSTORE_FILE(P_PROP * p, int length, char * key, char * iv, int doexit);
/* ---------------------------------------------------------------------------------------- */
/* -------------------------------------- verification ------------------------------------ */
void verifyResponseCode(P_PROP * p, int length, char * key, char * iv, int code, int doexit);
void verifyNbArg(int argc, int expected);


#endif // CLI_