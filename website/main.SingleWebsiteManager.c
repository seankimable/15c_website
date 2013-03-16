/*
 * main.InputManager.c
 */
#include "main.header.h"

//project.main.SingleWebsiteManager.PRIVATE_FUNCTION_DECLARATIONS
static char* _readOneLine(FILE* fPtr);
static void* _readSingleField(input_type type, char **line);

Website* SingleWebsiteManager(FILE* fPtr) {
	Website* curWebsite = NULL;            // current `struct Website`
	char *sUrl;
	char *sCompany;
	char *sDailyPageView;
	char *sRankTraffic;
	char *sBackLink;
	char *sWebsiteWorth;
	bool bContinue = true;
	/*
	 * `char *usLine;`
	 * unsafe single line read
	 * (may not represent original value)
	 */
	char *usLine = NULL;
	char *sLine = NULL;              // safe single line read
    
	MALLOC(curWebsite);
	usLine = readOneLine(fPtr);
    
	if (NULL == usLine) { /* reached: EOF of input file */
		return NULL;
	} else {
		sLine = usLine;
	}
    
	// set: fields in `curWebsite`
    
	sUrl = (char*) readSingleField(INPUT_TYPE_URL, &usLine);
	sCompany = (char*) readSingleField(INPUT_TYPE_URL, &usLine);
	sDailyPageView = (char*) readSingleField(INPUT_TYPE_URL, &usLine);
	sRankTraffic = (char*) readSingleField(INPUT_TYPE_URL, &usLine);
	sBackLink = (char*) readSingleField(INPUT_TYPE_URL, &usLine);
	sWebsiteWorth = (char*) readSingleField(INPUT_TYPE_URL, &usLine);
    
	while (bContinue && NULL != sUrl && NULL != sCompany
           && NULL != sDailyPageView && NULL != sRankTraffic
           && NULL != sBackLink && NULL != sWebsiteWorth) {
		curWebsite->url = sUrl;
        
		curWebsite->company = sCompany;
		curWebsite->dailyPageViewThousands = atoi(sDailyPageView);
		curWebsite->rankTraffic = atoi(sRankTraffic);
		curWebsite->backLinkThousands = atoi(sBackLink);
		curWebsite->websiteWorthThousands = atoi(sWebsiteWorth);
		free(sDailyPageView);
		free(sRankTraffic);
		free(sBackLink);
		free(sWebsiteWorth);
		bContinue = false;
	}
    
	free(sLine);
    
	// debug: print `curWebsite`
	printf(HR);
	printf("`curWebsite` fields:\n");
	printf("%s\n%s\n%d\n%d\n%d\n%d\n", curWebsite->url, curWebsite->company,
           curWebsite->dailyPageViewThousands, curWebsite->rankTraffic,
           curWebsite->backLinkThousands, curWebsite->websiteWorthThousands);
	printf(HR);
	return curWebsite;
}

static char* _readOneLine(FILE* fPtr) {
	int numCharRead = 0;                    // number of characters read
	char usBuffer[MAX_LENGTH_INPUT];        // unsafe buffer  string
	char *sBuffer;                           // safe buffer string
    
	// read: until linebreak or EOF is read
	usBuffer[numCharRead] = fgetc(fPtr);
	if (EOF != usBuffer[numCharRead]) {
		while ('\n' != usBuffer[numCharRead]) {
			numCharRead++;
			usBuffer[numCharRead] = fgetc(fPtr);
		}
	} else {
		return NULL; // reached EOF
	}
    
	// exclude: delimiter from bufferString
	usBuffer[numCharRead] = '\0';
    
	// dynamically allocate: bufferString
	sBuffer = malloc(strlen(usBuffer) + 1);
	if (!sBuffer) {
        exit(EXIT_NOT_ENOUGH_MEMORY);
    }
    
    // copy: unsafe buffer to safe buffer
    strcpy(sBuffer, usBuffer);
	return sBuffer;
}


static void* _readSingleField(input_type type, char **line) {
    char *usField;        // unsafe field string (processed from `line`)
    char *loc;
    int i;
    
    MALLOC(usField);
    // locate: delimiter
    loc = strchr(*line, DELIMITER_SEMICOLON);
    
    for(i = 0; i < loc - *line; i++) {
        usField[i] = (*line)[i];
    }
    
    *line = loc + 1;
    
    if (INPUT_VALUE_VALID == ValidateManager(type, usField)) {
        return usField;
    } else {
        // free: invalid field read
        free(usField);
        return NULL;
    }
}


