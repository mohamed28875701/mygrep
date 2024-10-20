#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <regex.h>
void print_finds(regmatch_t* pmatch,char* string,regex_t regex){
    int c = 0;
    while(1){
        if(regexec(&regex,string,1,pmatch,0)==0){
            c=1;
            for(int i=0;i!=strlen(string);i++){
                if(i>=pmatch[0].rm_so && i<pmatch[0].rm_eo){
                    printf("\033[31m%c\033[0m",string[i]);
                    if(i==pmatch[0].rm_eo-1){
                        string+=pmatch[0].rm_eo;
                        break;
                    }

                }else{
                    printf("%c",string[i]);
                }
            }
        } else {
            if(c==1){
                printf("%s",string);
                break;
            }
            break;
        }
    }
}
void find_patterns(FILE* f,const char* pattern,int flags){
    regex_t regex;
    regmatch_t pmatch[1];

    char string[256];
    if(f!=NULL){
        while(fgets(string,sizeof(string),f)){
            if(regcomp(&regex,pattern,flags)==0){
                print_finds(pmatch,string,regex);
            }else{
                printf("Cant printf compile regex");
            }
        }
    }

}
int main(int argc,char* argv[]){
    if(argc==1){
        printf("no argument provided\n");
        return 0;
    }
    int args=0;
    int opt;
    while((opt=getopt(argc,argv,"vEn"))!=-1){
        if(opt=='v'){
            printf("version 1.0.0\n");
        }else if(opt=='E'){
            if(args==0){
                args=REG_EXTENDED;
            }
            else{
                args=args|REG_EXTENDED;
            }
        }else if(opt=='n'){
            if(args==0){
                args=REG_ICASE;
            }
            else{
                args=args|REG_ICASE;
            }
        }
        else if(opt=='?'){
            fprintf(stderr,"Unknown option %d\n",optopt);
        }
    }
    FILE* f =fopen(argv[argc-1],"rb");
    if(f!=NULL){
        find_patterns(f,argv[argc-2],args);
    }else{
        printf("%s does not exist",argv[argc-1]);
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
