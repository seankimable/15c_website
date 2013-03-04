//
//  main.inputManager.getValue.readField.c
//  website
//
//  Created by Anonymous on 3/4/13.
//  Copyright (c) 2013 Anonymous. All rights reserved.
//

#include "header.h"
char* readOneLine(FILE* fPtr) {
	int numCharRead = 0;                    // number of characters read
	char usBuffer[MAX_LENGTH_INPUT];        // unsafe buffer  string
	char *sBuffer;                           // safe buffer string
	char *pBufferString;                    // pointer to buffer string
    
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
	usBuffer[numCharRead - 1] = '\0';
    
	// dynamically allocate: bufferString
	sBuffer = malloc(strlen(usBuffer) + 1);
	if (!sBuffer) {
        exit(EXIT_NOT_ENOUGH_MEMORY);
    }
    
    // copy: unsafe buffer to safe buffer
    strcpy(sBuffer, usBuffer);
	return sBuffer;
}


void* readSingleField(input_type type, char *line) {
    char *usField;        // unsafe field string (processed from `line`)
    char *loc;
    int i;
    
    loc = strchr(line,';');
    
    VS("readSingleField.line: %s\n", line);
    
    MALLOC(usField);
    
    for(i = 0; i < loc - line; i++) {
        usField[i] = line[i];
    }
    
    line = loc;
    VS("readSingleField.usField:_%s_\n", usField);
    
    return INPUT_VALUE_VALID == validateInput(type, usField) ? usField : NULL;
}

