
#include "responseheader.h"
#include "./config.h"
#include"dynamicbuff.h"
#include"./../applications/temp.h"

struct http{
    char method[100];
    char pathdata[1000];
    char httpv[255];
    char host[255];
    char userAgent[255];
};


struct http getreqdata(char *response){
    struct http data;
    int i=0,j=0,len=strlen(response);
    char done=0,httpv[255],host[255],userAgent[255];
    char pathdata[1000];
    while(i < len){
        if(done == 0){
            if(response[i]=='G' && response[i+1]=='E' && response[i+2]=='T'){
                strcpy(data.method,"GET");
                done = 1;
                i=i+4;
                j=0;
            }
        }

        if(done==1){
            if(response[i] != ' '){
                pathdata[j] = response[i];
                j++;
            }else{
                pathdata[j]='\0';
                strcpy(data.pathdata,pathdata);
                done=2;
                i++;
                j=0;
            }
        }
        if(done==2){
            if(response[i] != '\n'){
                httpv[j] = response[i];
                j++;
            }else{
                httpv[j]='\0';
                strcpy(data.httpv,httpv);
                done=3;
                i=i+7;
                j=0;
            }
        }
        if(done==3){
            if(response[i] != '\n'){
                host[j] = response[i];
                j++;
            }else{
                host[j]='\0';
                strcpy(data.host,host);
                done=4;
                i++;
                j=0;
            }
        }
        if(done == 4){
            if(response[i]=='U' && response[i+4]=='-' && response[i+9]=='t'){
                done = 5;
                i=i+12;
            }
        }
        if(done==5){
            if(response[i] != '\n' && ((i+1)!=len)){
                userAgent[j] = response[i];
                j++;
            }else{
                userAgent[j]='\0';
                strcpy(data.userAgent,userAgent);
            }
        }
        i++;
    }
    return data;
};

struct responsetocl{
    char *buff;
    int len;
};

struct responsetocl rtc(struct http creq,struct config configuration){
    getready();
    char path[255];
    FILE *fp;
    char *buff;
    char ext[255];
    char headerstr[4000];
    static char buff1[4000000],lenofdata[4000000];
    static struct responsetocl responsetoclfnc;
    int size=0,lenbuff,getdynamiccheck=1,headerlen=0;
    strcpy(path,exPath(creq.pathdata,configuration.root));
    strcpy(ext,strrchr(path, '.'));
    if (!ext) {
        strcpy(ext , ".html\0");
    }else{
        if((strcmp(ext,".png")==0) || (strcmp(ext,".jpg")==0) || (strcmp(ext,".jpeg")==0) || (strcmp(ext,".webp")==0)){
            getdynamiccheck=0;
        }
    }
    //printf("%s",path);
    fp = fopen(path,"r");
    if(fp == NULL){
        size = 4;
        strcpy(ext,".html");
        strcpy(buff1,header(ext,4,size));
        headerlen = strlen(buff1);
        strcat(buff1,"404\0");
        getdynamiccheck = 1;
        responsetoclfnc.len = size + headerlen;
    }else{
        fseek(fp,0L,SEEK_END);
        size=ftell(fp);
        fseek(fp,0L,SEEK_SET);
        buff = (char *)malloc(size);
        fread(buff,1,size,fp);
        fclose(fp);
        if(getdynamiccheck==1){
            strcpy(lenofdata,getdynamic(buff,fnc,MAXF));
            lenbuff = strlen(lenofdata);
            strcpy(buff1,header(ext,lenbuff,size));
            headerlen = strlen(buff1);
            strcat(buff1,getdynamic(buff,fnc,MAXF));
            responsetoclfnc.len = lenbuff + headerlen;
        }else{
            strcpy(buff1,header(ext,lenbuff,size));
            headerlen = strlen(buff1);
            memcpy(buff1+headerlen,buff,size);
            responsetoclfnc.len = size + headerlen;
        }
        free(buff);
    }
    responsetoclfnc.buff = buff1;
    return responsetoclfnc;

}