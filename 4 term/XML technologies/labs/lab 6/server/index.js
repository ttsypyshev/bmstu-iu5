const express = require('express');

const products = require('./internal/products');

const app = express();

const host = 'localhost';
const port = 8000;

app.use(express.json());

app.use('/products', products);

app.listen(port, host, () => {
    console.log(`Сервер запущен по адресу http://${host}:${port}`);
});