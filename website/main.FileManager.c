/*
 * main.fileManager.c
 */
#include "main.header.h"

// project.main.fileManager
// project.main.fileManager.CONSTANT_DEFINED

#define VERB_FILEOPEN(name, mode)               ">VERBOSE:  File \"%s\" is opened for %s mode.\n", name, mode
#define ERR_COULD_NOT_OPEN_FILE(filename)      ">>>ERROR : Could not open file, \"%s\".\n", filename
#define MSG_PROMPT_FILENAME                     "Please enter filename: "



// project.main.fileManager.PRIVATE_FUNCTION_DECLARATIONS
static char* _getFileName(const char *msg);
static char* _getBackupFileName(char *name, const char *extension);
static FILE* _openFile(const char *name, const char *mode);




FILE* LastSessionManager (void) {
    FILE* fPtr;
    char *usBacFileName; // unsafe backup filename

    usBacFileName = _getFileName(MSG_PROMPT_FILENAME);

    fPtr = _getLastSessionFileName(usBacFileName);
    fPtr = _openFile(usBacFileName, FILEMODE_READONLY);
    
    // FIXME:
    // fileopen: user-chosen input file's backup
    *fPtr = fopen(*sFileName, sFileMode);
    if (!fPtr) { /* if file does not exist */
        return NULL;
    }
}

static char* _getBackupFileName(char *name, const char *extension) {
	FILE* fPtr = NULL;
	char usBacFilename[MAX_LENGTH_INPUT]; // unsafe backup filename
	char *sUserInput;
	int validKey;
    
	// get: backup filename
	strcpy(usBacFilename, sInFilename);
    free(sInFilename); // free safe input file name (
	strcat(usBacFilename, PREFIX_BACKUP_FILENAME);
    

    switch (validKey) {
        case INPUT_VALUE_QUIT:
            exit(EXIT_ON_REQUEST);
            break;
        case INPUT_VALUE_VALID:
            *sFileName = usFileName;
        case INPUT_VALUE_NO:  // do not discard: last session
            return fPtr;
            break;
        case INPUT_VALUE_YES: // discard: last session
            fclose(fPtr);
            printf(VERB_LAST_SESSION_DISCARDED);
            return NULL;
        default:
            return NULL;
            break;
    }
    
}

static char* _getFileName(const char *msg) {
	char usInput[MAX_LENGTH_INPUT]; // unsafe user input string
	int validKey = 0;
	char *sInput;
    input_type type = INPUT_TYPE_FILENAME;
    
	MALLOC(sInput);
    do {
		printf("%s", msg); // prompt message
		fgets(usInput, MAX_LENGTH_INPUT, stdin);
        
		// trim: '\n'
		usInput[strlen(usInput) - 1] = '\0';
        
		// validate: user input
		validKey = ValidateManager(type, usInput);
		if (INPUT_VALUE_VALID == validKey) {
			strcpy(sInput, usInput);
			return sInput;
		} else if (INPUT_VALUE_QUIT == validKey) {
			exitOnUserRequest(EXIT_ON_REQUEST);
		}
	} while (INPUT_VALUE_INVALID == validKey);
    
	return sInput;
}

static FILE* _openFile(const char *name, const char *mode) {
    FILE* fPtr; // file pointer
    char *usFileName = NULL; // unsafe filename
    
    // fileopen: user-chosen input file's backup
    fPtr = fopen(name, mode);
    if (!fPtr) { /* if file does not exist */
        free(usFileName); // free: useless filename
    }
    
    return fPtr;
}

