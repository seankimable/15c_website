#include "main.inputManager.header.h"

#define DELIMITER_URL "./"


int validateInput(input_type type, char* usInput) {
	char usInputBuffer[MAX_LENGTH_INPUT];
    int (*validate)(char *usBuffer);
    int len = 0;
    int i = 0;
    
    // set: unsafe input buffer string
    if (NULL== usInput) {
        V("usInput is null\n");
    }
    strcpy(usInputBuffer, usInput);
    len = strlen(usInput);
    for (i = 0; i < len; i++) {
        usInputBuffer[i] = toupper(usInputBuffer[i]);
    }
    
    // set: validate with its given type
	switch (type) {
        case INPUT_TYPE_URL:
            validate = _valUrl;
            break;
        case INPUT_TYPE_COMPANY:
            validate = _valCompany;
            break;
        case INPUT_TYPE_DAILY_PAGE_VIEW:
        case INPUT_TYPE_RANK_TRAFFIC:
        case INPUT_TYPE_BACK_LINK:
        case INPUT_TYPE_WEBSITE_WORTH:
            validate = _valLongLongInt;
            break;
        case INPUT_TYPE_FILENAME:
            validate = _valFilename;
            break;
        case INPUT_TYPE_EXIT_ON_INVALID_FIELD:
            validate = _valExitOnInvalidField;
            break;
        case INPUT_TYPE_RECONFIRM:
        case INPUT_TYPE_DISCARD:
            validate = _valYesOrNo;
            break;
	}
    
    return validate(usInputBuffer);
}

int _valFilename(char *usInput) {
    int i = 0;
    int len = 0;
    
    len = strlen(usInput);
    
    for (i = 0;
         (isalnum(usInput[i])
          || '.' == usInput[i]) // FIXME: replace with DELIMITER_URL
         && len > i; i++)
        ;
    
    return len == i ? INPUT_VALUE_VALID : INPUT_VALUE_INVALID;
}

int _valUrl(char *usInput) {
    int i = 0;
    int len = 0;
    char *delimiter;
    
    delimiter = DELIMITER_URL;
    len = strlen(usInput);
    
    for (i = 0; (isalnum(usInput[i]) || '.' == usInput[i]) && len > i; i++)
        ;
    
    return len == i ? INPUT_VALUE_VALID : INPUT_VALUE_INVALID;
}

int _valCompany(char *usInput) {
    int i = 0;
    int len = 0;
    
    len = strlen(usInput);
    
    for (i = 0; (isnumber(usInput[i]) || isspecial(usInput[i])) && len > i; i++)
        ;
    
    return len == i ? INPUT_VALUE_VALID : INPUT_VALUE_INVALID;
}

int _valLongLongInt(char *usInput) {
    int i = 0;
    int len = 0;
    
    len = strlen(usInput);
    
    for (i = 0; isnumber(usInput[i]) && len > i; i++)
        ;
    
    return len == i ? INPUT_VALUE_VALID : INPUT_VALUE_INVALID;
}

int _valExitOnInvalidField(char *usInput) {
    if ('\0' != usInput[1]) {
        return INPUT_VALUE_INVALID;
    }

    switch (usInput[0]) {
        case ('Q'):
            return INPUT_VALUE_QUIT;
            break;
        case ('I'):
            return INPUT_VALUE_IGNORE;
            break;
        case ('A'):
            return INPUT_VALUE_IGNORE_ALL;
            break;
        default:
            return INPUT_VALUE_INVALID;
    }
}

int _valYesOrNo(char *usInput) {
    if ('\0' != usInput[1]) {
        return INPUT_VALUE_INVALID;
    }
    
    switch (usInput[0]) {
        case ('Q'):
            return INPUT_VALUE_QUIT;
            break;
        case ('Y'):
            return INPUT_VALUE_YES;
            break;
        case ('N'):
            return INPUT_VALUE_NO;
            break;
        default:
            return INPUT_VALUE_INVALID;
    }
}