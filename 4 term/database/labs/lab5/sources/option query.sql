-- Task 1
-- CREATE OR REPLACE FUNCTION get_products_from_orders (
--     order1 INT,
--     order2 INT
-- )
-- RETURNS TABLE (
--     itemid INT,
--     description TEXT,
--     quantity INT,
--     total NUMERIC,
--     shipdate DATE
-- )
-- LANGUAGE SQL
-- AS $$
--     SELECT 
--         i.itemid,
--         p.description,
--         i.quantity,
--         i.total,
--         o.shipdate
--     FROM items i
--     JOIN orders o ON i.orderid = o.idorder
--     JOIN products p ON i.productid = p.idproduct
--     WHERE i.orderid IN (order1, order2);
-- $$;

-- select * from items
-- SELECT * FROM get_products_from_orders(4, 5);

-- Task 2
SELECT 
    c.city AS Город,
    p.prname AS Товар,
    SUM(i.quantity) AS Количество
FROM 
    items i
JOIN 
    orders o ON i.orderid = o.idorder
JOIN 
    customers c ON o.idcustomer = c.idcustomer
JOIN 
    products p ON i.productid = p.idproduct
GROUP BY 
    c.city, p.prname
ORDER BY 
    c.city, p.prname;
