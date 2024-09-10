const express = require('express');
const {ProductsController} = require('./ProductsController');

const router = express.Router();

router.get('/', ProductsController.findProducts);
router.get('/:id', ProductsController.findProductById);
router.post('/', ProductsController.addProduct);
router.delete('/:id', ProductsController.deleteProduct);
router.get('/products/', ProductsController.findProducts);

module.exports = router;