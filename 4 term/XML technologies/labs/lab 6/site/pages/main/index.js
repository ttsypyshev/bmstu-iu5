import { ProductCardComponent } from "../../components/product-card/index.js";
import { ProductPage } from "../product/index.js";
import { ajax } from '../../modules/ajax.js';
import { urls } from '../../modules/urls.js';

export class MainPage {
    constructor(parent) {
        this.parent = parent;
    }

    get pageRoot() {
        return document.getElementById('main-page');
    }

    getHTML() {
        return `
            <div id="carouselExampleControls" class="carousel slide" data-bs-ride="carousel">
                <div class="carousel-inner" id="main-page"></div>
                <button class="carousel-control-prev" type="button" data-bs-target="#carouselExampleControls" data-bs-slide="prev">
                    <span class="carousel-control-prev-icon" aria-hidden="false"></span>
                    <span class="visually-hidden">Previous</span>
                </button>
                <button class="carousel-control-next" type="button" data-bs-target="#carouselExampleControls" data-bs-slide="next">
                    <span class="carousel-control-next-icon" aria-hidden="false"></span>
                    <span class="visually-hidden">Next</span>
                </button>
            </div>
            <button id="add-product" class="btn btn-primary mt-3">Добавить продукт</button>
            <div id="add-product-form" style="display: none;">
                <h3>Добавить продукт</h3>
                <form id="product-form">
                    <div class="mb-3">
                        <label for="product-title" class="form-label">Название</label>
                        <input type="text" class="form-control" id="product-title" required>
                    </div>
                    <div class="mb-3">
                        <label for="product-text" class="form-label">Описание</label>
                        <textarea class="form-control" id="product-text" rows="3" required></textarea>
                    </div>
                    <div class="mb-3">
                        <label for="product-src" class="form-label">URL картинки</label>
                        <input type="url" class="form-control" id="product-src" required>
                    </div>
                    <button type="submit" class="btn btn-success">Сохранить</button>
                    <button type="button" class="btn btn-secondary" id="cancel-add">Отмена</button>
                </form>
            </div>
        `;
    }

    async getData() {
        return await ajax.get(urls.getProducts({}));
    }

    clickCard(e) {
        const cardId = e.target.dataset.id;
        const productPage = new ProductPage(this.parent, cardId);
        productPage.render();
    }

    showAddProductForm() {
        document.getElementById('add-product-form').style.display = 'block';
    }

    hideAddProductForm() {
        document.getElementById('add-product-form').style.display = 'none';
    }

    async submitAddProductForm(e) {
        e.preventDefault();
        const title = document.getElementById('product-title').value;
        const text = document.getElementById('product-text').value;
        const src = document.getElementById('product-src').value;

        const newProduct = { title, text, src };
        const result = await ajax.post(urls.addProduct(), newProduct);
        if (result) {
            alert('Продукт успешно добавлен');
            this.hideAddProductForm();
            this.render();
        } else {
            alert('Ошибка при добавлении продукта');
        }
    }

    addEventListeners() {
        document.getElementById('add-product').addEventListener('click', this.showAddProductForm.bind(this));
        document.getElementById('cancel-add').addEventListener('click', this.hideAddProductForm.bind(this));
        document.getElementById('product-form').addEventListener('submit', this.submitAddProductForm.bind(this));
    }

    async render() {
        this.parent.innerHTML = '';
        const html = this.getHTML();
        this.parent.insertAdjacentHTML('beforeend', html);

        const data = await this.getData();
        if (data) {
            data.forEach((item, index) => {
                const productCard = new ProductCardComponent(this.pageRoot);
                productCard.render(item, this.clickCard.bind(this));
                if (index === 0) {
                    productCard.parent.querySelector('.carousel-item').classList.add('active');
                }
            });
        } else {
            this.pageRoot.innerHTML = '<p class="text-center">Failed to load products. Please try again later.</p>';
        }

        this.addEventListeners();
    }
}
