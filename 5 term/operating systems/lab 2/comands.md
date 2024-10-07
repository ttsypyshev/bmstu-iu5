Создание учётных записей пользователей с использованием useradd
sudo useradd -m -s /bin/bash admin_kaf
sudo useradd -m -s /bin/bash stud_51
sudo useradd -m -s /bin/bash stud_52
sudo useradd -m -s /bin/bash stud_53
sudo useradd -m -s /bin/bash stud_54
sudo useradd -m -s /bin/bash stud_55


Установка паролей для пользователей
echo "admin_kaf:adminkaf" | sudo chpasswd
echo "stud_51:stud51" | sudo chpasswd
echo "stud_52:stud52" | sudo chpasswd
echo "stud_53:stud53" | sudo chpasswd
echo "stud_54:stud54" | sudo chpasswd
echo "stud_55:stud55" | sudo chpasswd


Создание группы
sudo groupadd group_stud3k

Добавление пользователей в группу
sudo usermod -aG group_stud3k stud_51
sudo usermod -aG group_stud3k stud_52
sudo usermod -aG group_stud3k stud_53
sudo usermod -aG group_stud3k stud_54
sudo usermod -aG group_stud3k stud_55

Добавление пользователя admin_kaf в группу sudo
sudo usermod -aG wheel admin_kaf

Удаление учётной записи student
sudo useradd -m -s /bin/bash student 
sudo userdel -r student

Просмотр информации о пользователях в файлах /etc/passwd и /etc/group
cat /etc/passwd | grep 'admin_kaf\|stud_51\|stud_52\|stud_53\|stud_54\|stud_55'
cat /etc/group | grep 'group_stud3k'


find / -user admin_kaf - Ищет все файлы и директории на системе, принадлежащие пользователю admin_kaf
du -sh ~/ -Отображает размер домашней директории текущего пользователя
fuser -m /home/student -Показывает процессы, использующие файлы или директории в /home/student
ps aux -Отображает список всех запущенных процессов в системе
top -Запускает интерактивный монитор системы, отображающий обновляющийся список текущих процессов
last -Показывает историю входов пользователей в систему
lastb -Показывает историю неудачных попыток входа в систем
who -u -Показывает информацию о текущих пользователях, находящихся в системе
users -Выводит список пользователей, которые в данный момент вошли в систему
finger -Показывает подробную информацию о пользователях, которые в данный момент вошли в систему

