function in_dict(key,dict)
{
    return dict.hasOwnProperty(key);
}
export class ProductComponent {
    constructor(parent) {
        this.parent = parent
    }

    getHTML(data) {
        var sx = ''
        var bd = ''
        var country = ''
        var city = ''
        var occ = ''
        if (in_dict("sex", data)===true){
            if (data.sex===2){
                sx = "мужской"
            }
            else{
                sx= "женский"
            }
        }
        else {
            sx = "не указан"
        }
        if (in_dict("country", data)===true){country = data.country.title}
        else {country = "не указана"}
        if (in_dict("bdate", data)===true){bd = data.bdate}
        else {bd = "не указан"}
        if (in_dict("city", data)===true){city = data.city.title}
        else {city = "не указан"}
        if (in_dict("occupation", data)===true){occ = data.occupation.name}
        else {occ = "не указано"}
        return (
            `
                <div class="card mb-3" style="width: 540px; margin-top: 10px; margin-left: 10px;">
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
            `
        )
    }

    render(data) {
        const html = this.getHTML(data)
        this.parent.insertAdjacentHTML('beforebegin', html)
    }
}