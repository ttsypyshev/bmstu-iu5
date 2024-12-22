Для выполнения задания следуйте этому пошаговому руководству:

---

### 3.1 Подготовка:
1. **Запуск виртуальной машины:**
   - Откройте Oracle VM VirtualBox.
   - Настройте виртуальную машину Alt-10:
     - Порядок загрузки: **Жёсткий диск**, затем **Оптический диск**.
     - Вставьте ISO-образ: `alt-workstation-10/0-x86_64.iso` в контроллер IDE.

2. **Запуск ОС:**
   - Запустите виртуальную машину Alt-10.
   - Войдите в систему под учётной записью `admin_kaf` с паролем `adminkaf`.

---

### 3.2 Работа с репозиториями:
1. **Перейдите в консольный режим:**
   Откройте терминал (или используйте сочетание клавиш `Ctrl+Alt+T`).

2. **Просмотр файла со списком репозиториев:**
   ```bash
   cat /etc/apt/sources.list
   ```

3. **Просмотр каталога с файлами списков репозиториев:**
   ```bash
   ls /etc/apt/sources.list.d/
   ```

4. **Просмотр содержимого файлов списков репозиториев:**
   ```bash
   cat /etc/apt/sources.list.d/*.list
   ```

5. **Просмотр списка активных репозиториев:**
   ```bash
   sudo apt-get update
   ```

6. **Удаление активных репозиториев (если требуется):**
   ```bash
   sudo rm /etc/apt/sources.list.d/*.list
   sudo cp /dev/null /etc/apt/sources.list
   apt-repo rm all
   apt-repo add p10
   apt-get update
   apt-get dist-upgrade
   ```

7. **Добавление репозитория с CD/DVD-дистрибутива:**
   - Подключите ISO-образ Alt Linux 10 в настройках VirtualBox.
   - Добавьте репозиторий вручную:
     ```bash
     sudo mount /dev/cdrom /media/cdrom
     ls /media/cdrom/ALTLinux/RPMS.main/
     sudo alien -d /media/cdrom/ALTLinux/RPMS.main/yandex-browser-stable-23.9.1.1033-alt1.x86_64.rpm
     sudo sh -c 'echo "deb [trusted=yes] file:/var/local/repo/deb ./" >> /etc/apt/sources.list'
     sudo apt-get update
     ```

8. **Проверьте список активных репозиториев:**
   ```bash
   sudo apt-get list
   ```

---

### Установка пакетов с помощью `apt-get-get`:
1. **Установите VirtualBox:**
   ```bash
   sudo apt-get install virtualbox
   ```

2. **Установите LibreOffice:**
   ```bash
   sudo apt-get install libreoffice
   sudo apt-get install LibreOffice-still
   ```

---

### Установка пакетов через графическую утилиту Synapt-getic:
1. **Запустите Synapt-getic:**
   - Откройте приложение Synapt-getic через меню системы.
   - Введите пароль для выполнения административных действий.

2. **Установите пакеты:**
   - Найдите и установите **Blender**:
     - В строке поиска введите `blender`, отметьте для установки, нажмите "Применить".
   - Найдите и установите **GIMP**:
     - В строке поиска введите `gimp`, отметьте для установки, нажмите "Применить".

---

### Проверка установленного ПО:
1. **Проверка через терминал:**
   - Убедитесь, что программы установлены:
     ```bash
     virtualbox --version
     libreoffice --version
     blender --version
     gimp --version
     ```

     ```
     [test@host-15 ~]$ virtualbox --version
     Qt WARNING: could not connect to display 
     Qt FATAL: This application failed to start because no Qt platform plugin could be initialized. Reinstalling the application may fix this problem.

     Available platform plugins are: eglfs, linuxfb, minimal, minimalegl, offscreen, vnc, xcb.

     Аварийный останов
     [test@host-15 ~]$ libreoffice --version
     LibreOffice 24.2.6.2 420(Build:2)
     [test@host-15 ~]$ blender --version
     Blender 3.3.21
     [test@host-15 ~]$ gimp --version
     GNU Image Manipulation Program версии 2.10.30
     ```
     
2. **Проверка запуска GUI-программ:**
   - Запустите каждую программу через меню системы:
     - Найдите **VirtualBox**, **LibreOffice**, **Blender**, и **GIMP** в меню приложений.
     - Проверьте, что программы открываются корректно.