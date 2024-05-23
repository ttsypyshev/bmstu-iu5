class Urls {
    constructor() {
        this.url = 'http://localhost:8000/products';
    }

    getProducts(params = {}) {
        let query_string = Object.entries(params)
            .map(([key, value]) => `${key}=${value}`)
            .join('&');
        return `${this.url}${query_string ? '?' + query_string : ''}`;
    }

    getProductById(productID) {
        return `${this.url}/${productID}`;
    }

    addProduct() {
        return this.url;
    }

    deleteProduct(productID) {
        return `${this.url}/${productID}`;
    }
}

export const urls = new Urls();

