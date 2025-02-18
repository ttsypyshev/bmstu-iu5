# Установка операционной системы Альт Рабочая станция. Интерфейс пользователя

## Создание виртуальной машины alt-10

### Virtualbox

![](/5%20term/operating%20systems/lab%206/Screenshots/virtualbox.png)

## Работа с ОС Aльт Рабочая станция в графическом режиме

### Рабочий стол

![](/5%20term/operating%20systems/lab%206/Screenshots/mate.png)

### Переключение на пользователя root

Для выполнения административных задач необходимо стать суперпользователем:

```bash
su -
```

### Создание учётной записи пользователя `admin_kaf`

Создаём нового пользователя с домашним каталогом:

```bash
useradd -m admin_kaf
```

### Установка пароля для пользователя `admin_kaf`

Задаём пароль для нового пользователя:

```bash
passwd admin_kaf
```

### Установка режима многопользовательского запуска (multi-user.target)

Настроим систему на многопользовательский режим без графического интерфейса (для серверных задач):

```bash
systemctl set-default multi-user.target
```

Пример, как ернуть в изначальное состояние:
```bash
systemctl set-default graphical.target
```

## Работа с ОС Aльт Рабочая станция в консольном режиме

### Консольный режим для root

![](/5%20term/operating%20systems/lab%206/Screenshots/root.png)

### Консольный режим для admin_kaf

![](/5%20term/operating%20systems/lab%206/Screenshots/adminkaf.png)