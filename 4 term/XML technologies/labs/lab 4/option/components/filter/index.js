export class FilterComponent {
    constructor(parent) {
        this.parent = parent;
    }

    getHTML() {
        return (
            `
                <div class="form-group" style="width: 700px; margin-top: 10px; margin-left: 10px;">
                    <label for="filter-select">Фильтр:</label>
                    <select class="form-control" id="filter-select">
                        <option value="">Все</option>
                        <option value="friends">Друзья</option>
                        <option value="unsure">Пользователи, которые выбрали «Возможно пойду» </option>
                        <option value="managers">Менеджеры</option>
                        <option value="donut">Пользователи, у которых есть платная подписка VK Donut</option>
                    </select>
                </div>
            `
        )
    }
    

    addListeners(listener) {
        const select = document.getElementById('filter-select');
        select.addEventListener('change', () => {
            listener(select.value);
        });
    }

    render(listener) {
        const html = this.getHTML();
        this.parent.insertAdjacentHTML('beforeend', html);
        this.addListeners(listener);
    }
}