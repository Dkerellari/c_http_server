


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
        path1[i+1]='\0';
    }

    if(strcmp(path1,"/")==0){
        strcpy(path1,"/index.html");
    }
    strcat(path2,path1);

    return path2;

}

char *header(int message){
    char *buff = "HTTP/1.1 200 OK\n"
                    "Date: Thu, 4 Dec 2022 3:14:55 GMT\n"
                    "Server: c_http_server\n"
                    "Last-Modified: Wed, 18 Jun 2003 16:05:58 GMT\n"
                    "Content-Type: text/html;charset=utf-8\n"
                    "\n";
    return buff;
}