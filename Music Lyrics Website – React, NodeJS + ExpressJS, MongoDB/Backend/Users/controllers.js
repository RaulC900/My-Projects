const express = require('express');
const jwt = require('jsonwebtoken');
const UsersService = require('./services.js');
const {
    validateFields
} = require('../utils');

const {
    ServerError
} = require('../errors');

const router = express.Router();

router.get('/confirmation/:token', async(req, res, next) => {
    const {
        token
    } = req.params;
    try {

        validateFields({
            token: {
                value: token,
                type: 'string'
            }
        });
        const user = jwt.verify(req.params.token, process.env.JWT_SECRET_KEY);
        await UsersService.activate(token);
    } catch (err) {
        next(err);
    }
    return res.redirect('http://localhost:3001/login');
});

router.get('/', async (req, res, next) => {
    try {
        const users = await UsersService.getAll();
        res.json(users);
    } catch (err) {
        next(err);
    }
});

router.post('/approve/:id', async (req, res, next) => {
    const {
        id
    } = req.params;
    try {
        const fieldsToBeValidated = {
            id: {
                value: id,
                type: 'string'
            }
        }
        validateFields(fieldsToBeValidated);

        await UsersService.approveById(id);
        res.end()
    } catch (err) {
        next(err);
    }
});

router.delete('/approve/:id', async (req, res, next) => {
    const {
        id
    } = req.params;
    try {
        const fieldsToBeValidated = {
            id: {
                value: id,
                type: 'string'
            }
        }
        validateFields(fieldsToBeValidated);

        await UsersService.deleteById(id);
    } catch (err) {
        next(err);
    }
});

router.post('/register', async (req, res, next) => {
    const {
        username,
        name,
        email,
        password,
        roleId
    } = req.body;
    try {
        const fieldsToBeValidated = {
            username: {
                value: username,
                type: 'string'
            },
            name: {
                value: name,
                type: 'string'
            },
            email: {
                value: email,
                type: 'string'
            },
            password: {
                value: password,
                type: 'ascii'
            },
            roleId: {
                value: roleId,
                type: 'int'
            }
        };
        validateFields(fieldsToBeValidated);
        if(roleId === process.env.ADMIN_ROLE) {
            await UsersService.addAdmin(username, password);

        } else if(roleId === process.env.TECH_ROLE) {
            await UsersService.addTechnical(username, password);

        } else if(roleId === process.env.USER_ROLE) {
            let msg = await UsersService.addUser(username, password, name, email);
            if(msg === 'Email is already used !') {
                res.send('Email is already used !')
            } else if(msg === `The email is invalid!`) {
                res.send(`The email is invalid!`)
            }
        } else {
            throw new ServerError(`Nu exista rolul cu indicele ${roleId}`, 404);
    
        }

        res.status(201).end();
    } catch (err) {
        next(err);
    }
});

router.post('/login', async (req, res, next) => {
    const {
        username,
        password
    } = req.body;

    try {
        const fieldsToBeValidated = {
            username: {
                value: username,
                type: 'string'
            },
            password: {
                value: password,
                type: 'ascii'
            }
        };

        validateFields(fieldsToBeValidated);

        const tokenStructure = await UsersService.authenticate(username, password);
        if(tokenStructure === `Check your email for activation!`) {
            let msg = `Check your email for activation!`
            res.send(msg)
        }
        if(tokenStructure === `Admin has not approved your request!`) {
            let msg = `Admin has not approved your request!`
            res.send(msg)
        }
        if(tokenStructure === 'Combinatia de username si parola nu este buna!') {
            let msg = 'Combinatia de username si parola nu este buna!'
            res.send(msg)
        }

        res.status(200).json(tokenStructure);
    } catch (err) {
        next(err);
    }
});
router.put('/agree/:email', async (req, res, next) => {
    const {
        email
    } = req.params;
  
    try {
      const fieldsToBeValidated = {
          email: {
              value: email,
              type: 'string'
          }
      };
  
      validateFields(fieldsToBeValidated);
  
      await UsersService.agreeGDPR(email)
      res.status(200).end();
  } catch (err) {
      next(err);
  }

})
module.exports = router;