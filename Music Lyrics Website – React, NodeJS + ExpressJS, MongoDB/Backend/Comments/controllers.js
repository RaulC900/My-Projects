const express = require('express');

const CommentsService = require('./services.js');

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
        comment
    } = req.body;
    try {
        const fieldsToBeValidated = {
            authorUsername: {
                value: authorUsername,
                type: 'string'
            },
            comment: {
                value: comment,
                type: 'string'
            }
        };

        validateFields(fieldsToBeValidated);

        let comm = await CommentsService.add(authorUsername, comment);

        res.json(comm)
    } catch (err) {
        next(err);
    }
});

router.get('/', async (req, res, next) => {
    try {
        const comments = await CommentsService.getAll();
        res.json(comments);
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

        await CommentsService.deleteById(id);
        res.status(204).end();
    } catch (err) {
        next(err);
    }
});

module.exports = router;