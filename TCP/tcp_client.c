#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <WinSock2.h>


#pragma comment(lib,"ws2_32.lib")
#define dest_srvr_addr "127.0.88.10"

int main()
{
    WSADATA wsa;
	SOCKET client_skt;

	printf("\nInitialising Winsock...\n\r");
	if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
	{
		printf("Failed. Error Code : %d",WSAGetLastError()) ;
		return 1 ;
	}

	printf("Initialised.\n") ;

    if((client_skt = socket(AF_INET,SOCK_STREAM,0)) == INVALID_SOCKET)
        printf("Socket creation failed\n\r") ;

    printf("Socket Created\n\r") ;


    // define address and port
    struct sockaddr_in server_addr ;
    server_addr.sin_family = AF_INET ;
    server_addr.sin_addr.s_addr =  inet_addr(dest_srvr_addr);  // inet_addr(dest_srvr_addr) ;
    server_addr.sin_port = htons(9999) ;


    // since it is client therefore call the connect function
    if ( connect(client_skt,(struct sockaddr *)&server_addr,sizeof(server_addr)) !=0)
    {
        printf("Error Connecting \n\r");
    }

    char send_buffer[1024], recv_buffer[1024] ; ;
    while(1)
    {
        printf("Client:\t") ;
        memset(send_buffer,0x00,sizeof(send_buffer)) ;
        scanf("%s", &send_buffer) ;
        send(client_skt,&send_buffer,sizeof(send_buffer),0) ;

        if(strcmp(send_buffer,"exit") == 0)
        {
            printf("Disconnected from Server") ;
            break ;
        }
        else
        {
            memset(recv_buffer,0x00,sizeof(recv_buffer)) ;
            recv(client_skt,recv_buffer,sizeof(recv_buffer),0) ;
            printf("Server Message: %s \n\r",recv_buffer) ;
        }
    }
    close(client_skt) ;

    closesocket(client_skt) ;
    WSACleanup();



    return  0 ;
}

