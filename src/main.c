#include "cli.h"

int main(int argc, const char * argv[])
{ 
    printBanner();
    int command = readCommand(argv[1]);
    if(command == NEW)
    {
        verifyNbArg(argc, 4);
        printNewPassword(argv[2], argv[3]);
    }
    else if(command > FIRST_CMD && command < LAST_CMD)
    {
        verifyNbArg(argc, 2);
        action(command);
    }
    else
        printHelp();
    return SUCCESS;
}
