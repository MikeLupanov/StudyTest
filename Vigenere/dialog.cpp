/********************************************
*                                           *
*              Учебный пример               *
* Использование класса Vigenere в программе *
* с интерфейсом простого текстового диалога *
*                                           *
* (c) Лупанов М.Ю., ИБСТ, ПГУ, 2024         *
*                                           *
********************************************/

#include <iostream>
#include <string>
#include "vigenere.h"


int main(int argc, char **argv)
{
    std::string key;
    std::string text;
    unsigned op;
    std::cout<<"Cipher ready. Input key: ";
    std::getline(std::cin, key);
    Vigenere cipher(key);
    do {
        std::cout<<"Cipher ready. Input operation (0-exit, 1-encrypt, 2-decrypt): ";
        std::cin>>op;
        if (op > 2) {
            std::cout<<"Illegal operation\n";
        } else if (op >0) {
            std::cout<<"Cipher ready. Input text: ";
            std::cin >> std::ws;
            std::getline(std::cin, text);
            try {
                if (op==1) {
                    std::cout<<"Encrypted text: "<<cipher.encrypt(text)<<std::endl;
                } else {
                    std::cout<<"Decrypted text: "<<cipher.decrypt(text)<<std::endl;
                }
            } catch(std::invalid_argument& e) {
                std::cerr << e.what() << std::endl;
            }
        }
    } while (op!=0);
    return 0;
}
