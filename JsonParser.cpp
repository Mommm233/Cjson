#include "JsonParser.h"

JsonParser::JsonParser(const std::string& json) : json(json), position(0) {}

char JsonParser::getCurrentChar() {
    return json[position];
}

char JsonParser::getNextChar() {
    return json[position++];
}

void JsonParser::skipWhiteSpace() {
    while(std::isspace(getCurrentChar())) {
        ++position;
    }
}

JsonValue JsonParser::parse() {
    skipWhiteSpace();
    return parseValue();
}

JsonValue JsonParser::parseValue() {
    char currentChar = getCurrentChar();
    if(currentChar == '{') {
        return parseObject();
    } else if(currentChar == '[') {
        return parseArray();
    } else if(currentChar == '"') {
        return parseString();
    } else if(currentChar == '-' || std::isdigit(currentChar)) {
        return parseNumber();
    } else if(std::isalpha(currentChar)) {
        // isalpha()函数用来判断一个字符是否为字母
        return parseBoolOrNull();
    } else {
        throw std::runtime_error("Invalid JSON");
    }
}

JsonValue JsonParser::parseObject() {
    getNextChar(); // 返回'{'，position += 1
    JsonValue object(JsonValueType::OBJECT);

    while(getCurrentChar() != '}') {
        skipWhiteSpace();

        if(getCurrentChar() != '"') {
            
            throw std::runtime_error("Expected string as object key");
        }   
        std::string key = parseString().asString();

        skipWhiteSpace();

        if(getNextChar() != ':') {      // getCurrentChar() -> getNextChar()
            throw std::runtime_error("Expected colon in object");
        }

        skipWhiteSpace();

        JsonValue value = parseValue();
        object.addObject(key, value);

        skipWhiteSpace();

        if(getCurrentChar() == ',') {
            getNextChar(); // 返回','，position += 1
        } else if(getCurrentChar() != '}') {
            throw std::runtime_error("Expected comma or '}' in object");
        }
    }

    getNextChar(); // 返回'}'，position += 1
    return object;

}

JsonValue JsonParser::parseArray() {
    getNextChar(); // 返回'['，position += 1
    JsonValue array(JsonValueType::ARRAY);

    while(getCurrentChar() != ']') {
        skipWhiteSpace();

        array.addArrayElement(parseValue());

        skipWhiteSpace();
        if(getCurrentChar() == ',') {
            getNextChar(); // 返回','，position += 1
        } else if(getCurrentChar() != ']') {
            throw std::runtime_error("Expected comma or ']' in array");
        }
    }

    getNextChar(); // 返回']'，position += 1
    return array;

}

JsonValue JsonParser::parseString() {
    getNextChar(); // 返回'"'，position += 1
    std::string value;
    while(getCurrentChar() != '"') {
        value += getNextChar();
    }

    getNextChar(); // 返回'"'，position += 1
    return JsonValue(value);
}

JsonValue JsonParser::parseNumber() {
    std::string numStr;
    while(std::isdigit(getCurrentChar()) || getCurrentChar() == '-' || getCurrentChar() == '.') {
        numStr += getNextChar();
    }
    try {
        if(numStr.find('.') != std::string::npos) 
            return JsonValue(std::stod(numStr));
        else 
            return JsonValue(std::stoi(numStr));
    } catch (const std::invalid_argument& e) {
        throw std::runtime_error("Invalid number format");
    }
}

JsonValue JsonParser::parseBoolOrNull() {
    std::string word;
    while(std::isalpha(getCurrentChar())) {
        word += getNextChar();
    }

    if(word == "true") {
        return JsonValue(true);
    } else if(word == "false") {
        return JsonValue(false);
    } else if(word == "null") {
        return JsonValue();
    } else {
        throw std::runtime_error("Invalid value: " + word);
    }
}