#include "IdentifierManager.h"

void IdentifierManager::addIdentifier(const stc::Identifier &identifier) {
    identifiers[identifier.token] = identifier;
}

stc::Identifier IdentifierManager::getIdentifier(const std::string& name) {
    if (const auto it = identifiers.find(name); it != identifiers.end()) {
        return it->second;
    }
    return stc::Identifier(name, stc::IDENTIFIER_UNKNOWN);
}

void IdentifierManager::removeIdentifier(const std::string &name) {
    identifiers.erase(name);
}
