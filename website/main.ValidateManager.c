#include "main.header.h"

// project.main.fileManager.CONSTANT_DEFINED
#define DELIMITER_URL "./"
#define DELIMITER_DOT '.'
#define DELIMITER_ZERO '0'

#define INPUT_LENGTH_URL MAX_LENGTH_INPUT
#define INPUT_LENGTH_COMPANY MAX_LENGTH_INPUT
#define INPUT_LENGTH_DAILY_PAGE_VIEW INT_MAX
#define INPUT_LENGTH_RANK_TRAFFIC INT_MAX
#define INPUT_LENGTH_BACK_LINK INT_MAX
#define INPUT_LENGTH_WEBSITE_WORTH INT_MAX
#define INPUT_LENGTH_FILENAME MAX_LENGTH_INPUT
#define INPUT_LENGTH_EXIT_ON_INVALID_FIELD 1
#define INPUT_LENGTH_RECONFIRM 1
#define INPUT_LENGTH_DISCARD 1
#define INPUT_LENGTH_MENU 1
#define INPUT_LENGTH_EXIT_ON_INVALID_FIELD 1
#define INPUT_LENGTH_YES_OR_NO 1

#define INPUT_VALUE_QUIT_RAW 'Q'
#define INPUT_VALUE_IGNORE_RAW 'I'
#define INPUT_VALUE_IGNORE_ALL_RAW 'A'
#define INPUT_VALUE_YES_RAW 'Y'
#define INPUT_VALUE_NO_RAW 'N'

#define ERR_INVALID_INPUT_TYPE ">>>ERROR: Invalid input type.\n"

// project.main.fileManager.PRIVATE_FUNCTION_DECLARATIONS.fileInputValidation
static input_value _valFilename(char *usInput);
static input_value _valUrl(char *usInput);
static input_value _valCompany(char *usInput);
static input_value _valLongLongInt(char *usInput);

// project.main.fileManager.PRIVATE_FUNCTION_DECLARATIONS.userInputValidation
static input_value _valExitOnInvalidField(char *usInput);
static input_value _valYesOrNo(char *usInput);
static input_value _valMenuOption(char *usInput);

int ValidateManager(input_type type, char* usInput) {
	char usInputBuffer[MAX_LENGTH_INPUT];
	int (*validate)(char *usBuffer);
	int len = 0; // input length
	int i = 0;
    bool isLengthValid = false;
    
	// TODO: finish doc
	// pre-validate:
	if (NULL == usInput) {
		// usInput Error
	}
    
	strcpy(usInputBuffer, usInput);
	len = strlen(usInput);
	for (i = 0; i < len; i++) {
		usInputBuffer[i] = toupper(usInputBuffer[i]);
	}
    
	// set: validate with its given type
	switch (type) {
        case INPUT_TYPE_URL:
            isLengthValid = (INPUT_LENGTH_URL >= len); 
            validate = _valUrl;
           break;
        case INPUT_TYPE_COMPANY:
            isLengthValid = (INPUT_LENGTH_COMPANY >= len); 
            validate = _valCompany;
            break;
        case INPUT_TYPE_DAILY_PAGE_VIEW:
            isLengthValid = (INPUT_LENGTH_DAILY_PAGE_VIEW >= len); 
        case INPUT_TYPE_RANK_TRAFFIC:
            isLengthValid = (INPUT_LENGTH_RANK_TRAFFIC >= len); 
        case INPUT_TYPE_BACK_LINK:
            isLengthValid = (INPUT_LENGTH_BACK_LINK >= len); 
        case INPUT_TYPE_WEBSITE_WORTH:
            isLengthValid = (INPUT_LENGTH_WEBSITE_WORTH >= len); 
            validate = _valLongLongInt;
            break;
        case INPUT_TYPE_FILENAME:
            isLengthValid = (INPUT_LENGTH_FILENAME >= len); 
            validate = _valFilename;
            break;
        case INPUT_TYPE_EXIT_ON_INVALID_FIELD:
            isLengthValid = (INPUT_LENGTH_EXIT_ON_INVALID_FIELD == len);
            validate = _valExitOnInvalidField;
            break;
        case INPUT_TYPE_RECONFIRM:
            isLengthValid = (INPUT_LENGTH_RECONFIRM == len);
        case INPUT_TYPE_DISCARD:
            isLengthValid = (INPUT_LENGTH_DISCARD == len);
            validate = _valYesOrNo;
        case INPUT_TYPE_MENU:
            isLengthValid = (INPUT_LENGTH_MENU == len);
            validate = _valMenuOption;
            break;
	}
    
	return isLengthValid ? validate(usInputBuffer) : INPUT_VALUE_INVALID;
}

