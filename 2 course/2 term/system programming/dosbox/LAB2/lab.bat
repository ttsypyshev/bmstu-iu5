@echo off 

IF "%1"=="" GOTO NO_PARAMETERS
IF "%2"=="" GOTO NO_PARAMETERS

:MAIN_MENU
CLS
ECHO 1. Вывести сообщение
ECHO 2. Имитация команды PATH
ECHO 3. Вывести параметры
ECHO 4. Вывести справку из файла
ECHO 5. Выход

choice /C:12345 /N "Выберите пункт меню:"code .
echo.
IF ERRORLEVEL 5 GOTO EXIT
IF ERRORLEVEL 4 GOTO DISPLAY_REFERENCE
IF ERRORLEVEL 3 GOTO DISPLAY_PARAMETERS
IF ERRORLEVEL 2 GOTO IMITATE_PATH
IF ERRORLEVEL 1 GOTO DISPLAY_MESSAGE

goto EXIT

:DISPLAY_MESSAGE
echo Вывод сообщения на экран:
echo Работа выполнена студентом группы ИУ5-41Б Цыпышев Т.А.
pauseW
goto MAIN_MENU

:IMITATE_PATH
echo Команда по варианту:
echo Текущий путь (PATH):
echo %PATH%
pause
goto MAIN_MENU

:DISPLAY_PARAMETERS
echo Вывод параметров:
echo Первый параметр: %1
echo Второй параметр: %2
pause
goto MAIN_MENU

:DISPLAY_REFERENCE
echo Вывод справки из файла:
type %2
pause
goto MAIN_MENU

:EXIT
IF "%1"=="y" CLS
echo Выход. До свидания!
pause
EXIT /B

:NO_PARAMETERS
ECHO Необходимо указать параметры командной строки.
ECHO Пример: lab2.bat y reference.txt
EXIT /B 1