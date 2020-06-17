const {
    TempSongs
} = require('../data');

const {
    Artists,
} = require('../data');

const add = async (name, artistName, genres, lyrics) => {
    const artist = await Artists.findOne({name: artistName});

    const song = new TempSongs({
        artist: artist,
        name: name,
        lowercaseName: name.toLowerCase(),
        genres: genres,
        lyrics: lyrics
    });
    await song.save();
};

const getAll = async () => {
    // get all books
    // populate 'author' field
    // modify output so author is made of 'author.firstName author.lastName'
    return await TempSongs.find().populate('artist', 'name');
};

const getById = async (id) => {
    // get book by id
    // populate 'author' field
    // modify output so author is made of 'author.firstName author.lastName'
    return await TempSongs.findById(id).populate('artist', 'name');
};

const getByName = async (songName) => {
    return await TempSongs.findOne({name: songName}).populate('artist', 'name');
};

const getByArtistName = async (artistName) => {
    // get book by author id
    // modify output so author is made of 'author.firstName author.lastName'
    let response = []
    const songs = await TempSongs.find().populate('artist', 'name');
    for(let i of songs) {
        if(i.artist.name == artistName) {
            response.push(i)
        }
    }
    return response
    
};

const updateByName = async (songName, name, artistName, genres, lyrics) => {
    // update by id
    const artist = await Artists.findOne({name: artistName});
    await TempSongs.findOneAndUpdate({name: songName}, { artist: artist, name: name, genres: genres, lyrics: lyrics });
    //await Songs.findByIdAndUpdate(id, { artist: artist, name: name, genres: genres, lyrics: lyrics });
};

const deleteByName = async (name) => {
    // delete by id
    await TempSongs.findOneAndDelete(name);
};

module.exports = {
    add,
    getAll,
    getById,
    getByName,
    getByArtistName,
    updateByName,
    deleteByName
}