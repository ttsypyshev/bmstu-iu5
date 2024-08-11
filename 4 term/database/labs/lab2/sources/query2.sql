SELECT c.City, COUNT(DISTINCT c.IdCustomer) AS TotalCustomers
FROM customers c
INNER JOIN orders o ON c.IdCustomer = o.IdCustomer
WHERE o.Status = 'P'
GROUP BY c.City
ORDER BY TotalCustomers DESC;
