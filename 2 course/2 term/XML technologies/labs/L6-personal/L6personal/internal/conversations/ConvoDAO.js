const {ConvosRepository} = require('./ConvosRepository');

class ConvoDAO {
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

    static _validate(Convo) {
        if (
            Convo.id === undefined ||
            Convo.src === undefined ||
            Convo.title === undefined ||
            Convo.text === undefined ||
            Convo.sub_page === undefined
        ) {
            throw new Error('invalidate Convo data');
        }

        this._validateId(Convo.id);
    }

    static find() {
        const Convos = ConvosRepository.read();

        return Convos.map(({id, src, title, text, sub_page}) => {
            return new this(id, src, title, text, sub_page);
        });
    }

    static findById(id) {
        this._validateId(id);

        const Convos = ConvosRepository.read();
        const Convo = Convos.find((s) => s.id === id);

        return new this(Convo.id, Convo.src, Convo.title, Convo.text, Convo.sub_page);
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
    ConvoDAO,
}