const {ProductsService} = require('./ProductsService');

class ProductsController {
    static findProducts(req, res) {
        try {
            var asc = req.query.ascending;
            var alpha = req.query.alphabet;
            res.send(ProductsService.findProducts(asc, alpha));
        } catch (err) {
            res.status(400).send({status: 'Bad Request', message: err.message})
        }
    }

    static findProductById(req, res) {
        try {
            const id = Number.parseInt(req.params.id);
            res.send(ProductsService.findProduct(id))
        } catch (err) {
            res.status(400).send({status: 'Bad Request', message: err.message})
        }
    }

    static addProduct(req, res) {
        try {
            res.send(ProductsService.addProduct(req.body));
        } catch (err) {
            res.status(400).send({status: 'Bad Request', message: err.message})
        }
    }

    static deleteProduct(req, res) {
        try {
            const id = Number.parseInt(req.params.id);
            res.send(ProductsService.deleteProduct(id));
        } catch (err) {
            res.status(400).send({status: 'Bad Request', message: err.message})
        }
    }
}

module.exports = {
    ProductsController,
};