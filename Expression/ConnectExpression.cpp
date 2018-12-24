#include "ConnectExpression.h"
#include <stdio.h>
#include <stdlib.h>

#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>

#include <string.h>

double ConnectExpression::Execute() {
  int sockfd, portno, n;
  struct sockaddr_in serv_addr;
  struct hostent *server;

  char buffer[BUFFER_SIZE_OUT];

  portno = this->GetPort()->Execute();

  /* Create a socket point */
  sockfd = socket(AF_INET, SOCK_STREAM, 0);

  if (sockfd < 0) {
    perror("ERROR opening socket");
    exit(1);
  }

  server = gethostbyname(this->GetIp().c_str());

  if (server == NULL) {
    fprintf(stderr, "ERROR, no such host\n");
    exit(0);
  }

  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length);
  serv_addr.sin_port = htons(portno);

  /* Now connect to the server */
  if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
    perror("ERROR connecting");
    exit(1);
  }

  /* Now ask for a message from the user, this message
     * will be read by server
  */

  printf("Please enter the message: ");
  bzero(buffer, BUFFER_SIZE_OUT);
  fgets(buffer, BUFFER_SIZE_OUT, stdin);

  /* Send message to the server */

  n = write(sockfd, buffer, strlen(buffer));

  return 0;
}