static input_value _valFilename(char *usInput) {
	int i = 0;
	int len = 0;
    
	len = strlen(usInput);
    
	while ((isalnum(usInput[i]) || DELIMITER_DOT == usInput[i]) // FIXME: replace with DELIMITER_URL
           && len > i) {
		i++;
	}
    
	return len == i ? INPUT_VALUE_VALID : INPUT_VALUE_INVALID;
}

static input_value _valUrl(char *usInput) {
	int i = 0;
	int len = 0;
    
	len = strlen(usInput);
    
	// TODO: convert to DELIMITER_URL
	while ((isalnum(usInput[i]) || DELIMITER_DOT == usInput[i]) && len > i) {
		i++;
	}
    
	return len == i ? INPUT_VALUE_VALID : INPUT_VALUE_INVALID;
}

static input_value _valCompany(char *usInput) {
	int i = 0;
	int len = 0;
    
	len = strlen(usInput);
    
	while ((isnumber(usInput[i]) || isspecial(usInput[i])) && len > i) {
		i++;
	}
    
	return len == i ? INPUT_VALUE_VALID : INPUT_VALUE_INVALID;
}

static input_value _valLongLongInt(char *usInput) {
	int i = 0;
	int len = 0;
    
	// validate: input length
	len = strlen(usInput);
    
	while (0 <= usInput[i] && isnumber(usInput[i]) && len > i) {
		i++;
	}
    
	return len == i ? INPUT_VALUE_VALID : INPUT_VALUE_INVALID;
}

static input_value _valExitOnInvalidField(char *usInput) {
	int len = 0;
    
	// validate: input length
	len = strlen(usInput);
	if (INPUT_LENGTH_EXIT_ON_INVALID_FIELD != len) {
		return INPUT_VALUE_INVALID;
	}
    
	switch (usInput[0]) {
        case (INPUT_VALUE_QUIT_RAW):
            return INPUT_VALUE_QUIT;
            break;
        case (INPUT_VALUE_IGNORE_RAW):
            return INPUT_VALUE_IGNORE;
            break;
        case (INPUT_VALUE_IGNORE_ALL_RAW):
            return INPUT_VALUE_IGNORE_ALL;
            break;
        default:
            return INPUT_VALUE_INVALID;
	}
}

static input_value _valYesOrNo(char *usInput) {
	int len = 0;
    
	switch (usInput[0]) {
        case (INPUT_VALUE_QUIT_RAW):
            return INPUT_VALUE_QUIT;
            break;
        case (INPUT_VALUE_YES_RAW):
            return INPUT_VALUE_YES;
            break;
        case (INPUT_VALUE_NO_RAW):
            return INPUT_VALUE_NO;
            break;
        default:
            return INPUT_VALUE_INVALID;
	}
}

static input_value _valMenuOption(char *usInput) {
	const int usMenu = usInput[0] - DELIMITER_ZERO;
	
	switch (usMenu) {
        case (INPUT_VALUE_QUIT_RAW):
            return INPUT_VALUE_QUIT;
        case MENU_TYPE_ADD_DATA:
        case MENU_TYPE_DELETE_DATA:
        case MENU_TYPE_FIND_KEY:
        case MENU_TYPE_PRINT_HASH:
        case MENU_TYPE_PRINT_SORTED_SEQUENCE:
        case MENU_TYPE_PRINT_INDENTED_TREE:
        case MENU_TYPE_SAVE:
        case MENU_TYPE_PRINT_EFFICIENCY:
        case MENU_TYPE_SAVE_AND_QUIT:
            return INPUT_VALUE_VALID;
            break;
        default:
            return INPUT_VALUE_INVALID;
            break;
	}
}
