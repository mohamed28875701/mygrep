#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <regex.h>
void print_finds(regmatch_t* pmatch,char* string,regex_t regex){
    while(regexec(&regex,string,1,pmatch,0)==0){
        if(pmatch[0].rm_so==-1){
            continue;
        }
        size_t match_len=pmatch[0].rm_eo - pmatch[0].rm_so;
        char* match = malloc(match_len+1);
        strncpy(match,string+pmatch[0].rm_so,match_len);
        match[match_len]='\0';
        printf("\033[31m%s\033[0m",match);
        for(int i=pmatch[0].rm_eo;i!=strlen(string);i++){
            if(string[i]!='\n')
                printf("%c",string[i]);
            else{
                printf("\n");
                break;
            }
        }
            string+=pmatch[0].rm_eo;
        free(match);
    }
}
void find_patterns(FILE* f,const char* pattern){
    regex_t regex;
    regmatch_t pmatch[1];
    fseek(f,0,SEEK_END);
    long fsize = ftell(f);
    fseek(f,0,SEEK_SET);
    char* string =malloc(fsize+1);
    fread(string,fsize,1,f);
    string[fsize]='\0';
    if(regcomp(&regex,pattern,REG_EXTENDED)==0){
        print_finds(pmatch,string,regex);
    }else{
        printf("Cant compile regex");
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
    if(argc == 3){
        FILE* f =fopen(argv[2],"rb");
        if(f!=NULL){
            find_patterns(fopen("mygrep.c","rb"),argv[1]);
        }else{
            printf("%s does not exist",argv[2]);
        }
    }
    /*char* dir = malloc(100*sizeof( char));
    if(getcwd(dir,100)!=NULL){
        printf("%s",dir);
    }else{
        printf("something went wrong");
    }
    free(dir);*/
    return 1;
}
