#include <stdio.h>
#include<string.h>
#include<unistd.h>
#include <sys/socket.h>
#include<arpa/inet.h>


int main(int argc , char *argv[])
{
    //Creating socket
	int d_socket,c_socket,len;
    struct sockaddr_in server , client;
	char *message="HTTP/1.1 200 OK\n"
                    "Date: Thu, 4 Dec 2022 3:14:55 GMT\n"
                    "Server: Apache/2.2.3\n"
                    "Last-Modified: Wed, 18 Jun 2003 16:05:58 GMT\n"
                    "ETag: \"56d-9989200-1132c580\"\n"
                    "Content-Type: text/html\n"
                    "Content-Length: 103\n"
                    "Accept-Ranges: bytes\n"
                    "Connection: close\n"
                    "\n"
                    "<!DOCTYPE html><html><head><title> C Web Server </title></head><body><h1>Hello World<h1></body></html>";

	d_socket = socket(AF_INET , SOCK_STREAM , 0);


    server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons( 8888 );


    if(d_socket < 0){
        printf("\nError:\n could not create socket!\n");
        return(1);
    }else{
        printf("\nSuccess:\n Socket created\n");
    }



    if(bind(d_socket,(struct sockaddr *)&server , sizeof(server)) >= 0){
        printf("\nSuccess:\nServer is running\n");
    }else{
        printf("\nError:\nCould not bind!\n");
        return(1);
    }

    listen(d_socket , 3);

    len = sizeof(struct sockaddr_in);

    while(c_socket = accept(d_socket, (struct sockaddr *)&client, &len)){
	    write(c_socket , message , strlen(message));
        close(c_socket);
    }
	
    if(c_socket < 0){
        printf("Error");
        return 1;
    }

	
    close(d_socket);
	return 0;

}