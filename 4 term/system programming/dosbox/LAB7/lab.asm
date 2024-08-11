; Лабораторная работа №7
; Цыпышев Т.А. ИУ5-41 Вар. 20
;===============================================================================

prgr SEGMENT
                        ASSUME CS:prgr

     BEGIN:             
                        JMP    MAIN

     ; Сообщение о помощи
     help_message       DB     'Цыпышев Тимофей ИУ5-41Б Варю 20$'
     buffer             DB     256 DUP(0)
     flag_var           DB     0
     input_message      DB     'Введите число (длинный адрес: НННН:НННН)> $'
     digits             DW     10000,1000,100,10,1
     hex_digits         DB     '0123456789ABCDEF$'

MAIN PROC
                        CALL   CLRSCR
     main_loop:         
                        MOV    AH,09H                                            ; Вывод сообщения о вводе числа
                        MOV    DX,OFFSET input_message
                        INT    21H

                        call   INPUT                                             ; Ввод числа
                        cmp    flag_var,1
                        je     main_exit
                        push   BX

                        mov    dl,'='                                            ; Вывод символа "="
                        call   PUTCH

                        mov    dx,bx                                             ; Вывод числа в шестнадцатеричном виде
                        call   HEX_WRITE

                        mov    dl,' '                                            ; Вывод пробела
                        call   PUTCH

                        pop    BX
                        call   HEX_TO_DECIMAL                                    ; Вывод числа в десятичном виде

                        call   CLRF                                              ; Переход на новую строку
                        MOV    CX,2                                              ; Оставшееся количество итераций
                        LOOP   main_loop

     main_exit:         
                        MOV    AH,09H                                            ; Вывод сообщения о помощи
                        MOV    DX,OFFSET help_message
                        INT    21H
                        CALL   GETCH
                        CALL   CLRSCR
                        CALL   QUIT_PROGRAM
MAIN ENDP

     ; Процедура ввода числа
INPUT PROC
                        mov    bp,0                                              ; Инициализация счетчика
                        mov    bx,0                                              ; Инициализация результата
     in_loop:           
                        call   GETCH_NON_BLOCKING                                ; Получение символа
                        mov    dl,al
                        jmp    check

     shifting:          
                        call   PUTCH                                             ; Вывод символа
                        pop    ax                                                ; Получение символа из стека
                        mov    ah,0
                        shl    bx, 4                                             ; Сдвиг результата на 4 бита влево

                        add    bx,ax                                             ; Добавление новой цифры к результату
                        inc    bp                                                ; Инкремент счетчика
                        cmp    bp,4                                              ; Проверка количества введенных цифр
                        je     exit                                              ; Если введены 4 цифры, выход
                        jmp    in_loop

     check:             
                        cmp    al,'*'                                            ; Проверка на символ завершения ввода
                        jne    numder                                            ; Если не "*", обработка чисел
                        mov    flag_var,1                                        ; Установка флага завершения ввода
                        jmp    exit

     numder:            
                        cmp    al,'0'                                            ; Проверка на цифру
                        jb     big_case                                          ; Если меньше "0", переход к обработке больших символов

                        cmp    al,'9'                                            ; Проверка на цифру
                        ja     big_case                                          ; Если больше "9", переход к обработке больших символов

                        sub    al,'0'                                            ; Преобразование символа в число
                        push   ax                                                ; Запись числа в стек
                        jmp    shifting                                          ; Переход к сдвигу

     big_case:          
                        cmp    al,'A'                                            ; Проверка на символ от "A" до "F"
                        jb     small_case                                        ; Если меньше "A", переход к обработке маленьких символов

                        cmp    al,'F'                                            ; Проверка на символ от "A" до "F"
                        ja     small_case                                        ; Если больше "F", переход к обработке маленьких символов

                        sub    al,'A'-10                                         ; Преобразование символа в число
                        push   ax                                                ; Запись числа в стек
                        jmp    shifting                                          ; Переход к сдвигу

     small_case:        
                        cmp    al,'a'                                            ; Проверка на символ от "a" до "f"
                        jb     in_loop                                           ; Если меньше "a", продолжение ввода

                        cmp    al,'f'                                            ; Проверка на символ от "a" до "f"
                        ja     in_loop                                           ; Если больше "f", продолжение ввода

                        sub    al,'a'-10                                         ; Преобразование символа в число
                        push   ax                                                ; Запись числа в стек
                        jmp    shifting                                          ; Переход к сдвигу

     exit:              
                        ret
INPUT ENDP

     ; Процедура вывода числа в шестнадцатеричном виде
HEX PROC
                        push   ds
                        push   ax
                        push   bx
                        push   cx
                        push   cs
                        pop    ds

                        lea    bx,hex_digits
                  
                        mov    al,dh
                        shr    al, 4
                        xlat
                        push   dx
                        mov    dl,al
                        mov    ah,02h
                        int    21h

                        mov    al,dh
                        and    al,00001111b
                        xlat
                        mov    dl,al
                        mov    ah,02h
                        int    21h

                        pop    dx
                        pop    cx
                        pop    bx
                        pop    ax
                        pop    ds
                        ret
HEX ENDP

     ; Процедура вывода числа в шестнадцатеричном виде, с последующим "h"
HEX_WRITE PROC
                        push   dx
                        call   HEX
                        pop    dx
                        mov    dh,dl
                        call   HEX
                        mov    dl,'h'
                        int    21h
                        ret
HEX_WRITE ENDP

     ; Процедура преобразования шестнадцатеричного числа в десятичное
HEX_TO_DECIMAL PROC
                        mov    ax,bx
                        mov    di,0
     hex_loop:          
                        mov    dx,0
                        mov    bx,digits[di]
                        div    bx
                        push   dx
                        add    ax,'0'
                        mov    dl,al
                        call   PUTCH
                        pop    ax
                        inc    di
                        inc    di
                        cmp    di,10
                        jb     hex_loop
                        RET
HEX_TO_DECIMAL ENDP

     ; Процедура вывода символа
PUTCH PROC
                        mov    ah,2
                        int    21h
                        ret
PUTCH ENDP

     ; Процедура получения символа
GETCH PROC
                        mov    ah,1
                        int    21h
                        ret
GETCH ENDP

     ; Процедура получения символа без блокировки
GETCH_NON_BLOCKING PROC
                        mov    ah,8
                        int    21h
                        ret
GETCH_NON_BLOCKING ENDP

     ; Процедура перехода на новую строку
CLRF PROC
                        mov    dl,10
                        call   PUTCH
                        mov    dl,13
                        call   PUTCH
                        ret
CLRF ENDP

     ; Процедура очистки экрана
CLRSCR PROC
                        mov    ah,00
                        mov    al,03
                        int    10h
                        RET
CLRSCR ENDP

     ; Процедура завершения программы
QUIT_PROGRAM PROC
                        mov    ah,4ch
                        mov    al,00h
                        int    21h
QUIT_PROGRAM ENDP

prgr ENDS
END BEGIN
