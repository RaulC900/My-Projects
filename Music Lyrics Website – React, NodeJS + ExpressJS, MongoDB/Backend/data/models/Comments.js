
const mongoose = require('mongoose');
const Schema = mongoose.Schema;

const CommentSchema = new Schema({
    authorUsername: {
        type: String,
        ref: 'Users',
        required: true
    },
    comment: {
        type: String,
        required: true
    }
}, { timestamps: true });

const CommentModel = mongoose.model('Comments', CommentSchema);
module.exports = CommentModel;
