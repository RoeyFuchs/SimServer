#include "ExpressionMaps.h"


void ExpressionMaps::UpdateExpression() {
    for(auto itr = this->nameExpressionMap->begin(); itr != this->nameExpressionMap->end(); ++itr) {
        double value = this->bindValueMap->at((*itr).second->GetPath());
        (*itr).second->SetExpression(make_shared<Number>(value));
    }
}