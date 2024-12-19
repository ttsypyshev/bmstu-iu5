### 3.2.1 Установка новых жёстких дисков и запуск ОС

1. **Добавление дисков в VirtualBox:**
   - Откройте **Oracle VM VirtualBox** и выберите виртуальную машину **Alt-10**.
   - В настройках виртуальной машины перейдите в раздел **Носители (Storage)**.
   - Выберите контроллер **SATA** и нажмите кнопку **Добавить жёсткий диск (Add Hard Disk)**.
   - Создайте два динамических виртуальных диска:
     - **my_disk2** размером **10 ГБ**.
     - **my_disk3** размером **15 ГБ**.
   - Убедитесь, что созданные диски имеют тип **VDI** и настроены как динамические.

---

### 3.2.2 Создание логических томов LVM

#### 1. Подготовка дисков к использованию:
1. **Просмотр добавленных дисков:**
   ```bash
   fdisk -l
   ```
   Убедитесь, что диски **/dev/sdd** (10 ГБ) и **/dev/sdc** (15 ГБ) обнаружены.

2. **Создание разделов:**
   Для каждого диска используйте `fdisk`:
   ```bash
   fdisk /dev/sdd
   ```
   - Создайте новый раздел (n)
   - Выберите p (основной раздел) или оставьте по умолчанию.
   - Укажите номер раздела (например, 1).
   - Укажите начальный и конечный сектора (по умолчанию будет использован весь диск).
   - Нажмите t для изменения типа раздела.
   - Укажите код 8e для Linux LVM.
   - Нажмите w для записи изменений на диск.
   - Повторите для **/dev/sdc**.

3. **Просмотр разделов:**
   ```bash
   lsblk
   ```

   Получаем:

   ```bash
    NAME   MAJ:MIN RM  SIZE RO TYPE MOUNTPOINTS
    loop0    7:0    0    1G  0 loop /home/admin_kaf/virt_fs
    sda      8:0    0   40G  0 disk 
    ├─sda1   8:1    0  1,9G  0 part [SWAP]
    └─sda2   8:2    0 38,1G  0 part /
    sdb      8:16   0   27G  0 disk 
    ├─sdb1   8:17   0  1,9G  0 part 
    ├─sdb2   8:18   0  9,3G  0 part /home/admin_kaf/КАФЕДРА
    ├─sdb3   8:19   0  4,7G  0 part /home/admin_kaf/ИНФОРМАЦИЯ
    └─sdb4   8:20   0 11,2G  0 part /home/admin_stud/СТУДЕНТЫ
    sdc      8:32   0   15G  0 disk 
    └─sdc1   8:33   0   15G  0 part 
    sdd      8:48   0   10G  0 disk 
    └─sdd1   8:49   0   10G  0 part 
    sr0     11:0    1  6,7G  0 rom  
    sr1     11:1    1 1024M  0 rom 
    ```

#### 2. Создание физических томов и групп:
1. **Создание физических томов (PV):**
   ```bash
   pvcreate /dev/sdd1 /dev/sdc1
   ```

2. **Создание группы физических томов (VG):**
   ```bash
   vgcreate vg_alt /dev/sdd1 /dev/sdc1
   ```
   - Группа будет включать оба раздела.

