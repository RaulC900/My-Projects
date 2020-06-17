
const mongoose = require('mongoose');
const Schema = mongoose.Schema;

const SongSchema = new Schema({
    artist: {
        type: Schema.Types.ObjectId,
        ref: 'Artists',
        required: true
    },
    name: {
        type: String,
        required: true
    },
    lowercaseName: {
        type: String,
        required: true
    },
    genres: {
        type: String,
        enum: ['pop', 'rock', 'hip-hop'],
    },
    lyrics: {
        type: String,
        required: true
    },
    comments: [{
        type: Schema.Types.ObjectId,
        ref: 'Comments'
    }],
    samples: [{
        type: Schema.Types.ObjectId,
        ref: 'Samples'
    }]

}, { timestamps: true });

const SongModel = mongoose.model('Songs', SongSchema);
module.exports = SongModel;
