const mongoose = require('mongoose');

(async () => {
  try {
    await mongoose.connect(`mongodb://${process.env.MUSER}:${process.env.MPASSWORD}@${process.env.MHOST}:${process.env.MPORT}/${process.env.MDATABASE}?authSource=admin`,
      {
        useNewUrlParser: true,
        useUnifiedTopology: true
      }
    );
  } catch (e) {
    console.trace(e);
  }
})();

const Artists = require('./models/Artists.js');
const Songs = require('./models/Songs.js');
const Users = require('./models/Users.js');
const Admins = require('./models/Admins.js')
const Technical = require('./models/Technical.js')
const TempSongs = require('./models/TempSongs.js');
const TempArtists = require('./models/TempArtists.js');
const Reports = require('./models/Reports.js');
const Questions = require('./models/Questions.js');
const Comments = require('./models/Comments.js');
const Samples = require('./models/Samples.js');

module.exports = {
  Artists,
  Songs,
  Users,
  Admins,
  Technical,
  TempSongs,
  TempArtists,
  Reports,
  Questions,
  Comments,
  Samples
}