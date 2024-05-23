import {SubjectCardComponent} from "../../components/subject-card/index.js";
import {SubjectPage} from "../subject/index.js";
import { fetch_obj } from "../../server_modules/fetch_logic.js";
import { urls } from "../../server_modules/urls.js";


export class MainPage{
    constructor(parent){
        this.parent=parent;
    }
    
    get pageRoot() {
        return document.getElementById('main-page')
    }
        
    getHTML() {
        return (
            `
                <div id="main-page" class="d-flex flex-wrap"><div/>
            `
        )
    }
    
    clickCard(subjectPage) {
        subjectPage.render()
    }
    
    render() {
        this.parent.innerHTML = ''
        const html = this.getHTML()
        this.parent.insertAdjacentHTML('beforeend', html)
        var params = {alphabet: true, ascending: true}
        fetch_obj.get(urls.getCourses(params)).then((result) => {
            result.forEach((item) => {
                const subjectCard = new SubjectCardComponent(this.pageRoot)
                const subjectPage = new SubjectPage(this.parent, item)
                subjectCard.render(item, this.clickCard.bind(this, subjectPage))
            })
        })
    }
}