#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include <sys/socket.h>
#include<arpa/inet.h>

#include "config.h"
#include "functions/client_response.h"

#define FROOT "chs.cfg"






int main(int argc , char *argv[]){
    //Creating socket
    struct config configuration;
    int port;
    char root[100];
    configuration = cfg(FROOT);
    port = configuration.port;

	int d_socket,c_socket,len;
    struct sockaddr_in server , client;

    struct http crequest;
    char request[1012];
	char *response="HTTP/1.1 200 OK\n"
                    "Date: Thu, 4 Dec 2022 3:14:55 GMT\n"
                    "Server: c_http_server\n"
                    "Last-Modified: Wed, 18 Jun 2003 16:05:58 GMT\n"
                    "Content-Type: text/html;charset=utf-8\n"
                    "\n"
                    "<!DOCTYPE html><html><head><title> C Web Server </title></head><body><h1>Hello World<h1></body></html>";

	d_socket = socket(AF_INET , SOCK_STREAM , 0);


    server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons( port );


    if(d_socket < 0){
        printf("\nError:\n could not create socket!\n");
        return(1);
    }else{
        printf("\nSuccess:\n Socket created\n");
    }



    if(bind(d_socket,(struct sockaddr *)&server , sizeof(server)) >= 0){
        printf("\nSuccess:\nServer is running\n");
    }else{
        printf("\nError:\nServer failed!\n");
        return(1);
    }

    listen(d_socket , 3);

    len = sizeof(struct sockaddr_in);

    while(c_socket = accept(d_socket, (struct sockaddr *)&client, &len)){
        if((read(c_socket,request,255)) > 0){
            crequest = getreqdata(request);
        }else{
            printf("\nError:\nFailed to read client request!\n");
        }

	    write(c_socket , response , strlen(response));
        close(c_socket);
        break;
    }
	
    if(c_socket < 0){
        printf("\nError:\nClient socket error!\n");
        return 1;
    }

	
    close(d_socket);
	return 0;

}