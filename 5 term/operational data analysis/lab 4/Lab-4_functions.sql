-- Z-образная функция low
CREATE FUNCTION z_tr_low(value DOUBLE PRECISION, a DOUBLE PRECISION, b DOUBLE PRECISION)
RETURNS DOUBLE PRECISION AS $$
BEGIN
    IF value <= a THEN
        RETURN 1;
    ELSIF value >= b THEN
        RETURN 0;
    ELSE
        RETURN (b - value) / (b - a);
    END IF;
END;

$$ LANGUAGE plpgsql;

-- Z-образная функция mid
CREATE FUNCTION z_tr_mid(value DOUBLE PRECISION, a DOUBLE PRECISION, b DOUBLE PRECISION, c DOUBLE PRECISION, d DOUBLE PRECISION)
RETURNS DOUBLE PRECISION AS $$
BEGIN
    IF value <= a OR value >= d THEN
        RETURN 0;
    ELSIF value >= b AND value <= c THEN
        RETURN 1;
    ELSIF value > a AND value < b THEN
        RETURN (value - a) / (b - a);
    ELSE
        RETURN (d - value) / (d - c);
    END IF;
END;
$$ LANGUAGE plpgsql;

-- Z-образная функция high
CREATE FUNCTION z_tr_high(value DOUBLE PRECISION, a DOUBLE PRECISION, b DOUBLE PRECISION)
RETURNS DOUBLE PRECISION AS $$
BEGIN
    IF value <= a THEN
        RETURN 0;
    ELSIF value >= b THEN
        RETURN 1;
    ELSE
        RETURN (value - a) / (b - a);
    END IF;
END;
$$ LANGUAGE plpgsql;

-- Z-образная функция low
CREATE FUNCTION z_cust_low(value BIGINT, a BIGINT, b BIGINT)
RETURNS DOUBLE PRECISION AS $$
BEGIN
    IF value <= a THEN
        RETURN 1;
    ELSIF value >= b THEN
        RETURN 0;
    ELSE
        RETURN (b - value) / (b - a);
    END IF;
END;

$$ LANGUAGE plpgsql;

-- Z-образная функция mid
CREATE FUNCTION z_cust_mid(value BIGINT, a BIGINT, b BIGINT, c BIGINT, d BIGINT)
RETURNS DOUBLE PRECISION AS $$
BEGIN
    IF value <= a OR value >= d THEN
        RETURN 0;
    ELSIF value >= b AND value <= c THEN
        RETURN 1;
    ELSIF value > a AND value < b THEN
        RETURN (value - a) / (b - a);
    ELSE
        RETURN (d - value) / (d - c);
    END IF;
END;
$$ LANGUAGE plpgsql;

-- Z-образная функция high
CREATE FUNCTION z_cust_high(value BIGINT, a BIGINT, b BIGINT)
RETURNS DOUBLE PRECISION AS $$
BEGIN
    IF value <= a THEN
        RETURN 0;
    ELSIF value >= b THEN
        RETURN 1;
    ELSE
        RETURN (value - a) / (b - a);
    END IF;
END;
$$ LANGUAGE plpgsql;

-- Z-образная функция low
CREATE FUNCTION z_serv_low(value INT, a INT, b INT)
RETURNS DOUBLE PRECISION AS $$
BEGIN
    IF value <= a THEN
        RETURN 1;
    ELSIF value >= b THEN
        RETURN 0;
    ELSE
        RETURN (b - value) / (b - a);
    END IF;
END;

$$ LANGUAGE plpgsql;

-- Z-образная функция mid
CREATE FUNCTION z_serv_mid(value INT, a INT, b INT, c INT, d INT)
RETURNS DOUBLE PRECISION AS $$
BEGIN
    IF value <= a OR value >= d THEN
        RETURN 0;
    ELSIF value >= b AND value <= c THEN
        RETURN 1;
    ELSIF value > a AND value < b THEN
        RETURN (value - a) / (b - a);
    ELSE
        RETURN (d - value) / (d - c);
    END IF;
END;
$$ LANGUAGE plpgsql;

-- Z-образная функция high
CREATE FUNCTION z_serv_high(value INT, a INT, b INT)
RETURNS DOUBLE PRECISION AS $$
BEGIN
    IF value <= a THEN
        RETURN 0;
    ELSIF value >= b THEN
        RETURN 1;
    ELSE
        RETURN (value - a) / (b - a);
    END IF;
END;
$$ LANGUAGE plpgsql;

-- Платежеспособность
CREATE FUNCTION fcust(attrib BIGINT, term VARCHAR(25))
RETURNS DOUBLE PRECISION AS $$
BEGIN
CASE term
WHEN 'Малая' THEN RETURN z_cust_low(attrib, 2500000, 4000000);
WHEN 'Средняя' THEN RETURN z_cust_mid(attrib, 3500000, 4500000, 9500000, 10500000);
WHEN 'Высокая' THEN RETURN z_cust_high(attrib, 10000000, 12000000);
END CASE;
END;
$$ LANGUAGE plpgsql;

-- Сложностьуслуги
CREATE FUNCTION fserv(attrib INT, term VARCHAR(25))
RETURNS DOUBLE PRECISION AS $$
BEGIN
CASE term
WHEN 'Простая' THEN RETURN z_serv_low(attrib, 10, 15);
WHEN 'Средняя' THEN RETURN z_serv_mid(attrib, 10, 20, 30, 40);
WHEN 'Сложная' THEN RETURN z_serv_high(attrib, 35, 45);
END CASE;
END;
$$ LANGUAGE plpgsql;

-- Объем
CREATE FUNCTION ftr(attrib DOUBLE PRECISION, term VARCHAR(25))
RETURNS DOUBLE PRECISION AS $$
BEGIN
CASE term
WHEN 'Малая' THEN RETURN z_tr_low(attrib, 500, 2000);
WHEN 'Средняя' THEN RETURN z_tr_mid(attrib, 1000, 3000, 3000, 5000);
WHEN 'Большая' THEN RETURN z_tr_high(attrib, 4000, 6000);
END CASE;
END;
$$ LANGUAGE plpgsql;

--Индекс соответствия (CI) и нечеткие запросы
CREATE FUNCTION calculate_ci(degree1 DOUBLE PRECISION, degree2 DOUBLE PRECISION)
RETURNS DOUBLE PRECISION AS $$
BEGIN
    RETURN LEAST(degree1, degree2);
END;
$$ LANGUAGE plpgsql;