const {ConvoDAO} = require('./ConvoDAO');

class ConvosService {
    static findConvos(id) {
        if (id !== undefined) {
            return ConvoDAO.findById(id).toJSON();
        }

        return ConvoDAO.find().map((course) => course.toJSON());
    }
}

module.exports = {
    ConvosService,
}