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
    }
}
