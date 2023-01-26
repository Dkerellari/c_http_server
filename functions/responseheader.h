


char *exPath(char *path,char *root){
    int len = strlen(path);
    static char path1[255],path2[255];
    strcpy(path2,root);
    int i=0;
    while(i<len){
        if(path[i]=='?'){
            break;
        }
        path1[i] = path[i];
        i++;
    }
    if(path[i]=='?'){
        path1[i]='\0';
    }else{
        path1[i]='\0';
    }

    if(strcmp(path1,"/")==0){
        strcpy(path1,"/index.html");
    }
    strcat(path2,path1);
    printf("%s\n",path2);
    return path2;

}

char *header(char *ext,int contlength,int size){
    static char buff[2000]={0};
    char contype[255];
    char ranges[255];
    char contlengthstr[255];
    int datalen;
    strcpy(contlengthstr,"content-length: 4000");
    if(strcmp(ext,".html")==0){
        strcpy(contype , "text/html; charset=UTF-8");
        strcpy(ranges,"");
        datalen = contlength;

    }else  if(strcmp(ext,".css")==0){
        strcpy(contype , "text/css");
        strcpy(ranges , "Accept-Ranges: bytes");
        datalen = contlength;

    }else if((strcmp(ext,".png")==0) || (strcmp(ext,".jpg")==0) || (strcmp(ext,".jpeg")==0) || (strcmp(ext,".webp")==0)){
        sprintf(contype , "image/%s",ext+1);
        strcpy(ranges , "Accept-Ranges: bytes");
        datalen = size;
    }else{
        strcpy(contype , "text/plain; charset=UTF-8");
        datalen = contlength;
    }
    sprintf(contlengthstr,"content-length: %d",datalen);
    sprintf(buff, "HTTP/1.1 200 OK\r\n"
                    "Date: Wed, 25 Jan 2023 23:01:11 GMT\n"
                    "Server: c_http_server\n"
                    "Last-Modified: Wed, 18 Jun 2003 16:05:58 GMT\n"
                    "Content-Type: %s\n"
                    "%s\n"
                    "%s\n"
                    "\n",contype, contlengthstr,ranges);

    
    
    return buff;
}