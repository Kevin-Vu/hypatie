/* -------------------- */
/* --- parse_prop.h --- */
/* -------------------- */

#ifndef PARSE_PROP_
#define PARSE_PROP_

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "prop_def.h"
#include "util_file.h"

/* ----------------------------------------------------------- */
/* -------------------------- alloc -------------------------- */
P_PROP * P_PROParray(int n);
P_PROP * file_to_P_PROParray(char const * filename);
/* ----------------------------------------------------------- */
/* -------------------------- free --------------------------- */
void free_P_PROParray(P_PROP * p, int n);
/* ----------------------------------------------------------- */
P_CONT getContent(P_PROP *p, int length, int lno);
/* ----------------------------------------------------------- */
/* ------------------------- display ------------------------- */
void displayArrayP_PROP(P_PROP * p, int l);
void displayKeyP_PROP(P_PROP * p, int l);

#endif // PARSE_PROP_