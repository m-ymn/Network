/*
 * http_server.h
 *
 *  Created on: 13-Feb-2024
 *      Author: Yameen
 */

#ifndef HTTP_SERVER_H_
#define HTTP_SERVER_H_


#define MAX_CLIENT_SUPPORTED    32
#define SERVER_PORT     80 /*Server process is running on this port no. Client has to send data to this port no*/
#define SERVER_ADDR  "192.168.0.130" //"127.0.88.10" //"192.168.1.8"




void setup_mxtcp_server_communication();
int processhttprequest(char *reqdata, int reqdatalen, char **response, unsigned int *response_length);

#endif /* HTTP_SERVER_H_ */
