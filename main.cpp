#include <iostream>
#include "Client/Client.h"

using namespace std;



int main(int argc, char *argv[]) {
    shared_ptr<ExpressionMaps> expressionMaps = make_shared<ExpressionMaps>();
  shared_ptr<Parser> prsr = make_shared<Parser>(expressionMaps);
  shared_ptr<Lexer> lexer = make_shared<Lexer>(prsr);
  if (argc > 1) {
    string fileName = argv[1];
    shared_ptr<Client> Cli = make_shared<Client>(fileName, lexer);
    Cli->Read();
  } else {
    shared_ptr<Client> Cli = make_shared<Client>(lexer);
    Cli->Read();
  }

}