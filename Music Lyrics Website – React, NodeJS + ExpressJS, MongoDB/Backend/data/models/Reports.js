const mongoose = require('mongoose');
const Schema = mongoose.Schema;

const ReportsSchema = new Schema({
    report: {
        type: String,
        required: true
    },
    answer: {
        type: String,
        default: "Unanswered"
    }

}, { timestamps: true });

const ReportsModel = mongoose.model('Reports', ReportsSchema);
module.exports = ReportsModel;
