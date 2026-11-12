#include <stdio.h>
#include "preprocessor.h"

void remove_comments(char *filename)
{
    FILE *fp, *temp;
    int ch, next;
    int state=0;
    fp=fopen(filename, "r");
    temp=fopen("temp1.txt", "w");
    if (fp==NULL || temp==NULL)
    {
        printf("Comment removal file error\n");
        return;
    }

    while((ch=fgetc(fp))!=EOF)
    {
        if (state==0)
        {
            if (ch=='/')
            {
                next=fgetc(fp);
                if(next=='/')
                    state=1;
                else if (next=='*')
                    state=2;
                else
                {
                    fputc(ch, temp);

                    if (next!=EOF)
                        ungetc(next, fp);
                }
            }
            else if(ch=='"')
            {
                state=3;
                fputc(ch, temp);
            }
            else if(ch=='\'')
            {
                state=4;
                fputc(ch, temp);
            }
            else
                fputc(ch, temp);
        }
        else if(state==1)
        {
            if(ch=='\n')
            {
                fputc('\n', temp);
                state = 0;
            }
        }
        else if(state == 2)
        {
            if(ch=='\n')
                fputc('\n', temp);

            if(ch=='*')
            {
                next=fgetc(fp);

                if(next=='/')
                    state=0;
                else if(next!=EOF)
                    ungetc(next, fp);
            }
        }
        else if(state==3 || state==4)
        {
            fputc(ch, temp);

            if(ch=='\\')
            {
                next=fgetc(fp);
                if(next!=EOF)
                    fputc(next, temp);
            }
            else if((state==3 && ch=='"') || (state==4 && ch=='\''))
            {
                state=0;
            }
        }
    }
    fclose(fp);
    fclose(temp);
    remove(filename);
    rename("temp1.txt", filename);
}