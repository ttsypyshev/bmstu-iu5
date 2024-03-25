-- Вставка данных в таблицу customers
INSERT INTO customers (CompanyName, LastName, FirstName, Adress, City, IndexCode, Phone, EMail)
VALUES
('ABC Corporation', 'Smith', 'John', '123 Main St', 'New York', '10001', '555-1234', 'john@abccorp.com'),
('XYZ Enterprises', 'Johnson', 'Emily', '456 Elm St', 'Los Angeles', '90001', '555-5678', 'emily@xyz.com'),
('LMN Industries', 'Williams', 'Michael', '789 Oak St', 'Chicago', '60601', '555-9012', 'michael@lmnindustries.com'),
('DEF Limited', 'Brown', 'Jessica', '101 Pine St', 'Houston', '77002', '555-3456', 'jessica@def.com'),
('GHI Inc.', 'Jones', 'Daniel', '202 Maple St', 'Miami', '33101', '555-7890', 'daniel@ghiinc.com');

-- Вставка данных в таблицу orders
INSERT INTO orders (IdCustomer, OrderDate, ShipDate, PaidDate, Status)
VALUES
(1, '2024-03-01', '2024-03-03', '2024-03-04', 'C'),
(2, '2024-03-02', '2024-03-04', '2024-03-05', 'P'),
(3, '2024-03-03', '2024-03-05', '2024-03-06', 'A'),
(4, '2024-03-04', '2024-03-06', '2024-03-07', 'C'),
(5, '2024-03-05', '2024-03-07', '2024-03-08', 'P');

-- Вставка данных в таблицу products
INSERT INTO products (PrName, PrPrice, InStock, ReOrder, Description)
VALUES
('Product A', 10.99, 100, TRUE, 'Description of Product A'),
('Product B', 20.49, 75, FALSE, 'Description of Product B'),
('Product C', 15.29, 50, TRUE, 'Description of Product C'),
('Product D', 8.99, 120, FALSE, 'Description of Product D'),
('Product E', 25.99, 90, TRUE, 'Description of Product E');

-- Вставка данных в таблицу items
INSERT INTO items (OrderID, ProductID, Quantity, Total)
VALUES
(1, 1, 5, 54.95),
(2, 3, 3, 45.87),
(3, 2, 2, 40.98),
(4, 4, 4, 35.96),
(5, 5, 1, 25.99);