3. **Просмотр информации о физических томах и группах:**
   ```bash
   pvdisplay
   vgdisplay
   ```

   ```bash
    [root@host-15 ~]# pvdisplay
        --- Physical volume ---
        PV Name               /dev/sdd1
        VG Name               vg_alt
        PV Size               <10,00 GiB / not usable 3,00 MiB
        Allocatable           yes 
        PE Size               4,00 MiB
        Total PE              2559
        Free PE               2559
        Allocated PE          0
        PV UUID               ASw36B-ZCQ6-c8c3-dSXz-4wST-qRCe-sMbGAQ
        
        --- Physical volume ---
        PV Name               /dev/sdc1
        VG Name               vg_alt
        PV Size               <15,00 GiB / not usable 3,00 MiB
        Allocatable           yes 
        PE Size               4,00 MiB
        Total PE              3839
        Free PE               3839
        Allocated PE          0
        PV UUID               zqdA1v-y8Kg-mjBa-NSzN-pnVT-ye2h-krOSt9
        
    [root@host-15 ~]# vgdisplay
        --- Volume group ---
        VG Name               vg_alt
        System ID             
        Format                lvm2
        Metadata Areas        2
        Metadata Sequence No  1
        VG Access             read/write
        VG Status             resizable
        MAX LV                0
        Cur LV                0
        Open LV               0
        Max PV                0
        Cur PV                2
        Act PV                2
        VG Size               24,99 GiB
        PE Size               4,00 MiB
        Total PE              6398
        Alloc PE / Size       0 / 0   
        Free  PE / Size       6398 / 24,99 GiB
        VG UUID               pjy0yx-oQcc-71bW-g77Y-bRdr-gFio-ljM5NY
   ```

#### 3. Создание логических томов (LV):
1. **Линейный том (Linear Volume):**
   ```bash
   lvcreate -L 5G -n vtom_lin vg_alt
   ```

2. **Зеркальный том (Mirrored Volume):**
   ```bash
   lvcreate -L 5G -m1 -n vtom_mir vg_alt
   ```
   - Опция `-m1` означает создание зеркала.

3. **Просмотр информации о логических томах:**
   ```bash
   lvdisplay
   ```

   ```bash
    --- Logical volume ---
    LV Path                /dev/vg_alt/vtom_lin
    LV Name                vtom_lin
    VG Name                vg_alt
    LV UUID                BQ2UUv-Kmg3-oiFl-vz7w-vqZX-oi6O-SSyWi2
    LV Write Access        read/write
    LV Creation host, time host-15, 2024-12-09 01:29:59 +0300
    LV Status              available
    # open                 0
    LV Size                5,00 GiB
    Current LE             1280
    Segments               1
    Allocation             inherit
    Read ahead sectors     auto
    - currently set to     256
    Block device           253:0
    
    --- Logical volume ---
    LV Path                /dev/vg_alt/vtom_mir
    LV Name                vtom_mir
    VG Name                vg_alt
    LV UUID                7ihr7P-lAPl-cZUk-GVXV-8lpA-YcWC-VWxeIb
    LV Write Access        read/write
    LV Creation host, time host-15, 2024-12-09 01:31:20 +0300
    LV Status              available
    # open                 0
    LV Size                5,00 GiB
    Current LE             1280
    Mirrored volumes       2
    Segments               1
    Allocation             inherit
    Read ahead sectors     auto
    - currently set to     256
    Block device           253:5
   ```

---

### 3.2.3 Создание файловых систем в логических томах

1. **Создание файловой системы ext4:**
   - Для линейного тома:
     ```bash
     mkfs.ext4 /dev/vg_alt/vtom_lin
     ```
   - Для зеркального тома:
     ```bash
     mkfs.ext4 /dev/vg_alt/vtom_mir
     ```

