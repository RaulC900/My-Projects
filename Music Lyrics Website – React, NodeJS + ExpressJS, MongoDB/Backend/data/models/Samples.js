
const mongoose = require('mongoose');
const Schema = mongoose.Schema;

const SampleSchema = new Schema({
    authorUsername: {
        type: String,
        ref: 'Users',
        required: true
    },
    sample: {
        type: String,
        required: true
    },
    videoLink: {
        type: String,
        required: true
    }
}, { timestamps: true });

const SampleModel = mongoose.model('Samples', SampleSchema);
module.exports = SampleModel;
