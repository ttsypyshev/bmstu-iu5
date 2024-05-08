; Лабораторная работа №6
; Цыпышев Т.А. ИУ5-41 Вар. 20
;===============================================================================

prgr segment
	                       assume CS:prgr,DS:data

	begin:                                                  	; Начало программы
	                       mov    AX,data
	                       mov    ES,AX

	                       mov    SI,80h
	                       mov    DI,offset destination
	                       mov    CL,[SI]
	                       cmp    CL,0
	                       je     nope
	                       mov    CH,0
	                       push   CX
	                       inc    SI
	                       inc    SI
	                       cld
	                       rep    movsb
	                       push   ES
	                       pop    DS
	                       jmp    layer1
	nope:                                                   	; Нет параметров
	                       mov    AX,data
	                       mov    DS,AX
	                       mov    AH,09h
	                       mov    DX,offset error_1
	                       int    21h
	                       jmp    exit_program

	layer1:                                                 	; Первый слой проверки
	                       mov    SI,offset destination
	                       mov    DI,offset tmp1
	                       mov    CL,9
	                       rep    movsb
	check_first_1:                                          	; Проверка первого параметра
	                       mov    DI,offset parameter1_1
	                       mov    SI,offset tmp1
	                       mov    CL,9
	                       repe   cmpsb
	                       jne    check_first_2
	                       jmp    layer2
	check_first_2:                                          	; Проверка второго варианта первого параметра
	                       mov    DI,offset parameter1_2
	                       mov    SI,offset tmp1
	                       mov    CL,9
	                       repe   cmpsb
	                       jne    print_error_1
	                       jmp    layer2
	print_error_1:                                          	; Вывод ошибки
	                       mov    AH,09h
	                       mov    DX,offset error_2
	                       int    21h
	                       jmp    exit_program

	layer2:                                                 	; Второй слой проверки
	                       mov    SI,offset destination
	                       add    SI,10
	                       mov    DI,offset tmp2
	                       mov    CL,1
	                       rep    movsb
	second_check_1:                                         	; Проверка второго параметра
	                       mov    DI,offset parameter2_1
	                       mov    SI,offset tmp2
	                       mov    CL,1
	                       repe   cmpsb
	                       jne    second_check_2
	                       mov    falg[1],1
	                       jmp    third_check_2
	second_check_2:                                         	; Проверка второго варианта второго параметра
	                       mov    DI,offset parameter2_2
	                       mov    SI,offset tmp2
	                       mov    CL,1
	                       repe   cmpsb
	                       jne    third_check_1
	                       jmp    third_check_2

	third_check_1:                                          	; Первая проверка третьего параметра
	                       mov    SI,offset destination
	                       add    SI,10
	                       mov    DI,offset tmp3
	                       mov    CL,4
	                       rep    movsb
	                       mov    DI,offset password
	                       mov    SI,offset tmp3
	                       mov    CL,4
	                       repe   cmpsb
	                       jne    print_error_3
	                       jmp    output
	third_check_2:                                          	; Вторая проверка третьего параметра
	                       mov    SI,offset destination
	                       add    SI,12
	                       mov    DI,offset tmp3
	                       mov    CL,4
	                       rep    movsb
	                       mov    DI,offset password
	                       mov    SI,offset tmp3
	                       mov    CL,4
	                       repe   cmpsb
	                       jne    print_error_3
	                       jmp    output
	print_error_3:                                          	; Вывод ошибки третьего параметра
	                       mov    AH,09h
	                       mov    DX,offset error_3
	                       int    21h
	                       jmp    exit_program
	
	output:                                                 	; Вывод
	                       mov    AX,02h
	                       int    10h
	clear:                                                  	; Очистка
	                       cmp    falg[1],1
	                       jne    input_instructions_2
	                       mov    AH,09h
	                       mov    DX,offset help_text_1
	                       int    21h
	                       CALL   CLRF
	                       mov    AH,09h
	                       mov    DX,offset help_text_2
	                       int    21h
	                       CALL   CLRF
	                       CALL   CLRF
	input_instructions:                                     	; Ввод инструкций
	                       mov    AH,09h
	                       mov    DX,offset info_text
	                       int    21h
	                       mov    AH,01h
	                       int    21h
	                       cmp    AL,42
	                       je     next_step
	                       mov    AH,02h
	                       mov    DL,8
	                       int    21h
	                       mov    AH,02h
	                       mov    DL,0
	                       int    21h
	                       mov    AH,02h
	                       mov    DL,13
	                       int    21h
	                       loop   input_instructions
	                       jmp    greeting_message

	input_instructions_2:                                   	; Ввод инструкций (вторая часть)
	                       mov    AH,09h
	                       mov    DX,offset hlpno
	                       int    21h
	                       mov    AH,01h
	                       int    21h
	                       cmp    AL,13
	                       je     next_step
	                       mov    AH,02h
	                       mov    DL,8
	                       int    21h
	                       mov    AH,02h
	                       mov    DL,0
	                       int    21h
	                       mov    AH,02h
	                       mov    DL,13
	                       int    21h
	                       loop   input_instructions_2

	next_step:                                              	; Следующий шаг
	                       CALL   CLRF
	                       CALL   CLRF

	greeting_message:                                       	; Приветственное сообщение
	                       mov    AH,09h
	                       mov    DX,offset parameter_line
	                       int    21h
	                       mov    AH,40h
	                       mov    BX,1
	                       pop    CX
	                       mov    DX,offset destination
	                       int    21h
	                       CALL   CLRF
	                       mov    AH,40h
	                       mov    BX,1
	                       mov    CX,23
	                       mov    DX,offset dashes
	                       int    21h

	                       CALL   CLRF
	                       mov    AH,09h
	                       mov    DX,offset frst
	                       int    21h
	                       mov    AH,40h
	                       mov    BX,1
	                       mov    CX,9
	                       mov    DX,offset tmp1
	                       int    21h

	                       CALL   CLRF
	                       mov    AH,09h
	                       cmp    falg[1],1
	                       jne    print_second_parameter
	                       mov    DX,offset scnd1
	                       int    21h
	                       mov    AH,40h
	                       mov    BX,1
	                       mov    CX,1
	                       mov    DX,offset tmp2
	                       jmp    print_third_parameter

	print_second_parameter:                                 	; Вывод второго параметра
	                       mov    DX,offset scnd2

	print_third_parameter:                                  	; Вывод третьего параметра
	                       int    21h
	                       CALL   CLRF
	                       mov    AH,09h
	                       mov    DX,offset thrd
	                       int    21h
	                       mov    AH,40h
	                       mov    BX,1
	                       mov    CX,9
	                       mov    DX,offset stars
	                       int    21h

	                       CALL   CLRF
	                       CALL   CLRF
	                       mov    AH,09h
	                       mov    DX,offset exit_instruction
	                       int    21h
	                       CALL   GETCH
	                       mov    AH,02h
	                       mov    DL,8
	                       int    21h
	                       mov    AH,02h
	                       mov    DL,0
	                       int    21h
	                       CALL   CLRF
	                       cmp    falg[1],1
	                       jne    exit_program
	                       mov    AX,02h
	                       int    10h

	exit_program:                                           	; Конец программы
	                       mov    AX,4C00h
	                       int    21h

