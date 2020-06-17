const express = require('express');

const QuestionsService = require('./services.js');

const {
    validateFields
} = require('../utils');

const router = express.Router();

router.post('/', async (req, res, next) => {
    const {
        authorEmail,
        subject,
        report
    } = req.body;

    try {

        const fieldsToBeValidated = {
            authorEmail: {
                value: authorEmail,
                type: 'string'
            },
            subject: {
                value: subject,
                type: 'string'
            },
            report: {
                value: report,
                type: 'string'
            }
        };

        validateFields(fieldsToBeValidated);

        const message = await QuestionsService.add(authorEmail, subject, report);

        res.json(message);
    } catch (err) {
        next(err);
    }
});

router.get('/', async (req, res, next) => {
    try {
        const questions = await QuestionsService.getAll();
        res.json(questions);
    } catch (err) {
        next(err);
    }
});

router.put('/:id', async (req, res, next) => {
    const {
        id
    } = req.params;
    const {
        answer
    } = req.body;
    try {

        const fieldsToBeValidated = {
            answer: {
                value: answer,
                type: 'string'
            },
            id: {
                value: id,
                type: 'string'
            }
        };

        validateFields(fieldsToBeValidated);

        await QuestionsService.updateById(answer, id);
        res.status(204).end();
    } catch (err) {
        next(err);
    }
});

router.put('/starr/:id', async (req, res, next) => {
    const {
        id
    } = req.params;
    try {

        const fieldsToBeValidated = {
            id: {
                value: id,
                type: 'string'
            }
        };

        validateFields(fieldsToBeValidated);

        await QuestionsService.starrQuestion(id);
        res.status(204).end();
    } catch (err) {
        next(err);
    }
});

router.put('/unstarr/:id', async (req, res, next) => {
    const {
        id
    } = req.params;
    try {

        const fieldsToBeValidated = {
            id: {
                value: id,
                type: 'string'
            }
        };

        validateFields(fieldsToBeValidated);

        await QuestionsService.unstarrQuestion(id);
        res.status(204).end();
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
        await QuestionsService.deleteById(id);
        res.status(204).end();
    } catch (err) {
        next(err);
    }
});

module.exports = router;