CREATE TABLE customers(
  IdCustomer INT PRIMARY KEY GENERATED BY DEFAULT AS IDENTITY,
  CompanyName VARCHAR(100),
  LastName VARCHAR(50) NOT NULL,
  FirstName VARCHAR(50) NOT NULL,
  Adress VARCHAR(250),
  City VARCHAR(50),
  IndexCode VARCHAR(20),
  Phone VARCHAR(20),
  EMail VARCHAR(255)
);
ALTER TABLE customers ADD CONSTRAINT unique_last_firstname UNIQUE (LastName, FirstName);

CREATE TABLE orders (
  IdOrder INT PRIMARY KEY GENERATED BY DEFAULT AS IDENTITY,
  IdCustomer INT NOT NULL REFERENCES customers(IdCustomer),
  OrderDate date NOT NULL default current_date,
  ShipDate date,
  PaidDate date,
  Status char(1) CHECK (Status IN ('C', 'P', 'A'))
);

CREATE TABLE products (
  IdProduct INT PRIMARY KEY GENERATED BY DEFAULT AS IDENTITY,
  PrName VARCHAR(150) NOT NULL,
  PrPrice money,
  InStock INT,
  ReOrder BOOLEAN,
  Description TEXT
);

CREATE TABLE items (
  ItemID INT PRIMARY KEY GENERATED BY DEFAULT AS IDENTITY,
  OrderID INT NOT NULL REFERENCES orders(IdOrder),
  ProductID INT NOT NULL REFERENCES products(IDProduct),
  Quantity INT NOT NULL,
  Total MONEY
);