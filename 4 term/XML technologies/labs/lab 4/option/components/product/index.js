export class ProductComponent {
    constructor(parent) {
        this.parent = parent
    }

    getHTML(data) {
        const sx = data.hasOwnProperty("sex") ? (data.sex === 2 ? "мужской" : "женский") : "не указан";
        const bd = data.hasOwnProperty("bdate") ? data.bdate : "не указан";
        const country = data.hasOwnProperty("country") ? data.country.title : "не указана";
        const city = data.hasOwnProperty("city") ? data.city.title : "не указан";
        const occ = data.hasOwnProperty("occupation") ? data.occupation.name : "не указано";

        return (
            `
            <div style="margin-top: 10px; margin-left: 10px;"> 
                <div class="card mb-3" style="width: 540px;">
                    <div class="row g-0">
                        <div class="col-md-4">
                            <img src="${data.photo_400_orig}" class="img-fluid" alt="картинка">
                        </div>
                        <div class="col-md-8">
                            <div class="card-body">
                                <h5 class="card-title">${data.first_name} ${data.last_name}</h5>
                                <p class="card-text">Пол: ${sx}</p>
                                <p class="card-text">День рождения: ${bd}</p>
                                <p class="card-text">Страна: ${country}</p>
                                <p class="card-text">Город: ${city}</p>
                                <p class="card-text">Занятие: ${occ}</p>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
            `
        )
    }

    render(data) {
        const html = this.getHTML(data)
        this.parent.insertAdjacentHTML('beforebegin', html)
    }
}