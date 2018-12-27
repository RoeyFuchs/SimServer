
#ifndef SIMSERVER_CLIENT_H
#define SIMSERVER_CLIENT_H

#include <fstream>
#include <iostream>
#include "../Lexer/Lexer.h"
#include "regex"
#define REGEX_PATTERN "run\\s{1,}\"([^\"]+)\""
#define EXIT_WORD "exit"

using namespace std;

class Client {
  string fileName;
  bool readFromFile;
  shared_ptr<Lexer> lexer;
 public:
  explicit Client(string fileName, shared_ptr<Lexer> lex) {
    this->lexer = lex;
    this->fileName = fileName;
    this->readFromFile = true;
  }
  Client(shared_ptr<Lexer> lex) {
    this->lexer = lex;
    this->readFromFile = false;
  }

  void Read();

 private:
  void ReadFromFile();

  void ReadFromCommandLine();
};

#endif //SIMSERVER_CLIENT_H


