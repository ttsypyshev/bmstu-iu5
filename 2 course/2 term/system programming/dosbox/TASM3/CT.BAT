REM ECHO
REM Фаза редактирования исходного модуля
REM notepad %1.asm
REM  Asm_ed.exe %1.asm
REM Фаза компиляции
tasm /l /zi /c %1.asm
REM Фаза редактирования связей
tlink /m /v /l %1.obj
PAUSE
REM Фаза отладки
 td %1.exe
REM EXIT