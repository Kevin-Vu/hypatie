#include "cli.h"

/* --------------------------------------------------------------------------------------------------------- */
void printBanner()
/* --------------------------------------------------------------------------------------------------------- */
{
    puts(" ___  ___      ___    ___ ________  ________  _________  ___  _______");      
    puts("|\\  \\|\\  \\    |\\  \\  /  /|\\   __  \\|\\   __  \\|\\___   ___|\\  \\|\\  ___ \\");    
    puts("\\ \\  \\\\\\  \\   \\ \\  \\/  / \\ \\  \\|\\  \\ \\  \\|\\  \\|___ \\  \\_\\ \\  \\ \\   __/|");    
    puts(" \\ \\   __  \\   \\ \\    / / \\ \\   ____\\ \\   __  \\   \\ \\  \\ \\ \\  \\ \\  \\_|/__");  
    puts("  \\ \\  \\ \\  \\   \\/  /  /   \\ \\  \\___|\\ \\  \\ \\  \\   \\ \\  \\ \\ \\  \\ \\  \\_|\\ \\"); 
    puts("   \\ \\__\\ \\__\\__/  / /      \\ \\__\\    \\ \\__\\ \\__\\   \\ \\__\\ \\ \\__\\ \\_______\\");
    puts("    \\|__|\\|__|\\___/ /        \\|__|     \\|__|\\|__|    \\|__|  \\|__|\\|_______|");
    puts("             \\|___|/");                                 
    fprintf(stdout,"                                                                     %s\n", HYPATIE_VER);                                                                   
}
/* --------------------------------------------------------------------------------------------------------- */
void printHelp()
/* --------------------------------------------------------------------------------------------------------- */
{
    puts("Hypatie command-line interface");
    puts("");
    puts("usage:");
    puts("");
    puts("  new simple|special <length>    generate a random password");
    puts("  read                           print a password");
    puts("  add                            add a new password");
    puts("  rm                             remove a password");
    puts("  replace                        replace a password by a new one");
    puts("  passwd                         change the master password");
    puts("");
}
/* --------------------------------------------------------------------------------------------------------- */
void printNewPassword(const char * option, const char * length)
/* --------------------------------------------------------------------------------------------------------- */
{
    char * newPass = NULL;
    switch(readCommand(option))
    {
        case SIMPLE:
            newPass = randomAlphaNum(atoi(length));
            printf("The new simple password is : %s\n", newPass);
            break;

        case SPECIAL:
            newPass = randomAlphaSpecNum(atoi(length));
            printf("The new special password is : %s\n", newPass);
            break;

        default:
            verifyNbArg(0,1); /* 0 != 1 so printhelp() */  
    }
    free(newPass);
}
/* --------------------------------------------------------------------------------------------------------- */
void retrieveInput(char * input, char * message)
/* --------------------------------------------------------------------------------------------------------- */
{
    fprintf(stdout, "%s", message);
    if(fgets(input, BUFFERSIZE, stdin) != NULL)
    {
        if(strcmp(input, "\n") == 0 || containSpaces(input)){
            puts("ERROR: You have entered an empty input or an input with spaces.");
            strcpy(input, "(null)");
        }
        else
            input[strcspn(input, "\n")] = 0;
    }
    else
        input = "(null)";
}
/* --------------------------------------------------------------------------------------------------------- */
void encryptSTORE_FILE(P_PROP * p, int length, char * key, char * iv, int doexit)
/* --------------------------------------------------------------------------------------------------------- */
{
    /* encryp doc.csv to enc.csv and verify md5 */
    int res = call_encrypt_decrypt(STORE_FILE, ENC_FILE, key, (unsigned char *) iv, ENCRYPT_MODE);
    verifyResponseCode(p, length, key, iv, res, doexit);
    res = verify_encryption(STORE_FILE, ENC_FILE, key, (unsigned char *) iv);
    verifyResponseCode(p, length, key, iv, res, doexit);
}
/* --------------------------------------------------------------------------------------------------------- */
void displayArray(P_PROP * p, int length)
/* --------------------------------------------------------------------------------------------------------- */
{
    puts("+---------------------------+--------------------------------+--------+");
    printf("| %-25.25s | %-30.30s | %s |\n", "ID", "account", "number");
    puts("+---------------------------+--------------------------------+--------+");
    displayKeyP_PROP(p, length);
    puts("+---------------------------+--------------------------------+--------+");
}
/* --------------------------------------------------------------------------------------------------------- */
void printPassword(P_PROP * p, int length)
/* --------------------------------------------------------------------------------------------------------- */
{
    char lno[BUFFERSIZE];
    puts("Choose the password to show (number) :");
    displayArray(p, length);
    /* cli enter password to show */
    retrieveInput(lno, "Choice : ");
    /* display password */
    P_CONT c = getContent(p, length,atoi(lno));
    if(c != NULL)
    {
        fprintf(stdout, "The password for %s is :\n account \t= %s \n password \t= %s\n", p[atoi(lno)] -> key, c -> email, c -> value);
        free(c);
    }else
        fprintf(stderr,"ERROR : Verify that the number is correct : %d\n", atoi(lno)); 
}
/* --------------------------------------------------------------------------------------------------------- */
void addPassword(char * key, char * iv)
/* --------------------------------------------------------------------------------------------------------- */
{
    char id[BUFFERSIZE], password[BUFFERSIZE], account[BUFFERSIZE];
    /* cli enter id */
    retrieveInput(id, "Enter the id (e.g. : website name) : ");
    /* cli enter account */
    retrieveInput(account, "Enter the account (e.g. : email account, username ... ) : ");
    /* cli enter password */
    retrieveInput(password, "Enter the password (note : not the master password) : ");
    /* insert the new password and delete empty lines in doc.csv before encryption */
    insertLine(STORE_FILE, id, password, account);
    modifyFile(STORE_FILE, NULL, DELETE_EMPTY);
    encryptSTORE_FILE(NULL, 0, key, iv, DO_EXIT);
    
    puts("Password added");
}
/* --------------------------------------------------------------------------------------------------------- */
void removePassword(P_PROP * p, int length, char * key, char * iv)
/* --------------------------------------------------------------------------------------------------------- */
{
    char lno[BUFFERSIZE];
    puts("Choose the password to delete (number) :");
    displayArray(p,length);
    /* cli choose password to remove */
    retrieveInput(lno, "Choice : ");
    if(atoi(lno) > length - 1 ||  atoi(lno) < 0 )
        fprintf(stderr,"ERROR : Verify that the number is correct : %d\n", atoi(lno)); 
    else{
        /* removing */
        modifyFile(STORE_FILE, NULL, atoi(lno));
        encryptSTORE_FILE(p, length, key, iv, DO_EXIT);
    }
    puts("Password removed");
}
/* --------------------------------------------------------------------------------------------------------- */
void replacePassword(P_PROP * p, int length, char * key, char * iv)
/* --------------------------------------------------------------------------------------------------------- */
{
    char lno[BUFFERSIZE], password[BUFFERSIZE], account[BUFFERSIZE];
    char newline[4*BUFFERSIZE];
    displayArray(p,length);
    /* cli choose password to replace */
    retrieveInput(lno, "Choice : ");
    if(atoi(lno) > length - 1 ||  atoi(lno) < 0 )
    {
        fprintf(stderr,"ERROR : Verify that the number is correct : %d\n", atoi(lno)); 
        return;
    }
    /* cli enter new account */
    retrieveInput(account, "Enter the account (e.g. : email account, username ... ) : ");
    /* cli enter new password */
    retrieveInput(password, "Enter the password (note : not the master password) : ");
    /* if modify last password, do not add return line */
    if(atoi(lno) == length - 1)
        sprintf(newline, "%s %s %s", p[atoi(lno)] -> key, password, account);
    else
        sprintf(newline, "%s %s %s\n", p[atoi(lno)] -> key, password, account);
    modifyFile(STORE_FILE, newline, atoi(lno));

    encryptSTORE_FILE(p, length, key, iv, DO_EXIT);
    puts("Password changed");
}
/* --------------------------------------------------------------------------------------------------------- */
void changeMasterPassword(P_PROP * p, int length)
/* --------------------------------------------------------------------------------------------------------- */
{
    char password[BUFFERSIZE], password_test[BUFFERSIZE];
    char * key = NULL, * iv = NULL;
    /* cli enter new masster password */
    retrieveInput(password, "Enter the new master password : ");
    /* cli retype master */
    retrieveInput(password_test, "Retype the new master password : ");
    /* test match */
    if(strcmp(password, password_test) != 0)
        puts("Sorry, passwords do not match");
    else{
        key = sha256_hash_from_string(password);
        iv = md5_hash_from_string(password);
        encryptSTORE_FILE(p, length, key, iv, DO_NOT_EXIT);
        /* clean free */
        free(key);
        free(iv);
        puts("Master password updated successfully");
    }
}
/* --------------------------------------------------------------------------------------------------------- */
void action(int command)
/* --------------------------------------------------------------------------------------------------------- */
{
    char master[BUFFERSIZE];
    /* cli master password */
    retrieveInput(master, "Enter the master password : ");

    /* generate key and init vect from master */
    char * key = sha256_hash_from_string(master);
    char * iv = md5_hash_from_string(master);
    
    /* decrypt enc.csv file if exist else create doc.csv */
    int res = createFileIfNotExist(master, command);
    if(res != INFO)
    {
        res = call_encrypt_decrypt(ENC_FILE, STORE_FILE, key, (unsigned char *) iv, DECRYPT_MODE);
        verifyResponseCode(NULL, 0, key, iv, res, DO_EXIT);
    }

    P_PROP * p = file_to_P_PROParray(STORE_FILE);
    int length = countLine(STORE_FILE);
    /* clean free if no lines and command is not password or add */
    if(length == 0 && !(command == PASSWORD || command == ADD)) 
    {
        free(key);
        free(iv);
        if(p != NULL)
            free_P_PROParray(p, length);
        remove(STORE_FILE);
        puts("There is no password stored");
        exit(SUCCESS);
    }

    /* execute command */
    switch(command)
    {
        case READ: printPassword(p, length); break;
        case ADD: addPassword(key, iv); break;
        case REMOVE: removePassword(p, length, key, iv); break;   
        case REPLACE: replacePassword(p, length, key, iv); break;
        case PASSWORD: changeMasterPassword(p, length); break;
        default: break;                 
    }
    
    /* clean free */
    remove(STORE_FILE);
    free_P_PROParray(p, length);
    free(key);
    free(iv);
}
/* --------------------------------------------------------------------------------------------------------- */
int createFileIfNotExist(char * master, int command)
/* --------------------------------------------------------------------------------------------------------- */
{
    /* create doc.csv file if enc.csv does not exist */
    FILE * testfp = fopen(ENC_FILE,"rb");
    if(testfp == NULL)
    {
        FILE * fp = fopen(STORE_FILE,"w");
        fclose(fp);
        if(command == ADD)
            fprintf(stdout, "INFO : enc.csv file not found -  a new one will be created with encryption password : %s\n", master);
        else
            puts("INFO : enc.csv file not found");
        return INFO;
    }
    else{
        fclose(testfp);
        return SUCCESS;
    }
}
/* --------------------------------------------------------------------------------------------------------- */
void verifyResponseCode(P_PROP * p, int l, char * key, char * iv, int code, int doexit)
/* --------------------------------------------------------------------------------------------------------- */
{
    /* proper exit if error and doexit is true */
    if(code == ERROR)
    {
        if(p != NULL)
            free_P_PROParray(p,l);
        remove(STORE_FILE);
        free(key);
        free(iv);
        if(doexit)
            exit(1);
    }
}
/* --------------------------------------------------------------------------------------------------------- */
void verifyNbArg(int argc, int expected)
/* --------------------------------------------------------------------------------------------------------- */
{
    if(argc != expected)
    {
        puts("Invalid arguments, see help below ");
        printHelp();
        exit(1);
    }
}
