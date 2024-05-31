-- CREATE PROCEDURE retake (m INT, n VARCHAR(255))
-- LANGUAGE SQL
-- AS $$
--     UPDATE Студенты SET Оценка_2 = m WHERE Группа = n;
-- $$;

-- CALL retake(5, '18У137');

SELECT * FROM Студенты;