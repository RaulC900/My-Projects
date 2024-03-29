const mongoose = require('mongoose');

const Schema = mongoose.Schema;

const ArtistSchema = new Schema({
    name: {
        type: String,
        required: true
    },
    lowercaseName: {
        type: String,
        required: true
    }
}, { timestamps: true });

const TempArtistModel = mongoose.model('TempArtists', ArtistSchema);

module.exports = TempArtistModel;
