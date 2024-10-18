#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <regex.h>
void find_patterns(FILE* f,const char* pattern){
    regex_t regex;
    regmatch_t pmatch[1];
    fseek(f,0,SEEK_END);
    long fsize = ftell(f);
    fseek(f,0,SEEK_SET);
    char* string =malloc(fsize+1);
    fread(string,fsize,1,f);
    string[fsize]='\0';
    if(regcomp(&regex,pattern,0)==0){
        while(regexec(&regex,string,1,pmatch,0)==0){
                if(pmatch[0].rm_so==-1){
                    continue;
                }
                size_t match_len=pmatch[0].rm_eo - pmatch[0].rm_so;
                char* match = malloc(match_len+1);
                strncpy(match,string+pmatch[0].rm_so,match_len);
                match[match_len]='\0';
                printf("%s\n",match);
                string+=pmatch[0].rm_eo;
                free(match);
        }
    }

}
int main(int argc,char* argv[]){
    if(argc==1){
        printf("no argument provided\n");
        return 0;
    }
    if(strcmp(argv[1],"-v")==0 ||strcmp(argv[1],"--version")==0){
        printf("version 1.0.0\n");
    }
    find_patterns(fopen("mygrep.c","rb"),"print");
    char* dir = malloc(100*sizeof( char));
    if(getcwd(dir,100)!=NULL){
        printf("%s",dir);
    }else{
        printf("something went wrong");
    }
    free(dir);
    return 1;
}
