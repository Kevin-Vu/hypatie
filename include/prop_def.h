/* ----------------- */
/* --- propdef.h --- */
/* ----------------- */

#ifndef PROP_DEF_
#define PROP_DEF_

typedef struct { char key[30]; char value[30]; char email[30]; } PROP;
typedef PROP * P_PROP;

typedef struct { char value[30]; char email[30]; } CONT ;
typedef CONT * P_CONT;

#endif // PROP_DEF_