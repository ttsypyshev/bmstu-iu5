class Urls {
    constructor() {
        this.url = 'http://localhost:8000/products';
    }

    getProducts(params = {}) {
        const query_string = new URLSearchParams(params).toString();
        return `${this.url}${query_string ? `?${query_string}` : ''}`;
    }

    getProductById(productID) {
        return `${this.url}/${productID}`;
    }

    addProduct() {
        return `${this.url}/`;
    }

    deleteProduct(productID) {
        return `${this.url}/${productID}`;
    }
}

export const urls = new Urls();
