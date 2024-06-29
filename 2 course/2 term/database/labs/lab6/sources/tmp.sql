-- Создание таблицы "people"
CREATE TABLE people (
	id SERIAL PRIMARY KEY,
    name VARCHAR(255),
    surname VARCHAR(255),
    age INT
);
