//
//  main.c
//  website
//
//  Created by Anonymous on 3/3/13.
//  Copyright (c) 2013 Anonymous. All ritghts reserved.
//

#include <stdio.h>
#include "main.inputManager.header.h"

int main(int argc, const char * argv[])
{
    Website *curWebsite;
    FILE *fPtr;
    
    printf("Hello, World!\n");
    fPtr = LastSessionManager();
    
    do {
     curWebsite = SingleWebsiteManager();
        // call: Hash
        // call: BST
    } while(0);
    return 0;
}


void exitOnUserRequest (const int *exitCode) {
    exit(exitCode);
}

int getUserSelection(input_type type, const char *msg) {
	char usInput[MAX_LENGTH_INPUT];
	int validKey = 0;
    
	do {
		printf("%s", msg);
		fgets(usInput, MAX_LENGTH_INPUT, stdin);
        
		// trim: '\n'
		usInput[strlen(usInput) - 1] = '\0';
        
		// validate: user input
		validKey = ValidateManager(type, usInput);
		if (INPUT_VALUE_QUIT == validKey) {
			exit(EXIT_ON_REQUEST);
		}
	} while (INPUT_VALUE_INVALID == validKey);
	return validKey;
}
