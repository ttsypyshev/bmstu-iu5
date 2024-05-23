const express = require('express');

const courses = require('./internal/courses');

const app = express();

const host = 'localhost';
const port = 8000;

app.use(express.json());

app.use('/courses', courses);

app.listen(port, host, () => {
    console.log(`Сервер запущен по адресу http://${host}:${port}`);
});