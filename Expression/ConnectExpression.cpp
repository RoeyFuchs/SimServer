#include "ConnectExpression.h"


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

  this->sockfd = sockfd;
  return 0;
}

void ConnectExpression::SendData() {
  /* Send message to the server */
  while (!deq.empty()) {
    string str = this->deq.front();
    cout << str << endl;
    this->deq.pop_front();
    write(this->sockfd, str.c_str(), str.length());
  }
}