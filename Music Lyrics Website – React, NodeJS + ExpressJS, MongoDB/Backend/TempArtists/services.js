const {
    TempArtists,
} = require('../data');

const add = async (name) => {
    const artists = new TempArtists({
        name: name,
        lowercaseName: name.toLowerCase()
    });
    await artists.save();
};

const getAll = async () => {
    return await TempArtists.find();
};

const getByName = async (name) => {
    return await TempArtists.findOne({name: name});
};

const updateByName = async (artistName, name) => {
    await TempArtists.findOneAndUpdate({name: artistName}, { name: name });
};

const deleteByName = async (name) => {
    await TempArtists.findOneAndDelete({name: name});
};

module.exports = {
    add,
    getAll,
    getByName,
    updateByName,
    deleteByName
}