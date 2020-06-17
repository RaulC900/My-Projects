const mongoose = require('mongoose');

const Schema = mongoose.Schema;

const TechnicalSchema = new Schema({
    username: {
        type: String,
        required: true
    },
    password: {
        type: String,
        required: true
    }
}, { timestamps: true });

const TechnicalModel = mongoose.model('Technical', TechnicalSchema);
module.exports = TechnicalModel;
