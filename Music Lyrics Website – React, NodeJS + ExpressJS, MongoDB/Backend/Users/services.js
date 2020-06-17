const jwt = require('jsonwebtoken');
const nodemailer = require('nodemailer');
const {
    Users,
    Admins,
    Technical
} = require('../data');

const {
    generateToken,
} = require('../security/Jwt');

const {
    ServerError
} = require('../errors');

const {
    hash,
    compare
} = require('../security/Password');

function ValidateEmail(email) {
    var re = /^(([^<>()\[\]\\.,;:\s@"]+(\.[^<>()\[\]\\.,;:\s@"]+)*)|(".+"))@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\])|(([a-zA-Z\-0-9]+\.)+[a-zA-Z]{2,}))$/;
    return re.test(String(email).toLowerCase());
}

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

const getAll = async () => {
    return await Users.find();
};

const getById = async (id) => {
    return await Users.findById(id);
};

const deleteById = async (id) => {
    return await Users.findByIdAndDelete(id);
};

const getByEmail = async (email) => {
    return await Users.findOne({email: email});
}

const addAdmin = async (username, password) => {
    const hashedPassword = await hash(password);
    const admin = new Admins({
        username,
        password: hashedPassword
    });
    await admin.save();
};

const approveById = async (id) => {
    const user = await Users.findByIdAndUpdate(id, {approved: true});
}

const addUser = async (username, password, name, email) => {
    const existingUser = await getByEmail(email);
    if(existingUser == null) {
        const hashedPassword = await hash(password);
        if(ValidateEmail(email) == false) {
            let msg = `The email is invalid!`
            return msg
        }
        const emailToken = jwt.sign(
        {
            username
        }, 
        process.env.JWT_SECRET_KEY, 
        {
            expiresIn: '1d',
        });

        const url = `http://localhost:3000/api/v1/users/confirmation/${emailToken}`;

        try {
            transporter.sendMail({
                to: email,
                subject: 'Confirm Email',
                html: `Please click this email to confirm your email: <a href="${url}">${url}</a>`,
            });
        } catch(err) {
            next(err);
        }

        const user = new Users({
            username,
            password: hashedPassword,
            name,
            email,
            token: emailToken
        });
        await user.save();
    } else {
        let msg = 'Email is already used !'
        return msg;
    }
};

const addTechnical = async (username, password) => {
    const hashedPassword = await hash(password);
    const technical = new Technical({
        username,
        password: hashedPassword
    });
    await technical.save();
};

const authenticate = async (username, password) => {

    const user = await Users.findOne({ username: username });
    const user_email = await Users.findOne({ email: username });
    const admin_user = await Admins.findOne({ username });
    const technical_user = await Technical.findOne({ username });

    if ((user === null) && (admin_user === null) && (technical_user === null) && (user_email === null)) {
        throw new ServerError(`Utilizatorul inregistrat cu ${username} nu exista!`, 404);
    }
    
    if(user !== null) {
        if(user.approved === false) {
            let msg = `Admin has not approved your request!`
            return msg
        } else {
            if(user.activated === false) {
                let msg = `Check your email for activation!`
                return msg
            }
            if (await compare(password, user.password)) {
                const tok = await generateToken({
                    userId: user._id,
                    userRole: process.env.USER_ROLE
                });
                var structure = {
                    token: tok,
                    userRole: process.env.USER_ROLE,
                    username: user.username,
                    email: user.email,
                    showGDPR: user.showGDPR
                };
                return structure;
            }
        }

    } else if(user_email !== null) {
        if(user_email.approved === false) {
            let msg = `Admin has not approved your request!`
            return msg
        } else {
            if(user_email.activated === false) {
                let msg = `Check your email for activation!`
                return msg
            }
            if (await compare(password, user_email.password)) {
                const tok = await generateToken({
                    userId: user_email._id,
                    userRole: process.env.USER_ROLE
                });
                var structure = {
                    token: tok,
                    userRole: process.env.USER_ROLE,
                    username: user_email.username,
                    email: user_email.email,
                    showGDPR: user_email.showGDPR
                };
                return structure;
            }
        }

    } else if(admin_user !== null) {
        if (await compare(password, admin_user.password)) {
            const tok = await generateToken({
                userId: admin_user._id,
                userRole: process.env.ADMIN_ROLE
            });
            var structure = {
                token: tok,
                userRole: process.env.ADMIN_ROLE
            };
            return structure;
        }

    } else if(technical_user !== null) {
        if (await compare(password, technical_user.password)) {
            const tok = await generateToken({
                userId: technical_user._id,
                userRole: process.env.TECH_ROLE
            });
            var structure = {
                token: tok,
                userRole: process.env.TECH_ROLE
            };
            return structure;
        }

    }
    let msg = 'Combinatia de username si parola nu este buna!'
    return msg
};

const activate = async (tok) => {
    const user = await Users.findOne({ token: tok });
    if (user === null) {
        throw new ServerError(`User with token ${tok} not found!`, 404);
    }
    user.activated = true;
    await user.save();
}

const agreeGDPR = async (email) => {
    const user = await Users.findOne({ email: email });
    if (user === null) {
        throw new ServerError(`User with email ${email} not found!`, 404);
    }
    user.showGDPR = false;
    await user.save();
}

module.exports = {
    addAdmin,
    addTechnical,
    addUser,
    authenticate,
    activate,
    getAll,
    getById,
    deleteById,
    agreeGDPR,
    approveById
}