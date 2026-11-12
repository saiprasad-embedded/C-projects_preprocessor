#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "preprocessor.h"
#define MAX_MACROS 100
char names[MAX_MACROS][100];
char values[MAX_MACROS][500];
char params[MAX_MACROS][100];
int types[MAX_MACROS];
int count=0;

void add_macro(char *line)
{
    char name[100], value[500], param[100];
    char *p;
    int i=0, j=0;
    if(sscanf(line, "#define %99s", name)!=1)
        return;
    if(count >= MAX_MACROS)
        return;
    if(name[0]=='\0')
        return;
    while(name[i] && name[i] != '(')
        i++;
    if(name[i]=='(')
    {
        name[i]='\0';
        i++;
        while(name[i] && name[i] != ')' && j < 99)
            param[j++] = name[i++];

        param[j]='\0';
        p=strchr(line, ')');
        if(p==NULL)
            return;
        p++;
        while(*p==' ' || *p=='\t')
            p++;
        snprintf(value, sizeof(value), "%s", p);
        types[count] = 1;
        strcpy(params[count], param);
    }
    else
    {
        p = line + 8;
        while(*p == ' ' || *p == '\t')
            p++;
        p+=strlen(name);
        while(*p == ' ' || *p == '\t')
            p++;

        snprintf(value, sizeof(value), "%s", p);
        types[count]=0;
        params[count][0]='\0';
    }
    value[strcspn(value, "\n")] = '\0';
    strcpy(names[count], name);
    strcpy(values[count], value);
    count++;
}
// Replace function macro parameter
void replace_param(char *value, char *param, char *arg, char *result)
{
    int i=0, j=0;
    int len=strlen(param);
    while (value[i] && j < 1900)
    {
        if (len > 0 && strncmp(value + i, param, len)==0 && (i == 0 || !(isalnum((unsigned char)value[i-1]) ||value[i-1] == '_')) && !(isalnum((unsigned char)value[i+len]) || value[i+len] == '_'))
        {
            int k=0;
            while(arg[k] && j < 1900)
                result[j++]=arg[k++];
            i+=len;
        }
        else
        {
            result[j++]=value[i++];
        }
    }
    result[j]='\0';
}

// Substitute macros in a line
void substitute(char *line, FILE *out)
{
    char result[2000], word[100], arg[500];
    char temp[2000];
    int i,j,k,m;
    strcpy(temp, line);
    for (m=0; m<count; m++)
    {
        result[0] = '\0';
        i=0;
        j=0;
        while (temp[i] && j < 1900)
        {
            if (isalpha((unsigned char)temp[i]) || temp[i] == '_')
            {
                k=0;
                while ((isalnum((unsigned char)temp[i]) || temp[i] == '_') && k < 99)
                {
                    word[k++]=temp[i++];
                }
                word[k]='\0';
                if(strcmp(word, names[m])==0)
                {
                    if(types[m] == 0)
                    {
                        k=0;
                        while(values[m][k] && j < 1900)
                            result[j++]=values[m][k++];
                    }
                    else
                    {
                        int start=i;
                        while(temp[i] == ' ' || temp[i] == '\t')
                            i++;
                        if(temp[i] == '(')
                        {
                            i++;
                            k=0;
                            while(temp[i] && temp[i] != ')' && k < 499)
                                arg[k++] = temp[i++];
                            arg[k]='\0';
                            if(temp[i] == ')')
                            {
                                i++;
                                replace_param(values[m],params[m],arg, result + j);
                                j+=strlen(result + j);
                            }
                            else
                            {
                                result[j++] = '(';
                            }
                        }
                        else
                        {
                            i=start;
                            k=0;
                            while(word[k] && j < 1900)
                                result[j++]=word[k++];
                        }
                    }
                }
                else
                {
                    k=0;
                    while (word[k] && j < 1900)
                        result[j++]=word[k++];
                }
            }
            else
            {
                result[j++]=temp[i++];
            }
        }
        result[j]='\0';
        strcpy(temp, result);
    }
    fputs(temp, out);
}

void process_macros(char *filename)
{
    FILE *fp, *temp;
    char line[2000];
    fp=fopen(filename, "r");
    temp=fopen("temp3.txt", "w");
    if(fp==NULL || temp==NULL)
    {
        printf("Macro file error\n");
        return;
    }
    count=0;
    while(fgets(line, sizeof(line), fp))
    {
        if (strncmp(line, "#define", 7) == 0 && (line[7] == ' ' || line[7] == '\t'))
        {
            add_macro(line);
        }
        else
        {
            substitute(line, temp);
        }
    }
    fclose(fp);
    fclose(temp);
    remove(filename);
    rename("temp3.txt", filename);
}