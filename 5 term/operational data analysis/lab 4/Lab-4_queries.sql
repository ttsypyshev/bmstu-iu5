--Запрос на выбор транзакций
SELECT *, ftr(transaction_amount, 'Большая') FROM transactions
WHERE ftr(transaction_amount, 'Большая')>0;

--Запрос на выбор транзакций
SELECT *, ftr(transaction_amount, 'Средняя') FROM transactions
WHERE ftr(transaction_amount, 'Средняя')>0;

--Запрос на выбор транзакций
SELECT *, ftr(transaction_amount, 'Малая') FROM transactions
WHERE ftr(transaction_amount, 'Малая')>0;

--Запрос на выбор клиентов
SELECT *, fcust(net_worth, 'Малая') FROM clients
WHERE fcust(net_worth, 'Малая')>0;

--Запрос на выбор клиентов
SELECT *, fcust(net_worth, 'Средняя') FROM clients
WHERE fcust(net_worth, 'Средняя')>0;

--Запрос на выбор клиентов
SELECT *, fcust(net_worth, 'Высокая') FROM clients
WHERE fcust(net_worth, 'Высокая')>0;

--Запрос на выбор услуг
SELECT *, fserv(time_to_elapse, 'Простая') FROM services
WHERE fserv(time_to_elapse, 'Простая')>0;

--Запрос на выбор услуг
SELECT *, fserv(time_to_elapse, 'Средняя') FROM services
WHERE fserv(time_to_elapse, 'Средняя')>0;

--Запрос на выбор услуг
SELECT *, fserv(time_to_elapse, 'Сложная') FROM services
WHERE fserv(time_to_elapse, 'Сложная')>0;

SELECT *, fserv(time_to_elapse, 'Сложная'), ftr(transaction_amount, 'Малая') FROM 
transactions JOIN services on transactions.service_id = services.service_id
WHERE fserv(time_to_elapse, 'Сложная')>0 AND ftr(transaction_amount, 'Малая')>0

--Примеры нечетких запросов с CI
-- Запрос на transactions с низкими amount и comission
SELECT *, calculate_ci(fserv(time_to_elapse, 'Сложная'), ftr(transaction_amount, 'Малая')) AS ci
FROM transactions JOIN services on transactions.service_id = services.service_id
WHERE calculate_ci(fserv(time_to_elapse, 'Сложная'), ftr(transaction_amount, 'Малая'))>0
ORDER BY ci DESC;


SELECT *, fcust(net_worth, 'Высокая'), ftr(transaction_amount, 'Малая') FROM 
transactions JOIN customers on transactions.customer_id = customers.customer_id
WHERE fcust(net_worth, 'Высокая')>0 AND ftr(transaction_amount, 'Малая')>0
