; Лабораторная работа №4
;Цыпышев Т.А. ИУ5-41 Вар. 20
;===============================================================================
PRGR SEGMENT                           		; Начало сегмента PRGR
	             ASSUME CS:PRGR, DS:DATA   	; Предполагаемые сегменты кода и данных

	BEGIN:                                 	; Метка начала программы
	             MOV    AX, DATA           	; Помещаем адрес сегмента данных в регистр AX
	             MOV    DS, AX             	; Загружаем регистр DS адресом сегмента данных
	             MOV    AX, 02h            	; Помещаем значение 02h в регистр AX
	             INT    10h                	; Вызываем прерывание 10h для установки видеорежима
	             MOV    DX, DS             	; Помещаем адрес сегмента данных в регистр DX
	             MOV    ES, DX             	; Копируем адрес сегмента данных из DX в ES
	             MOV    BX, OFFSET HEXTB   	; Помещаем смещение HEXTB в регистр BX
	             MOV    CX, 20             	; Помещаем значение 20 в регистр CX
	             MOV    AX, 0080h          	; Помещаем значение 0080h в регистр AX
	             CALL   PRINT_HEADER       	; Вызываем процедуру печати заголовка

	СYCLE:                                 	; Метка цикла СYCLE
	             CALL   HEX                	; Вызываем процедуру HEX
	             CALL   PUTCH              	; Вызываем процедуру PUTCH
	             CMP    CX, 1              	; Сравниваем значение в CX с 1
	             JE     END_СYCLE          	; Если CX равен 1, переходим к метке TEST1
				 
	             CALL   PRINT_LINE         	; Вызываем процедуру печати линии
	             MOV    AH, 00             	; Помещаем значение 00 в регистр AH
	             INC    AX                 	; Увеличиваем значение в AX на 1
	             LOOP   СYCLE              	; Уменьшаем значение в CX и переходим к СYCLE

END_СYCLE:                             		; Метка END_СYCLE
	             CALL   PRINT_FOOTER       	; Вызываем процедуру печати нижнего колонтитула
	             MOV    AH, 09h            	; Помещаем значение 09h в регистр AH
	             MOV    DX, OFFSET MSG     	; Помещаем смещение MSG в регистр DX
	             INT    21h                	; Вызываем прерывание 21h (для вывода сообщения)
	             CALL   CLRF               	; Вызываем процедуру очистки экрана

	CHECK_INPUT:                           	; Метка CHECK_INPUT
	             CALL   GETCH              	; Вызываем процедуру получения символа
	             CMP    AL, '*'            	; Сравниваем символ с '*'
	             JE     EXIT_PROGRAM       	; Если символ - '*', переходим к выходу из программы
	             MOV    CX, 20             	; Помещаем значение 20 в регистр CX
	             MOV    AH, 0              	; Помещаем значение 0 в регистр AH
	             JMP    СYCLE              	; Переходим к метке СYCLE

	EXIT_PROGRAM:                          	; Метка EXIT_PROGRAM
	             MOV    AH, 09h            	; Помещаем значение 09h в регистр AH
	             MOV    DX, OFFSET EXIT_MSG	; Помещаем смещение EXIT_MSG в регистр DX
	             INT    21h                	; Вызываем прерывание 21h (для вывода сообщения)
	             MOV    AH, 4CH            	; Устанавливаем функцию завершения программы
	             MOV    AL, 0              	; Устанавливаем код возврата 0
	             INT    21H                	; Вызываем прерывание для завершения программы

	; - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
GETCH PROC
	             MOV    AH, 01h            	; Установка номера функции для чтения символа с клавиатуры
	             INT    21h                	; Вызов прерывания 21h для чтения символа
	             RET                       	; Возвращение из процедуры
GETCH ENDP

	; - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
PRINT_HEADER PROC
	             PUSH   AX                 	; Сохранение регистра AX на стеке
	             PUSH   BX                 	; Сохранение регистра BX на стеке
	             MOV    AH, 02h
	             MOV    DL, 218
	             INT    21h                	; Вывод символа ┌
	             MOV    DL, 196
	             INT    21h                	; Вывод символа ─
	             INT    21h                	; Вывод символа ─
	             INT    21h                	; Вывод символа ─
	             INT    21h                	; Вывод символа ─
	             INT    21h                	; Вывод символа ─
	             MOV    DL, 191
	             INT    21h                	; Вывод символа ┐
	             CALL   CLRF               	; Вызов процедуры для очистки экрана
	             POP    BX                 	; Восстановление регистра BX из стека
	             POP    AX                 	; Восстановление регистра AX из стека
	             RET                       	; Возвращение из процедуры
