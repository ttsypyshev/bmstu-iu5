# ОС Ubuntu. Управление процессами

## Мониторинг и управление процессами с помощью графической утилиты «Системный монитор»

### Информация о процессе

![](/5%20term/operating%20systems/lab%205/Screenshots/info.png)

### Приоритет процесса

![](/5%20term/operating%20systems/lab%205/Screenshots/priority.png)

### Убийство процесса

![](/5%20term/operating%20systems/lab%205/Screenshots/kill.png)

### Ресурсы

![](/5%20term/operating%20systems/lab%205/Screenshots/resouces.png)

### Файловое хранилище

![](/5%20term/operating%20systems/lab%205/Screenshots/files.png)

## Мониторинг и управление процессами с помощью утилит командной строки

### Получить общую информацию о системе

1. Информация о текущем интерпретаторе команд:

   ```bash
   echo $SHELL
   ```

2. Информация о текущем пользователе:

   ```bash
   whoami
   ```

3. Информация о текущем каталоге:

   ```bash
   pwd
   ```

4. Информация об оперативной памяти и области подкачки:

   ```bash
   free -h
   ```

5. Информация о дисковой памяти:

   ```bash
   df -h
   ```

### Получение информации о процессах

1. Получение идентификатора текущего процесса (PID):

   ```bash
   echo $$
   ```

2. Получение идентификатора родительского процесса (PPID):

   ```bash
   echo $PPID
   ```

3. Получение идентификатора процесса по его имени (например, init):

   ```bash
   pgrep init
   ```

4. Получение информации о выполняющихся процессах с помощью команды ps:

   ```bash
   ps aux
   ```

   Этот вывод покажет все процессы, выполняющиеся в системе, с информацией о пользователе, PID, CPU, памяти и т.д.

### Выполнение команд управления процессами

1. Получение информации о выполняющихся процессах текущего пользователя в текущем интерпретаторе:

   ```bash
   ps -u $(whoami)
   ```

2. Определение текущего значения приоритета по умолчанию:

   ```bash
   nice -n 0
   ```

3. Запуск командного процессора bash с понижением приоритета:

   ```bash
   nice -n 10 bash
   ```

   (Здесь `10` — это значение nice, указывающее понижение приоритета.)

4. Определение PID запущенного командного процессора:

   После запуска команды, в новом терминале выполните:

   ```bash
   echo $$
   ```

   Если вы запустили новый процесс `bash`, PID будет отображен.

5. Установка приоритета командного процессора равным 5:

   Вы можете использовать команду `renice`:

   ```bash
   sudo renice 5 -p <PID>
   ```

   Замените `<PID>` на идентификатор процесса, полученный на предыдущем шаге.

6. Получение информации об активных процессах пользователя, включая их приоритеты, с помощью утилиты `top`:

   Запустите команду:

   ```bash
   top
   ```

   В верхней части экрана будет показана информация о текущих процессах и их приоритетах (в столбце `NI`).