const express = require('express');
const router = express.Router();
const email = require('../models/email_model');
const jwt = require('jsonwebtoken');
const dotenv = require('dotenv');

const nodemailer = require('nodemailer');

router.post('/',
    function (request, response) {
        if (request.body.idaccount && request.body.log) {
            const idaccount = request.body.idaccount;
            const log = request.body.log;

            console.log("idaccount: ", idaccount);
            console.log("log: ", log);

            // const email = 'banksimul18@gmail.com';
            // const emailResponse = sendEmail(email, log);
            // response.send(emailResponse);

            email.getEmail(idaccount, function (err, dbResult) {
                if (err || (dbResult.length == 0)) {
                    response.json(err);
                }
                else {
                    console.log("dbResult: ", dbResult);
                    console.log("dbResult[0].email: ", dbResult[0].email);

                    const email = dbResult[0].email;
                    const emailResponse = sendEmail(email, log);
                    response.send(emailResponse);
                }
            });
        }
        else {
            console.log("idaccount or log missing");
            response.send(false);
        }
    }
);

function sendEmail(email, mailbody) {
    var transporter = nodemailer.createTransport({
        service: 'gmail',
        auth: {
            user: 'banksimul18@gmail.com',
            pass: 'jiuoirovzglxmmyj'
        }
    });

    var mailOptions = {
        from: 'banksimul18@gmail.com',
        to: email,
        subject: 'BankSimul transaction',
        text: mailbody
    };

    transporter.sendMail(mailOptions, function (error, info) {
        if (error) {
            console.log(error);
            return false;
        } else {
            console.log('Email sent: ' + info.response);
            return true;
        }
    });
}

module.exports = router;
