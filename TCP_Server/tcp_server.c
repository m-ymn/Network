
#include <stdio.h>
#include <winSock2.h>
#include <time.h>

#define dest_srvr_addr "127.0.88.10"

#pragma comment(lib,"ws2_32.lib")

int main(void)
{
    char server_msg[256] = "You have reached the server" ;

    WSADATA wsa;
	SOCKET server_skt , client_skt;
	struct sockaddr_in server_addr, client_addr ;
	printf("\nInitialising Winsock...\n\r");
	if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
	{
		printf("Failed. Error Code : %d",WSAGetLastError()) ;
		return 1 ;
	}

	printf("Initialised.\n") ;
    server_skt = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(server_skt == INVALID_SOCKET)
        printf("Socket creation failed\n\r") ;

    printf("Socket Created\n\r") ;

    // define address and port
    server_addr.sin_family = AF_INET ;
    server_addr.sin_addr.s_addr = inet_addr(dest_srvr_addr);  //inet_addr(dest_srvr_addr) ;
    server_addr.sin_port = htons(9999) ;

    // Call the bind function to bind the address to the server
    if (bind(server_skt,(struct sockaddr *)&server_addr,sizeof(server_addr)) == SOCKET_ERROR)
    {
        printf("Bind failed\n\r");
        printf("bind failed with error: %d\n", WSAGetLastError());
        closesocket(server_skt);
        WSACleanup();
        return 1;
    }
    printf("TCP Server started at %s on port %d\n\r",dest_srvr_addr,9999);
    // call the listen function to start listening on the port
    listen(server_skt,5) ;   // backlog is num of connections
    printf("Waiting for incoming connections...\n\r") ;
    int process_id ;
    int c = sizeof(struct sockaddr_in) ;
    char buffer[1024] ;
    while(1)
    {
        client_skt = accept(server_skt, (struct sockaddr *)&client_addr , &c) ;
       // process_id = fork();
        if(client_skt != INVALID_SOCKET)
        {   printf("Connection accepted from %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
            //send(client_skt, "You have reached the server!", 28, 0);
            while(1)
            {
                recv(client_skt, buffer, 1024, 0);
                if(strcmp(buffer, ":exit") == 0){
                    printf("Disconnected from %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
                    break;
                }else{
                    printf("Client: %s\r\n", buffer);
                    send(client_skt, buffer, strlen(buffer), 0);
                    memset(buffer,0x00,sizeof(buffer)) ;
                }
            }
        }
    }


    closesocket(server_skt) ;
    WSACleanup();

    return 0;
}


