# Учебный пример реализации программы зашифрования/расшифрования методом Виженера с простым диалоговым интерфейсом

## Функциональный тест

Функциональный тест проверяет работу интерфейса:

  * ключ устанавливается;
  * зашифрование/расшифрование выполняется;
  * ошибки в интерфейсе обнаруживаются;
  * исключения от модуля Vigenere обрабатываются.
 
Тестовый сценаций 

|  Сценарий                        | Тест | Предусловие              | Тестовое действие       | Постусловие                    | Ожидаемый результат                               |
|----------------------------------|------|--------------------------|-------------------------|--------------------------------|---------------------------------------------------|
| **Зашифрование/расшифрование**   | **1**|                          |                         |                                 |                                       |
| Ввод ключа                       | 1.1  |  Нет                     | Ввести ключ ABC         | Ввести 0 (завершить программу) | Появление приглашения на ввод действия            |
| Зашифрование                     | 1.2  |Ввести ключ ABC, Ввести 1 |Вести текст HELLO        | Ввести 0  (завершить программу)| Вывод "Encrypted text: HFNLP"                     |
| Расшифрование                    | 1.3  | Ввести ключ ABC, Ввести 2|Вести текст HFNLP        | Ввести 0  (завершить программу)| Вывод "Decrypted text: HELLO"                     |
|  **Ошибка интерфейса**           | **2**|                          |                         |                                |                                                   |
| Ввод целого числа больше 2       | 2.1  | Ввести ключ ABC          |  Ввести 3               | Ввести 0 (завершить программу) |  Сообщение об ошибке, приглашения на ввод действия|
| Ввод отрицательного целого числа | 2.2  | Ввести ключ ABC          |  Ввести -3              | Ввести 0 (завершить программу) |  Сообщение об ошибке, приглашения на ввод действия|
| Ввод не целого числа             | 2.3  | Ввести ключ ABC          | Вести 1.123             | Нет                            | Сообщение об ошибке, аварийное завершение         |
| Ввод строки не цифр              | 2.4  | Ввести ключ ABC          |  Вести ONE              | Нет                            | Сообщение об ошибке, аварийное завершение         |
| Ввод строки, начинающейся с цифры| 2.5  | Ввести ключ ABC          | 2HELLO                  | Нет                            | Сообщение об ошибке, аварийное завершение         |
| Ввод строки с пробелом           | 2.6  | Ввести ключ ABC          | 2 HELLO                 | Нет                            | Сообщение об ошибке, аварийное завершение         |
| **Ошибка модуля Vigenere**       | **3**|                          |                         |                                |                                                   |
| Ошибка ключа                     | 3.1  | Нет                      | Ввести ключ AAA         | Нет                            | Сообщение об ошибке, аварийное завершение         |
| Ошибка текста                    | 3.2  | Ввести ключ ABC, Ввести 1| Ввести текст HELLO WORLD| Нет                            | Сообщение об ошибке, приглашения на ввод действия |
| Ошибка шифртекста                | 3.3  | Ввести ключ ABC, Ввести 2| Ввести текст HFNLP YOSND| Нет                            | Сообщение об ошибке, приглашения на ввод действия |

Тестовый сценарий предусматривает ручное выполнение

--------------------------------------------------

(с) ИБСТ ПГУ 2020-2024
