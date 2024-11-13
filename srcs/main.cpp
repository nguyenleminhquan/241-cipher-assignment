#include <iostream>
#include <string>
#include <vector>

using namespace std;

string CaesarEncrypt(string text, int shift) {
    string result = text;
    for (char& c : result) {
        if (isalpha(c)) {
            char base = islower(c) ? 'a' : 'A';
            c = (c - base + shift) % 26 + base;
        }
    }

    return result;
}

string CaesarDecrypt(string text, int shift) {
    return CaesarEncrypt(text, 26 - shift);
}

string RailFenceEncrypt(string text, int key) {
    // init 2D array with key rows
    vector<string> rail(key);
    int current_row = 0, step = 1;
    
    for (char c : text) {
        rail[current_row].push_back(c);
        if (current_row == 0) step = 1;
        else if (current_row == key - 1) step = -1;
        current_row += step;
    }
    
    string result;
    for (string r : rail) {
        result += r;
    }

    return result;
}

string RailFenceDecrypt(string text, int key) {
    vector<int> length(key, 0);
    int row = 0, direction = 1;
    
    // Set length of each rows
    for (int i = 0; i < text.length(); i++) {
        length[row]++;
        if (row == 0) direction = 1;
        else if (row == key - 1) direction = -1;
        row += direction;
    }

    // Set string on each row
    vector<string> rail(key);
    int index = 0;
    for (int i = 0; i < key; i++) {
        rail[i] = text.substr(index, length[i]);
        index += length[i];
    }

    string result;
    row = 0;
    direction = 1;
    for (int i = 0; i < text.length(); i++) {
        result += rail[row][0];
        rail[row].erase(0, 1);
        if (row == 0) direction = 1;
        else if (row == key - 1) direction = -1;
        row += direction;
    }

    return result;
}

string MultiEncrypt(string text, int shift, int multiplier) {
    string caesar_text = CaesarEncrypt(text, shift);
    return RailFenceEncrypt(caesar_text, multiplier);
}

string MultiDecrypt(string text, int shift, int multiplier) {
    string rail_fence_text = RailFenceDecrypt(text, multiplier);
    return CaesarDecrypt(rail_fence_text, shift);
}

int main() {
    int caesar_shift = 3;
    int rail_fence_key = 3;
    vector<string> test_cases = {
        "HELLO WORLD",
        "ho chi minh university of technology"
    };

    cout << "Caesar shift: " << caesar_shift << endl;
    cout << "Rail fence key: " << rail_fence_key << endl;

    for (string input : test_cases) {
        string caesar_text = CaesarEncrypt(input, caesar_shift);
        string rail_fence_text = RailFenceEncrypt(input, rail_fence_key);
        string multiply_text = MultiEncrypt(input, caesar_shift, rail_fence_key);

        cout << "==============================" << endl;
        cout << "Plain text: " << input << endl << endl;
        cout << "Cesar Cipher Encrypt: " << caesar_text << endl;
        cout << "Rail Fence Encrypt: " << rail_fence_text << endl;
        cout << "Multiply Encrypt: " << multiply_text << endl;

        cout << endl << "Cesar Cipher Decrypt: " << CaesarDecrypt(caesar_text, caesar_shift) << endl;
        cout << "Rail Fence Decrypt: " << RailFenceDecrypt(rail_fence_text, rail_fence_key) << endl;
        cout << "Multiply Decrypt: " << MultiDecrypt(multiply_text, caesar_shift, rail_fence_key) << endl;
    }

    return 0;
}
