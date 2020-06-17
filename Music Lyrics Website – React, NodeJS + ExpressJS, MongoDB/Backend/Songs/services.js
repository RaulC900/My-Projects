const {
    Songs
} = require('../data');

const {
    Artists,
} = require('../data');

const {
    Users,
} = require('../data');

const add = async (name, artistName, genres, lyrics) => {
    const artist = await Artists.findOne({name: artistName});

    const song = new Songs({
        artist: artist,
        name: name,
        lowercaseName: name.toLowerCase(),
        genres: genres,
        lyrics: lyrics
    });
    await song.save();
};

const getAll = async () => {
    return await Songs.find().populate('artist', 'name');
};

const getById = async (id) => {
    let a;
    try {
        a = await Songs.findById(id).populate('artist', 'name');
    } catch (err) {
        next(err)
    }
    return a
};

const getByName = async (songName) => {
    let a;
    try {
        a = await Songs.findOne({name: songName}).populate('artist', 'name')
    } catch (err) {
        next(err)
    }
    return a
};

const getSearchLowercaseByName = async (songName) => {
    let a;
    try {
        a = await Songs.findOne({lowercaseName: songName}).populate('artist', 'name')
    } catch (err) {
        next(err)
    }
    return a
};

const getByArtistName = async (artistName) => {
    let response = []
    const songs = await Songs.find().populate('artist', 'name');
    for(let i of songs) {
        if(i.artist.name == artistName) {
            response.push(i)
        }
    }
    return response
    
};

const updateByName = async (songName, name, artistName, genres, lyrics) => {
    const artist = await Artists.findOne({name: artistName});
    await Songs.findOneAndUpdate({name: songName}, { artist: artist, name: name, genres: genres, lyrics: lyrics });
};

const deleteById = async (id) => {
    await Songs.findByIdAndDelete(id);
};

const addComment = async (songName, comment) => {
    const song = await Songs.findOne({name: songName});
    if(song != null) {
        let aux = song.comments
        aux.push(comment)
        song.comments = aux
        await song.save()
    }
}

const getComments = async (songName) => {
    const song = await Songs.findOne({name: songName}).populate('comments')
    return song.comments
}

const deleteComment = async (songName, id) => {
    const song = await Songs.findOne({name: songName})
    let list = song.comments.filter(x => {
        return x._id != id;
    })
    song.comments = list
    await song.save()
}

const addSample = async (songName, sample) => {
    const song = await Songs.findOne({name: songName});
    song.samples.push(sample)
    await song.save()
}

const getSamples = async (songName) => {
    const song = await Songs.findOne({name: songName}).populate('samples')
    return song.samples
}

const deleteSample = async (songName, id) => {
    const song = await Songs.findOne({name: songName})
    let list = song.samples.filter(x => {
        return x._id != id;
    })
    song.samples = list
    await song.save()
}

module.exports = {
    add,
    getAll,
    getById,
    getByName,
    getSearchLowercaseByName,
    getByArtistName,
    updateByName,
    deleteById,
    deleteComment,
    addComment,
    getComments,
    deleteSample,
    addSample,
    getSamples
}