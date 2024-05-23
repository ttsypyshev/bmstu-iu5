const express = require('express');

const app = express(); // 1

const host = 'localhost';
const port = 8000;

app.listen(port, host, () => { // 3
    console.log(`Сервер запущен по адресу http://${host}:${port}`);
});

app.get('/product', (req, res) => {
    res.json({ product: 'учебные предметы' });
});