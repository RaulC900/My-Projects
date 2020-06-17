const {
    Songs,
    Comments
} = require('../data');

const add = async (authorUsername, comment) => {
    const comm = new Comments({
        authorUsername: authorUsername,
        comment: comment
    });
    await comm.save();
    return comm
};

const getAll = async () => {
    return await Comments.find();
};

const deleteById = async (id) => {
    await Songs.findByIdAndDelete(id);
};

module.exports = {
    add,
    getAll,
    deleteById
}