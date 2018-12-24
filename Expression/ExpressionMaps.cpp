#include "ExpressionMaps.h"


void ExpressionMaps::UpdateExpression() {
    for(auto itr = this->nameExpressionMap->begin(); itr != this->nameExpressionMap->end(); ++itr) {
        if (this->CheckMapHaveKey(*this->bindValueMap, (*itr).second->GetPath())) {
            double value = this->bindValueMap->at((*itr).second->GetPath());
            (*itr).second->SetExpression(make_shared<Number>(value));
        }
    }
}

/**
 * initialize the map - check the order of the xml file and put it in the map
 */
void ExpressionMaps::initializeMap() {
    vector<string> vec;
    ifstream myFile(XML_ORDER_FILE);
    if(!myFile.is_open()) {
        throw runtime_error(string("can't open XML file"));
    }
    string line;
    while(getline(myFile, line)) {
        vec.push_back(line);
    }
    myFile.close();
    for(int i = 0; i < vec.size(); ++i) {
        bindValueMap->insert(pair<string, double>(vec.at(i), 0));
    }
}