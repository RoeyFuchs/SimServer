#include "Client.h"

/**
 * the function check if we got a file to read from, and call to the correct function.
 */
void Client::Read() {
    if(this->readFromFile) {
        ReadFromFile();
    } else {
        ReadFromCommandLine();
    }
}

/**
 * the function read line by line of commands, and send them to the lexer.
 */
void Client::ReadFromFile() {
    ifstream fileStream(this->fileName);
    if (!fileStream.is_open()) {
        throw runtime_error(string("FILE ERROR"));
    }
    string str;
    while (getline(fileStream,str))
    {
        /** ###################
         * HERE SEND TO LEXAR
         */
    }
    fileStream.close();
}
/**
 * the function read commands from commandline, and send them to the lexer.
 */
void Client::ReadFromCommandLine() {
    string str;
    while(true) {
        cin >> str;
        /** ###################
         * HERE SEND TO LEXAR
         */
    }
}