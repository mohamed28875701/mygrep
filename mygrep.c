#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <regex.h>
void find_patterns(FILE* f,const char* pattern){
    regex_t regex;
    regmatch_t pmatch[100];
    fseek(f,0,SEEK_END);
    long fsize = ftell(f);
    fseek(f,0,SEEK_SET);
    char* string =malloc(fsize+1);
    fread(string,fsize,1,f);
    string[fsize]='\0';
    if(regcomp(&regex,pattern,0)==0){
        if(regexec(&regex,string,100,pmatch,0)==0){
            for(int i = 0;i!=100;i++){
                if(pmatch[i].rm_so==-1){
                    continue;
                }
                printf("match : %d",i);
                size_t match_len=pmatch[i].rm_eo - pmatch[i].rm_so;
                char* match = malloc(match_len+1);
                strncpy(match,string+pmatch[i].rm_so,match_len);
                match[match_len]='\0';
                printf("%s\n",match);
                free(match);
            }
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
