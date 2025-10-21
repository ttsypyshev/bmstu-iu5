## **1. Подготовка виртуальных машин**

### 1.1 Запуск VirtualBox

1. Откройте программу **VirtualBox**.
2. Запустите виртуальные машины:

   * `server-ubuntu2204`
   * `ws1-ubuntu2204`

### 1.2 Данные для входа:

* **server-ubuntu2204:**

  * Логин: `admin_server`
  * Пароль: `adminserver`
* **ws1-ubuntu2204:**

  * Логин: `admin_ws`
  * Пароль: `adminws`

---

## **2. Подключение к серверу через SSH**

На машине `ws1-ubuntu2204`:

1. Откройте терминал.
2. Выполните команду:

```bash
ssh admin_server@192.168.100.100
```

*(или IP-адрес сервера, если он отличается)*

---

## **3. Установка Samba**

На сервере `server-ubuntu2204`:

```bash
sudo apt update
sudo apt install samba -y
```

---

## **4. Создание каталогов**

```bash
sudo mkdir -p /samba/share_samba
sudo mkdir -p /samba/share_usersamba
sudo mkdir -p /samba/share_adminsamba
```

---

## **5. Создание групп**

```bash
sudo groupadd gruser_samba
sudo groupadd gradmin_samba
```

---

## **6. Назначение владельцев каталогов**

```bash
sudo chown :gruser_samba /samba/share_usersamba
sudo chown :gradmin_samba /samba/share_adminsamba
```

---

## **7. Права доступа**

```bash
sudo chmod 2775 /samba/share_usersamba
sudo chmod 2770 /samba/share_adminsamba
sudo chmod 0777 /samba/share_samba
```

---

## **8. Создание администратора Samba**

### 8.1 Создание пользователя:

```bash
sudo adduser admin_samba
```

*(пароль: `adminsamba`)*

### 8.2 Добавление в группы:

```bash
sudo usermod -aG sudo,gruser_samba,gradmin_samba admin_samba
```

### 8.3 Назначение владельца каталога:

```bash
sudo chown admin_samba:gradmin_samba /samba/share_adminsamba
```

### 8.4 Регистрация в Samba:

```bash
sudo smbpasswd -a admin_samba
sudo smbpasswd -e admin_samba
```

---

## **9. Создание обычного пользователя Samba**

### 9.1 Создание пользователя:

```bash
sudo adduser user_samba
```

*(пароль: `usersamba`)*

### 9.2 Добавление в группу:

```bash
sudo usermod -aG gruser_samba user_samba
```

### 9.3 Назначение владельца каталога:

```bash
sudo chown user_samba:gruser_samba /samba/share_usersamba
```

### 9.4 Регистрация в Samba:

```bash
sudo smbpasswd -a user_samba
sudo smbpasswd -e user_samba
```

---

## **10. Настройка конфигурационного файла Samba**

Открытие конфигурационного файла:

```bash
sudo nano /etc/samba/smb.conf
```

### В конец файла добавить:

```ini
[share_samba]
   path = /samba/share_samba
   browsable = yes
   writable = yes
   guest ok = yes
   read only = no

[share_usersamba]
   path = /samba/share_usersamba
   valid users = @gruser_samba
   browsable = yes
   writable = yes
   read only = no

[share_adminsamba]
   path = /samba/share_adminsamba
   valid users = @gradmin_samba
   browsable = yes
   writable = yes
   read only = no
```

Сохраните и закройте файл: `Ctrl+O`, `Enter`, `Ctrl+X`

---

## **11. Проверка конфигурации**

```bash
testparm
```

---

## **12. Перезапуск службы Samba**

```bash
sudo systemctl restart smbd
```

---

## **13. Подключение к Samba**

### 13.1 Из терминала на `ws1-ubuntu2204`:

```bash
sudo apt update
sudo apt install smbclient -y
```

