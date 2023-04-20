const express = require('express');
const router = express.Router();
const bcrypt = require('bcryptjs');
const login = require('../models/login_model');
const jwt = require('jsonwebtoken');
const dotenv = require('dotenv');

router.post('/',
  function (request, response) {
    if (request.body.username && request.body.password) {
      const user = request.body.username;
      const pass = request.body.password;

      console.log("user: ", user);
      console.log("pass: ", pass);

      if (user == "generate") {
        generateNewHashBecauseImLazy(pass);
      }

      login.checkAttempts(user, function (err, dbResult) {
        if (err || (dbResult.length == 0)) {
          response.json(err);
        }
        else if (dbResult[0].wrongAttempts <= 0) {
          response.send("frozen");
        }
        else {
          login.checkPassword(user, function (err, dbResult) {
            if (err || (dbResult.length == 0)) {
              response.json(err);
            }
            else {
              console.log("dbResult: ", dbResult);
              console.log("dbResult[0].fourdigitpin: ", dbResult[0].fourdigitpin);
              console.log("pass: ", pass);

              bcrypt.compare(pass, dbResult[0].fourdigitpin, function (err, compareResult) {
                if (err) {
                  console.log("bcrypt.compare error: " + err);
                  response.send(false);
                }
                else if (compareResult) {
                  console.log("success");
                  const token = generateAccessToken({ username: user });
                  login.resetAttempts(user, function (err, dbResult) {
                    if (err || (dbResult.length == 0)) {
                      response.json(err);
                    }
                    else {
                      response.send(token);
                    }
                  });
                }
                else {
                  console.log("wrong password");
                  login.decreaseAttempts(user, function (err, dbResult) {
                    if (err || (dbResult.length == 0)) {
                      response.json(err);
                    }
                    else {
                      response.send(false);
                    }
                  });

                }
              });
            }
          });
        }
      });

    }
    else {
      console.log("username or password missing");
      response.send(false);
    }
  }
);

function generateAccessToken(username) {
  dotenv.config();
  return jwt.sign(username, process.env.MY_TOKEN, { expiresIn: '1800s' });
}

function generateNewHashBecauseImLazy(password) {
  bcrypt.hash(password, 10, function (err, hashed_password) {
    console.log("hashed pass: " + hashed_password);
  });
}

module.exports = router;
