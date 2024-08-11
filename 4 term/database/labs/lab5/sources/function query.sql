-- Создание функции "gpa" с одним параметром x типа real и возвращающей набор записей
CREATE FUNCTION gpa (x real)
RETURNS SETOF record
LANGUAGE SQL
AS $$
	-- Выборка всех студентов, у которых средний балл выше x
	SELECT * FROM Студенты WHERE (Оценка_1 + Оценка_2 + Оценка_3) / 3 > x;
$$;

-- Вызов функции "gpa" с аргументом 3
SELECT gpa(3);