```bash
smbclient //192.168.100.100/share_samba -U%
smbclient //192.168.100.100/share_usersamba -U user_samba
smbclient //192.168.100.100/share_adminsamba -U admin_samba
```

### 13.2 Из графической оболочки:

1. Откройте **Файлы** → **Другие места**
2. В поле "Подключиться к серверу" введите:

```
smb://192.168.100.100
```

3. Нажмите **Подключиться**
4. Выберите каталог `share_adminsamba`
5. Введите данные:

   * Имя пользователя: `admin_samba`
   * Домен (можно оставить пустым)
   * Пароль: `adminsamba`
6. Нажмите **Подключиться**

---

### **1. В чём особенность реализации файловой системы Samba?**

**Samba** — это программный пакет, реализующий **протокол SMB/CIFS** (используется в Windows) в **Linux/Unix-системах**.

**Особенности реализации:**

* Обеспечивает **доступ к файлам и принтерам Linux-систем с Windows-компьютеров** по локальной сети.
* Работает **по сетевому протоколу SMB**, совместимому с Windows.
* **Не требует установки дополнительных программ на стороне клиента (например, Windows)**.
* Позволяет Linux-машинам **выступать как обычные Windows-серверы** в рабочей группе или домене.

---

### **2. Какие есть типы серверов Samba?**

Существует несколько **режимов (типов) работы сервера Samba**:

1. **Сервер автономной рабочей группы (Standalone Server)**
   – Простой режим без контроля домена, используется в небольших одноранговых сетях.

2. **Основной контроллер домена (PDC – Primary Domain Controller)**
   – Управляет учётными записями пользователей и компьютеров в домене (в старых Windows-сетях).

3. **Член домена (Domain Member)**
   – Входит в существующий домен, управляемый Windows или другим контроллером.

4. **Сервер с ролями файлового и/или принт-сервера**
   – Предоставляет общий доступ к папкам и принтерам, может использоваться отдельно или совместно с другими ролями.

---

### **3. Для чего предназначен файловый сервер Samba?**

**Файловый сервер Samba** предназначен для:

* **Обеспечения общего доступа к папкам и файлам** в сети;
* **Организации совместной работы пользователей Windows и Linux**;
* **Упрощения обмена данными между рабочими станциями**;
* **Управления правами доступа к файлам и папкам**;
* **Создания защищённой сетевой среды с аутентификацией пользователей**.

---

### **4. Какие типы пользователей могут иметь доступ к ресурсам файлового сервера Samba?**

К ресурсам Samba могут получить доступ:

1. **Гостевые пользователи (guest)**
   – Без пароля и регистрации, если разрешено в конфигурации (`guest ok = yes`).

2. **Локальные пользователи Linux**, добавленные в базу Samba с помощью:

   ```
   sudo smbpasswd -a имя_пользователя
   ```

3. **Доменные пользователи** (если Samba настроена как член домена или контроллер).

Права доступа могут быть **чтение**, **запись**, или **полный контроль**, задаются через конфигурацию и права на уровне файловой системы.

---

### **5. В чём заключается настройка конфигурации файлового сервера Samba?**

Настройка включает:

1. **Установку Samba**:

   ```
   sudo apt install samba
   ```

2. **Создание общей папки**:

   ```
   mkdir /home/user/shared
   chmod 777 /home/user/shared
   ```

3. **Редактирование конфигурационного файла**:
   Файл: `/etc/samba/smb.conf`
   Добавление раздела:

   ```ini
   [Shared]
   path = /home/user/shared
   browsable = yes
   writable = yes
   guest ok = yes
   read only = no
   ```

4. **Добавление пользователя (если нужно)**:

   ```
   sudo smbpasswd -a user
   ```

5. **Перезапуск службы Samba**:

   ```
   sudo systemctl restart smbd
   ```

6. **Проверка доступа с другого ПК**:

   * В Windows: `\\IP_адрес\Shared`
   * В Linux: `smb://IP_адрес/Shared`