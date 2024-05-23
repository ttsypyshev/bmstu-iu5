const {ConvosService} = require('./ConvosService');

class ConvosController {
    static findCourses(req, res) {
        try {
            res.send(ConvosService.findCourses());
        } catch (err) {
            res.status(400).send({status: 'Bad Request', message: err.message})
        }
    }

    static findCourseById(req, res) {
        try {
            const id = Number.parseInt(req.params.id);
            res.send(ConvosService.findCourses(id))
        } catch (err) {
            res.status(400).send({status: 'Bad Request', message: err.message})
        }
    }

    static addCourse(req, res) {
        try {
            res.send(ConvosService.addCourse(req.body));
        } catch (err) {
            res.status(400).send({status: 'Bad Request', message: err.message})
        }
    }

    static deleteCourse(req, res) {
        try {
            const id = Number.parseInt(req.params.id);
            res.send(ConvosService.deleteCourse(id));
        } catch (err) {
            res.status(400).send({status: 'Bad Request', message: err.message})
        }
    }
}

module.exports = {
    ConvosController,
};