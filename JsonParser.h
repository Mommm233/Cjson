#ifndef JSONPARSER_H
#define JSONPARSER_H



#include <string>
#include <stdexcept>

#include "JsonValue.h"


class JsonParser {
public:
    JsonParser(const std::string& json);

    JsonValue parse();

private:
    const std::string& json;
    std::size_t position;

    char getCurrentChar();
    char getNextChar();
    void skipWhiteSpace();
    JsonValue parseValue();
    JsonValue parseObject();
    JsonValue parseArray();
    JsonValue parseString();
    JsonValue parseNumber();
    JsonValue parseBoolOrNull();
};

#endif