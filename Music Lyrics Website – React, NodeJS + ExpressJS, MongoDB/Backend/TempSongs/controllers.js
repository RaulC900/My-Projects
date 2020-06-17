const express = require('express');

const TempSongsService = require('./services.js');
const {
    validateFields
} = require('../utils');

const {
    ServerError
} = require('../errors');

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

        await TempSongsService.add(name, artistName, genres, lyrics);

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
        const songs = await TempSongsService.getAll();
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
        const song = await TempSongsService.getByName(name);
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
        const songs = await TempSongsService.getByArtistName(name);
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

        await TempSongsService.updateByName(songName, name, artistName, genres, lyrics);
        
        res.status(201).end()

    } catch (err) {
        const msg = err.message

        if(msg.includes('is not a valid enum')) {
            res.status(400).json("The selected genre doesen't exist")
        }

        next(err);
    }
});

router.delete('/:name', async (req, res, next) => {
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

        await TempSongsService.deleteByName(name);
        res.status(204).end();
    } catch (err) {
        next(err);
    }
});

module.exports = router;