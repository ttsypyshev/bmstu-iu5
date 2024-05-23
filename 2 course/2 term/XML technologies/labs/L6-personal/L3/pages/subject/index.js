import {SubjectComponent} from "../../components/subject/index.js";
import {BackButtonComponent} from "../../components/back-button/index.js";
import {MainPage} from "../main/index.js";

export class SubjectPage {
    constructor(parent, dataset) {
        this.parent = parent
        this.dataset = dataset
    }

    get pageRoot() {
        return document.getElementById('subject-page')
    }

    getHTML() {
        return (
            `
                <div id="subject-page" style="width:100%; height: 100%;"></div>
            `
        )
    }

    clickBack() {
        const mainPage = new MainPage(this.parent)
        mainPage.render()
    }
    
    render() {
        this.parent.innerHTML = ''
        const html = this.getHTML()
        this.parent.insertAdjacentHTML('beforeend', html)
    
        const backButton = new BackButtonComponent(this.pageRoot)
        backButton.render(this.clickBack.bind(this))
    
        const subjectComponent = new SubjectComponent(this.pageRoot)
        subjectComponent.render(this.dataset)
    }
}