/******************************************
*                                         *
*         Учебный пример                  *
* Модульный тест для класса Vigenere      *
*                                         *
* (c) Лупанов М.Ю., ИБСТ, ПГУ, 2020-2024  *
*                                         *
******************************************/
#include <stdexcept>
#include <UnitTest++/UnitTest++.h>
#include "vigenere.h"

// Фикстура для тестирования Vigenere::convert
struct expected {
    std::vector<int> vect {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25};
    std::string str {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
};

// Сценарий тестирования статических методов класса convert
SUITE(ConvertTest)
{
    //Конвертация строки в массив
    TEST_FIXTURE(expected, ConvertStringToVector) {
        CHECK_ARRAY_EQUAL(vect, Vigenere::convert(str), vect.size());
    }
    //конвертация массива в строку
    TEST_FIXTURE(expected, ConvertVectorToString) {
        CHECK_EQUAL(str, Vigenere::convert(vect));
    }
}
// Сценарии тестирования конструктора
SUITE(KeyTest)
{
    // Регистр ключа
    TEST(UpperCaseKey) {
        Vigenere v("ABC");
        CHECK(true);
    }
    TEST(LowCaseKey) {
        Vigenere v("abc");
        CHECK(true);
    }
    TEST(MixCaseKey) {
        Vigenere v("AbC");
        CHECK(true);
    }
    // Длина ключа
    TEST(ShortKey) {
        Vigenere v("H");
        CHECK(true);
    }
    TEST(LongKey) {
        Vigenere v("QWERTYUIOPASDFGHJKLZXCVBNM");
        CHECK(true);
    }
    // пустой ключ
    TEST(EmptyKey) {
        CHECK_THROW(Vigenere v(""),std::invalid_argument);
    }
    // слабый ключ
    TEST(WeakKey_100) {
        CHECK_THROW(Vigenere v("A"),std::invalid_argument);
    }
    TEST(WeakKey_75) {
        CHECK_THROW(Vigenere v("AAAB"),std::invalid_argument);
    }
    TEST(WeakKey_50) {
        CHECK_THROW(Vigenere v("AAAAAAAAAABBBBBBBBBB"),std::invalid_argument);
    }
    TEST(WeakKey_47) {
        Vigenere v("AAAAAAAAABBBBBBBBBB");
        CHECK(true);
    }
    // недопустимые символы в ключе
    TEST(DigitsInKey) {
        CHECK_THROW(Vigenere v("HELL0"),std::invalid_argument);
    }
    TEST(ColonInKey) {
        CHECK_THROW(Vigenere v("HE,LLO"),std::invalid_argument);
    }
    TEST(WhitespaceInKey) {
        CHECK_THROW(Vigenere v(" HELLO"),std::invalid_argument);
    }
    TEST(NewlineInKey) {
        CHECK_THROW(Vigenere v("HELLO\n"),std::invalid_argument);
    }
}

// Фикстуры с различными конструкторами
struct VigenereZZZ {
    Vigenere v {"ZZZ"};
};
struct VigenereABC {
    Vigenere v {"ABC"};
};
struct VigenereABCXYZ {
    Vigenere v {"ABCXYZ"};
};

// Сценарии тестирования зашифрования
SUITE(EncryptTest)
{
    // регистр текста
    TEST_FIXTURE(VigenereABC, UpperCaseText) {
        CHECK_EQUAL("HFNLP", v.encrypt("HELLO"));
    }
    TEST_FIXTURE(VigenereABC, LowCaseText) {
        CHECK_EQUAL("HFNLP", v.encrypt("hello"));
    }
    TEST_FIXTURE(VigenereABC, MixCaseText) {
        CHECK_EQUAL("HFNLP", v.encrypt("hElLo"));
    }
    // длина текста
    TEST_FIXTURE(VigenereABCXYZ, ShortText) {
        CHECK_EQUAL("HFNIM", v.encrypt("HELLO"));
    }
    TEST_FIXTURE(VigenereABCXYZ, EqualText) {
        CHECK_EQUAL("AMRFLD", v.encrypt("ALPINE"));
    }
    TEST_FIXTURE(VigenereABCXYZ, LongText) {
        CHECK_EQUAL("LJUPYAOO", v.encrypt("LISSABON"));
    }
    // максимальный сдвиг
    TEST_FIXTURE(VigenereZZZ, MaxShiftText) {
        CHECK_EQUAL("ZABCDEFGHIJKLMNOPQRSTUVWXY", v.encrypt("ABCDEFGHIJKLMNOPQRSTUVWXYZ"));
    }
    // недопустимые символы в тексте
    TEST_FIXTURE(VigenereABC, CommaInText) {
        CHECK_THROW(v.encrypt("HELLO,WORLD"),std::invalid_argument);
    }
    TEST_FIXTURE(VigenereABC, WhitespaceInText) {
        CHECK_THROW(v.encrypt("HELLO WORLD"),std::invalid_argument);
    }
    TEST_FIXTURE(VigenereABC, NewlineInText) {
        CHECK_THROW(v.encrypt("HELLO\nWORLD"),std::invalid_argument);
    }
    TEST_FIXTURE(VigenereABC, DigitsInText) {
        CHECK_THROW(v.encrypt("HELL0W0RLD"),std::invalid_argument);
    }
}

// Сценарии тестирования расшифрования
SUITE(DecryptTest)
{
    // регистр шифротекста
    TEST_FIXTURE(VigenereABC, UpperCaseCipherText) {
        CHECK_EQUAL("HELLO", v.decrypt("HFNLP"));
    }
    TEST_FIXTURE(VigenereABC, LowCaseCipherText) {
        CHECK_EQUAL("HELLO", v.decrypt("hfnlp"));
    }
    TEST_FIXTURE(VigenereABC, MixCaseCipherText) {
        CHECK_EQUAL("HELLO", v.decrypt("HfNlP"));
    }
    // длина шифротекста
    TEST_FIXTURE(VigenereABCXYZ, ShortCipherText) {
        CHECK_EQUAL("HELLO", v.decrypt("HFNIM"));
    }
    TEST_FIXTURE(VigenereABCXYZ, EqualCipherText) {
        CHECK_EQUAL("ALPINE", v.decrypt("AMRFLD"));
    }
    TEST_FIXTURE(VigenereABCXYZ, LongCipherText) {
        CHECK_EQUAL("LISSABON", v.decrypt("LJUPYAOO"));
    }
    // максимальный сдвиг
    TEST_FIXTURE(VigenereZZZ, MaxShiftCipherText) {
        CHECK_EQUAL("ABCDEFGHIJKLMNOPQRSTUVWXYZ",v.decrypt("ZABCDEFGHIJKLMNOPQRSTUVWXY"));
    }
    // недопустимые символы в шифротексте
    TEST_FIXTURE(VigenereABC, CommaInCipherText) {
        CHECK_THROW(v.decrypt("HFNLP,YOSND"),std::invalid_argument);
    }
    TEST_FIXTURE(VigenereABC, WhitespaceInCipherText) {
        CHECK_THROW(v.decrypt("HFNLP YOSND"),std::invalid_argument);
    }
    TEST_FIXTURE(VigenereABC, NewlineInCipherText) {
        CHECK_THROW(v.decrypt("HFNLP\nYOSND"),std::invalid_argument);
    }
    TEST_FIXTURE(VigenereABC, DigitsInCipherText) {
        CHECK_THROW(v.decrypt("HFNLPY05ND"),std::invalid_argument);
    };
}
/*
#include <UnitTest++/TestReporterStdout.h>
auto RunSuite (const char* SuiteName)
{
        UnitTest::TestReporterStdout reporter;
        UnitTest::TestRunner runner(reporter);
        return runner.RunTestsIf(UnitTest::Test::GetTestList(), SuiteName, UnitTest::True(), 0);
}
*/
int main(int argc, char **argv)
{
    // run all tests
    return UnitTest::RunAllTests();
    // return RunSuite("KeyTest");
}
