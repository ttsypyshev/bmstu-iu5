#!/bin/bash

if [ $# -eq  0 ]; then
	echo "Ошибка: Введите параметр."
       	exit 1
fi 

filename=${1}

if [ ! -f $filename ]; then
	echo "Ошибка: Файл '$filename' отсутствует."
	exit 1
fi

DATE_BIN=$(command -v date)
DATE=`${DATE_BIN} +%y-%m-%d--%H:%M:%S`

echo "Файл: $filename"
echo "Дата и время: $DATE"
cat "$filename"
