#include "JsonValue.h"

JsonValue::JsonValue() : type(JsonValueType::NULL_VALUE) {}

JsonValue::JsonValue(JsonValueType t) : type(t) {}

JsonValue::JsonValue(const std::string str) : type(JsonValueType::STRING), str_value(str) {}

JsonValue::JsonValue(int num) : type(JsonValueType::NUMBER), num_value(num) {}

JsonValue::JsonValue(double num) : type(JsonValueType::NUMBER), num_value(num) {}

JsonValue::JsonValue(bool boolean) : type(JsonValueType::BOOL), bool_value(boolean) {}

void JsonValue::addObject(const std::string key, const JsonValue value) {
    if(type != JsonValueType::OBJECT) {
        type = JsonValueType::OBJECT;
    }
    obj_value[key] = value;
}

void JsonValue::addArrayElement(const JsonValue value) {
    if(type != JsonValueType::ARRAY) {
        type = JsonValueType::ARRAY;
    }
    arr_value.push_back(value);
}

void JsonValue::printObject() const {
    std::cout << "{";
    bool first = true;
    for(const auto &pair : obj_value) {
        if(!first) {
            std::cout << ",";
        }
        std::cout << "\"" << pair.first << "\":";
        // pair<std::string key, JsonValue value>
        pair.second.print();
        first = false;
    }
    std::cout << "}";
}

void JsonValue::printArray() const {
    std::cout << "[";
    bool first = true;
    for(const auto& element : arr_value) {
        if(!first) {
            std::cout << ",";
        }
        element.print();
        first = false;
    }
    std::cout << "]";
}

void JsonValue::print() const {
    switch(type) {
        case JsonValueType::OBJECT:
            printObject();
            break;
        case JsonValueType::ARRAY:
            printArray();
            break;
        case JsonValueType::STRING:
            std::cout << "\"" << str_value << "\"";
            break;
        case JsonValueType::NUMBER:
            std::cout << num_value;
            break;
        case JsonValueType::BOOL:
            std::cout << (bool_value ? "true" : "false");
            break;
        case JsonValueType::NULL_VALUE:
            std::cout << "null";
            break;
    }
}

std::string JsonValue::asString() {
    if(type == JsonValueType::STRING) {
        return str_value;
    } else {
        throw std::runtime_error("Not a string value");
    }
}

