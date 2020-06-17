const express = require('express');

const SamplesService = require('./services.js');
const {
    validateFields
} = require('../utils');

const {
    ServerError
} = require('../errors');

const {
    Comments
} = require('../data');

const router = express.Router();

router.post('/', async (req, res, next) => {
    const {
        authorUsername,
        sample,
        videoLink
    } = req.body;
    try {
        const fieldsToBeValidated = {
            authorUsername: {
                value: authorUsername,
                type: 'string'
            },
            sample: {
                value: sample,
                type: 'string'
            },
            videoLink: {
                value: videoLink,
                type: 'string'
            }
        };

        validateFields(fieldsToBeValidated);

        let samp = await SamplesService.add(authorUsername, sample, videoLink);

        res.json(samp)
    } catch (err) {
        next(err);
    }
});

router.get('/', async (req, res, next) => {
    try {
        const samples = await SamplesService.getAll();
        res.json(samples);
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

        await SamplesService.deleteById(id);
        res.status(204).end();
    } catch (err) {
        next(err);
    }
});

module.exports = router;