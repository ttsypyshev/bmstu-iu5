const {CoursesRepository} = require('./CoursesRepository');

class CourseDAO {
    constructor(id, src, title, text, sub_page) {
        this.id = id;
        this.src = src;
        this.title = title;
        this.text = text;
        this.sub_page = sub_page
    }

    static _validateId(id) {
        const numberId = Number.parseInt(id);
        if (Number.isNaN(numberId)) {
            throw new Error('invalidate id');
        }
    }

    static _validate(Course) {
        if (
            Course.id === undefined ||
            Course.src === undefined ||
            Course.title === undefined ||
            Course.text === undefined ||
            Course.sub_page === undefined
        ) {
            throw new Error('invalidate Course data');
        }

        this._validateId(Course.id);
    }

    static find() {
        const Courses = CoursesRepository.read();

        return Courses.map(({id, src, title, text, sub_page}) => {
            return new this(id, src, title, text, sub_page);
        });
    }

    static findById(id) {
        this._validateId(id);

        const Courses = CoursesRepository.read();
        const Course = Courses.find((s) => s.id === id);

        return new this(Course.id, Course.src, Course.title, Course.text, Course.sub_page);
    }

    static insert(Course) {
        this._validate(Course);

        const Courses = CoursesRepository.read();
        CoursesRepository.write([...Courses, Course]);

        return new this(Course.id, Course.src, Course.title, Course.text, Course.sub_page);
    }

    static delete(id) {
        this._validateId(id);

        const Courses = CoursesRepository.read();
        const filteredCourses = Courses.filter((s) => s.id !== id);

        CoursesRepository.write(filteredCourses);

        return filteredCourses.map(({id, src, title, text, sub_page}) => {
            return new this(id, src, title, text, sub_page);
        });
    }

    toJSON() {
        return {
            id: this.id,
            src: this.src,
            title: this.title,
            text: this.text,
            sub_page: this.sub_page
        }
    }
}

module.exports = {
    CourseDAO,
}