#include <getopt.h>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

class ShiftCipher {
    
    bool encrypt_check;
    int shift_key = 0;
    vector<string> message;
    vector<string> result;

    void print(vector<string> vec) {
        for (auto& i : vec) {
            cout << i << " ";
        }
        cout << endl;
    }// print

    string crypt(string& word) {
        string new_word = "";
        for (char letter : word) {
            if (int(letter) < 65 || int(letter) > 122) {
                new_word += letter;
            }
            else if (isupper(letter)) {
                new_word += char(int(letter + shift_key - 65) % 26 + 65);
            }
            else {
                new_word += char(int(letter + shift_key - 97) % 26 + 97);
            }   
        }// for
        return new_word;
    }// crypt

public:
    void get_choice(int argc, char** argv);

    void read();

    void process();

    void output();

};// ShiftCipher class declaration

int main(int argc, char *argv[]) {
    ios_base::sync_with_stdio(false);

    ShiftCipher shifty;

    try {
        shifty.get_choice(argc, argv);
        shifty.read();
        shifty.process();
        shifty.output();
    }// try

    catch (std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }// catch

    return 0;
}// main

void ShiftCipher::get_choice(int argc, char** argv) {
    int option_index = 0, option = 0;
    opterr = false;

    struct option longOpts[] = { { "decrypt", required_argument, nullptr, 'd' },
                                {"encrypt", no_argument, nullptr, 'e' },
                                { "shift", required_argument, nullptr, 's' },
                                { "help", no_argument, nullptr, 'h' },
                                { nullptr, 0, nullptr, '\0' } };

    int de_counter = 0;

    while ((option = getopt_long(argc, argv, "des:h", longOpts, &option_index)) != -1) {
        switch (option) {
        case 'd':
            encrypt_check = false;
            de_counter++;
            if (de_counter > 1) {
                throw std::runtime_error("encrypt OR decrypt, only specify one!"
                    " Exiting...");
            }
            break;

        case 'e':
            encrypt_check = true;
            de_counter++;
            if (de_counter > 1) {
                throw std::runtime_error("encrypt OR decrypt, only specify one"
                    " Exiting...");
            }
            break;

        case 's':
            shift_key = atoi(optarg);
            shift_key = shift_key % 26;
            break;

        case 'h':
            std::cout << "This program reads a message in the form of a .txt file\n"
                << "then either encrypts or decrypts the message.\n"
                << "this program requires a shift key in the command line\n"
                << "it also must know if it is encrypting or decrypting\n"
                << "Usage: \'./cipher\n\t[--help | -h]\n"
                << "\t[--encrypt | -e]\n"
                << "\t[--decrypt | -d]\n"
                << "\t[--shift | -s] <N>\n"
                << "\t< <text file>\'" << std::endl;
            exit(0);
        }// switch
    }// while
}// get_options

void ShiftCipher::read() {
    string word;
    while (cin >> word) {
        message.push_back(word);
    }// while
}// read

void ShiftCipher::process() {
    if (!encrypt_check) {
        shift_key = 26 - shift_key;
    }
    for (size_t i = 0; i < message.size(); i++) {
        result.push_back(crypt(message[i]));
    }
}// process

void ShiftCipher::output() {
    cout << "Original Message: \n";
    print(message);
    if (encrypt_check) {
        cout << "Encrypted Message: \n";
        print(result);
    }
    else {
        cout << "Decrypted Message: \n";
        print(result);
    }
}