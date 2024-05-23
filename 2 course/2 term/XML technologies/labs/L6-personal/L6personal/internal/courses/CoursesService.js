const {CourseDAO} = require('./CourseDAO');

class CoursesService {
    static findCourses(asc, alpha) {
        var result = CourseDAO.find().map((course) => course.toJSON());
        if (alpha=="true"){
            result.sort((a,b) => {
                (a.title).localeCompare(b.title);
            })
        }
        if (asc=="false"){
            result.reverse();
        }
        return result;
    }
    static findCourse(id){
        return CourseDAO.findById(id).toJSON();
    }
    static addCourse(course) {
        return CourseDAO.insert(course).toJSON();
    }

    static deleteCourse(id) {
        return CourseDAO.delete(id).map((course) => course.toJSON());
    }
}

module.exports = {
    CoursesService,
}