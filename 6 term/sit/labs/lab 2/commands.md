# Лабораторная работа №2

## Настройка DSL (ИУ5-61Б. Вариант 18)

### 1. Общая информация

- **IP адрес маршрутизатора**: 192.161.18.1

### 2. Конфигурация маршрутизаторов

---

**Маршрутизатор R0**

```bash
conf t
interface GigabitEthernet0/0/0
 ip address 192.161.38.1 255.255.255.0
 duplex auto
 speed auto
 exit

interface GigabitEthernet0/0/1
 no ip address
 duplex auto
 speed auto
 shutdown
 exit

interface GigabitEthernet0/0/2
 no ip address
 duplex auto
 speed auto
 shutdown
 exit

interface Serial0/1/0
 ip address 192.161.128.2 255.255.255.0
 clock rate 2000000
 exit

interface Serial0/1/1
 ip address 192.161.118.2 255.255.255.0
 clock rate 2000000
 exit

interface Vlan1
 no ip address
 shutdown
 exit

router rip
 exit

ip classless
ip route 192.161.18.0 255.255.255.0 192.161.118.1
ip route 192.161.28.0 255.255.255.0 192.161.128.1

end
write memory
```

---

**Маршрутизатор R1**

```bash
conf t
interface GigabitEthernet0/0/0
 ip address 192.161.18.1 255.255.255.0
 duplex auto
 speed auto
 exit

interface GigabitEthernet0/0/1
 no ip address
 duplex auto
 speed auto
 shutdown
 exit

interface GigabitEthernet0/0/2
 no ip address
 duplex auto
 speed auto
 shutdown
 exit

interface Serial0/1/0
 ip address 192.161.118.1 255.255.255.0
 exit

interface Serial0/1/1
 no ip address
 clock rate 2000000
 shutdown
 exit

interface Vlan1
 no ip address
 shutdown
 exit

router rip
 exit

ip classless
ip route 192.161.38.0 255.255.255.0 192.161.118.2
ip route 192.161.128.0 255.255.255.0 192.161.118.2

end
write memory
```

---

**Маршрутизатор R2**

```bash
conf t
interface GigabitEthernet0/0/0
 ip address 192.161.28.1 255.255.255.0
 duplex auto
 speed auto
 exit

interface GigabitEthernet0/0/1
 no ip address
 duplex auto
 speed auto
 shutdown
 exit

interface GigabitEthernet0/0/2
 no ip address
 duplex auto
 speed auto
 shutdown
 exit

interface Serial0/1/0
 ip address 192.161.128.1 255.255.255.0
 exit

interface Serial0/1/1
 no ip address
 clock rate 2000000
 shutdown
 exit

interface Vlan1
 no ip address
 shutdown
 exit

router rip
 exit

ip classless
ip route 192.161.38.0 255.255.255.0 192.161.128.2
ip route 192.161.118.0 255.255.255.0 192.161.128.2
end
write memory
```

---

### 3. Настройка GRE туннелей

**На R1:**

```bash
ip route 192.161.28.0 255.255.255.0 68.68.68.1

interface Tunnel1
 ip address 68.68.68.2 255.255.255.0
 mtu 1476
 tunnel source Serial0/1/0
 tunnel destination 192.161.128.1
 exit
```

**На R2:**

```bash
ip route 192.161.18.0 255.255.255.0 68.68.68.2

interface Tunnel1
 ip address 68.68.68.1 255.255.255.0
 mtu 1476
 tunnel source Serial0/1/0
 tunnel destination 192.161.118.1
 exit
```

---

### 4. Настройка VPN (IPSec)

**На R1:**

```bash
crypto isakmp policy 1
 encr 3des
 hash md5
 authentication pre-share
 group 2
 exit

crypto isakmp key merionet address 192.161.128.1

ip access-list extended VPN-TRAFFIC
 permit ip 192.161.18.0 0.0.0.255 192.161.28.0 0.0.0.255
 exit

crypto ipsec transform-set TS esp-3des esp-md5-hmac

crypto map CMAP 10 ipsec-isakmp
 set peer 192.161.128.1
 set transform-set TS
 match address VPN-TRAFFIC
 exit

interface Serial0/1/0
 crypto map CMAP
 exit

ip route 192.161.28.0 255.255.255.0 192.161.118.2
```

**На R2:**

```bash
crypto isakmp policy 1
 encr 3des
 hash md5
 authentication pre-share
 group 2
 exit

crypto isakmp key merionet address 192.161.118.1

ip access-list extended VPN-TRAFFIC
 permit ip 192.161.28.0 0.0.0.255 192.161.18.0 0.0.0.255
 exit

crypto ipsec transform-set TS esp-3des esp-md5-hmac

crypto map CMAP 10 ipsec-isakmp
 set peer 192.161.118.1
 set transform-set TS
 match address VPN-TRAFFIC
 exit

interface Serial0/1/0
 crypto map CMAP
 exit

ip route 192.161.18.0 255.255.255.0 192.161.128.2
```

