#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

char buffer[1024];

void tail(int fileDescriptor, int linesToSubtract) {
    int bytesRead, i;
    int totalLines = 0;
    int linesRemaining = 0;
    char *fileBuffer;
    fileBuffer = (char*) malloc (500000);
    int bufferIndex = 0;

    while ((bytesRead = read(fileDescriptor, buffer, sizeof(buffer))) > 0) {
        for (i = 0; i < bytesRead; i++) {
            fileBuffer[bufferIndex] = (char) buffer[i];
            bufferIndex++;
            if (buffer[i] == '\n')
                totalLines++;
        }
    }

    if (bytesRead < 0) {
        printf(1, "Internal Error \n");
        exit();
    }

    if (totalLines < linesToSubtract)
        linesRemaining = 0;
    linesRemaining = totalLines - linesToSubtract;

    int lineCounter = 0;
    for (i = 0; i < bufferIndex; i++) {
        if (lineCounter >= linesRemaining)
            printf(1, "%c", fileBuffer[i]);
        if (fileBuffer[i] == '\n')
            lineCounter++;
    }

    free(fileBuffer);
}

int main(int argc, char *argv[]) {
    int inputNumber = 10, k, i;
    int fileDescriptor = -1;

    if (argc <= 1) {
        tail(0, inputNumber);
        exit();
    } else if (argc > 1 && argv[1][0] == '-') {
        char getInputNumber[10];
        for (k = 1; k < strlen(argv[1]); k++) {
            getInputNumber[k-1] = argv[1][k];
        }
        inputNumber = atoi(getInputNumber);
    } else {
        if ((fileDescriptor = open(argv[1], inputNumber)) < 0) {
            printf(1, "Unable to open the file: %s\n", argv[1]);
            exit();
        }
        tail(fileDescriptor, inputNumber);
        close(fileDescriptor);
    }

    if (argc > 2) {
        for (i = 2; i < argc; i++) {
            if ((fileDescriptor = open(argv[i], 0)) < 0) {
                printf(1, "Unable to open the file: %s\n", argv[i]);
                exit();
            } else {
                tail(fileDescriptor, inputNumber);
                close(fileDescriptor);
            }
        }
    }

    exit();
}
