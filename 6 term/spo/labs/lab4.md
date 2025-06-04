
## **3.2.1 Запустить виртуальные машины**

### 1. Запуск VirtualBox:

Откройте программу VirtualBox.

### 2. Запустить ВМ `server-ubuntu2204`:

* Операционная система: Ubuntu Server 22.04.3 LTS
* Вход:

  * **Логин**: `admin_server`
  * **Пароль**: `adminserver`

### 3. Запустить ВМ `ws1-ubuntu2204`:

* Операционная система: Ubuntu 22.04.3 LTS (Desktop)
* Вход:

  * **Логин**: `admin_ws`
  * **Пароль**: `adminws`

---

## **3.2.2 Установить сервер файловой системы NFS**

Перейдите в окно ВМ `server-ubuntu2204`:

```bash
sudo apt update
sudo apt install nfs-kernel-server -y
```

Проверить, что порт 2049 используется:

```bash
sudo ss -tulnp | grep 2049
```

Проверить поддержку NFS в ядре:

```bash
grep NFS /boot/config-$(uname -r)
```

Добавить NFS-сервер в автозагрузку:

```bash
sudo systemctl enable nfs-server
sudo systemctl start nfs-server
```

---

## **3.2.3 Создать пользователя сервера NFS**

```bash
sudo adduser admin_nfs
# Введите пароль: adminnfs (при запросе)
```

---

## **3.2.4 Создать каталоги и настроить права**

```bash
sudo mkdir -p /nfs/share_nfs
sudo mkdir -p /nfs/sharer_nfs
sudo touch /nfs/share_nfs/file_nfs
sudo chown -R admin_nfs:admin_nfs /nfs
sudo chmod -R 0777 /nfs
```

Проверка:

```bash
ls -l /nfs

drwxrwxrwx 2 admin_nfs admin_nfs 4096 мая 21 05:21 share_nfs
drwxrwxrwx 2 admin_nfs admin_nfs 4096 мая 21 05:21 sharer_nfs
```

---

## **3.2.5 Настроить сервер NFS через конфигурационный файл**

Открыть файл:

```bash
sudo nano /etc/exports
```

Добавить строку:

```bash
/nfs/share_nfs *(rw,sync,no_subtree_check)
/nfs/sharer_nfs *(ro,sync,no_subtree_check)
```

Сохранить и выйти, затем перезапустить службу:

```bash
sudo exportfs -ra
sudo systemctl restart nfs-server
```

---

## **3.2.6 Настроить сервер NFS через Webmin**

1. Откройте Webmin в браузере: `http://192.168.100.100:10000`
2. Войдите:

   * Логин: `admin_server`
   * Пароль: `adminserver`
3. Перейдите: **"Networking" > "NFS Exports"**
4. Добавьте каталог `/nfs/sharer_nfs`

   * Разрешения: только чтение (`ro`)
   * Хост: `*`
5. Примените изменения.

---

## **3.2.7 Установить клиента NFS на рабочей станции**

На ВМ `ws1-ubuntu2204`:

```bash
sudo apt update
sudo apt install nfs-common -y
```

---

## **3.2.8 Настроить клиента NFS (статическое монтирование)**

Создать точки монтирования:

```bash
sudo mkdir -p /mnt/client_nfs
sudo mkdir -p /mnt/clientr_nfs
```

Монтировать каталоги:

```bash
sudo mount 192.168.100.100:/nfs/share_nfs /mnt/client_nfs
sudo mount 192.168.100.100:/nfs/sharer_nfs /mnt/clientr_nfs
```

Проверить доступ:

* Через **Файловый менеджер**:
  * Зайти в `+ Другие места` > `Компьютер` > `mnt`
  * Перейти в каталоги `client_nfs`, `clientr_nfs`
* Создайте тестовые файлы и папки
* Размонтировать:

```bash
sudo umount /mnt/client_nfs
sudo umount /mnt/clientr_nfs
```

---

## **3.2.9 Настроить автомонтирование (autofs)**

Установить `autofs`:

```bash
sudo apt install autofs -y
```

Открыть `/etc/auto.master`:

```bash
sudo nano /etc/auto.master
```

Добавить строку:

```bash
/mnt/auto /etc/auto.nfs --timeout=60
```

Создать файл `/etc/auto.nfs`:

```bash
sudo nano /etc/auto.nfs
```

Добавить:

```bash
client_nfs   -fstype=nfs,rw,soft,intr  192.168.100.100:/nfs/share_nfs
clientr_nfs  -fstype=nfs,ro,soft,intr  192.168.100.100:/nfs/sharer_nfs
```

Применить:

```bash
sudo systemctl restart autofs
```

Проверить:

```bash
ls /mnt/auto/client_nfs
ls /mnt/auto/clientr_nfs
```
