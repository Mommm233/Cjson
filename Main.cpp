#include "JsonValue.h"
#include "JsonParser.h"

#include <iostream>
#include <fstream>
#include <sstream>


int main() {
    // 文件路径
    std::string filePath = "config.txt";

    // 打开文件
    std::ifstream fileStream(filePath);

    // 检查文件是否成功打开
    if (!fileStream.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return 1;
    }

    // 使用 std::stringstream 读取文件内容到字符串
    std::stringstream buffer;
    buffer << fileStream.rdbuf();
    std::string jsonStr = buffer.str();

    // 关闭文件
    fileStream.close();

    // std::string jsonStr = R"(
    //     {
    //         "name": "John",
    //         "age": 30,
    //         "city": "New York",
    //         "isStudent": false,
    //         "grades": [95, 89, 75],
    //         "address": 
    //             {
    //                 "street": "123 Main St",
    //                 "zip": "10001"
    //             },
    //         "b": null
    //     }
    // )";


    try {
        JsonParser parser(jsonStr);
        JsonValue parsedValue = parser.parse();

        // Print the parsed JSON
        parsedValue.print();
        std::cout << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    getchar();
    return 0;
}

illustrate