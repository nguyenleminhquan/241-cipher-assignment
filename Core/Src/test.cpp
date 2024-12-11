#include <iostream>
#include <string>
#include <locale>
#include <codecvt>
#include <regex>

using namespace std;

// Chuyển ký tự UTF-8 đầu tiên sang mã Unicode để so sánh
char32_t utf8ToUnicode(const std::string& utf8Char) {
    wstring_convert<codecvt_utf8<char32_t>, char32_t> converter;
    u32string utf32Char = converter.from_bytes(utf8Char);
    return utf32Char[0];
}

string getCharUTF8(string text) {
    wstring_convert<codecvt_utf8<char32_t>, char32_t> converter;
    u32string utf32Text = converter.from_bytes(text); // Chuyển chuỗi UTF-8 sang UTF-32

    return converter.to_bytes(utf32Text);
}

// Hàm mã hóa Caesar với UTF-8
string caesarEncryptUTF8(const string& text, int key) {
    wstring_convert<codecvt_utf8<char32_t>, char32_t> converter;
    u32string utf32Text = converter.from_bytes(text); // Chuyển chuỗi UTF-8 sang UTF-32

    for (char32_t& ch : utf32Text) {
        if (ch >= 0x20 && ch <= 0x10FFFF) { // Chỉ xử lý các ký tự in được
            ch = (ch + key) % 0x10FFFF;    // Dịch ký tự trong không gian UTF-8
        }
    }

    return converter.to_bytes(utf32Text); // Chuyển chuỗi UTF-32 về UTF-8
}

// Hàm giải mã Caesar với UTF-8
string caesarDecryptUTF8(const string& text, int key) {
    wstring_convert<codecvt_utf8<char32_t>, char32_t> converter;
    u32string utf32Text = converter.from_bytes(text); // Chuyển chuỗi UTF-8 sang UTF-32

    for (char32_t& ch : utf32Text) {
        if (ch >= 0x20 && ch <= 0x10FFFF) { // Chỉ xử lý các ký tự in được
            ch = (ch - key + 0x10FFFF) % 0x10FFFF; // Đảm bảo không bị giá trị âm
        }
    }

    return converter.to_bytes(utf32Text); // Chuyển chuỗi UTF-32 về UTF-8
}

int main() {
    // Chuỗi gốc
    std::string plaintext = "Founded in 1902 as Madrid Football Club, the club has traditionally worn a white home kit since its inception. The honorific title real is Spanish for royal and was bestowed to the club by King Alfonso XIII in 1920 alongside with the crown in the club crest. Real Madrid have played their home matches in the 85,000-capacity Santiago Bernabéu in Madrid since 1947.";
    int key = 1003;

    // Mã hóa
    std::string encryptedText = caesarEncryptUTF8(plaintext, key);
    std::cout << "Mã hóa: " << encryptedText << std::endl;
    cout << "length of original string: " << plaintext.size() << endl;

    // Lấy ký tự đầu tiên UTF-8 đúng cách
    size_t charLength = 0;
    unsigned char firstByte = encryptedText[0];
    if ((firstByte & 0x80) == 0) { // 1 byte (ASCII)
        charLength = 1;
    } else if ((firstByte & 0xE0) == 0xC0) { // 2 bytes
        charLength = 2;
    } else if ((firstByte & 0xF0) == 0xE0) { // 3 bytes
        charLength = 3;
    } else if ((firstByte & 0xF8) == 0xF0) { // 4 bytes
        charLength = 4;
    }

    string firstChar = encryptedText.substr(0, charLength);

    // Chuyển ký tự UTF-8 đầu tiên sang Unicode
    char32_t firstCharCode = utf8ToUnicode(firstChar);
    char32_t firstAscii = utf8ToUnicode("0");
    char32_t lastAscii = utf8ToUnicode("z");

    int minKey = firstCharCode - lastAscii;
    int maxKey = firstCharCode - firstAscii;
    cout << minKey << " -> " << maxKey << endl;
    string caesarDecrypt = caesarDecryptUTF8(encryptedText, 1008);
    cout << "length of string: " << caesarDecrypt.size() << endl;

    for (int i = 1; i <= 1; i++) {
        for (int j = 0; j + i < caesarDecrypt.size(); j++) {
            string sub = caesarDecrypt.substr(j, i);
            regex validRegex("^[a-zA-Z0-9 ]+$");

            // Kiểm tra chuỗi có match với regex hay không
            if (std::regex_match(sub, validRegex)) {
                std::cout << "Valid string: " << sub << std::endl;
                // Thực hiện xử lý với chuỗi hợp lệ ở đây
            } else {
                std::cout << "Invalid string, skipping: " << std::endl;
                break;
                // Bỏ qua chuỗi không hợp lệ
            }
                    // cout << "sub: " << sub << endl;
        }
    }
    // for (int i = 1008; i <= 1008; i++) {
    // // for (int i = minKey; i <= maxKey; i++) {
    //     string caesarDecrypt = caesarDecryptUTF8(encryptedText, i);
    //     cout << "[" << i << "]: " << caesarDecrypt << endl;
    // }
    // // Tính toán hiệu số Unicode
    // int difference = firstCharCode - aUnicode;

    // // In kết quả
    // cout << "First Character (UTF-8): " << firstChar << endl;
    // cout << "Unicode Difference from 'a': " << difference << endl;

    return 0;
}
