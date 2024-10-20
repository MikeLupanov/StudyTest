/******************************************
*                                         *
*         Учебный пример                  *
* Модуль Vigenere, объявление класса      *
*                                         *
* (c) Лупанов М.Ю., ИБСТ, ПГУ, 2020-2024  *
*                                         *
******************************************/

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
    static const std::map <char,int> alpha_num; //ассоциативный массив "номер по символу"

// Если используется UnitTest++, то сделать приватные методы публичными для тестирования
#if defined UNITTEST_WIN32 or defined UNITTEST_POSIX
public:
#else
private:
#endif
    static std::vector <int> convert(const std::string& s); //перевод строки в целочисленный вектор
    static std::string convert(const std::vector<int>& v);  //перевод целочисленного вектора в строку

private:
    std::vector <int> key; //ключ в формате "число сдвигов"

public:
    Vigenere()=delete;                         //запретим конструктор без параметров
    Vigenere(Vigenere &v)=default;
    Vigenere(Vigenere &&v)=default;
    Vigenere(Vigenere * v_ptr):key(v_ptr->key) {}
    Vigenere(const std::string& skey);         //конструктор для установки ключа
    std::string encrypt(const std::string& open_text);  //зашифрование
    std::string decrypt(const std::string& cipher_text);//расшифрование
};
