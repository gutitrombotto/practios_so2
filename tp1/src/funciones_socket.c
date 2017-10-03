#include "../includes/includes.h"
#include "../includes/variables.h"

int escribir_socket(int sockfd, const char* buffer)
{
	int datalen = strlen(buffer);
	int tmp = htonl(datalen);
	printf("Enviando: %s\n", buffer);
	int n = write(sockfd, (char*)&tmp, sizeof(tmp));
	if (n < 0) {perror("ERROR writing to socket"); return -1;} 
	n = write(sockfd, buffer, datalen);
	if (n < 0) {perror("ERROR writing to socket"); return -1;}
	return n;
}

int leer_socket(int sockfd,char* buffer)
{
	memset( buffer, '\0', TAM );
	int buflen;
	int n = read(sockfd, (char*)&buflen, sizeof(buflen));
	if (n < 0) {perror("ERROR writing to socket"); return -1;}
	buflen = ntohl(buflen);
	n = read(sockfd, buffer, buflen);
	if (n < 0) {perror("ERROR writing to socket"); return -1;}
	return n;
}