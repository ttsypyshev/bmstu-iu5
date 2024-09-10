export class ProductCardComponent {
    constructor(parent) {
        this.parent = parent;
    }

    getHTML(data) {
        return `
            <div class="carousel-item">
                <div class="card" style="width: 100%;">
                    <img class="card-img-top" src="${data.src}" alt="картинка">
                    <div class="card-body">
                        <h5 class="card-title">${data.title}</h5>
                        <p class="card-text">${data.text}</p>
                        <button class="btn btn-primary" data-id="${data.id}">Нажми на меня</button>
                    </div>
                </div>
            </div>
        `;
    }

    addListeners(data, listener) {
        this.parent.querySelector(`[data-id="${data.id}"]`).addEventListener("click", listener)
    }
    
    render(data, listener) {
        const html = this.getHTML(data)
        this.parent.insertAdjacentHTML('beforeend', html)
        this.addListeners(data, listener)
    }
}