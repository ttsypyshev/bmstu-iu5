import { ProductCardComponent } from "../../components/product-card/index.js";
import { ProductPage } from "../product/index.js";
import { ajax } from "../../modules/ajax.js";
import { urls } from "../../modules/urls.js";
import { groupId } from "../../modules/consts.js";
import { FilterComponent } from "../../components/filter/index.js";

// Класс для управления главной страницей
export class MainPage {
    constructor(parent) {
        this.parent = parent; // Родительский элемент для вставки содержимого
        this.filterValue = null; // Значение фильтра
        this.items = []; // Список элементов для отображения
        this.loading = false; // Флаг загрузки данных
    }

    get pageRoot() {
        return document.getElementById('main-page');
    }

    getHTML() {
        return `
            <div id="filter-container"></div>
            <div id="main-page" class="d-flex flex-wrap justify-content-start"></div>
            <div id="loading-indicator" class="text-center my-3" style="display: none;">
                <div class="spinner-border" role="status">
                    <span class="sr-only">Loading...</span>
                </div>
            </div>
        `;
    }

    // Метод для получения данных с сервера
    async getData() {
        this.setLoading(true); // Устанавливаем флаг загрузки
        const data = await ajax.post(urls.getGroupMembers(groupId, this.filterValue));
        this.setLoading(false); // Снимаем флаг загрузки
        if (data && data.response && data.response.items !== undefined) {
            this.items = data.response.items; // Сохраняем полученные элементы
            this.renderData(this.items); // Отображаем данные
        } else {
            console.error("Ошибка получения данных:", data);
        }
    }

    // Метод для установки состояния загрузки
    setLoading(isLoading) {
        this.loading = isLoading;
        document.getElementById('loading-indicator').style.display = isLoading ? 'block' : 'none';
    }

    // Метод для обработки клика на карточке продукта
    clickCard(e) {
        const cardId = e.target.dataset.id;
        const productPage = new ProductPage(this.parent, cardId, this);
        productPage.render();
    }

    // Метод для отображения данных на странице
    renderData(items) {
        if (!this.pageRoot) return;
        this.pageRoot.innerHTML = '';
        if (items.length === 0) {
            this.pageRoot.innerHTML = '<p class="text-left w-100" style="margin-left: 10px;">Нет данных для отображения</p>';
        } else {
            items.forEach((item) => {
                const productCard = new ProductCardComponent(this.pageRoot);
                productCard.render(item, this.clickCard.bind(this));
            });
        }
    }

    // Метод для обработки изменения фильтра
    onFilterChange(filter) {
        this.filterValue = filter;
        this.getData();
    }

    // Метод для рендеринга главной страницы
    render() {
        this.parent.innerHTML = '';
        const html = this.getHTML();
        this.parent.insertAdjacentHTML('beforeend', html);

        this.filterComponent = new FilterComponent(document.getElementById('filter-container'));
        this.filterComponent.render(this.onFilterChange.bind(this));

        if (this.items.length > 0) {
            this.renderData(this.items);
        } else {
            this.getData();
        }
    }
}
