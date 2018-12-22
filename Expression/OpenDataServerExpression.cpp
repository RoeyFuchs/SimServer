#include "OpenDataServerExpression.h"


double OpenDataServerExpression::Execute(){
    int sockfd, newsockfd, portno, clilen;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in serv_addr, cli_addr;
    int  n;

    /* First call to socket() function */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

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

    listen(sockfd,5);
    clilen = sizeof(cli_addr);

    /* Accept actual connection from the client */
    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, (socklen_t*)&clilen);

    if (newsockfd < 0) {
        perror("ERROR on accept");
        exit(1);
    }

    /* If connection is established then start communicating */
    bzero(buffer,BUFFER_SIZE);
    while (true) {
        n = read(newsockfd, buffer, BUFFER_SIZE);
        vector<string> data = Utils::SplitByChar(buffer, DELIMITER);
        for(int i = 0; i < data.size(); ++i) {
            string bind = this->xmlOrder.at(i);
            this->maps->EditVal(bind, stoi(data.at(i)));
        }
        this->maps->UpdateExpression();
    }
}

