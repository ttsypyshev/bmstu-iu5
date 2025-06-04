## **3.2.1 Запуск виртуальных машин**

1. **Открыть Oracle VM VirtualBox.**
2. **Запустить сервер:**

   * Виртуальная машина: `server-alt10`
   * Пользователь: `admin_server`
   * Пароль: `adminserver`
3. **Запустить рабочую станцию:**

   * Виртуальная машина: `ws1-alt10`
   * Пользователь: `admin_ws`
   * Пароль: `adminws`

---

## **3.2.2 Создание пользователей и каталогов на сервере**

1. **Перейти в виртуальную машину `server-alt10` под пользователем `admin_server`.**

2. **Установить пакет `anonftp`:**

   ```bash
   sudo apt-get install anonftp
   ```

3. **Создать пользователей:**

   ```bash
   sudo useradd -m admin_ftp
   sudo passwd admin_ftp
   sudo useradd -m user_ftp
   sudo passwd user_ftp
   ```

4. **Создать группу `ftpadmin` и добавить в неё пользователя `admin_ftp`:**

   ```bash
   sudo groupadd ftpadmin
   sudo usermod -aG ftpadmin admin_ftp
   ```

5. **Создать каталоги FTP-сервера:**

   ```bash
   sudo mkdir -p /var/ftp/public
   sudo mkdir -p /var/ftp/incoming
   sudo mkdir -p /var/ftp/admin_ftp/uploads
   sudo mkdir -p /var/ftp/user_ftp/uploads
   ```

6. **Назначить владельцев и права:**

   * Для `/var/ftp/public` (общедоступный каталог, доступ на чтение анонимам):

     ```bash
     sudo chown root:ftpadmin /var/ftp/public
     sudo chmod 2775 /var/ftp/public
     ```

   * Для `/var/ftp/incoming` (анонимный доступ на запись, без просмотра содержимого):

     ```bash
     sudo chown admin_ftp:ftpadmin /var/ftp/incoming
     sudo chmod 3773 /var/ftp/incoming
     ```

   * Для домашнего каталога пользователя `admin_ftp`:

     ```bash
     sudo chown root:ftpadmin /var/ftp/admin_ftp
     sudo chmod 755 /var/ftp/admin_ftp

     sudo chown admin_ftp:ftpadmin /var/ftp/admin_ftp/uploads
     sudo chmod 755 /var/ftp/admin_ftp/uploads
     ```

   * Для домашнего каталога пользователя `user_ftp`:

     ```bash
     sudo chown root:user_ftp /var/ftp/user_ftp
     sudo chmod 755 /var/ftp/user_ftp

     sudo chown user_ftp:user_ftp /var/ftp/user_ftp/uploads
     sudo chmod 755 /var/ftp/user_ftp/uploads
     ```

---

## **3.2.3 Настройка FTP-сервера vsftpd**

1. **Установить `vsftpd`, если не установлен:**

   ```bash
   sudo apt-get install vsftpd
   ```

2. **Отредактировать файл `/etc/vsftpd.conf`:**

   ```bash
   sudo nano /etc/vsftpd.conf
   ```

   Добавить/проверить наличие следующих параметров:

   ```ini
   # Анонимный доступ
   anonymous_enable=YES
   anon_upload_enable=YES
   anon_mkdir_write_enable=NO
   anon_other_write_enable=NO
   anon_root=/var/ftp

   # Локальные пользователи
   local_enable=YES
   write_enable=YES
   chroot_local_user=YES
   allow_writeable_chroot=YES

   # Использование подкаталогов по имени пользователя
   user_sub_token=$USER
   local_root=/var/ftp/$USER

   # Логирование
   xferlog_enable=YES
   xferlog_file=/var/log/vsftpd.log
   ```

---

## **3.2.4 Настройка и перезапуск демона `xinetd`**

1. **Установить `xinetd`:**

   ```bash
   sudo apt-get install xinetd
   ```

2. **Перезапустить службу:**

   ```bash
   sudo systemctl restart xinetd
   ```

---

## **3.2.5 Установка автозапуска `xinetd`**

```bash
sudo systemctl enable xinetd
```

---

## **3.2.6 Установка FTP-клиентов на рабочей станции**

1. **Войти на `ws1-alt10` под `admin_ws`.**

2. **Установить консольный FTP-клиент:**

   ```bash
   sudo apt-get install ftp
   ```

3. **Установить графический FTP-клиент FileZilla:**

   ```bash
   sudo apt-get install filezilla
   ```

---

## **3.2.7 Подключение к FTP-серверу в консольном режиме**

### Анонимное подключение

```bash
ftp <IP-адрес сервера>
# Логин: anonymous
# Пароль: любой или пустой
```

### Авторизованное подключение

```bash
ftp <IP-адрес сервера>
# Логин: admin_ftp или user_ftp
# Пароль: заданный при создании пользователя
```

---

## **3.2.8 Подключение к FTP-серверу через FileZilla**

1. Открыть FileZilla.
2. В поле «Хост» ввести IP-адрес сервера.
3. Ввести имя пользователя:

   * Для анонимного доступа: `anonymous`
   * Для авторизованного: `admin_ftp` или `user_ftp`
4. Ввести пароль.
5. Порт: 21 (по умолчанию).
6. Нажать «Быстрое соединение».
7. После подключения перетаскивать файлы для загрузки/скачивания.
