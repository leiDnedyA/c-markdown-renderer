#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_OUTPUT_FILENAME "out.md"
#define MAX_FILE_NAME_LENGTH 30

void printUsage() {
  printf("USAGE: render_markdown <input filename> <output filename>\n");
}

int main(int argc, char **argv) {
  char* inputFileName = (char*)malloc(sizeof(char)*MAX_FILE_NAME_LENGTH);
  char* outputFileName = (char*)malloc(sizeof(char)*MAX_FILE_NAME_LENGTH);

  if (argc < 3) {
    if (argc == 2 && !strcmp(argv[1], "-h")) {
      printUsage();
      return 1;
    }
    fprintf(stderr, "Incorrect usage. Run `render_markdown -h` to see proper usage.\n");
    return 1;
  } else {
    strcpy(inputFileName, argv[1]);
    strcpy(outputFileName, argv[2]);
  }

  // Scan
  FILE *inputFile = fopen(inputFileName, "r");

  if (inputFile == NULL) {
    fprintf(stderr, "ERROR: Could not find input file %s\n.", inputFileName);
    return 1;
  }

  char ch;
  while ((ch = fgetc(inputFile)) != EOF) {
    switch (ch) {
      case '\n':
      case '\r':
        break;
      case '#': {
        int headerNumber = 1;
        while ((ch = fgetc(inputFile)) == '#') {
          headerNumber++;
        }
        if (ch == EOF || ch == '\n' || ch == '\r') {
          printf("<h%d></h%d>\n", headerNumber, headerNumber);
          break;
        }
        char* headerText = (char*)malloc(sizeof(char)*100);
        size_t n = 0;
        while ((ch = fgetc(inputFile)) != EOF && ch != '\n' && ch != '\r') {
          headerText[n] = ch;
          n++;
        }
        printf("<h%d>%s</h%d>\n", headerNumber, headerText, headerNumber);
        free(headerText);
        break;
      }
      default: {
        char* text = (char*)malloc(sizeof(char)*300);
        size_t n = 0;
        text[n] = ch;
        while ((ch = fgetc(inputFile)) != EOF && ch != '\n' && ch != '\r') {
          n++;
          text[n] = ch;
        }
        printf("<p>%s</p>\n", text);
        free(text);
      }
    }
  }
  printf("\n");

  // Parse
  
  // Codegen
}
