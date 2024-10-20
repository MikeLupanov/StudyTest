#!/bin/bash
prog=./vigenere-command
fail_counter=0
all_counter=0

function RUN_STDOUT {
	echo -e "\nТест $1: $2" 
	res=$($2)
	echo "$res"
	echo -n "Тест $1 "
	((all_counter++)) 
}

function RUN_STDERR {
	echo -e "\nТест $1: $2" 
	res=$( { $2; } 2>&1 )
	echo "$res"
	echo -n "Тест $1 "
	((all_counter++)) 
}


# Тест 1.1, зашифрование, позитивный
# Ожидаемый результат:
# Encrypted: HELLO --> HFNLP
RUN_STDOUT 1.1 "$prog -k ABC -e HELLO"
grep -Fqw HFNLP <<< $res && \
echo OK || { echo FAILED; ((fail_counter++)); }    

# Тест 1.2, расшифрование, поз{ $prog -h; } 2>&1итивный
# Ожидаемый результат:
# Decrypted: HFNLP --> HELLO
RUN_STDOUT 1.2 "$prog -k ABC -d HFNLP"
grep -Fqw HELLO <<< $res && \
echo OK || { echo FAILED; ((fail_counter++)); }    

# Тест 1.3, несколько операций зашифрования/расшифрования, позитивный
# Ожидаемый результат:
# Decrypted: ITVAODUM --> ISTANBUL 
# Encrypted: LISSABON --> LJUSBDOO 
# Decrypted: WPTLE --> WORLD 
# Encrypted: HELLO --> HFNLP
RUN_STDOUT 1.3 "$prog -k ABC -e HELLO -d WPTLE -e LISSABON -d ITVAODUM"
grep -Fwq "ISTANBUL" <<< $res && \
grep -Fwq "LJUSBDOO" <<< $res && \
grep -Fwq "WORLD" <<< $res && \
grep -Fwq "HFNLP" <<< $res && \
echo OK || { echo FAILED; ((fail_counter++)); }

# Тест 2.1, вывод подсказки по параметру -h, позитивный
# Ожидаемый результат: текст подсказки
RUN_STDERR 2.1 "$prog -h"
grep -Fqw "Использование:" <<< $res && \
echo OK || { echo FAILED; ((fail_counter++)); }

# Тест 2.2, вывод подсказки при запуске без параметров, позитивный
# Ожидаемый результат: текст подсказки
RUN_STDERR 2.2 "$prog"
grep -Fqw "Использование:" <<< $res && \
echo OK || { echo FAILED; ((fail_counter++)); }

# Тест 3.1, не задан ключ, негативный
# Ожидаемый результат: текст ошибки, текст подсказки
RUN_STDERR 3.1 "$prog -e HELLO"
grep -Fqw "Ошибка:" <<< $res && \
grep -Fqw "Использование:" <<< $res && \
echo OK || { echo FAILED; ((fail_counter++)); }

# Тест 3.2, не задан текст, негативный
# Ожидаемый результат: текст ошибки, текст подсказки
RUN_STDERR 3.2 "$prog -k ABC"
grep -Fqw "Ошибка:" <<< $res && \
grep -Fqw "Использование:" <<< $res && \
echo OK || { echo FAILED; ((fail_counter++)); }

# Тест 3.3, несуществующий параметр, негативный
# Ожидаемый результат: текст ошибки, текст подсказки
RUN_STDERR 3.3 "$prog -k ABC -s HELLO"
grep -Fqw "Ошибка:" <<< $res && \
grep -Fqw "Использование:" <<< $res && \
echo OK || { echo FAILED; ((fail_counter++)); }

# Тест 3.4, нет значения параметра, негативный
# Ожидаемый результат: текст ошибки, текст подсказки
RUN_STDERR 3.4 "$prog -k -e HELLO"
grep -Fqw "Ошибка:" <<< $res && \
grep -Fqw "Использование:" <<< $res && \
echo OK || { echo FAILED; ((fail_counter++)); }

# Тест 3.5, нет значения параметра, негативный
# Ожидаемый результат: текст ошибки, текст подсказки
RUN_STDERR 3.5 "$prog -k ABC -e"
grep -Fqw "Ошибка:" <<< $res && \
grep -Fqw "Использование:" <<< $res && \
echo OK || { echo FAILED; ((fail_counter++)); }

# Тест 4.1, ошибка Vigenere - ключ, негативный
# Ожидаемый результат: текст ошибки
RUN_STDERR 4.1 "$prog -k AAAA -e HELLO"
grep -Fqw "Vigenere:" <<< $res && \
grep -Fqw "key" <<< $res && \
echo OK || { echo FAILED; ((fail_counter++)); }

# Тест 4.2, ошибка Vigenere - текст, негативный
# Ожидаемый результат: текст ошибки
RUN_STDERR 4.2 "$prog -k ABC -e HELLO,WORLD"
grep -Fqw "Vigenere:" <<< $res && \
grep -Fqw "message" <<< $res && \
echo OK || { echo FAILED; ((fail_counter++)); }

echo -e "\nTest running: $all_counter"
echo "Test failed:  $fail_counter"
