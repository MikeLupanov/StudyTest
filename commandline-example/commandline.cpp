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
#include <memory>
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
    // read command line
    if (argc == 1) {
        help(argv[0]);
    }
    while( (option = getopt(argc, argv, ":k:e:d:h")) != -1) {
        switch (option) {
        case 'k':
            if (optarg[0] == '-') {
                std::cerr << "Ошибка: у параметра -k нет значения\n";
                help(argv[0]);
            }
            if (key.empty()) {
                key = optarg;
            } else {
                std::cerr << "Ошибка: Повторное указание ключа\n";
                help(argv[0]);
            }
            break;
        case 'e':
        case 'd':
            if (optarg[0] == '-') {
                std::cerr << "Ошибка: у параметра -" << (char)option << " нет значения\n";
                help(argv[0]);
            }
            op_stack.emplace(option, optarg);
            break;
        case ':':
            std::cerr << "Ошибка: у параметра -" << (char)optopt << " нет значения\n";
            help(argv[0]);
        case '?':
            std::cerr << "Ошибка: неизвестный параметр -" << (char)optopt << "\n";
            help(argv[0]);
        default:
            help(argv[0]);
        }
    }
    if (key.empty()) {
        std::cerr << "Ошибка: Не задан ключ\n";
        help(argv[0]);
    }
    if (op_stack.empty()) {
        std::cerr << "Ошибка: Не задана операция и текст\n";
        help(argv[0]);
    }

    // working with vigenere cipher
    std::unique_ptr<Vigenere> cipher_ptr;
    try {
        cipher_ptr = std::make_unique<Vigenere>(new Vigenere(key));
    } catch(std::invalid_argument& e) {
        std::cerr << "Ошибка модуля Vigenere: " << e.what() << std::endl;
        exit(2);
    }
    while (!op_stack.empty()) {
        try {
            std::string text(op_stack.top().second);
            if (op_stack.top().first == 'e') {
                std::cout << "Encrypted: " << text << " --> " <<
                          (cipher_ptr->encrypt(text)) << std::endl;
            } else {
                std::cout << "Decrypted: " << text << " --> " <<
                          cipher_ptr->decrypt(text) << std::endl;
            }
        } catch(std::invalid_argument& e) {
            std::cerr << "Ошибка модуля Vigenere: " << e.what() << std::endl;
        }

        op_stack.pop();
    }

    return 0;
}
