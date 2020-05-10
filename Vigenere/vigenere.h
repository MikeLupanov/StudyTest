#pragma once
#include <vector>
#include <string>
#include <map>

// Класс для шифрования методом Виженера
// Ключ - строка, где A - сдвиг на 0, B - сдвиг на 1, Z - сдвиг на 25
// Первый символ сдвигается по значению первого символа ключа, второй - второго, и т.д.
// Если ключ заканчивается - повторяем его заново
// Если ключ длиной N, то для N+1 символа текста сдвиг по первому символу ключа и т.д.
class Vigenere
{
private:
    static const std::string alpha;   //алфавит по порядку
    static const std::map <char,int> alpha_num;     //ассоциативный массив "номер по символу"
    static std::vector <int> convert(const std::string& s); //перевод строки в целочисленный вектор
    static std::string convert(const std::vector<int>& v);  //перевод целочисленного вектора в строку
    std::vector <int> key;             //ключ в формате "число сдвигов"
public:
    Vigenere()=delete;                         //запретим конструктор без параметров
    Vigenere(const std::string& skey);         //конструктор для установки ключа
    std::string encrypt(const std::string& open_text);  //зашифрование
    std::string decrypt(const std::string& cipher_text);//расшифрование
};
