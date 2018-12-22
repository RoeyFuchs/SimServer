#include <iostream>
#include "OpenDataServerExpression.h"


double OpenDataServerExpression::Execute(){
    int sockfd, newsockfd, portno, clilen;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in serv_addr, cli_addr;
    ssize_t  n = 1;

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

    listen(sockfd,1);
    clilen = sizeof(cli_addr);

    /* Accept actual connection from the client */
    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, (socklen_t*)&clilen);

    if (newsockfd < 0) {
        perror("ERROR on accept");
        exit(1);
    }

    /* If connection is established then start communicating */

    double samplRate = this->samplingRate->Execute();
    string temp("");
    while (n != 0) {
        auto startTime = chrono::high_resolution_clock::now();
        bzero(buffer,BUFFER_SIZE);
        n = read(newsockfd, buffer, BUFFER_SIZE);
        string A;
        if(temp.length() != 0) {
            A = temp + "," + string(buffer);
        } else {
            A = string(buffer);
        }
        string B = A;
        //הבאג קורה כאשר TEMP היא מחרוזת שלמה שמגיעה עד \N, ואז מחברים אליה את הפסיק וזה עושה בלאגן.
        for (int i = 0; i < A.length(); ++i) {
            if (A.at(i) == NEW_LINE_CHAR) {
                temp = A.substr(i+1, A.length());
                A = A.substr(0, i);
                break;
            }
        }
        if(A.at(0) == ',') {
            A = A.substr(1, A.length());
        }
        vector<string> data = Utils::SplitByChar(A, DELIMITER);
        for(int i = 0; i < data.size(); ++i) {
            string bind = this->xmlOrder.at(i);
            this->maps->EditVal(bind, stod(data.at(i)));
        }
        this->maps->UpdateExpression();
        auto currentTime = chrono::high_resolution_clock::now();
        auto diff = chrono::duration_cast<chrono::microseconds>(currentTime - startTime);
        if (diff.count() < MICRO/samplRate){
            useconds_t waitingTime = MICRO/samplRate-diff.count();
            usleep(waitingTime);
        }
    }
}

