#ifndef IDENTIFIERMANAGER_H
#define IDENTIFIERMANAGER_H
#include <map>
#include "Program.h"


class IdentifierManager {
    std::map<std::string, stc::Identifier> identifiers;
public:
    void addIdentifier(const stc::Identifier &identifier);
    stc::Identifier getIdentifier(const std::string& name);
    void removeIdentifier(const std::string& name);

    IdentifierManager(){}
};



#endif //IDENTIFIERMANAGER_H
