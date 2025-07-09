//
// Created by julian on 7/4/25.
//

#ifndef TYPE_H
#define TYPE_H


#include <string>
#include <stdexcept>
#include <unordered_map>

namespace stc::type
{
    enum SimpleType
    {
        I64_T,
        BOOL_T,
        I8_T,
        F64_T,
        STRING_T,
        ARRAY_T,
        REF_T,
        Type_T,
        Struct_T,
        ANY_T,
    };
    SimpleType fromString(const std::string& str);
    class Type
    {
        public:
        SimpleType base;
        bool isStruct{};
        std::string structName;
        Type *childType{};

        Type(SimpleType base, bool isStruct) : base(base), isStruct(isStruct) {}
        Type()= default;

    };

}

#endif //TYPE_H
