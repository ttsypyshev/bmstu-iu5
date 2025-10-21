# Управление пользователями

## Создание новых пользователей

### Создание учётных записей пользователей с использованием `useradd`

```bash
useradd -m -s /bin/bash admin_stud
useradd -m -s /bin/bash stud_51
useradd -m -s /bin/bash stud_52
useradd -m -s /bin/bash stud_53
useradd -m -s /bin/bash stud_54
useradd -m -s /bin/bash stud_55
```

### Установка паролей для пользователей

```bash
echo "admin_stud:adminstud" | chpasswd
echo "stud_51:stud51" | chpasswd
echo "stud_52:stud52" | chpasswd
echo "stud_53:stud53" | chpasswd
echo "stud_54:stud54" | chpasswd
echo "stud_55:stud55" | chpasswd
```

## Назначение прав доступа пользователям и группам

### Создание группы

```bash
groupadd student
```

### Добавление пользователей в группу

```bash
usermod -aG student stud_51
usermod -aG student stud_52
usermod -aG student stud_53
usermod -aG student stud_54
usermod -aG student stud_55
```

### Добавление пользователя `admin_kaf` в группу `wheel`

Для предоставления прав администратора, добавляем пользователя в группу `wheel`, которая обычно предоставляет доступ к правам sudo:

```bash
usermod -aG wheel admin_kaf
```


## Настройка прав доступа с помощью `sudo`

### Редактирование sudoers файла

Для настройки прав доступа откройте файл sudoers с помощью редактора:

```bash
visudo
```

По умолчанию в качестве текстового редактора используется vi, однако вам будет привычнее использовать nano:

```bash
EDITOR=nano visudo
```

### Пример конфигурации sudoers:

```bash
# Пользователь root: администратор системы с полным доступом
root    ALL=(ALL) ALL

# Пользователь admin_kaf: права на выполнение команд для управления пользователями и группами
admin_kaf    ALL=(ALL) /usr/sbin/useradd, /usr/sbin/usermod, /usr/sbin/groupadd, /usr/sbin/groupdel, /usr/sbin/userdel

# Пользователь admin_stud: права на выполнение команд для работы с каталогами и файлами
admin_stud    ALL=(ALL) /bin/ls, /bin/cp, /bin/mv, /bin/rm, /bin/mkdir, /bin/rmdir, /bin/chmod, /bin/chown

# Пользователи stud_51, stud_52, stud_53, stud_54, stud_55: права на выполнение команд для управления процессами
%student    ALL=(ALL) /bin/ps, /usr/bin/top, /bin/kill, /usr/bin/killall, /bin/nice
```

## Проверка групп

### Проверка группы `wheel`

```bash
cat /etc/group | grep "wheel"
```

Пример вывода:

```bash
wheel:x:10:root,admin_kaf,admin_stud
```

### Проверка группы `student`

```bash
cat /etc/group | grep "student"
```

Пример вывода:

```bash
student:x:507:stud_51,stud_52,stud_53,stud_54,stud_55
```

## Проверка информации о пользователе

Для получения информации о пользователе `stud_51` используйте команду:

```bash
id stud_51
```

Пример вывода:

```bash
uid=502(stud_51) gid=502(stud_51) группы=502(stud_51),507(student)
```