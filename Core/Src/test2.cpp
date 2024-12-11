#include <iostream>
#include <string>
#include <regex>

void processString(const std::string& input) {
    // Regex để kiểm tra chuỗi chỉ chứa a-z, A-Z, 0-9, và khoảng trắng
    std::regex validRegex("^[a-zA-Z0-9 ]+$");

    // Kiểm tra chuỗi có match với regex hay không
    if (std::regex_match(input, validRegex)) {
        std::cout << "Valid string: " << input << std::endl;
        // Thực hiện xử lý với chuỗi hợp lệ ở đây
    } else {
        std::cout << "Invalid string, skipping: " << input << std::endl;
        // Bỏ qua chuỗi không hợp lệ
    }
}

int main() {
    std::string test1 = "Hello World 123";
    std::string test2 = "Invalid@String!";
    std::string test3 = "Another valid string";

    processString(test1); // Hợp lệ
    processString(test2); // Không hợp lệ
    processString(test3); // Hợp lệ

    return 0;
}
