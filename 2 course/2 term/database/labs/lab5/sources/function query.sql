-- CREATE FUNCTION gpa (x real)
-- RETURNS SETOF record
-- LANGUAGE SQL
-- AS $$
-- 	SELECT * FROM Студенты WHERE (Оценка_1 + Оценка_2 + Оценка_3)/3>x
-- $$;

SELECT gpa(3);