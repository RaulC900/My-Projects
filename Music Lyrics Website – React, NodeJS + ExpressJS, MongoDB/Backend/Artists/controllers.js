const express = require('express');

const ArtistsService = require('./services.js');

const {
    validateFields
} = require('../utils');

const router = express.Router();

router.post('/', async (req, res, next) => {
    const {
        name
    } = req.body;

    try {

        const fieldsToBeValidated = {
            name: {
                value: name,
                type: 'string'
            }
        };

        validateFields(fieldsToBeValidated);

        await ArtistsService.add(name);

        res.status(201).end();
    } catch (err) {
        next(err);
    }
});

router.get('/', async (req, res, next) => {
    try {

        const artists = await ArtistsService.getAll();
        res.json(artists);
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
        const artist = await ArtistsService.getByName(name);
        res.json(artist);
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
        const artist = await ArtistsService.getSearcLowercasehByName(name);
        res.json(artist);
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
        const artist = await ArtistsService.getByName(name);
        res.json(artist);
    } catch (err) {
        next(err);
    }
});

router.put('/:artistName', async (req, res, next) => {
    const {
        artistName
    } = req.params;
    const {
        name
    } = req.body;
    try {

        const fieldsToBeValidated = {
            artistName: {
                value: artistName,
                type: 'string'
            },
            name: {
                value: name,
                type: 'string'
            }
        };

        validateFields(fieldsToBeValidated);

        await ArtistsService.updateByName(artistName, name);
        res.status(204).end();
    } catch (err) {
        // daca primesc eroare, pasez eroarea mai departe la handler-ul de errori declarat ca middleware in start.js 
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
        // se poate modifica 
        await ArtistsService.deleteByName(name);
        res.status(204).end();
    } catch (err) {
        // daca primesc eroare, pasez eroarea mai departe la handler-ul de errori declarat ca middleware in start.js 
        next(err);
    }
});

module.exports = router;