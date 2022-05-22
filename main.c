#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Does not work for recently memory allocated string, with empty content.
// Because it does not contain the '\0'
int sizeOfString(char *string) {
    int size = 0;

    for (int i = 0; string[i] != '\0'; i++) {
        size++;
    }

    return size;
}

char *concatenate(char *firstString, char *secondString) {
    int size = sizeOfString(firstString) + sizeOfString(secondString);
    char *string = (char *) malloc(size * sizeof(char));
    int currentIndex = 0;
    int i, j;

    for (i = 0; i < size && firstString[i] != '\0'; i++) {
        string[i] = firstString[i];
        currentIndex++;
    }

    for (i = currentIndex, j = 0; i < size; i++, j++) {
        string[i] = secondString[j];
    }

   return string;
}

char *toUpperCase(char *string) {
    char *upperCase = (char *) malloc(sizeOfString(string) * sizeof(char));

    for (int i = 0; i < sizeOfString(string); i++) {
        if (string[i] >= 'a' && string[i] <= 'z') {
             upperCase[i] = string[i] - 32;
        } else {
            upperCase[i] = string[i];
        }  
    }

    return upperCase;
}

void jumpLine(FILE *file) {
    fprintf(file, "%s", "\n");
}

void createHeaderFile(char *filename) {
    char *object = concatenate(filename, ".h");
    char *ifndef = concatenate("#ifndef ", concatenate(toUpperCase(filename), "_H"));
    char *define = concatenate("#define ", concatenate(toUpperCase(filename), "_H"));

    FILE *file = fopen(object, "w");

    fprintf(file, "%s", ifndef);
    fprintf(file, "%s", "\n");
    fprintf(file, "%s", define);
    jumpLine(file);
    jumpLine(file);
    fprintf(file, "%s", "#endif");
} 

void createImplementationFile(char *fileName) {
    char *object = concatenate(fileName, ".c");
    char *mainFunction = "int main() {\n\n\treturn 0;\n}";
    char *headerLibrary = concatenate("#include ", concatenate(concatenate("\"", fileName), ".h\""));

    FILE *file = fopen(object, "w");

    fprintf(file, "%s", "#include <stdio.h>");
    jumpLine(file);
    fprintf(file, "%s", headerLibrary);
    jumpLine(file);
    jumpLine(file);
    fprintf(file, "%s", mainFunction);
}

void createFiles(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        createHeaderFile(argv[i]);
        createImplementationFile(argv[i]);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("No file names were provided\n");
        return 0;
    }

    createFiles(argc, argv);

    return 0;
}

