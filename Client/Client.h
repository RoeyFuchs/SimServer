
#ifndef SIMSERVER_CLIENT_H
#define SIMSERVER_CLIENT_H

#include <fstream>
#include <iostream>
#include "regex"
#define REGEX_PATTERN "run\\s{1,}\"([^\"]+)\""

using namespace std;

class Client {
    string fileName;
    bool readFromFile;
//Lexer* lexer;
public:
    explicit Client(string& fileName) {
        this->fileName = fileName;
        this->readFromFile = true;
    }
    Client() {
        this->readFromFile = false;
    }

    void Read();

private:
    void ReadFromFile();

    void ReadFromCommandLine();
};


#endif //SIMSERVER_CLIENT_H


