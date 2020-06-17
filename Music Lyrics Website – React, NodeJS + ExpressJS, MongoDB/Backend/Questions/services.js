const {
    Questions,
    Users
} = require('../data');

const nodemailer = require('nodemailer');

const transporter = nodemailer.createTransport({
    host: 'smtp.gmail.com',
    port: 587,
    secure: false,
    requireTLS: true,
    auth: {
      user: process.env.GMAIL_USERNAME,
      pass: process.env.GMAIL_PASSWORD,
    },
});

const checkEmail = async (email) => {
    return await Users.findOne({email: email});
};

const add = async (authorEmail, subject, report) => {
    const question = new Questions({
        authorEmail: authorEmail,
        subject: subject,
        report: report
    });
    const userExists = await checkEmail(authorEmail);
    if(userExists != null) {
        await question.save();
        let message = "Username registered!"
        return message;
    } else {
        let message = "Username not registered!"
        return message;
    }
};

const getAll = async () => {
    return await Questions.find();
};

const updateById = async (answer, id) => {
    const question = await Questions.findByIdAndUpdate(id, { answer: answer });
    try {
        transporter.sendMail({
            to: `${question.authorEmail}`,
            subject: `Answer to your question: ${question.report}`,
            html: `The answer to your question is: <p>${answer}</p>`,
        });
    } catch(err) {
        next(err);
    }

};

const starrQuestion = async (id) => {
    await Questions.findByIdAndUpdate(id, { starred: true });
};

const unstarrQuestion = async (id) => {
    await Questions.findByIdAndUpdate(id, { starred: false });
};

const deleteById = async (id) => {
    await Questions.findByIdAndDelete(id);
};

module.exports = {
    add,
    getAll,
    updateById,
    starrQuestion,
    unstarrQuestion,
    deleteById
}