#include "accbpl.h"

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>
#include <math.h>

static int32_t accumulator = 0;
static bool isRunning = false;

void accbpl(int argc, char** argv) {
	if(argc == 1) {
		printf("Entering REPL mode.\n");
		isRunning = true;
		repl();
	}
	else if(argc == 2) {
		isRunning = true;
		interpretFile(argv[1]);
	}
	else {
		printf("Invalid command line arguments.\n");
		printf("Run 'accbpl' with no arguments for REPL mode.\n");
		printf("Or run 'accbpl filename.accbpl' to interpret the file.\n");
	}
}

void repl() {
	int inputChar;
	while(isRunning) {
		inputChar = getchar();
		if(inputChar == EOF) {
			break;
		}
		executeInstruction((char)inputChar);
	}
}

void interpretFile(const char* fileName) {
	int inputChar;
	FILE *inFile = fopen(fileName, "r");
	if(inFile == NULL) {
		printf("Error: Cannot open file %s\n", fileName);
		return;
	}
	while(isRunning && ((inputChar = fgetc(inFile)) != EOF)) {
		executeInstruction((char)inputChar);
	}
	fclose(inFile);
}

void executeInstruction(char instruction) {
	if(instruction == 'q') {
		isRunning = false;
		return;
	}
	if(instruction == 'i') {
		accumulator++;
	}
	else if(instruction == 'd') {
		accumulator--;
	}
	else if(instruction == 's') {
		accumulator *= accumulator;
	}
	else if(instruction == 'r') {
		if(accumulator < 0) {
			printf("Error: Negative accumulator value for square root.\n");
			printf("Program will now terminate.\n");
			isRunning = false;
			return;
		}
		accumulator = (int32_t)floor(sqrt(accumulator));
	}
	else if(instruction == 'o') {
		printf("%" PRId32, accumulator);
	}
	else if(instruction == 'c') {
		printf("%c", (char)accumulator);
	}
	else if (instruction == 'g') {
		scanf("%" SCNd32, &accumulator);
	}
}
