#include<string.h>


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
                i++;
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