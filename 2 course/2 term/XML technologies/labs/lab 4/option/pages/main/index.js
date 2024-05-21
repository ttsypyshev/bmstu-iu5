import { ProductCardComponent } from "../../components/product-card/index.js";
import { ProductPage } from "../product/index.js";
import { ajax } from "../../modules/ajax.js";
import { urls } from "../../modules/urls.js";
import { groupId } from "../../modules/consts.js";
import { FilterComponent } from "../../components/filter/index.js";

export class MainPage {
    constructor(parent) {
        this.parent = parent;
        this.filterValue = null;
        this.items = []; // Добавляем свойство для хранения текущих данных
    }

    get pageRoot() {
        return document.getElementById('main-page');
    }

    getHTML() {
        return (
            `
                <div id="filter-container"></div>
                <div id="main-page"></div>
            `
        );
    }

    getData() {
        ajax.post(urls.getGroupMembers(groupId, this.filterValue), (data) => {
            if (data.response && data.response.items !== undefined) {
                this.items = data.response.items; // Сохраняем данные
                this.renderData(this.items);
            } else {
                // Обрабатываем ошибку
                console.error("Ошибка получения данных:", data);
            }
        });
    }

    clickCard(e) {
        const cardId = e.target.dataset.id;
        const productPage = new ProductPage(this.parent, cardId, this); // Передаем this как parent_obj
        productPage.render();
    }

    renderData(items) {
        this.pageRoot.innerHTML = ''; // Очищаем содержимое div перед рендером
        items.forEach((item) => {
            const productCard = new ProductCardComponent(this.pageRoot);
            productCard.render(item, this.clickCard.bind(this));
        });
    }

    onFilterChange(filter) {
        this.filterValue = filter;
        this.getData();
    }

    render() {
        this.parent.innerHTML = '';
        const html = this.getHTML();
        this.parent.insertAdjacentHTML('beforeend', html);

        this.filterComponent = new FilterComponent(document.getElementById('filter-container'));
        this.filterComponent.render(this.onFilterChange.bind(this));

        if (this.items.length > 0) {
            this.renderData(this.items); // Если есть сохраненные данные, рендерим их
        } else {
            this.getData(); // Иначе загружаем данные
        }
    }
}
