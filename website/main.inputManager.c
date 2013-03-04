#include "main.inputManager.header.h"

Website* inputManager(void) {
    Website* curWebsite = NULL;
    FILE* fPtr = NULL;
    char *sInFilename = NULL; // safe input filename
    
    // get: source file from user
    sInFilename = getFilename(INPUT_TYPE_FILENAME, MSG_PROMPT_FILENAME);
        
    // check: if last program run was not saved and (sInFilename + ".bac") exists
    fPtr = getLastSessionStatus(sInFilename);
    if (!fPtr) { /* if lastSession not found */
        // fileopen: user-chosen input file
        do {
            fPtr = fopen(sInFilename, FILEMODE_READONLY);
            if (!fPtr) { /* if file does not exist */
                printf(ERRR_COULD_NOT_OPEN_FILE(sInFilename));
                sInFilename = getFilename(INPUT_TYPE_FILENAME, MSG_PROMPT_FILENAME);
            }
        } while(!fPtr);
        printf(VERB_FILEOPEN(sInFilename, FILEMODE_READONLY));
    }
    
    // get: validate `struct Website`
    curWebsite = getValidatedInput(fPtr);
    
    // fileclose: user-chosen source file
    return curWebsite;
}
