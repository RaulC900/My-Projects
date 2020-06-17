const {
    Artists,
} = require('../data');

const add = async (name) => {
    const artists = new Artists({
        name: name,
        lowercaseName: name.toLowerCase()
    });
    await artists.save();
};

const getAll = async () => {
    return await Artists.find();
};

const getByName = async (name) => {
    let a;
    try {
        a = await Artists.findOne({name: name});
    } catch (err) {
        next(err)
    }
    return a
};

const getSearcLowercasehByName = async (name) => {
    let a;
    try {
        a = await Artists.findOne({lowercaseName: name});
    } catch (err) {
        next(err)
    }
    return a
};

const updateByName = async (artistName, name) => {
    await Artists.findOneAndUpdate({name: artistName}, { name: name });
};

const deleteByName = async (name) => {
    await Artists.findOneAndDelete({name: name});
};

module.exports = {
    add,
    getAll,
    getByName,
    getSearcLowercasehByName,
    updateByName,
    deleteByName
}