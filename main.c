#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdbool.h>
int main(void)
{  
    struct stat *stat_buf=calloc(1,sizeof(struct stat));
    if(stat_buf==NULL)
    {
        fprintf(stderr,"Error: Calloc returns NULL for stat_buf.\n");
        exit(EXIT_FAILURE);
    }
    if(stat("all.txt",stat_buf)!=0)
    {
        fprintf(stderr,"Error: stat function failure.\n");
        free(stat_buf);
        exit(EXIT_FAILURE);
    }
    stat("name_list.txt",stat_buf);
    int *data=calloc(stat_buf->st_size,sizeof(int));
    if(data==NULL)
    {
        fprintf(stderr,"Error: calloc returns NULL for data.\n");
        exit(EXIT_FAILURE);
    }
    FILE *fp=fopen("all.txt","r");
    if(fp==NULL)
    {
        fprintf(stderr,"ERROR: fp==NULL.\n");
        free(stat_buf);
        fclose(fp);
        exit(EXIT_FAILURE);
    }
    for(size_t i=0;i<stat_buf->st_size;i++)
    {
        *(data+i)=fgetc(fp);
    }
    char *all_lines=calloc(stat_buf->st_size,sizeof(char));
    if(all_lines==NULL)
    {
        fprintf(stderr,"ERROR: calloc returns NULL for all_lines.\n");
        free(stat_buf);
        fclose(fp);
        exit(EXIT_FAILURE);
    }
    for(size_t i=0;i<stat_buf->st_size;i++) // improve by filtering out lines that cointain (, ,@)
    {
        switch(*(data+i))
        {
            case EOF:
            {
                continue;
                break;
            }
            case ' ':
            {

                break;
            }
                 case '\t':
            {

                break;
            }
                 case '@':
            {

                break;
            }
                 case '(':
            {

                break;
            }
                 case ')':
            {

                break;
            }
            default:
            {
                *(all_lines+i)=*(data+i);
                break;
            }
        }
    }
    char *suffix_template="@bbex.com";
    for(size_t i=0;i<stat_buf->st_size;i++)
    {
        static size_t count=0;
        if(*(all_lines+i)!='\n')
        {
            continue;
        }
        else
        {
            char *temp=calloc(strlen(suffix_template)+i-count+2,sizeof(char)); // +3 for the '\n' and '\0' and the a-z
            if(temp==NULL)
            {
                fprintf(stderr,"ERROR: calloc returns NULL for temp.\n");
                exit(EXIT_FAILURE);
            }
            char *suffix=calloc(strlen(suffix_template)+2,sizeof(char));
            if(suffix==NULL)
            {
                fprintf(stderr,"ERROR: calloc returns NULL for suffix.\n");
                exit(EXIT_FAILURE);
            }
            for(size_t j=count,k=0;j<i-1;j++,k++)
            {
                *(temp+k)=*(all_lines+j);
            }
            strcpy(suffix,suffix_template);
            *(suffix +strlen(suffix_template))='\n';
            strcat(temp,suffix);
            for(int c='a';c<='z';c++)
            {
                printf("%c%s",c,temp);
            }
            free(suffix);
            free(temp);
            count=i+1;
        }     
    }
    fclose(fp);
    free(stat_buf);
    return 0;
}
