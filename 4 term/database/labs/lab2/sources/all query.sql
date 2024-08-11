-- Общий запрос, включающий различные типы SELECT-запросов
SELECT * FROM customers; -- (a) выбор всех данных из таблицы customers

SELECT FirstName, LastName, City FROM customers; -- (b) выбор некоторых столбцов таблицы customers

SELECT * FROM customers ORDER BY LastName ASC; -- (c) сортировка данных по фамилии

SELECT * FROM customers LIMIT 5; -- (d) ограничение выборки до первых 5 строк

SELECT * FROM customers WHERE LastName = 'Smith'; -- (e) выборка по фамилии 'Smith'

SELECT * FROM orders WHERE OrderDate BETWEEN '2024-03-01' AND '2024-03-03'; -- (f) выборка заказов между указанными датами

SELECT * FROM customers WHERE IdCustomer IN (SELECT IdCustomer FROM orders WHERE Status = 'C'); -- (g) выборка клиентов, у которых есть заказы со статусом 'C'

SELECT * FROM customers WHERE EMail LIKE '%@abccorp.com'; -- (h) выборка клиентов с почтовым адресом на домене 'abccorp.com'

SELECT * FROM customers WHERE Phone IS NULL; -- (i) выборка клиентов без указанного номера телефона

SELECT COUNT(*) AS TotalCustomers FROM customers; -- (j) подсчет общего числа клиентов

SELECT IdCustomer, COUNT(*) AS TotalOrders FROM orders GROUP BY IdCustomer HAVING COUNT(*) > 2; -- (k) подсчет числа заказов для каждого клиента, у которого их больше 2

SELECT o.OrderDate, c.FirstName, c.LastName
FROM orders o
JOIN customers c ON o.IdCustomer = c.IdCustomer; -- (l) выборка данных из нескольких таблиц с использованием соединения по предикату

SELECT DISTINCT City FROM customers; -- (m) выбор уникальных значений городов клиентов

SELECT * FROM customers WHERE EXISTS (SELECT * FROM orders WHERE customers.IdCustomer = orders.IdCustomer); -- (n) выборка клиентов, у которых есть заказы

SELECT FirstName, LastName, 
    CASE 
        WHEN City = 'New York' THEN 'East Coast'
        WHEN City = 'Los Angeles' THEN 'West Coast'
        ELSE 'Other'
    END AS Region
FROM customers; -- (o) использование функции CASE для определения региона клиентов
