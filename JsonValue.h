#ifndef JSONVALUE_H
#define JSONVALUE_H

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <stdexcept>


enum class JsonValueType {
    OBJECT,
    ARRAY,
    STRING,
    NUMBER,
    BOOL,
    NULL_VALUE
};


class JsonValue {
public:
    JsonValueType type;

    JsonValue();
    JsonValue(JsonValueType t);
    // explicit表明构造函数是显示的
    explicit JsonValue(const std::string str);
    explicit JsonValue(int num);
    explicit JsonValue(double num);
    explicit JsonValue(bool boolean);

    void addObject(const std::string key, const JsonValue value);
    void addArrayElement(const JsonValue value);

    void print() const;
    std::string asString();



private:
    std::string str_value;
    double num_value;
    bool bool_value;
    std::map<std::string, JsonValue> obj_value;
    std::vector<JsonValue> arr_value;

    void printObject() const;
    void printArray() const;
};

#endif