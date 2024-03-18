-- Удаление представлений
DROP VIEW IF EXISTS customer_orders;
DROP VIEW IF EXISTS customer_orders_check;

-- Задание 2: Создание простого представления и запрос данных с использованием него
CREATE VIEW customer_orders AS
SELECT c.CompanyName, o.OrderDate, o.ShipDate, o.PaidDate, o.Status
FROM customers c
JOIN orders o ON c.IdCustomer = o.IdCustomer;

-- Проверка данных из представления
SELECT * FROM customer_orders;

-- Задание 3: Проверка соответствия данных прямым запросом
SELECT c.CompanyName, o.OrderDate, o.ShipDate, o.PaidDate, o.Status
FROM customers c
JOIN orders o ON c.IdCustomer = o.IdCustomer;

-- Задание 4: Изменение созданного представления с помощью команды ALTER VIEW, добавление псевдонимов полям
DROP VIEW IF EXISTS customer_orders;
CREATE VIEW customer_orders AS
SELECT c.CompanyName AS CustomerName, o.OrderDate AS DateOrdered, o.ShipDate AS DateShipped, o.PaidDate AS DatePaid, o.Status AS OrderStatus
FROM customers c
JOIN orders o ON c.IdCustomer = o.IdCustomer;

-- Задание 5: Изменение запроса созданного представления с помощью команды CREATE OR REPLACE VIEW, добавление условия
CREATE OR REPLACE VIEW customer_orders AS
SELECT c.CompanyName AS CustomerName, o.OrderDate AS DateOrdered, o.ShipDate AS DateShipped, o.PaidDate AS DatePaid, o.Status AS OrderStatus
FROM customers c
JOIN orders o ON c.IdCustomer = o.IdCustomer
WHERE o.Status = 'C';

-- Задание 6: Вставка данных с помощью представления
INSERT INTO customer_orders (CustomerName, DateOrdered, DateShipped, DatePaid, OrderStatus)
VALUES ('PQR Corp', '2024-03-06', '2024-03-08', '2024-03-09', 'C');

-- Задание 7: Создание представления с опцией WITH CHECK OPTION и проверка его работы
CREATE VIEW customer_orders_check AS
SELECT c.CompanyName AS CustomerName, o.OrderDate AS DateOrdered, o.ShipDate AS DateShipped, o.PaidDate AS DatePaid, o.Status AS OrderStatus
FROM customers c
JOIN orders o ON c.IdCustomer = o.IdCustomer
WITH CHECK OPTION;

-- Попытка вставить недопустимую запись
INSERT INTO customer_orders_check (CustomerName, DateOrdered, DateShipped, DatePaid, OrderStatus)
VALUES ('RST Ltd', '2024-03-07', '2024-03-09', '2024-03-10', 'P');

-- Задание 8: Удаление представлений
DROP VIEW IF EXISTS customer_orders;
DROP VIEW IF EXISTS customer_orders_check;