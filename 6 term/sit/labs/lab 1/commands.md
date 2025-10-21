# Лабораторная работа №1

## Настройка FrameRelay (ИУ5-61Б. Вариант 18)

### 1. Общая информация

- **IP адрес маршрутизатора**: 192.161.18.1

### 2. Конфигурация маршрутизаторов

#### Настройка без саб интерфейсов

---

**Маршрутизатор R1**

```bash
configure terminal
interface GigabitEthernet0/0
 ip address 192.161.18.1 255.255.255.0
 duplex auto
 speed auto
 exit
interface GigabitEthernet0/1
 no ip address
 duplex auto
 speed auto
 shutdown
 exit
interface GigabitEthernet0/2
 no ip address
 duplex auto
 speed auto
 shutdown
 exit
interface Serial0/0/0
 bandwidth 64
 ip address 192.161.60.1 255.255.255.0
 encapsulation frame-relay
 frame-relay map ip 192.168.0.2 102 broadcast
 frame-relay map ip 192.168.0.3 103 broadcast
 frame-relay map ip 192.161.60.2 102 broadcast
 frame-relay map ip 192.161.60.3 103 broadcast
 exit
interface Serial0/0/1
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
ip route 192.161.118.0 255.255.255.0 192.168.0.2 
ip route 192.161.218.0 255.255.255.0 192.168.0.3 
ip route 192.161.118.0 255.255.255.0 192.161.60.2 
ip route 192.161.218.0 255.255.255.0 192.161.60.3 
end
write memory
```

---

**Маршрутизатор R2**

```bash
configure terminal
interface GigabitEthernet0/0
 ip address 192.161.118.1 255.255.255.0
 duplex auto
 speed auto
 exit
interface GigabitEthernet0/1
 no ip address
 duplex auto
 speed auto
 shutdown
 exit
interface GigabitEthernet0/2
 no ip address
 duplex auto
 speed auto
 shutdown
 exit
interface Serial0/0/0
 bandwidth 64
 ip address 192.161.60.2 255.255.255.0
 encapsulation frame-relay
 frame-relay map ip 192.168.0.1 201 broadcast
 frame-relay map ip 192.168.0.3 203 broadcast
 frame-relay map ip 192.161.60.1 201 broadcast
 frame-relay map ip 192.161.60.3 203 broadcast
 exit
interface Serial0/0/1
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
ip route 192.161.218.0 255.255.255.0 192.168.0.3
ip route 192.161.18.0 255.255.255.0 192.168.0.1
ip route 192.161.218.0 255.255.255.0 192.161.60.3
ip route 192.161.18.0 255.255.255.0 192.161.60.1
end
write memory
```

---

**Маршрутизатор R3**

```bash
configure terminal
interface GigabitEthernet0/0
 ip address 192.161.218.1 255.255.255.0
 duplex auto
 speed auto
 exit
interface GigabitEthernet0/1
 no ip address
 duplex auto
 speed auto
 shutdown
 exit
interface GigabitEthernet0/2
 no ip address
 duplex auto
 speed auto
 shutdown
 exit
interface Serial0/0/0
 bandwidth 64
 ip address 192.161.60.3 255.255.255.0
 encapsulation frame-relay
 frame-relay map ip 192.168.0.1 301 broadcast
 frame-relay map ip 192.168.0.2 302 broadcast
 frame-relay map ip 192.161.60.1 301 broadcast
 frame-relay map ip 192.161.60.2 302 broadcast
 exit
interface Serial0/0/1
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
ip route 192.161.18.0 255.255.255.0 192.168.0.1
ip route 192.161.118.0 255.255.255.0 192.168.0.2
ip route 192.161.18.0 255.255.255.0 192.161.60.1
ip route 192.161.118.0 255.255.255.0 192.161.60.2
end
write memory
```

---

#### Настройка с саб интерфейсами

---

**Маршрутизатор R1**

```bash
configure terminal
interface GigabitEthernet0/0
 ip address 192.161.18.1 255.255.255.0
 duplex auto
 speed auto
 exit
interface GigabitEthernet0/1
 no ip address
 duplex auto
 speed auto
 shutdown
 exit
interface GigabitEthernet0/2
 no ip address
 duplex auto
 speed auto
 shutdown
 exit
interface Serial0/0/0
 no ip address
 encapsulation frame-relay
 clock rate 2000000
 exit
interface Serial0/0/0.102 point-to-point
 bandwidth 64
 ip address 192.161.60.1 255.255.255.252
 frame-relay interface-dlci 102
 clock rate 2000000
 exit
interface Serial0/0/0.103 point-to-point
 bandwidth 64
 ip address 192.161.60.5 255.255.255.252
 frame-relay interface-dlci 103
 clock rate 2000000
 exit
interface Serial0/0/1
 no ip address
 clock rate 2000000
 shutdown
 exit
interface Vlan1
 no ip address
 shutdown
 exit
router rip
 network 192.161.18.0
 network 192.161.60.0
 network 192.161.118.0
 network 192.161.218.0
 network 192.168.0.0
 exit
end
write memory
```

---

**Маршрутизатор R2**

```bash
configure terminal
interface GigabitEthernet0/0
 ip address 192.161.118.1 255.255.255.0
 duplex auto
 speed auto
 exit
interface GigabitEthernet0/1
 no ip address
 duplex auto
 speed auto
 shutdown
 exit
interface GigabitEthernet0/2
 no ip address
 duplex auto
 speed auto
 shutdown
 exit
interface Serial0/0/0
 no ip address
 encapsulation frame-relay
 clock rate 2000000
 exit
interface Serial0/0/0.201 point-to-point
 ip address 192.161.60.2 255.255.255.252
 frame-relay interface-dlci 201
 clock rate 2000000
 exit
interface Serial0/0/0.203 point-to-point
 ip address 192.161.60.9 255.255.255.252
 frame-relay interface-dlci 203
 clock rate 2000000
 exit
interface Serial0/0/1
 no ip address
 clock rate 2000000
 shutdown
 exit
interface Vlan1
 no ip address
 shutdown
 exit
router rip
 network 192.161.18.0
 network 192.161.60.0
 network 192.161.118.0
 network 192.161.218.0
 network 192.168.0.0
 exit
end
write memory
```

---

**Маршрутизатор R3**

```bash
configure terminal
interface GigabitEthernet0/0
 ip address 192.161.218.1 255.255.255.0
 duplex auto
 speed auto
 exit
interface GigabitEthernet0/1
 no ip address
 duplex auto
 speed auto
 shutdown
 exit
interface GigabitEthernet0/2
 no ip address
 duplex auto
 speed auto
 shutdown
 exit
interface Serial0/0/0
 no ip address
 encapsulation frame-relay
 clock rate 2000000
 exit
interface Serial0/0/0.301 point-to-point
 ip address 192.161.60.6 255.255.255.252
 frame-relay interface-dlci 301
 clock rate 2000000
 exit
interface Serial0/0/0.302 point-to-point
 ip address 192.161.60.10 255.255.255.252
 frame-relay interface-dlci 302
 clock rate 2000000
 exit
interface Serial0/0/1
 no ip address
 clock rate 2000000
 shutdown
 exit
interface Vlan1
 no ip address
 shutdown
 exit
router rip
 network 192.161.18.0
 network 192.161.60.0
 network 192.161.118.0
 network 192.161.218.0
 network 192.168.0.0
 exit
end
write memory
```