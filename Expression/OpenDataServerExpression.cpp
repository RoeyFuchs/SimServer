#include <iostream>
#include "OpenDataServerExpression.h"

double OpenDataServerExpression::Execute() {
  int sockfd, newsockfd, portno, clilen;
  char buffer[BUFFER_SIZE];
  struct sockaddr_in serv_addr, cli_addr;
  ssize_t n = 1;

  /* First call to socket() function */
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  this->sockfd = sockfd;

  if (sockfd < 0) {
    perror("ERROR opening socket");
    exit(1);
  }

  /* Initialize socket structure */
  bzero((char *) &serv_addr, sizeof(serv_addr));
  portno = (int) this->port->Execute();
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(portno);
  /* Now bind the host address using bind() call.*/
  if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
    perror("ERROR on binding");
    exit(1);
  }
  /* Now start listening for the clients, here process will
     * go in sleep mode and will wait for the incoming connection
  */
  listen(sockfd, 1);
  clilen = sizeof(cli_addr);

  /* Accept actual connection from the client */
  int t = accept(sockfd, (struct sockaddr *) &cli_addr, (socklen_t *) &clilen);
  this->newsockfd = t;
  if (newsockfd < 0) {
    perror("ERROR on accept");
    exit(1);
  }
  thread t1(&OpenDataServerExpression::ReadData, this);
  t1.detach();

}

void OpenDataServerExpression::ReadData() {
  double samplRate = this->samplingRate->Execute();
  char buffer[BUFFER_SIZE];
  string temp;
  string rest;
  string str;
  ssize_t n = 1;
  while (n != 0) {
    //start record the time
    auto startTime = chrono::high_resolution_clock::now();
    bzero(buffer, BUFFER_SIZE);
    //read to buffer
    n = read(this->newsockfd, buffer, BUFFER_SIZE);
    //take the previous rest data
    temp = rest + string(buffer);
    str = Utils::SubStringUntilChar(temp, NEW_LINE_CHAR);
    rest = Utils::SubStringFromChar(temp, NEW_LINE_CHAR);
    vector<string> data = Utils::SplitByChar(str, DELIMITER);
    //update the data in the table
    for (int i = 0; i < data.size(); ++i) {
      string bind = this->xmlOrder.at(i);
      this->maps->EditVal(bind, stod(data.at(i)));
    }
    this->maps->UpdateExpression();
    //check if we need to wait
    auto currentTime = chrono::high_resolution_clock::now();
    auto diff = chrono::duration_cast<chrono::microseconds>(currentTime - startTime);
    if (diff.count() < MICRO / samplRate) {
      useconds_t waitingTime = MICRO / samplRate - diff.count();
      this_thread::sleep_for(chrono::microseconds(waitingTime));
    }
  }
}

