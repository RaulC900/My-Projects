const mongoose = require('mongoose');
const Schema = mongoose.Schema;

const QuestionsSchema = new Schema({
    authorEmail: {
        type: String,
        required: true
    },
    subject: {
        type: String,
        required: true
    },
    report: {
        type: String,
        required: true
    },
    answer: {
        type: String,
        default: "Unanswered"
    },
    starred: {
        type: Boolean,
        default: false
    }
}, { timestamps: true });

const QuestionsModel = mongoose.model('Questions', QuestionsSchema);
module.exports = QuestionsModel;
