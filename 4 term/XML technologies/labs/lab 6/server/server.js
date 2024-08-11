const express = require('express');
const fs = require('fs');
const path = require('path');

const app = express();
const host = 'localhost';
const port = 8000;

app.use(express.json());

const readJson = (fileName) => {
    const file = fs.readFileSync(path.join(__dirname, 'db', fileName), 'utf8');
    const json = JSON.parse(file);
    return json;
};

const writeJson = (fileName, data) => {
    fs.writeFileSync(path.join(__dirname, 'db', fileName), JSON.stringify(data, null, 4));
};

const storageName = 'products.json';

app.get('/product', (req, res) => {
    res.json({ product: 'Учебные предметы' });
});

app.get('/products/', (req, res) => {
    const products = readJson(storageName);
    let sortedProducts = products;

    // Sorting logic
    const { ascending, alphabet } = req.query;
    if (alphabet === 'true') {
        sortedProducts = products.sort((a, b) => a.title.localeCompare(b.title));
        if (ascending === 'false') {
            sortedProducts.reverse();
        }
    } else {
        sortedProducts = products.sort((a, b) => {
            if (ascending === 'true') {
                return a.id - b.id;
            } else {
                return b.id - a.id;
            }
        });
    }

    res.json(sortedProducts);
});

app.get('/products/:id', (req, res) => {
    const id = req.params.id;

    const numberId = Number.parseInt(id);
    if (Number.isNaN(numberId)) {
        res.status(400).json({ status: 'Bad Request', message: 'id must be number!' });
        return;
    }

    const products = readJson(storageName);
    const product = products.find((value) => value.id === numberId);

    if (product) {
        res.json(product);
    } else {
        res.status(404).json({ status: 'Not Found', message: `not found stock with id ${numberId}` });
    }
});

app.post('/products', (req, res) => {
    const newProduct = req.body;

    if (!newProduct || !newProduct.title || !newProduct.text || !newProduct.src) {
        res.status(400).json({ status: 'Bad Request', message: 'Invalid product data' });
        return;
    }

    const products = readJson(storageName);
    const newProductId = products.length > 0 ? products[products.length - 1].id + 1 : 1;
    newProduct.id = newProductId;

    products.push(newProduct);
    writeJson(storageName, products);

    res.status(201).json({ status: 'Success', message: 'Product added successfully', data: newProduct });
});

app.listen(port, host, () => {
    console.log(`Сервер запущен по адресу http://${host}:${port}`);
});
