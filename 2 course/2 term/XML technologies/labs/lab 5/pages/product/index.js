import { ProductComponent } from "../../components/product/index.js";
import { BackButtonComponent } from "../../components/back-button/index.js";
import { MainPage } from "../main/index.js";
import { ajax } from "../../modules/ajax.js";
import { urls } from "../../modules/urls.js";

// Класс для управления страницей продукта
export class ProductPage {
    constructor(parent, id, parent_obj) {
        this.parent = parent; // Родительский элемент для вставки содержимого
        this.id = id; // ID продукта
        this.parent_obj = parent_obj; // Объект родительской страницы
    }

    get pageRoot() {
        return document.getElementById('product-page');
    }

    getHTML() {
        return `
            <div id="product-page"></div>
        `;
    }

    // Метод для получения данных о продукте с сервера
    async getData() {
        const data = await ajax.get(urls.getUserInfo(this.id));
        if (data && data.response && data.response.length > 0) {
            this.renderData(data.response[0]);
        } else {
            console.error("Ошибка получения данных:", data);
        }
    }

    // Метод для отображения данных о продукте
    renderData(item) {
        const product = new ProductComponent(this.pageRoot);
        product.render(item);
    }

    // Метод для обработки клика на кнопку "Назад"
    clickBack() {
        document.getElementById("product-page").innerHTML = '';
        const mainPage = new MainPage(this.parent);
        mainPage.chat_chosen = this.parent_obj;
        mainPage.render();
    }

    // Метод для рендеринга страницы продукта
    render() {
        this.parent.innerHTML = '';
        const html = this.getHTML();
        this.parent.insertAdjacentHTML('beforeend', html);

        const backButton = new BackButtonComponent(this.pageRoot);
        backButton.render(this.clickBack.bind(this));

        this.getData();
    }
}
