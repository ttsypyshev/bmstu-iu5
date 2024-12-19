### **Шаг 3. Создание разделов**
1. Войдите в систему под учетной записью `root` или `adminroot`.

2. Получите информацию о подключенных дисках:  
   ```bash
   fdisk -l
   ```

3. Создайте разделы на новом диске (`/dev/sdb`) с использованием GPT:  
   ```bash
   parted /dev/sdb mklabel gpt
   parted /dev/sdb mkpart primary 0% 2GB
   parted /dev/sdb mkpart primary 2GB 12GB
   parted /dev/sdb mkpart primary 12GB 17GB
   parted /dev/sdb mkpart primary 17GB 100%
   ```

4. Убедитесь, что разделы созданы:  
   ```bash
   lsblk
   ```

---

### **Шаг 4. Настройка раздела подкачки (sdb1)**
1. Форматируйте раздел как swap:  
   ```bash
   mkswap /dev/sdb1
   ```

2. Проверьте раздел на повреждения:  
   ```bash
   badblocks -v /dev/sdb1
   ```

3. Активируйте swap:  
   ```bash
   swapon /dev/sdb1
   ```

4. Проверьте текущие настройки swap:  
   ```bash
   swapon --show
   ```

---

### **Шаг 5. Создание файловых систем**
#### Для раздела `sdb2`:
1. Создайте файловую систему ext4:  
   ```bash
   mkfs.ext4 /dev/sdb2
   ```

2. Создайте точку монтирования в домашнем каталоге `admin_kaf`:  
   ```bash
   mkdir -p /home/admin_kaf/КАФЕДРА
   ```

3. Смонтируйте раздел:  
   ```bash
   mount /dev/sdb2 /home/admin_kaf/КАФЕДРА
   ```

#### Для раздела `sdb3`:
1. Создайте файловую систему ext4:  
   ```bash
   mkfs.ext4 /dev/sdb3
   ```

2. Создайте точку монтирования:  
   ```bash
   mkdir -p /home/admin_kaf/ИНФОРМАЦИЯ
   ```

3. Смонтируйте раздел:  
   ```bash
   mount /dev/sdb3 /home/admin_kaf/ИНФОРМАЦИЯ
   ```

#### Для раздела `sdb4`:
1. Создайте файловую систему ext4:  
   ```bash
   mkfs.ext4 /dev/sdb4
   ```

2. Создайте точку монтирования в домашнем каталоге `admin_stud`:  
   ```bash
   mkdir -p /home/admin_stud/СТУДЕНТЫ
   ```

3. Смонтируйте раздел:  
   ```bash
   mount /dev/sdb4 /home/admin_stud/СТУДЕНТЫ
   ```

---

### **Шаг 6. Создание виртуальной файловой системы**
1. Создайте файл размером 1 ГБ:  
   ```bash
   dd if=/dev/zero of=/home/admin_kaf/fs_virt bs=1M count=1024
   ```

2. Создайте в нем файловую систему ext4:  
   ```bash
   mkfs.ext4 /home/admin_kaf/fs_virt
   ```

3. Создайте точку монтирования:  
   ```bash
   mkdir -p /home/admin_kaf/virt_fs
   ```

4. Смонтируйте виртуальную файловую систему:  
   ```bash
   mount -o loop /home/admin_kaf/fs_virt /home/admin_kaf/virt_fs
   ```

---

### **Шаг 7. Создание файла подкачки**
1. Создайте файл подкачки:  
   ```bash
   dd if=/dev/zero of=/tmp/my_swap bs=1M count=1024
   ```

2. Отформатируйте файл подкачки:  
   ```bash
   mkswap /tmp/my_swap
   ```

3. Подключите файл подкачки:  
   ```bash
   swapon /tmp/my_swap
   ```

4. Задайте разделу `sdb1` высший приоритет:  
   ```bash
   swapon -p 100 /dev/sdb1
   ```

5. Проверьте используемые swap:  
   ```bash
   swapon --show
   ```

---

### **Шаг 8. Редактирование файла `/etc/fstab`**
1. Добавьте следующие строки в файл `/etc/fstab`:  
   ```plaintext
   /dev/sdb2 /home/admin_kaf/КАФЕДРА ext4 defaults 0 0
   /dev/sdb3 /home/admin_kaf/ИНФОРМАЦИЯ ext4 defaults 0 0
   /dev/sdb4 /home/admin_stud/СТУДЕНТЫ ext4 defaults 0 0
   /home/admin_kaf/fs_virt /home/admin_kaf/virt_fs ext4 loop 0 0
   /tmp/my_swap none swap sw 0 0
   ```

2. Перезагрузите систему:  
   ```bash
   reboot
   ```

3. Проверьте смонтированные файловые системы:  
   ```bash
   df -h
   ```