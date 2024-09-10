--создаём таблицу
CREATE TABLE BOOKS (
    BookID INT PRIMARY KEY,
    Bookname VARCHAR(255),
    Author VARCHAR(255),
    Publisher VARCHAR(255)
);

--заполняем талицу данными
INSERT INTO BOOKS (Bookname, Author, Publisher) VALUES
(1, 'Война и мир', 'Л. Толстой', 'BHV'),
(2, 'Анна Каренина', 'Л. Толстой', 'BHV'),
(3, 'Преступление и наказание', 'Ф. Достоевский', 'Эксмо');

--создаем представление
CREATE VIEW vBOOKS AS SELECT bookid, Bookname, Author, Publisher FROM BOOKS
WHERE Publisher =’BHV’
--вставляем запись
INSERT INTO vBOOKS VALUES (4, ‘Война и мир’,’Л. Толстой’,’BHV’)

--вставляем запись с издательством, отсутствующем в представлении
INSERT INTO vBOOKS VALUES (5, ‘Война и мир’,’Л. Толстой’,’Эксмо’)

--добавляем опциюWITH CHECK OPTION
ALTER VIEW vBOOKS SET (check_option='cascaded');

--вставляем запись с издательством, отсутствующем в представлении
INSERT INTO vBOOKS VALUES (6, ‘Война и мир’,’Л. Толстой’,’Эксмо’)