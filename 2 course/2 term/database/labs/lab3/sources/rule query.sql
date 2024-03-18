-- Удаление представлений
DROP VIEW IF EXISTS customer_orders;

-- Задание 9: Создать представление на выборку из двух таблиц с помощью редактора.
CREATE VIEW customer_orders AS
SELECT c.CompanyName, o.OrderDate, o.ShipDate, o.PaidDate, o.Status
FROM customers c
JOIN orders o ON c.IdCustomer = o.IdCustomer;

-- Проверка данных представления
SELECT * FROM customer_orders;

-- Задание 10: Создать роль Test_creator без права входа в систему, но с правом создания БД и ролей.
CREATE ROLE Test_creator;
GRANT CREATE DATABASE, CREATE ROLE TO Test_creator;

-- Задание 11: Создать пользователя user1 с правом входа в систему. Убедиться, что user1 не может создать БД.
CREATE USER user1 WITH PASSWORD 'password';
DENY CREATE DATABASE TO user1;

-- Задание 12: Включить пользователя user1 в группу Test_creator.
ALTER USER user1 IN ROLE Test_creator;

-- Задание 13: Создать БД под пользователем user1, для проверки создать новое подключение для пользователя user1 с ролью Test_creator.

-- Задание 14: Создать роли без права создания таблицы и с правом создания таблицы, последовательно проверить работу ролей.
CREATE ROLE Table_creator_without_create_table;
GRANT SELECT, INSERT, UPDATE, DELETE ON customers TO Table_creator_without_create_table;

CREATE ROLE Table_creator_with_create_table;
GRANT SELECT, INSERT, UPDATE, DELETE, CREATE TABLE ON customers TO Table_creator_with_create_table;

-- Проверка роли Table_creator_without_create_table (предполагая, что у пользователя test_user эта роль)
-- Добавление строки с помощью роли без права создания таблицы должно вызвать ошибку, так как не может быть создана новая таблица
-- INSERT INTO customers (CompanyName, LastName, FirstName, Adress, City, IndexCode, Phone, EMail) VALUES ('Test Company', 'Doe', 'Jane', '123 Test St', 'Test City', '12345', '555-1234', 'jane@test.com');

-- Проверка роли Table_creator_with_create_table (предполагая, что у пользователя test_user эта роль)
-- Добавление строки с помощью роли с правом создания таблицы должно быть успешным
-- INSERT INTO customers (CompanyName, LastName, FirstName, Adress, City, IndexCode, Phone, EMail) VALUES ('Test Company', 'Doe', 'Jane', '123 Test St', 'Test City', '12345', '555-1234', 'jane@test.com');

-- Задание 15: Добавить к роли право на любые действия с таблицей, проверить работу прав.
GRANT ALL PRIVILEGES ON customers TO Table_creator_with_create_table;

-- Задание 16: Удалить право вставки в таблицу, проверить работу прав.
REVOKE INSERT ON customers FROM Table_creator_with_create_table;

-- Удаление представлений
DROP VIEW IF EXISTS customer_orders;
