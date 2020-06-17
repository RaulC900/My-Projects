const express = require('express');

const SongsService = require('./services.js');

const {
    validateFields
} = require('../utils');

const {
    ServerError
} = require('../errors');

const {
    Comments,
    Samples
} = require('../data');

const router = express.Router();

router.post('/', async (req, res, next) => {
    const {
        name,
        artistName,
        genres,
        lyrics
    } = req.body;
    try {
        const fieldsToBeValidated = {
            name: {
                value: name,
                type: 'string'
            },
            artistName: {
                value: artistName,
                type: 'string'
            },
            lyrics: {
                value: lyrics,
                type: 'string'
            }
        };

        let existingGenres = ['pop', 'rock', 'hip-hop']

        let genreValidate = {
            genres: {
                value: genres,
                type: 'string'
            }
        }
        validateFields(genreValidate)

        if(!existingGenres.includes(genres)) {

            let errMsg = "The genre you selected " + "'" + genres + "'" + " doesen't exist !"
            return res.status(400).send({
                message: errMsg
            });
        }

        validateFields(fieldsToBeValidated);

        await SongsService.add(name, artistName, genres, lyrics);

        res.status(201).end();
    } catch (err) {
        const msg = err.message

        if(msg.includes('is not a valid enum')) {
            res.status(400).json("The selected genre doesen't exist")
        }
        next(err);
    }
});

router.get('/', async (req, res, next) => {
    try {
        const songs = await SongsService.getAll();
        res.json(songs);
    } catch (err) {
        next(err);
    }
});

router.get('/:name', async (req, res, next) => {
    const {
        name
    } = req.params;
    try {
        validateFields({
            name: {
                value: name,
                type: 'string'
            }
        });
        const song = await SongsService.getByName(name);
        res.json(song);
    } catch (err) {
        next(err);
    }
});

router.get('/searchLowercase/:name', async (req, res, next) => {
    const {
        name
    } = req.params;
    try {
        validateFields({
            name: {
                value: name,
                type: 'string'
            }
        });
        const song = await SongsService.getSearchLowercaseByName(name);
        res.json(song);
    } catch (err) {
        next(err);
    }
});

router.get('/search/:name', async (req, res, next) => {
    const {
        name
    } = req.params;
    try {
        validateFields({
            name: {
                value: name,
                type: 'string'
            }
        });
        const song = await SongsService.getByName(name);
        res.json(song);
    } catch (err) {
        next(err);
    }
});

router.get('/artists/:name', async (req, res, next) => {
    const {
        name
    } = req.params;
    try {
        validateFields({
            name: {
                value: name,
                type: 'string'
            }
        });
        const songs = await SongsService.getByArtistName(name);
        res.json(songs);

    } catch (err) {
        next(err);
    }
});

router.put('/:songName', async (req, res, next) => {
    const {
        songName
    } = req.params;
    const {
        name,
        artistName,
        genres,
        lyrics
    } = req.body;
    try {
       validateFields({
            songName: {
                value: songName,
                type: 'string'
            }
        });

       const fieldsToBeValidated = {
            name: {
                value: name,
                type: 'string'
            },
            artistName: {
                value: artistName,
                type: 'string'
            },
            lyrics: {
                value: lyrics,
                type: 'string'
            }
        };

        let existingGenres = ['pop', 'rock', 'hip-hop']

        let genreValidate = {
            genres: {
                value: genres,
                type: 'string'
            }
        }
        validateFields(genreValidate)

        if(!existingGenres.includes(genres)) {

            let errMsg = "The genre you selected " + "'" + genres + "'" + " doesen't exist !"
            return res.status(400).send({
                message: errMsg
            });
        }
      

        validateFields(fieldsToBeValidated);

        await SongsService.updateByName(songName, name, artistName, genres, lyrics);
        
        res.status(201).end()

    } catch (err) {
        const msg = err.message

        if(msg.includes('is not a valid enum')) {
            res.status(400).json("The selected genre doesen't exist")
        }

        next(err);
    }
});

router.put('/comments/:songName', async (req, res, next) => {
    const {
        songName
    } = req.params;
    const {
        comm
    } = req.body;
    try {
       validateFields({
            songName: {
                value: songName,
                type: 'string'
            },
            comm: {
                value: comm,
                type: Comments
            }
        });

        await SongsService.addComment(songName, comm)
        res.status(201).end()
    } catch (err) {
        next(err);
    }
});

router.delete('/comments/:songName/:id', async (req, res, next) => {
    const {
        songName,
        id
    } = req.params;
    try {
       validateFields({
            songName: {
                value: songName,
                type: 'string'
            },
            id: {
                value: id,
                type: Comments
            }
        });

        await SongsService.deleteComment(songName, id)
        res.status(201).end()
    } catch (err) {
        next(err);
    }
});

router.get('/comments/:songName', async (req, res, next) => {
    const {
        songName
    } = req.params;
    try {
       validateFields({
            songName: {
                value: songName,
                type: 'string'
            }
        });
        let comments = await SongsService.getComments(songName);
        if(comments == null) {
            let msg = 'No comments'
            return msg
        }
        res.json(comments)
    } catch (err) {
        next(err);
    }
});

router.put('/samples/:songName', async (req, res, next) => {
    const {
        songName
    } = req.params;
    const {
        samp
    } = req.body;
    try {
       validateFields({
            songName: {
                value: songName,
                type: 'string'
            },
            samp: {
                value: samp,
                type: Samples
            }
        });

        await SongsService.addSample(songName, samp)
        res.status(201).end()
    } catch (err) {
        next(err);
    }
});

router.delete('/samples/:songName/:id', async (req, res, next) => {
    const {
        songName,
        id
    } = req.params;
    try {
       validateFields({
            songName: {
                value: songName,
                type: 'string'
            },
            id: {
                value: id,
                type: Samples
            }
        });

        await SongsService.deleteSample(songName, id)
        res.status(201).end()
    } catch (err) {
        next(err);
    }
});

router.get('/samples/:songName', async (req, res, next) => {
    const {
        songName
    } = req.params;
    try {
       validateFields({
            songName: {
                value: songName,
                type: 'string'
            }
        });
        let samples = await SongsService.getSamples(songName);
        if(samples == null) {
            let msg = 'No samples'
            res.send(msg)
        }
        res.json(samples)
    } catch (err) {
        next(err);
    }
});

router.delete('/:id', async (req, res, next) => {
    const {
        id
    } = req.params;
    try {
        validateFields({
            id: {
                value: id,
                type: 'string'
            }
        });

        await SongsService.deleteById(id);
        res.status(204).end();
    } catch (err) {
        next(err);
    }
});

module.exports = router;