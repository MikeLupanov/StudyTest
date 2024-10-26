/******************************************
*                                         *
*         Учебный пример                  *
* Модуль Vigenere, реализация класса      *
*                                         *
* (c) Лупанов М.Ю., ИБСТ, ПГУ, 2020       *
*                                         *
******************************************/

#include <algorithm>
#include <functional>
#include <algorithm>
#include <execution>
#include <stdexcept>
#include <cctype>
#include "vigenere.h"
#include <iostream>

//алфавит по порядку - реализация
const std::string Vigenere::alpha {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};

//лямбда-функция для заполнения ассоциативного массива
auto make_alpha_num
{
    [](const std::string & s) {
        std::map <char,int> r;
        for(unsigned i=0; i<s.size(); i++) {
            r[s[i]] = i;
        }
        return r;
    }
};
//ассоциативный массив "номер по символу" - реализация
const std::map <char,int> Vigenere::alpha_num {make_alpha_num(Vigenere::alpha)};

//конструктор для установки ключа - реализация
Vigenere::Vigenere(const std::string& skey)
{
    if (skey.size() == 0) {
        throw std::invalid_argument("Empty key");    // исключение, пустой ключ
    }
    if (std::find_if_not(skey.begin(),skey.end(),isalpha) != skey.end()) {
        throw std::invalid_argument("Non-alpha symbols in key");    // исключение, если не буквы
    }
    key = convert(skey);
    if (std::count(key.begin(), key.end(), 0) >= key.size()/2.0) {
        throw std::invalid_argument("Weak key");    // исключение, если слабый ключ
    }
}


//зашифрование - реализация
std::string Vigenere::encrypt(const std::string& open_text)
{
    if (std::find_if_not(open_text.begin(),open_text.end(),isalpha) != open_text.end()) {
        throw std::invalid_argument("Non-alpha symbols in message");    // исключение, если не буквы
    }
    std::vector<int> work = convert(open_text);
    for(unsigned i=0; i < work.size(); i++) {
        work[i] = (work[i] + key[i % key.size()]) % alpha_num.size();
    }
    return convert(work);
}

//расшифрование - реализация
std::string Vigenere::decrypt(const std::string& cipher_text)
{
    if (std::find_if_not(cipher_text.begin(),cipher_text.end(),isalpha) != cipher_text.end()) {
        throw std::invalid_argument("Non-alpha symbols in message");    // исключение, если не буквы
    }
    std::vector<int> work = convert(cipher_text);
    for(unsigned i=0; i < work.size(); i++) {
        work[i] = (work[i] + alpha_num.size() - key[i % key.size()]) % alpha_num.size();
    }
    return convert(work);
}

std::vector<int> Vigenere::convert(const std::string& s)
{
    auto ToUpper = [](char c) {
        return alpha_num.at(std::toupper(c));
    };
    std::vector<int> result(s.size());
    std::transform(std::execution::par,
                   s.cbegin(), s.cend(),
                   result.begin(),
                   ToUpper);
    return result;
}

std::string Vigenere::convert(const std::vector<int>& v)
{
    std::string result(v.size(),' ');
    std::transform(std::execution::par,
                   v.cbegin(), v.cend(),
                   result.begin(),
                   [](int i) { return alpha[i]; });
    return result;
}
