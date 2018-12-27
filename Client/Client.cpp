#include "Client.h"

/**
 * the function check if we got a file to read from, and call to the correct function.
 */
void Client::Read() {
  if (this->readFromFile) {
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
  while (getline(fileStream, str)) {
    if (str == EXIT_WORD) {
      break;
    }
    this->lexer->SeparateLine(str);
  }
  fileStream.close();
}
/**
 * the function read commands from commandline, and send them to the lexer.
 */
void Client::ReadFromCommandLine() {
  string str;
  smatch regMatch;
  while (true) {
    getline(cin, str);
    //check if the user want to run from a file (run "file.txt")
    regex_search(str, regMatch, regex(REGEX_PATTERN));
    if (regMatch[1].matched) {
      this->fileName = regMatch[1];
      ReadFromFile();
    } else {
      this->lexer->SeparateLine(str);
    }
  }
}