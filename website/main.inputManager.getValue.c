//
//  prompt.c
//  website
//
//  Created by Anonymous on 3/3/13.
//  Copyright (c) 2013 Anonymous. All rights reserved.
//

#include "header.h"

int getUserSelection(input_type type, const char *msg) {
	char usInput[MAX_LENGTH_INPUT];
	int validKey = 0;
    
	do {
		printf("%s", msg);
		fgets(usInput, MAX_LENGTH_INPUT, stdin);
        
		// trim: '\n'
		usInput[strlen(usInput) - 1] = '\0';
        
		// validate: user input
		validKey = validateInput(type, usInput);
		if (INPUT_VALUE_QUIT == validKey) {
			exit(EXIT_ON_REQUEST);
		}
	} while (INPUT_VALUE_INVALID == validKey);
	return validKey;
}

FILE* getLastSessionStatus(char *sInFilename) {
	FILE* fPtr = NULL;
	char usBacFilename[MAX_LENGTH_INPUT]; // unsafe backup filename
	char *sUserInput;
	int validKey;
    
	// get: backup filename
	strcpy(usBacFilename, sInFilename);
	strcat(usBacFilename, PREFIX_BACKUP_FILENAME);
    
	// fileopen: user-chosen input file's backup
	fPtr = fopen(usBacFilename, FILEMODE_READONLY);
	if (!fPtr) { /* if backup file does not exist */
		return NULL;
	} else { /* if backup file exists */
		printf(VERB_LAST_SESSION_FOUND);
		validKey = getUserSelection(INPUT_TYPE_DISCARD, MSG_PROMPT_DISCARD);
		switch (validKey) {
            case INPUT_VALUE_QUIT:
                exit(EXIT_ON_REQUEST);
                break;
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
}

char* getFilename(input_type type, const char *msg) {
	char usInput[MAX_LENGTH_INPUT];
	int validKey = 0;
	char *sInput;
    
	MALLOC(sInput);
    
	do {
		printf("%s", msg);
		fgets(usInput, MAX_LENGTH_INPUT, stdin);
        
		// trim: '\n'
		usInput[strlen(usInput) - 1] = '\0';
        
		// validate: user input
		validKey = validateInput(type, usInput);
		if (INPUT_VALUE_VALID == validKey) {
			strcpy(sInput, usInput);
			return sInput;
		} else if (INPUT_VALUE_QUIT == validKey) {
			exit(EXIT_ON_REQUEST);
		}
	} while (INPUT_VALUE_INVALID == validKey);
    
	return sInput;
}

Website* getValidatedInput(FILE* fPtr) {
	Website* curWebsite;            // current `struct Website`
	char *sUrl;
	char *sCompany;
    int sDailyPageView;
    int sRankTraffic;
    int sBackLink;
    int sWebsiteWorth;
	/*
	 * `char *usLine;`
	 * unsafe single line read
	 * (may not represent original value)
	 */
    char *usLine = NULL;              // safe single line read
    char *sLine = NULL;

	MALLOC(curWebsite);
	usLine = readOneLine(fPtr);
    
	
	if (NULL == usLine) { /* reached: EOF of input file */
        VS("%s_sSingleLine is NULL", usLine);
        return NULL;
	} else {
        sLine = usLine;
    }
    
    VS("safesingline:_%s_\n", usLine);
    
	// set: fields in `curWebsite`
    sUrl = (char*) readSingleField(INPUT_TYPE_URL, usLine);
    sCompany = (char*) readSingleField(INPUT_TYPE_URL, usLine);
    sDailyPageView = (int) readSingleField(INPUT_TYPE_URL, usLine);
    sRankTraffic = (int) readSingleField(INPUT_TYPE_URL, usLine);
    sBackLink = (int) readSingleField(INPUT_TYPE_URL, usLine);
    sWebsiteWorth = (int) readSingleField(INPUT_TYPE_URL, usLine);
    
    printf("%s_%s_%d_%d_%d_%d\n", sUrl, sCompany, sDailyPageView, sRankTraffic, sBackLink,
           sWebsiteWorth);
    
    return curWebsite;
}