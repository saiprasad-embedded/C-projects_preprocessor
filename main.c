#include <stdio.h>
#include <string.h>
#include "preprocessor.h"

void copy_file(char *source, char *destination)
{
    FILE *fp1, *fp2;
    int ch;
    fp1=fopen(source, "r");
    fp2=fopen(destination, "w");
    if (fp1==NULL || fp2==NULL)
    {
        printf("File opening error\n");
        return;
    }
    while((ch=fgetc(fp1))!=EOF)
        fputc(ch, fp2);

    fclose(fp1);
    fclose(fp2);
}

int main(int argc, char *argv[])
{
    char output[500];
    char temp[]="temp_input.c";
    char *dot;
    if(argc!=2)
    {
        printf("Usage: ./mypreprocessor inputfile.c\n");
        return 1;
    }

    dot=strrchr(argv[1], '.');
    if(dot!=NULL && strchr(dot, '/')==NULL)
    {
        strcpy(output, argv[1]);
        dot=strrchr(output, '.');
        strcpy(dot, ".i");
    }
    else
    {
        strcpy(output, argv[1]);
        strcat(output, ".i");
    }
    copy_file(argv[1], temp);
    remove_comments(temp);
    process_includes(temp);
    process_macros(temp);
    copy_file(temp, output);
    remove(temp);
    printf("Preprocessing completed successfully!\n");
    printf("Output file: %s\n", output);
    return 0;
}