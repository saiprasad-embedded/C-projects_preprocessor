#include <stdio.h>
#include <string.h>
#include "preprocessor.h"

void copy_includes(FILE *fp, FILE *out, int depth)
{
    char line[2000];
    char name[500];
    char *p;
    FILE *header;
    int i;
    if (depth>20)
        return;

    while(fgets(line, sizeof(line), fp))
    {
        if(strncmp(line, "#include", 8) == 0)
        {
            // Check for user-defined header
            p=strchr(line, '"');

            if (p!=NULL)
            {
                p++;
                i=0;

                while (p[i] && p[i] != '"' && i < 499)
                {
                    name[i] = p[i];
                    i++;
                }

                name[i]='\0';
                header=fopen(name, "r");
                if (header!=NULL)
                {
                    copy_includes(header, out, depth + 1);
                    fclose(header);
                }
                else
                {
                    printf("Header file not found: %s\n", name);
                }
            }
            else
            {
                // Keep system header unchanged
                fputs(line, out);
            }
        }
        else
        {
            fputs(line, out);
        }
    }
}

void process_includes(char *filename)
{
    FILE *fp, *temp;
    fp=fopen(filename, "r");
    temp=fopen("temp2.txt", "w");

    if (fp==NULL || temp==NULL)
    {
        printf("Include file error\n");
        return;
    }

    copy_includes(fp, temp, 0);
    fclose(fp);
    fclose(temp);
    remove(filename);
    rename("temp2.txt", filename);
}