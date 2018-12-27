/* ---------------------------------------------------------------------------------------------------- */
/* Adapted from :																						*/
/* Sources : alk https://stackoverflow.com/questions/17984628/switch-statement-using-string-on-an-array */
/*           create a switch with char * arguments                                                      */
/* ---------------------------------------------------------------------------------------------------- */
#include "switch.h"

struct Command_info command_infos[10] = {
	{""			, NO_COMMAND},   
	{"new"		, NEW  		},
	{"read"		, READ	    },
	{"add"		, ADD 	    },
	{"rm"		, REMOVE    },
	{"replace"  , REPLACE   }, 
	{"help"     , HELP      },
	{"simple"   , SIMPLE    },
	{"special"  , SPECIAL   },
	{"passwd"   , PASSWORD  },
};

/* ------------------------------------------------------ */
int cmp_command_infos(const void * pvCI1, const void* pvCI2)
/* ------------------------------------------------------ */
{
	const struct Command_info * pCI1 = pvCI1;
	const struct Command_info * pCI2 = pvCI2;

	return strcmp(pCI1->command, pCI2->command);
}
/* ------------------------------- */
int readCommand(const char * command)
/* ------------------------------- */
{
	if(command == NULL) return -1;
	qsort(command_infos, sizeof command_infos / sizeof *command_infos, sizeof *command_infos, cmp_command_infos);
	{
    	struct Command_info * pCI = bsearch(&(struct Command_info){command, NO_COMMAND}, command_infos, sizeof command_infos / sizeof *command_infos, sizeof *command_infos, cmp_command_infos);
    	return pCI == NULL ? NO_COMMAND : pCI -> id;
	}
}