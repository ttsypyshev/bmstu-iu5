### 3.1 Задание

1. **Создание учётных записей пользователей** и каталогов:
   - Создадим три учётные записи: `dekan`, `sotrudnik`, `admin_dek`.
   - Создадим группу пользователей `group_dek` и добавим в неё этих пользователей.

2. **Обеспечение доступа к каталогу ДЕКАНАТ**:
   - Настроим расширенные разрешения для группы пользователей `group_dek` с использованием битов `setgid` и `sticky`.

3. **Обеспечение разграничения доступа пользователей** группы `group_dek` к подкаталогам с использованием ACL.

---

### 3.2 Порядок выполнения работы

#### 1. Войти в систему и запустить VirtualBox

1. Войдите в операционную систему под учётной записью `stud_XX`.
2. Запустите **Oracle VM VirtualBox** и включите виртуальную машину **Alt-10**.
3. Войдите в гостевую ОС **Alt Linux** под учётной записью `root` или `adminroot`.

---

### 3.2.1 Создание учётных записей пользователей и каталогов

1. **Создание учётных записей пользователей** с использованием `useradd`:
   ```bash
   useradd dekan
   useradd sotrudnik
   useradd admin_dek
   ```
   Установите пароль для всех пользователей:
   ```bash
   echo "dekanat" | passwd --stdin dekan
   echo "dekanat" | passwd --stdin sotrudnik
   echo "dekanat" | passwd --stdin admin_dek
   ```

2. **Создание группы пользователей** `group_dek`:
   ```bash
   groupadd group_dek
   ```

3. **Добавление пользователей в группу** `group_dek` и в группу `wheel`:
   ```bash
   usermod -aG group_dek dekan
   usermod -aG group_dek sotrudnik
   usermod -aG group_dek admin_dek
   usermod -aG wheel dekan
   usermod -aG wheel sotrudnik
   usermod -aG wheel admin_dek
   ```

4. **Вход в систему под учётной записью admin_dek**:
   Войдите в систему под `admin_dek`:
   ```bash
   su - admin_dek
   ```

5. **Создание каталога ДЕКАНАТ и монтирование логического тома**:
   Создайте каталог **ДЕКАНАТ**:
   ```bash
   mkdir ~/ДЕКАНАТ
   ```
   Смонтируйте в него файловую систему логического тома **vtom_lin**:
   ```bash
   mount /dev/vg_alt/vtom_lin ~/ДЕКАНАТ
   ```

6. **Установка владельца и группы для каталога ДЕКАНАТ**:
   Установите владельцем каталог `admin_dek`, а группой — `group_dek`:
   ```bash
   chown admin_dek:group_dek ~/ДЕКАНАТ
   ```

---

### 3.2.2 Установка прав доступа с использованием битов расширенных разрешений

1. **Убедитесь, что группа `group_dek` имеет права на доступ к каталогу.** Права доступа к каталогу `ДЕКАНАТ` должны быть такими, чтобы группа group_dek имела право на запись. Для этого используйте команду:
   ```bash
   chmod g+rwx /home/admin_dek/ДЕКАНАТ
   ```

1. **Установка битов `setgid` для каталога ДЕКАНАТ**, чтобы файлы, созданные в каталоге, наследовали группу владельца:
   ```bash
   chmod g+s ~/ДЕКАНАТ
   ```

2. **Установка бита `sticky`**, чтобы пользователи могли удалять только свои файлы:
   ```bash
   chmod +t ~/ДЕКАНАТ
   ```

3. **Создание подкаталогов ПРИКАЗЫ и ИНФОРМАЦИЯ**:
   ```bash
   mkdir ~/ДЕКАНАТ/ПРИКАЗЫ
   mkdir ~/ДЕКАНАТ/ИНФОРМАЦИЯ
   ```

