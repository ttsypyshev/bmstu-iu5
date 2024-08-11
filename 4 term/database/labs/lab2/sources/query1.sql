SELECT c.CompanyName, c.LastName, c.FirstName, c.Adress, c.Phone, c.City
FROM customers c
INNER JOIN orders o ON c.IdCustomer = o.IdCustomer
WHERE o.Status = 'P'
ORDER BY c.City, c.LastName;
