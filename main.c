/*
main

Author: Jason Dominguez
Date: 2023-02-09
*/

#include <stdio.h>
#include <stdlib.h>

void parse(char ch, FILE **pFile, char **ptr);
void iterate(FILE **pFile, char **ptr);

int main() {
    FILE *pFile;

    pFile = fopen("helloworld.bf", "r");

    if (pFile == NULL)
    {
        printf("File is not available.\n");
        return -1;
    }

    char ch;
    char array[20] = {0};
    char *ptr = array;
    while ((ch = fgetc(pFile)) != EOF)
    {
        parse(ch, &pFile, &ptr);
    }
    
    fclose(pFile);

    return 0;
}

void parse(char ch, FILE **pFile, char **ptr) {
    switch (ch)
    {
    case '>': ++*ptr; break;
    case '<': --*ptr; break;
    case '+': ++**ptr; break;
    case '-': --**ptr; break;
    case '.': putchar(**ptr); break;
    case ',': **ptr = getchar(); break;
    case '[': iterate(&*pFile, &*ptr); break;
    default: break;
    }
}

void iterate(FILE **pFile, char **ptr) {
    while (**ptr != 0)
    {
        int numIters = 0;
        char ch = fgetc(*pFile);
        while (ch != ']')
        {
            parse(ch, &*pFile, &*ptr);

            ch = fgetc(*pFile);
            ++numIters;
        }
        if (**ptr != 0) {
            fseek(*pFile, -(numIters + 1), SEEK_CUR);
        }
    }
}