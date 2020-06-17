const express = require('express');
const morgan = require('morgan'); //middleware de logare
const helmet = require('helmet'); //middleware de securitate
const cors = require('cors')
const routes = require('./routes');

const app = express();

app.use(helmet());
app.use(morgan(':remote-addr - :remote-user [:date[web]] ":method :url HTTP/:http-version" :status :res[content-length]'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));

app.use(cors());
app.use(function (err, req, res, next) {
    res.header('Access-Control-Allow-Origin', 'http://localhost:3001/');
    res.header('Access-Control-Allow-Credentials', 'true');
})


app.use('/api/v1', routes);

// handler de erori declarat ca middleware
app.use((err, req, res, next) => {
    console.trace(err);
    let status = 500;
    let message = 'Something Bad Happened';
    if (err.httpStatus) {
        status = err.httpStatus;
        message = err.message;
    }
    res.status(status).json({
        error: message,
    });
});


app.listen(process.env.PORT, () => {
    console.log(`App is listening on ${process.env.PORT}`);
});
