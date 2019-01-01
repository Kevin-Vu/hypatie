/* ----------------- */
/* --- propdef.h --- */
/* ----------------- */

#ifndef PROP_DEF_
#define PROP_DEF_

typedef struct { char key[100]; char value[100]; char email[100]; } PROP;
typedef PROP * P_PROP;

typedef struct { char value[100]; char email[100]; } CONT ;
typedef CONT * P_CONT;

#endif // PROP_DEF_