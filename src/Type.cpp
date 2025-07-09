//
// Created by julian on 7/4/25.
//

#include "Type.h"
namespace stc::type
{
    SimpleType fromString(const std::string& str)
    {
        static const std::unordered_map<std::string, SimpleType> typeMap = {
            {"I64", I64_T},
            {"Bool", BOOL_T},
            {"I8", I8_T},
            {"F64", F64_T},
            {"Str", STRING_T},
            {"Arr", ARRAY_T},
            {"Ref", REF_T},
            {"Type", Type_T},
            {"?", ANY_T},
        };

        auto it = typeMap.find(str);
        if (it != typeMap.end())
            return it->second;

        throw std::runtime_error("Unknown type: " + str);
    }
}
