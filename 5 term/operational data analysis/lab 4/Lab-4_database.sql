-- Создание таблицы Clients (Клиенты)
CREATE TABLE Clients (
    client_id INT PRIMARY KEY,
    name VARCHAR(100),
    business_type VARCHAR(100),
    address VARCHAR(255),
    phone VARCHAR(30),
	net_worth BIGINT
);

-- Создание таблицы Services (Услуги)
CREATE TABLE Services (
    service_id INT PRIMARY KEY,
    service_name VARCHAR(100),
    description TEXT,
	time_to_elapse INT
);

-- Создание таблицы Transactions (Сделки)
CREATE TABLE Transactions (
    transaction_id INT PRIMARY KEY,
    client_id INT,
    service_id INT,
    transaction_amount DECIMAL(10, 2),
    commission DECIMAL(10, 2),
    transaction_date DATE,
    FOREIGN KEY (client_id) REFERENCES Clients(client_id),
    FOREIGN KEY (service_id) REFERENCES Services(service_id)
);