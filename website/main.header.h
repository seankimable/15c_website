#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <strings.h>
#include <limits.h>
// constant.enum

typedef enum {
    INPUT_VALUE_INVALID = -1,           /* -1 */
    INPUT_VALUE_NO,                     /*  0 */
    INPUT_VALUE_YES,                    /*  1 */
    INPUT_VALUE_VALID,                  /*  2 */
    INPUT_VALUE_IGNORE,                 /*  3 */
    INPUT_VALUE_IGNORE_ALL,             /*  4 */
    INPUT_VALUE_QUIT                    /*  5 */
} input_value;

typedef enum {
	INPUT_TYPE_URL = 2001,              /* 2001 */
	INPUT_TYPE_COMPANY,                 /* 2002 */
	INPUT_TYPE_DAILY_PAGE_VIEW,         /* 2003 */
	INPUT_TYPE_RANK_TRAFFIC,            /* 2004 */
	INPUT_TYPE_BACK_LINK,               /* 2005 */
	INPUT_TYPE_WEBSITE_WORTH,           /* 2006 */
    
	INPUT_TYPE_FILENAME = 3001,         /* 3001 */
	INPUT_TYPE_EXIT_ON_INVALID_FIELD,   /* 3002 */
	INPUT_TYPE_RECONFIRM,               /* 3003 */
    INPUT_TYPE_DISCARD,                 /* 3004 */
    
    INPUT_TYPE_MENU = 4001              /* 4001 */
} input_type;

typedef enum {
    MENU_TYPE_ADD_DATA = 1,             /* 1 */
    MENU_TYPE_DELETE_DATA,              /* 2 */
    MENU_TYPE_FIND_KEY,                 /* 3 */
    MENU_TYPE_PRINT_HASH,               /* 4 */
    MENU_TYPE_PRINT_SORTED_SEQUENCE,    /* 5 */
    MENU_TYPE_PRINT_INDENTED_TREE,      /* 6 */
    MENU_TYPE_SAVE,                     /* 7 */
    MENU_TYPE_PRINT_EFFICIENCY,         /* 8 */
    MENU_TYPE_SAVE_AND_QUIT             /* 9 */
} menu_type;

// constant.string
const char* menu_msg[] = { /* captions for each menu option */
    /* 0 */"DUMMY MENU MESSAGE", // TODO: explain why dummy menu exists (for UI)
    /* 1 */"Add: new Website",
    /* 2 */"Delete: Website",
    /* 3 */"Search and Print: Website using its URL",
    /* 4 */"Print: List of Websites in hash table sequence",
    /* 5 */"Print: List of Websites in key sequence (sorted)",
    /* 6 */"Print: List of Websites in indented tree",
    /* 7 */"Save: Modified Website info to a file"
    /* 8 */"Print: Efficiency statistics"
};

// project.main.CONSTANT_DEFINED
#define FILEMODE_READONLY                       "r"
#define HR  "================================================\n"
#define BR  "\n"
#define MSG_EXIT_SELECTION "Enter \"I\" to ignore once, \"A\" to ignore all, or \"Q\" to quit program\n"
#define FLUSH while (getchar() != '\n');

#define MAX_LENGTH_INPUT                        255
#define MAX_LENGTH_DOB                          8
#define MAX_LENGTH_ID                           3
#define MAX_NUMBER_PERSON                       100
#define EXIT_NOT_ENOUGH_MEMORY                  101
#define EXIT_FILE_NOT_OPENED                    102
#define EXIT_FILE_NOT_CLOSED                    103
#define EXIT_ON_REQUEST                         104

#define ERR_NOT_ENOUGH_MEMORY                  ">>>ERROR : Not enough memory.\n"
#define ERR_FILE_NOT_OPENED                    ">>>ERROR : File could not be opened.\n"
#define ERR_FILE_NOT_CLOSED                    ">>>ERROR : File could not be closed.\n"
#define ERR_INVALID_INPUT                      ">>>ERROR : Invalid input. Please try again.\n"
#define WARN_ID_NOT_FOUND(type)                 ">>WARNING: %s is not found.\n", type
#define WARN_DUPLICATE_HOBBY(name)              ">>WARNING: Unable to add duplicated hobby \"%s\".\n", name
#define WARN_DUPLICATE_ID(name)                 ">>WARNING: Unable to add duplicated id \"%s\".\n", name
#define WARN_HOBBY_NOT_FOUND(hobby)             ">>WARNING: \"%s\" is not found from hobby list.\n", hobby
#define VERB_LAST_SESSION_FOUND                 ">VERBOSE:  Last session was not saved.\n"
#define VERB_LAST_SESSION_DISCARDED             ">VERBOSE:  Last session was discarded.\n"


#define MSG_PROMPT_EXIT_ON_INVALID_FIELD        "Invalid field has been read. Enter your selection\n"
#define MSG_PROMPT_DISCARD                      "Discard last session(Y/N)? Enter \"Y\" to discard or \"N\" to load last session.\n"
#define MSG_PROMPT_RECONFIRM                    "Are you sure?\n"
#define MSG_PROMPT_MENU_SELECTION               "Choose menu (1-9): "


#define USERINPUT_QUIT                          "QUIT"
#define DELIMITER_SPACE                         ' '
#define DELIMITER_SEMICOLON                     ';'
#define DELIMITER_NEWLINE                       '\n'
#define DELIMITER_SLASH                         '/'
#define PREFIX_BACKUP_FILENAME                  ".bac"
#define MALLOC(param)                 if (!(param = malloc(sizeof(*param)))) {\
printf(ERR_NOT_ENOUGH_MEMORY);\
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

//project.main
void exitOnUserRequest (const int *exitCode);

//project.main.managers
Website* InputManager(FILE *fPtr);

menu_type menuManager(void);
FILE* LastSessionManager (void);
int ValidateManager(input_type type, char* usInput);

//project.main.managers.menuManager

//project.main.managers.inputManager.getValue
int getUserSelection(input_type type, const char *msg);


Website* SingleWebsiteManager(FILE* fPtr);