2. **Просмотр информации о созданных файловых системах:**
   ```bash
   blkid
   ```

   ```bash
    /dev/sdd1: UUID="ASw36B-ZCQ6-c8c3-dSXz-4wST-qRCe-sMbGAQ" TYPE="LVM2_member" PARTUUID="41773bb1-01"
    /dev/sdb4: UUID="c3d39d63-ea8b-4714-ba31-3ef3ff7455aa" BLOCK_SIZE="4096" TYPE="ext4" PARTLABEL="primary" PARTUUID="2a227e20-e012-488a-a523-b8c73d52bae6"
    /dev/sdb2: UUID="7a6dee6e-0663-4e93-96ef-3f617bc8a7c6" BLOCK_SIZE="4096" TYPE="ext4" PARTLABEL="primary" PARTUUID="eced2400-a16c-4a51-87ce-16e9d21cd28b"
    /dev/sdb3: UUID="fae3779a-7857-4021-8ce9-0a79e0600aab" BLOCK_SIZE="4096" TYPE="ext4" PARTLABEL="primary" PARTUUID="7223faef-001c-4204-b0d9-268a67e6af26"
    /dev/sdb1: PARTLABEL="primary" PARTUUID="de41feb5-86d5-4a48-bbf6-643929247748"
    /dev/mapper/vg_alt-vtom_mir_rimage_1: UUID="169b1258-5178-40b1-911f-68be61fba582" BLOCK_SIZE="4096" TYPE="ext4"
    /dev/sr0: BLOCK_SIZE="2048" UUID="2024-03-06-10-45-49-00" LABEL="ALT Workstation 10.2 x86_64" TYPE="iso9660" PTTYPE="PMBR"
    /dev/mapper/vg_alt-vtom_mir_rimage_0: UUID="169b1258-5178-40b1-911f-68be61fba582" BLOCK_SIZE="4096" TYPE="ext4"
    /dev/loop0: UUID="4aa92dd0-836c-47fd-a791-540e2e20aebc" BLOCK_SIZE="4096" TYPE="ext4"
    /dev/mapper/vg_alt-vtom_lin: UUID="e5f3d9b3-3922-4d84-a657-f93238226143" BLOCK_SIZE="4096" TYPE="ext4"
    /dev/sdc1: UUID="zqdA1v-y8Kg-mjBa-NSzN-pnVT-ye2h-krOSt9" TYPE="LVM2_member" PARTUUID="0ed6b618-01"
    /dev/sda2: UUID="ea963b26-eca4-41d7-a00f-a576510d7e54" BLOCK_SIZE="4096" TYPE="ext4"
    /dev/sda1: UUID="02cd7bdf-e5ec-49d4-995a-f9b9d9dc65d5" TYPE="swap"
    /dev/mapper/vg_alt-vtom_mir: UUID="169b1258-5178-40b1-911f-68be61fba582" BLOCK_SIZE="4096" TYPE="ext4"
   ```

3. **Монтирование томов:**
   - Создайте точки монтирования:
     ```bash
     mkdir /mnt/vtom_lin /mnt/vtom_mir
     ```
   - Смонтируйте тома:
     ```bash
     mount /dev/vg_alt/vtom_lin /mnt/vtom_lin
     mount /dev/vg_alt/vtom_mir /mnt/vtom_mir
     ```

4. **Проверьте доступность:**
   ```bash
   df -h
   ```

   ```bash
    Файловая система            Размер Использовано  Дост Использовано% Cмонтировано в
    udevfs                        5,0M          96K  5,0M            2% /dev
    runfs                         984M         1,1M  983M            1% /run
    /dev/sda2                      38G          11G   26G           30% /
    tmpfs                         984M            0  984M            0% /dev/shm
    /dev/loop0                    974M          24K  907M            1% /home/admin_kaf/virt_fs
    tmpfs                         984M            0  984M            0% /tmp
    /dev/sdb3                     4,6G          24K  4,3G            1% /home/admin_kaf/ИНФОРМАЦИЯ
    /dev/sdb2                     9,1G          24K  8,6G            1% /home/admin_kaf/КАФЕДРА
    /dev/sdb4                      11G          24K   11G            1% /home/admin_stud/СТУДЕНТЫ
    tmpfs                         197M          56K  197M            1% /run/user/0
    tmpfs                         197M          60K  197M            1% /run/user/500
    /dev/mapper/vg_alt-vtom_lin   4,9G          24K  4,6G            1% /mnt/vtom_lin
    /dev/mapper/vg_alt-vtom_mir   4,9G          24K  4,6G            1% /mnt/vtom_mir
   ```