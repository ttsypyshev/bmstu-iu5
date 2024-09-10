const {DBConnector} = require('../../modules/DBConnector');

class ProductsRepository {
    static db = new DBConnector('products.json');

    static read() {
        const file = this.db.readFile();

        return JSON.parse(file);
    }

    static write(json) {
        this.db.writeFile(JSON.stringify(json));
    }
}

module.exports = {
    ProductsRepository,
}