PRINT_HEADER ENDP

	; - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
PRINT_LINE PROC
	             PUSH   AX
	             PUSH   BX
	             MOV    AH, 02h
	             MOV    DL, 195
	             INT    21h                	; Вывод символа ┬
	             MOV    DL, 196
	             INT    21h                	; Вывод символа ─
	             INT    21h                	; Вывод символа ─
	             INT    21h                	; Вывод символа ─
	             INT    21h                	; Вывод символа ─
	             INT    21h                	; Вывод символа ─
	             INT    21h                	; Вывод символа ─
	             MOV    DL, 180
	             INT    21h                	; Вывод символа ├
	             CALL   CLRF               	; Очистка экрана
	             POP    BX
	             POP    AX
	             RET
PRINT_LINE ENDP

	; - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
PUTCH PROC
	             PUSH   AX
	             PUSH   BX
	             MOV    AH, 02h
	             MOV    DL, 179
	             INT    21h                	; Вывод символа │
	             POP    BX
	             POP    AX
	             PUSH   AX
	             PUSH   BX
	             MOV    AH, 02h
	             MOV    DL, AL
	             INT    21h                	; Вывод символа
	             MOV    AH, 09h
	             MOV    DX, OFFSET DEF
	             INT    21h                	; Вывод текста " - "
	             MOV    AH, 40h
	             MOV    BX, 1
	             PUSH   CX
	             MOV    CX, 2
	             MOV    DX, OFFSET HEXDGT
	             INT    21h                	; Вывод шестнадцатеричных символов
	             POP    CX
	             MOV    AH, 02h
	             MOV    DL, 179
	             INT    21h                	; Вывод символа │
	             CALL   CLRF               	; Очистка экрана
	             POP    BX
	             POP    AX
	             RET
PUTCH ENDP

	; - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
PRINT_FOOTER PROC
	             MOV    AH, 02h
	             MOV    DL, 192
	             INT    21h                	; Вывод символа └
	             MOV    DL, 196
	             INT    21h                	; Вывод символа ─
	             INT    21h                	; Вывод символа ─
	             INT    21h                	; Вывод символа ─
	             INT    21h                	; Вывод символа ─
	             INT    21h                	; Вывод символа ─
	             INT    21h                	; Вывод символа ─
	             MOV    DL, 217
	             INT    21h                	; Вывод символа ┘
	             CALL   CLRF               	; Очистка экрана
	             RET
PRINT_FOOTER ENDP

	; - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
CLRF PROC
	             MOV    AH, 02h
	             MOV    DL, 10
	             INT    21h                	; Перевод каретки
	             MOV    AH, 02h
	             MOV    DL, 13
	             INT    21h                	; Перевод строки
	             RET
CLRF ENDP

	; - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
HEX PROC
	             PUSH   AX
	             MOV    SI, 0
	             PUSH   AX
	             SHR    AL, 1
	             SHR    AX, 1
	             SHR    AX, 1
	             SHR    AX, 1
	             XLAT
	             MOV    HEXDGT[SI], AL     	; Сохранение старших 4 бит в массиве HEXDGT
	             INC    SI
	             POP    AX
	             AND    AL, 00001111b
	             XLAT
	             MOV    HEXDGT[SI], AL     	; Сохранение младших 4 бит в массиве HEXDGT
	             POP    AX
	             RET
HEX ENDP

PRGR ENDS
;==================================================================================

DATA SEGMENT
	HEXTB    DB '0123456789ABCDEF'
	HEXDGT   DB 2 DUP ('*')
	MSG      DB 'Press any key to continue or "*" to exit... $'
	EXIT_MSG DB 'Exiting the program... $'
	DEF      DB ' - $'
DATA ENDS
;==================================================================================

STK SEGMENT STACK
	    DB 256 DUP (0)
STK ENDS
;==================================================================================

END BEGIN
