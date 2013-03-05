//Group 6: Header File

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <strings.h>
// constant.enum
typedef enum {
	INPUT_TYPE_URL = 101,
	INPUT_TYPE_COMPANY,
	INPUT_TYPE_DAILY_PAGE_VIEW,
	INPUT_TYPE_RANK_TRAFFIC,
	INPUT_TYPE_BACK_LINK,
	INPUT_TYPE_WEBSITE_WORTH,
    
	INPUT_TYPE_FILENAME = 201,
	INPUT_TYPE_EXIT_ON_INVALID_FIELD,
	INPUT_TYPE_RECONFIRM,
    INPUT_TYPE_DISCARD
} input_type;

typedef enum {
    INPUT_VALUE_INVALID = -1,
    INPUT_VALUE_NO = 0,
    INPUT_VALUE_YES = 1,
    INPUT_VALUE_VALID = 2,
    INPUT_VALUE_IGNORE = 3,
    INPUT_VALUE_IGNORE_ALL = 4,
    INPUT_VALUE_QUIT = 5
} input_value;

// constant.defined.debug
#define DEBUG true
#define VS(str,value) if(DEBUG) printf(str, value);
#define V(str) if(DEBUG) printf(str);

// constant.defined
#define HR  "================================================\n"
#define BR  "\n"
#define MSG_EXIT_SELECTION "Enter \"I\" to ignore once, \"A\" to ignore all, or \"Q\" to quit program\n"
#define FLUSH while (getchar() != '\n');
#define FILENAME_SOURCE                 "hobbies.txt"
#define FILEMODE_READONLY               "r"
#define MAX_LENGTH_INPUT                255
#define MAX_LENGTH_DOB                  8
#define MAX_LENGTH_ID                   3
#define MAX_NUMBER_PERSON               100
#define EXIT_NOT_ENOUGH_MEMORY          101
#define EXIT_FILE_NOT_OPENED            102
#define EXIT_FILE_NOT_CLOSED            103
#define EXIT_ON_REQUEST                 104

#define ERRR_COULD_NOT_OPEN_FILE(filename)      ">>>ERROR : Could not open file, \"%s\".\n", filename
#define ERRR_NOT_ENOUGH_MEMORY                  ">>>ERROR : Not enough memory.\n"
#define ERRR_FILE_NOT_OPENED                    ">>>ERROR : File could not be opened.\n"
#define ERRR_FILE_NOT_CLOSED                    ">>>ERROR : File could not be closed.\n"
#define ERRR_INVALID_INPUT                      ">>>ERROR : Invalid input. Please try again.\n"
#define WARN_ID_NOT_FOUND(type)                 ">>WARNING: %s is not found.\n", type
#define WARN_DUPLICATE_HOBBY(name)              ">>WARNING: Unable to add duplicated hobby \"%s\".\n", name
#define WARN_DUPLICATE_ID(name)                 ">>WARNING: Unable to add duplicated id \"%s\".\n", name
#define WARN_HOBBY_NOT_FOUND(hobby)             ">>WARNING: \"%s\" is not found from hobby list.\n", hobby
#define VERB_LAST_SESSION_FOUND                 ">VERBOSE:  Last session was not saved.\n"
#define VERB_LAST_SESSION_DISCARDED             ">VERBOSE:  Last session was discarded.\n"
#define VERB_FILEOPEN(name, mode)               ">VERBOSE:  File \"%s\" is opened for %s mode.\n", name, mode 

#define MSG_PROMPT_FILENAME             "Please enter filename: "
#define MSG_PROMPT_EXIT_ON_INVALID_FIELD   "Invalid field has been read. Enter your selection\n"
#define MSG_PROMPT_DISCARD              "Discard last session(Y/N)? Enter \"Y\" to discard or \"N\" to load last session.\n"
#define MSG_PROMPT_RECONFIRM            "Are you sure?\n"

#define USERINPUT_QUIT                  "QUIT"
#define DELIMITER_SPACE                 ' '
#define DELIMITER_SEMICOLON             ';'
#define DELIMITER_NEWLINE               '\n'
#define DELIMITER_SLASH                 '/'
#define PREFIX_BACKUP_FILENAME          ".bac"
#define MALLOC(param)                 if (!(param = malloc(sizeof(*param)))) {\
printf(ERRR_NOT_ENOUGH_MEMORY);\
exit(EXIT_NOT_ENOUGH_MEMORY);\
}

typedef struct
{
    char *url;  //primary key
    char *company;
    int dailyPageViewThousands;
    int rankTraffic;
    int backLinkThousands;
    int websiteWorthThousands;
} Website;

typedef struct _hashNode
{
    char *key;
    Website *site;
} HashNode;

typedef struct _bstNode
{
    struct _bstNode *left;
    char *key;
    Website *site;
    struct _bstNode *right;
} BstNode;

typedef struct
{
    int count;
    int arySize;
    int bucketSize;
    HashNode *pHash;
    BstNode *pTree;
} ListHead;

//project.main.managers
Website* inputManager(void);

//project.main.managers.inputManager
FILE* getLastSessionStatus(char *sInFilename);


bool confirmUserSelection(void);
//void getLastSessionStatus(void);
bool promptDiscardLastSession(void);
Website* getValidatedInput(FILE* fPtr);
char* readSingleLine(FILE* fPtr);
char* parseSingleField(char* line);
bool promptExit(void);

int getUserSelection(input_type type, const char *msg);
char* getFilename(input_type type, const char *msg);
char* readOneLine(FILE* fPtr);
void* readSingleField(input_type type, char **line);

//project.main.managers.inputManager.validate
int validateInput(input_type type, char* usInput);
int _valFilename(char *usInput);
int _valUrl(char *usInput);
int _valCompany(char *usInput);
int _valLongLongInt(char *usInput);
int _valExitOnInvalidField(char *usInput);
int _valYesOrNo(char *usInput);
