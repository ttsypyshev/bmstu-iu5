;Лабораторная работа №5
;Цыпышев Т.А. ИУ5-41 Вар. 20
;===============================================================================

PRGR SEGMENT
	             ASSUME CS:PRGR, DS:DATA

	BEGIN:       
	             MOV    AX, DATA          	; Инициализация сегмента данных
	             MOV    DS, AX
	             CALL   INFO              	; Вызов процедуры INFO для вывода приветствия

	INIT:        
	             MOV    CX, 20            	; Установка счетчика символов в 20
	             MOV    SI, 3             	; Установка индекса начала строки в 3
	             MOV    BX, OFFSET hextb  	; Загрузка таблицы шестнадцатеричных символов

	INPUT:       
	             CALL   GETCH             	; Получение символа
	             CMP    AL, '$'           	; Проверка на конец строки
	             JE     END_LINE
	             CMP    AL, '*'           	; Проверка на символ завершения ввода
	             JE     EXIT_PROGRAM
	             CALL   HEX               	; Преобразование символа в шестнадцатеричное представление
	             DEC    CX                	; Уменьшение счетчика символов
	             JZ     END_LINE          	; Если счетчик стал равен нулю, завершаем ввод
	             JMP    INPUT             	; Повторяем ввод

	END_LINE:    
	             PUSH   BX                	; Сохранение регистров
	             PUSH   CX
	             MOV    BX, 1             	; Установка начального индекса для вывода строки
	             DEC    SI                	; Уменьшение индекса строки до последнего символа
	             MOV    CX, SI            	; Установка счетчика на количество введенных символов
	             MOV    AH, 40h           	; Услуга для вывода строки
	             MOV    DX, OFFSET line
	             INT    21h
	             MOV    CX, 20            	; Восстановление счетчика символов
	             MOV    SI, 3             	; Восстановление индекса строки

	CLEAR:       
	             MOV    line[SI], 32      	; Очистка символов в строке
	             INC    SI
	             LOOP   CLEAR
	             POP    CX                	; Восстановление регистров
	             POP    BX
	             MOV    CX, 4
	             CALL   CLRF              	; Очистка экрана
	             LOOP   INIT              	; Повторное начало ввода

	EXIT_PROGRAM:
	             CALL   CLRF              	; Очистка экрана
	             CALL   CLRF              	; Очистка экрана
	             MOV    AH, 09h           	; Вывод сообщения о завершении программы
	             LEA    DX, msg_input_name
	             INT    21h
	             CALL   CLRF              	; Очистка экрана
	             MOV    DX, OFFSET msg
	             INT    21h
	             CALL   GETCH             	; Ожидание нажатия любой клавиши
	             MOV    AX, 02h           	; Выход из программы
	             INT    10h
	             MOV    AX, 4C00h
	             INT    21h

INFO PROC
	             MOV    AX, 02h           	; Установка видеорежима
	             INT    10h
	             MOV    AH, 09h           	; Вывод приветствия
	             MOV    DX, OFFSET greet
	             INT    21h
	             CALL   CLRF              	; Очистка экрана
	             MOV    AH, 09h           	; Вывод информации о программе
	             MOV    DX, OFFSET defl
	             INT    21h
	             CALL   CLRF              	; Очистка экрана
	             MOV    AH, 02h           	; Установка курсора в позицию
	             MOV    DL, 36
	             INT    21h
	             MOV    AH, 09h           	; Вывод дополнительной информации
	             MOV    DX, OFFSET info1
	             INT    21h
	             CALL   CLRF              	; Очистка экрана
	             MOV    AH, 09h
	             MOV    DX, OFFSET info2
	             INT    21h
	             CALL   CLRF              	; Очистка экрана
INFO ENDP

GETCH PROC
	             MOV    AH, 01h           	; Получение символа
	             INT    21h
	             RET
GETCH ENDP

CLRF PROC
	             MOV    AH, 02h           	; Вывод символов перевода строки
	             MOV    DL, 10
	             INT    21h
	             MOV    AH, 02h
	             MOV    DL, 13
	             INT    21h
	             RET
CLRF ENDP

CLRSCR PROC
	             MOV    AX, 02H           	; Очистка экрана
	             INT    10H
	             RET
CLRSCR ENDP

HEX PROC
	             PUSH   AX                	; Сохранение регистра AX
	             SHR    AL, 4             	; Сдвиг вправо на 4 бит
	             XLAT                     	; Перевод символа в шестнадцатеричный эквивалент
	             MOV    line[SI], AL      	; Сохранение первой половины шестнадцатеричного представления
	             INC    SI                	; Увеличение индекса текущего символа
	             POP    AX                	; Восстановление регистра AX
	             AND    AL, 00001111b     	; Очистка старших битов
	             XLAT                     	; Перевод символа в шестнадцатеричный эквивалент
	             MOV    line[SI], AL      	; Сохранение второй половины шестнадцатеричного представления
	             INC    SI                	; Увеличение индекса текущего символа
	             MOV    AL, 32            	; Установка пробела в строку
	             MOV    line[SI], AL      	; Сохранение пробела
	             INC    SI                	; Увеличение индекса текущего символа
	             RET
HEX ENDP

PRGR ENDS

DATA SEGMENT
	hextb          DB '0123456789ABCDEF'                    	; Таблица шестнадцатеричных символов
	line           DB 20 DUP (' = ')                        	; Буфер для хранения строки
	msg            DB 'Press any key to exit... $'          	; Сообщение о выходе
	greet          DB 'Type any chars, maximum length - 20$'	; Приветствие
	defl           DB '----------------------------------$' 	; Разделитель
	info1          DB ' - end of string$'                   	; Информация о конце строки
	info2          DB '* - end of input$'                   	; Информация о конце ввода
	msg_input_name DB 'TSYPYSHEV T.A. UI5-41 Var-20$'       	; Имя автора и номер варианта
DATA ENDS

STK SEGMENT STACK
	    DB 256 DUP (0)	; Стек
STK ENDS

END BEGIN
