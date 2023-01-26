#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include <sys/socket.h>
#include<arpa/inet.h>
#include <pthread.h>
#include <signal.h>


#include "functions/client_response.h"


#define FROOT "chs.cfg"

int exitctrlc = 0;
struct config configuration;

void intHandler(int) {
    exitctrlc = 1;
}


void *threadconection(void *);


int main(int argc , char *argv[]){

    struct sigaction act;
    act.sa_handler = intHandler;
    sigaction(SIGINT, &act, NULL);

    //Creating socket
    
    int port;
    char root[100],fpath[255];
    FILE *clientfile;
    configuration.port = cfg(FROOT).port;
    strcpy(configuration.root , cfg(FROOT).root);
    port = configuration.port;

	int d_socket,c_socket,len;
    struct sockaddr_in server , client;
    
    
    
    
    pthread_t thread_id;


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
    
    while((c_socket = accept(d_socket, (struct sockaddr *)&client, &len)) && (exitctrlc == 0)){
        if(pthread_create(&thread_id, NULL, threadconection, (void*)&c_socket)>0){
            printf("\nAnother thread created");
        }
    }
	
    if(c_socket < 0){
        printf("\nError:\nClient socket error!\n");
        return 1;
    }

	
    close(d_socket);
	return 0;

}

void *threadconection(void *c_socket1){
        int c_socket = *(int*)c_socket1;
        struct http crequest;
        struct responsetocl responsetoclmain;
        char response1[4000000];
        char request[1012];
        if((read(c_socket,request,255)) > 0){
            //printf(request);
            crequest = getreqdata(request);
            responsetoclmain = rtc(crequest,configuration);
            memcpy(response1,responsetoclmain.buff,responsetoclmain.len);
        }else{
            printf("\nError:\nFailed to read client request!\n");
        }

	    write(c_socket , response1 , responsetoclmain.len);
        close(c_socket);
        return 0;
}