4. **Проверка прав доступа**:
   ```bash
   ls -ld ~/ДЕКАНАТ ~/ДЕКАНАТ/ПРИКАЗЫ ~/ДЕКАНАТ/ИНФОРМАЦИЯ
   ```

   ```bash
    drwxrwsr-t 5 admin_dek group_dek 4096 дек  9 01:59 /home/admin_dek/ДЕКАНАТ
    drwxrwsr-t 2 admin_dek group_dek 4096 дек  9 02:12 /home/admin_dek/ДЕКАНАТ/ИНФОРМАЦИЯ
    drwxrws--T 2 admin_dek group_dek 4096 дек  9 02:09 /home/admin_dek/ДЕКАНАТ/ПРИКАЗЫ
   ```

5. **Проверка прав доступа с учётных записей пользователей**:
   - Войдите под пользователем `dekan` и создайте файл в каталоге `ПРИКАЗЫ`:
     ```bash
     su - dekan
     touch /home/admin_dek/ДЕКАНАТ/ПРИКАЗЫ/Приказ061121.txt
     ls -l /home/admin_dek/ДЕКАНАТ/ПРИКАЗЫ
     ```
   - Войдите под пользователем `sotrudnik` и создайте файл в каталоге `ИНФОРМАЦИЯ`:
     ```bash
     su - sotrudnik
     touch /home/admin_dek/ДЕКАНАТ/ИНФОРМАЦИЯ/Новости.txt
     ls -l /home/admin_dek/ДЕКАНАТ/ИНФОРМАЦИЯ
     ```

---

### 3.2.3 Управление расширенными правами доступа с использованием ACL

1. **Проверка текущих прав доступа к каталогу ПРИКАЗЫ**:
   Для пользователя `admin_dek`:
   ```bash
   getfacl ~/ДЕКАНАТ/ПРИКАЗЫ
   ```

   ```bash
    # file: home/admin_dek/ДЕКАНАТ/ПРИКАЗЫ
    # owner: admin_dek
    # group: group_dek
    # flags: -st
    user::rwx
    group::rwx
    other::---
   ```

2. **Установка прав доступа с использованием ACL**:
   - Дать полные права пользователю `dekan`:
     ```bash
     setfacl -m u:dekan:rwx ~/ДЕКАНАТ/ПРИКАЗЫ
     ```
   - Дать права только на чтение пользователю `sotrudnik`:
     ```bash
     setfacl -m u:sotrudnik:r-- ~/ДЕКАНАТ/ПРИКАЗЫ
     ```

3. **Проверка текущих прав доступа к каталогу ПРИКАЗЫ**:
   ```bash
   getfacl ~/ДЕКАНАТ/ПРИКАЗЫ
   ```

   ```bash
    # file: home/admin_dek/ДЕКАНАТ/ПРИКАЗЫ
    # owner: admin_dek
    # group: group_dek
    # flags: -st
    user::rwx
    user:dekan:rwx
    user:sotrudnik:r--
    group::rwx
    mask::rwx
    other::---
   ```

4. **Проверка текущих прав доступа к каталогу ИНФОРМАЦИЯ**:
   ```bash
   getfacl ~/ДЕКАНАТ/ИНФОРМАЦИЯ
   ```

   ```bash
    # file: home/admin_dek/ДЕКАНАТ/ИНФОРМАЦИЯ
    # owner: admin_dek
    # group: group_dek
    # flags: -st
    user::rwx
    group::rwx
    other::r-x
   ```

5. **Установка прав доступа с использованием ACL для каталога ИНФОРМАЦИЯ**:
   - Дать полные права пользователю `sotrudnik`:
     ```bash
     setfacl -m u:sotrudnik:rwx ~/ДЕКАНАТ/ИНФОРМАЦИЯ
     ```
   - Дать только права на чтение пользователю `dekan`:
     ```bash
     setfacl -m u:dekan:r-- ~/ДЕКАНАТ/ИНФОРМАЦИЯ
     ```

6. **Проверка прав доступа к каталогу ИНФОРМАЦИЯ**:
   ```bash
   getfacl ~/ДЕКАНАТ/ИНФОРМАЦИЯ
   ```

   ```bash
    # file: home/admin_dek/ДЕКАНАТ/ИНФОРМАЦИЯ
    # owner: admin_dek
    # group: group_dek
    # flags: -st
    user::rwx
    user:dekan:r--
    user:sotrudnik:rwx
    group::rwx
    mask::rwx
    other::r-x
   ```