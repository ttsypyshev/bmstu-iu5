const {ProductsRepository} = require('./ProductsRepository');

class ProductDAO {
    constructor(id, src, title, text, sub_page) {
        this.id = id;
        this.src = src;
        this.title = title;
        this.text = text;
        this.sub_page = sub_page
    }

    static _validateId(id) {
        const numberId = Number.parseInt(id);
        if (Number.isNaN(numberId)) {
            throw new Error('invalidate id');
        }
    }

    static _validate(Product) {
        if (
            Product.id === undefined ||
            Product.src === undefined ||
            Product.title === undefined ||
            Product.text === undefined ||
            Product.sub_page === undefined
        ) {
            throw new Error('invalidate Product data');
        }

        this._validateId(Product.id);
    }

    static find() {
        const Products = ProductsRepository.read();

        return Products.map(({id, src, title, text, sub_page}) => {
            return new this(id, src, title, text, sub_page);
        });
    }

    static findById(id) {
        this._validateId(id);

        const Products = ProductsRepository.read();
        const Product = Products.find((s) => s.id === id);

        return new this(Product.id, Product.src, Product.title, Product.text, Product.sub_page);
    }

    static insert(Product) {
        this._validate(Product);

        const Products = ProductsRepository.read();
        ProductsRepository.write([...Products, Product]);

        return new this(Product.id, Product.src, Product.title, Product.text, Product.sub_page);
    }

    static delete(id) {
        this._validateId(id);

        const Products = ProductsRepository.read();
        const filteredProducts = Products.filter((s) => s.id !== id);

        ProductsRepository.write(filteredProducts);

        return filteredProducts.map(({id, src, title, text, sub_page}) => {
            return new this(id, src, title, text, sub_page);
        });
    }

    toJSON() {
        return {
            id: this.id,
            src: this.src,
            title: this.title,
            text: this.text,
            sub_page: this.sub_page
        }
    }
}

module.exports = {
    ProductDAO,
}