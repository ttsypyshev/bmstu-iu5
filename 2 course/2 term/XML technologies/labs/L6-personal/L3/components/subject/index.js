export class SubjectComponent {
    constructor(parent) {
        this.parent = parent
    }
    getHTML(data) {
        const result1 = 
        `
                <div style="width: 50%; height: auto;">
                    <div>
                        <div style="width:200%; margin-top: 20px;">
                            <div id="carousel-${data.id}" class="carousel slide" data-bs-ride="carousel" data-bs-interval="3000">
                                <div class="carousel-indicators">
                                    <button type="button" data-bs-target="#carousel-${data.id}" data-bs-slide-to="0" class="active" aria-current="true" aria-label="Slide 1"></button>
                                    <button type="button" data-bs-target="#carousel-${data.id}" data-bs-slide-to="1" aria-label="Slide 2"></button>
                                    <button type="button" data-bs-target="#carousel-${data.id}" data-bs-slide-to="2" aria-label="Slide 3"></button>
                                </div>
                                <div class="carousel-inner">
        `
        const result2 = 
        `
                                </div>
                                <button class="carousel-control-prev" type="button" data-bs-target="#carousel-${data.id}" data-bs-slide="prev">
                                    <span class="carousel-control-prev-icon" aria-hidden="true"></span>
                                    <span class="visually-hidden">Previous</span>
                                </button>
                                <button class="carousel-control-next" type="button" data-bs-target="#carousel-${data.id}" data-bs-slide="next">
                                    <span class="carousel-control-next-icon" aria-hidden="true"></span>
                                    <span class="visually-hidden">Next</span>
                                </button>
                            </div>
                        </div>
                        <div>
                            <div>
                                <h1 class="card-title" style="position: relative; left: 50%; text-align: center; margin-top: 20px;">${data.sub_page.title}</h1>
                                <p class="card-text" style="position: relative; left: 50%; text-align: center;">${data.sub_page.text}</p>
                            </div>
                        </div>
                    </div>
                </div>
        `
        var content = new String()
        const len = data.sub_page.src.length
        
        if (len === 0){
            content=""
        } else {          
            content = 
            `
                                    <div class="carousel-item active">
                                        <img class="d-block w-100" src="${data.sub_page.src[0]}" alt="Description" style="height: 500px; width: 100%; object-position: center; object-fit: cover;">
                                    </div>
            `
            for (var i = 1; i < len; i++)
            {
                content = content +
                (
                `
                                    <div class="carousel-item">
                                        <img class="d-block w-100" src="${data.sub_page.src[i]}" alt="Description" style="height: 500px; width: 100%; object-position: center; object-fit: cover;">
                                    </div>
                `
                )
            }
            
        }
        return (result1+content+result2)
    }
    
    render(data) {
        const html = this.getHTML(data)
        this.parent.insertAdjacentHTML('beforeend', html)
    }
}