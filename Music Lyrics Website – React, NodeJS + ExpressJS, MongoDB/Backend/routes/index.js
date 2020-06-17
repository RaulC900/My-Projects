const Router = require('express')();

const ArtistsController = require('../Artists/controllers.js');
const SongsController = require('../Songs/controllers.js');
const TempSongsController = require('../TempSongs/controllers.js');
const TempArtistsController = require('../TempArtists/controllers.js');
const UsersController = require('../Users/controllers.js');
const QuestionsController = require('../Questions/controllers.js')
const CommentsController = require('../Comments/controllers.js')
const SamplesController = require('../Samples/controllers.js')

Router.use('/artists', ArtistsController);
Router.use('/songs', SongsController);
Router.use('/tempsongs', TempSongsController);
Router.use('/tempartists', TempArtistsController);
Router.use('/users', UsersController);
Router.use('/questions', QuestionsController);
Router.use('/comments', CommentsController);
Router.use('/samples', SamplesController);

module.exports = Router;