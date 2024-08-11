export class BackButtonComponent {
    constructor(parent) {
        this.parent = parent;
    }

    getHTML() {
        return `
            <button class="btn btn-secondary mb-3">Назад</button>
        `;
    }

    render(listener) {
        this.parent.insertAdjacentHTML('afterbegin', this.getHTML());
        this.parent.querySelector('button').addEventListener('click', listener);
    }
}
