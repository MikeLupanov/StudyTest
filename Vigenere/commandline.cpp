/********************************************
*                                           *
*              Учебный пример               *
* Использование класса Vigenere в программе *
* с интерфейсом параметров командной строки *
*                                           *
* (c) Лупанов М.Ю., ИБСТ, ПГУ, 2024         *
*                                           *
********************************************/

#include <iostream>
#include <string>
#include <stack>
#include <unistd.h>
#include "vigenere.h"

// Подсказка
void help(const char * name)
{
    std::cerr << "Использование: " << name << " -k КЛЮЧ -e|-d ТЕКСТ [-e|-d ТЕКСТ [...] ]\n";
    std::cerr << "Параметры:\n";
    std::cerr << "\t -k КЛЮЧ  \t Использовать КЛЮЧ для зашифрования/расшифрования\n";
    std::cerr << "\t -e ТЕКСТ \t Зашифровать  ТЕКСТ\n";
    std::cerr << "\t -d ТЕКСТ \t Расшифровать ТЕКСТ\n";
    exit(1);
}

int main(int argc, char **argv)
{
    std::string key;
    std::string text;
    int option;
    std::stack<std::pair<char, std::string>> op_stack;
    while( (option = getopt(argc, argv, "k:e:d:")) != -1) {
        switch (option) {
        case 'k':
            if (key.empty()) {
                key = optarg;
            } else {
                std::cerr << "Ошибка: Повторное указание ключа\n";
                help(argv[0]);
            }
            break;
        case 'e':
        case 'd':
            op_stack.emplace(option, optarg);
            break;
        default:
            help(argv[0]);
        }
    }
    Vigenere cipher(key);
    while (!op_stack.empty()) {
        try {
            std::string text(op_stack.top().second);
            if (op_stack.top().first == 'e') {
                std::cout << "Encrypted: " << text << " --> " <<
                          cipher.encrypt(text) << std::endl;
            } else {
                std::cout << "Decrypted: " << text << " --> " <<
                          cipher.decrypt(text) << std::endl;
            }
        } catch(std::invalid_argument& e) {
            std::cerr << e.what() << std::endl;
        }

        op_stack.pop();
    }
    return 0;
}
