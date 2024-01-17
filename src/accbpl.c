#include "accbpl.h"

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>
#include <math.h>

int32_t accumulator=0;

void accbpl(int argc, char** argv) {
	if(argc==1) {
		printf("Entering REPL mode.\n");
		repl();
	}
	else if(argc==2) {
		interpretFile(argv[1]);
	}
	else {
		printf("Invalid command line arguments.\n");
		printf("Run 'accbpl' with no arguments for REPL mode.\n");
		printf("Or run 'accbpl filename.accbpl' to interpret the file.\n");
	}
}

void repl() {
	char inputChar;
	while(true) {
		inputChar=getchar();
		executeInstruction(inputChar);
	}
}

void interpretFile(char* fileName) {
	char inputChar;
	FILE *inFile=fopen(fileName, "r");
	if(inFile==NULL) {
		printf("Error: Cannot open file %s\n", fileName);
		return;
	}
	while((inputChar=fgetc(inFile))!=EOF) {
		executeInstruction(inputChar);
	}
}

void executeInstruction(char instruction) {
	if(instruction=='i') {
		accumulator++;
	}
	else if(instruction=='d') {
		accumulator--;
	}
	else if(instruction=='s') {
		accumulator*=accumulator;
	}
	else if(instruction=='r') {
		accumulator=(int32_t)floor(sqrt(accumulator));
	}
	else if(instruction=='o') {
		printf("%" PRId32, accumulator);
	}
	else if(instruction=='c') {
		printf("%c", (char)accumulator);
	}
}