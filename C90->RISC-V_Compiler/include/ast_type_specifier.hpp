#pragma once

#include <string_view>
#include <stdexcept>

namespace ast {

enum class TypeSpecifier
{
    INVALID,
    LONG,
    INT,
    FLOAT,
    CHAR,
    STRING,     // probably unneeded becasue of char * (character pointer which is a string)
    BOOL,
    DOUBLE,
    VOID,
    UNSIGNED,
    SIGNED,
    SHORT,
    ENUM
};

enum class EntitySpecifier
{
    INVALID,
    FUNCTION,
    VARIABLE,
    PARAMETER,
    POINTER,
    POINTER_DEREFERENCE,    //ast_unary, arithmetic
    POINTER_ADDRESS,        //ast_unary, arithmetic
    UNARY,                  //ast_unary
    STRING_DEFINITION,       //ast_literal
    CHAR_DEFINITION,        //ast_literal
    SEMICOLON,
    SIZE_OF,
    ARRAY,
    ENUMERATOR,
    ENUM_SPECIFIER,
    SWITCH_STATEMENT,
    CASE_STATEMENT
};

const int TYPE_SIZE_INT = 4;
const int TYPE_SIZE_FLOAT = 4;
const int TYPE_SIZE_CHAR = 1;                     // irrelevant must count up by blocks of 4
const int TYPE_SIZE_STRING = sizeof(std::string); // Depends on the system
const int TYPE_SIZE_BOOL = 1;
const int TYPE_SIZE_DOUBLE = 8;
const int TYPE_SIZE_VOID = 0;
const int TYPE_SIZE_RETURN_ADDRESS = 4;

template<typename LogStream>

LogStream& operator<<(LogStream& ls, const TypeSpecifier& type)
{
    const auto TypeToString = [&type] {
        switch (type)
        {
        case TypeSpecifier::INVALID:
            return "invalid";
        case TypeSpecifier::INT:
            return "int";
        case TypeSpecifier::FLOAT:
            return "float";
        case TypeSpecifier::CHAR:
            return "char";
        case TypeSpecifier::STRING:
            return "string";
        case TypeSpecifier::BOOL:
            return "bool";
        case TypeSpecifier::DOUBLE:
            return "double";
        case TypeSpecifier::VOID:
            return "void";
        case TypeSpecifier::LONG:
            return "long";
        case TypeSpecifier::UNSIGNED:
            return "unsigned";
        case TypeSpecifier::SIGNED:
            return "signed";
        case TypeSpecifier::SHORT:
            return "short";
        case TypeSpecifier::ENUM:
            return "enum";
        }
        throw std::runtime_error("Unexpected type specifier");
    };
    return ls << TypeToString();
}

}

