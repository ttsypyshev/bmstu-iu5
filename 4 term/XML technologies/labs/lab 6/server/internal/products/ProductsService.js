const {ProductDAO} = require('./ProductDAO');

class ProductsService {
    static findProducts(asc, alpha) {
        var result = ProductDAO.find().map((product) => product.toJSON());
        if (alpha=="true"){
            result.sort((a,b) => {
                (a.title).localeCompare(b.title);
            })
        }
        if (asc=="false"){
            result.reverse();
        }
        return result;
    }
    static findProduct(id){
        return ProductDAO.findById(id).toJSON();
    }
    static addProduct(product) {
        return ProductDAO.insert(product).toJSON();
    }

    static deleteProduct(id) {
        return ProductDAO.delete(id).map((product) => product.toJSON());
    }
}

module.exports = {
    ProductsService,
}