CLRF proc
	                       mov    AH,02h
	                       mov    DL,10
	                       int    21h
	                       mov    AH,02h
	                       mov    DL,13
	                       int    21h
	                       RET
CLRF endp

GETCH proc
	                       mov    AH,01h
	                       int    21h
	                       RET
GETCH endp

prgr ends

data segment
	parameter_line   db 'Line of parameters are: $'
	frst             db '+ first parameter is: $'
	scnd1            db '+ second parameter is: $'
	scnd2            db '- there is no second parameter $'
	thrd             db '+ third parameter is: $'
	falg             db 2 dup (0)
	dashes           db 23 dup ('-')
	exit_instruction db 'Press any key to exit... $'
	destination      db 20 dup ('#')
	error_1          db 'There are no paremeters$'
	error_2          db 'Error of the first parameter$'
	error_3          db 'Access denied$'
	parameter1_1     db 'Tsypyshev'
	parameter1_2     db 'tsypyshev'
	parameter2_1     db 'y'
	parameter2_2     db 'n'
	tmp1             db 9 dup ('1')
	tmp2             db 1 dup ('2')
	tmp3             db 9 dup ('3')
	password         db '1234'
	help_text_1      db 'This program just shows, how to use launch-parameters$'
	help_text_2      db 'created by Ivanov Ivan, student of IU5-41 group, var.20$'
	info_text        db 'Press * to continue $'
	stars            db 9 dup ('*')
	hlpno            db 'There is no spoon... Press ENTER $'

data ends

stk segment stack
	    db 256 dup (0)
stk ends

end begin
