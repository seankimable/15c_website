#include "main.header.h"


// project.main.MenuManager.PRIVATE_FUNCTION_DECLARATIONS
static void _printMenu();
static menu_type _chooseMenu(void);


menu_type menuManager(void) {
	menu_type sMenuSelection; // safe menu selection
	
    printMenu();
	sMenuSelection = chooseMenu();
	return sMenuSelection;
}


/*  printMenu: This function prints menu options.
 *
 *  PRE:    none
 *  POST:   prints menu options
 *  RETURN: none
 *
 */
static void _printMenu() {
	int i;
    
	printf(HR);
	for (i = MENU_TYPE_ADD_DATA; i <= MENU_TYPE_SAVE_AND_QUIT; i++) {
		printf("%d.  %s\n", i, menu_msg[i]);
	}
	printf(HR);
    
	return;
}

/*  chooseMenu: This function prompts user to input menu selection
 *              from his or her keyboard and returns validated .
 *
 *  PRE:    none
 *  POST:   prompts user to input menu selection
 *  RETURN: sInput // safe user-input for menu selection
 *
 */
static menu_type _chooseMenu(void) {
	char usInput[MAX_LENGTH_INPUT + 1]; // unsafe user-input
	int sInput; // safe user-input
    
	do {
        sInput = getUserSelection(INPUT_TYPE_MENU, MSG_PROMPT_MENU_SELECTION);
	} while (INPUT_VALUE_INVALID == sInput ? printf(ERR_INVALID_INPUT) : 0);
	return sInput;
}