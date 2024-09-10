CREATE TABLE Technical_Specialists (
  TechnicalSpecialist_ID SERIAL PRIMARY KEY,
  First_Name VARCHAR(50),
  Middle_Name VARCHAR(50),
  Last_Name VARCHAR(50),
  Email VARCHAR(100),
  Phone_Number VARCHAR(20),
  Date_Of_Birth DATE,
  Passport_Data VARCHAR(50),
  Number_Of_Orders INTEGER
);

CREATE TABLE Service_Centers (
  ServiceCenter_ID SERIAL PRIMARY KEY,
  Location VARCHAR(100),
  Contact_Number VARCHAR(20),
  Email VARCHAR(100),
  Operating_Hours VARCHAR(50),
  Degree_Of_Workload VARCHAR(20)
);

CREATE TABLE Offices (
  Office_ID SERIAL PRIMARY KEY,
  Name_Office VARCHAR(100),
  Location VARCHAR(100),
  Phone_Number VARCHAR(20),
  Email VARCHAR(100),
  Working_Hours VARCHAR(50),
  Equipment VARCHAR(100),
  Policies VARCHAR(200),
  Remarks VARCHAR(200),
  Rating INTEGER
);

CREATE TABLE Orders (
  Order_ID SERIAL PRIMARY KEY,
  Office_ID INTEGER,
  ServiceCenter_ID INTEGER,
  Order_Date DATE,
  Ship_Date DATE,
  Total_Amount VARCHAR(10),
  Payment_Method VARCHAR(50),
  Priority VARCHAR(20),
  Notes VARCHAR(200),
  FOREIGN KEY (Office_ID) REFERENCES Offices(Office_ID),
  FOREIGN KEY (ServiceCenter_ID) REFERENCES Service_Centers(ServiceCenter_ID)
);

CREATE TABLE Devices (
  Device_ID SERIAL PRIMARY KEY,
  Order_ID INTEGER,
  Description VARCHAR(200),
  Manufacturer VARCHAR(100),
  Model VARCHAR(100),
  Serial_Number VARCHAR(50),
  Release_Date DATE,
  Price VARCHAR(10),
  Weight VARCHAR(10),
  Color VARCHAR(20),
  Dimensions VARCHAR(50),
  FOREIGN KEY (Order_ID) REFERENCES Orders(Order_ID)
);


CREATE TABLE Spare_Parts (
  SparePart_ID SERIAL PRIMARY KEY,
  Device_ID INTEGER,
  Description VARCHAR(200),
  Manufacturer VARCHAR(100),
  Model VARCHAR(100),
  Serial_Number VARCHAR(50),
  Price VARCHAR(10),
  Weight VARCHAR(10),
  Dimensions VARCHAR(50),
  Availability VARCHAR(20),
  FOREIGN KEY (Device_ID) REFERENCES Devices(Device_ID)
);



CREATE TABLE Clients (
  Client_ID SERIAL PRIMARY KEY,
  Office_ID INTEGER,
  First_Name VARCHAR(50),
  Middle_Name VARCHAR(50),
  Last_Name VARCHAR(50),
  Email VARCHAR(100),
  Phone_Number VARCHAR(20),
  Date_Of_Birth DATE,
  Passport_Data VARCHAR(50),
  FOREIGN KEY (Office_ID) REFERENCES Offices(Office_ID)
);



CREATE TABLE Employments (
  Employment_ID SERIAL PRIMARY KEY,
  TechnicalSpecialist_ID INTEGER,
  ServiceCenter_ID INTEGER,
  FOREIGN KEY (TechnicalSpecialist_ID) REFERENCES Technical_Specialists(TechnicalSpecialist_ID),
  FOREIGN KEY (ServiceCenter_ID) REFERENCES Service_Centers(ServiceCenter_ID)
);
