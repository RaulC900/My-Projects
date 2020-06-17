const {
    Songs,
    Samples
} = require('../data');

const add = async (authorUsername, sample, videoLink) => {
    const samp = new Samples({
        authorUsername: authorUsername,
        sample: sample,
        videoLink: videoLink
    });
    await samp.save();
    return samp
};

const getAll = async () => {
    return await Samples.find();
};

const deleteById = async (id) => {
    await Songs.findByIdAndDelete(id);
};

module.exports = {
    add,
    getAll,
    deleteById
}