const express = require('express');
const router = express.Router();
const bcrypt = require('bcryptjs');
const login = require('../models/login_model');
const jwt = require('jsonwebtoken');
const dotenv = require('dotenv');

router.post('/', 
  function(request, response) {
    if(request.body.username && request.body.password){
      const user = request.body.username;
      const pass = request.body.password;

      console.log("user: ", user);
      console.log("pass: ", pass);
      
        login.checkPassword(user, function(err, dbResult) {
          if(err || (dbResult.length == 0)){
            response.json(err);
          }
          else{
            console.log("dbResult: ", dbResult);
            console.log("dbResult[0].fourdigitpin: ", dbResult[0].fourdigitpin);
            console.log("pass: ", pass);

            //comparing plaintext, change to bcrypt.compare when hashing implemented
            if(pass == dbResult[0].fourdigitpin)
            {
                  const token = generateAccessToken({ username: user });
                  response.send(token);
            }
            else {
              console.log("wrong password");
              response.send(false);
            }
            // if (dbResult.length > 0) {
            //   bcrypt.compare('1','1', function(err,compareResult) {
            //     if (err){
            //       console.log("bcrypt.compare error");
            //     }
            //     console.log("compareResult: ", compareResult);
            //     if(compareResult) {
            //       console.log("success");
            //       const token = generateAccessToken({ username: user });
            //       response.send(token);
            //     }
            //     else {
            //         console.log("wrong password");
            //         response.send(false);
            //     }			
            //   }
            //   );
            // }
            // else{
            //   console.log("user does not exists");
            //   response.send(false);
            // }
          }
          }
        );
      }
    else{
      console.log("username or password missing");
      response.send(false);
    }
  }
);

function generateAccessToken(username) {
  dotenv.config();
  return jwt.sign(username, process.env.MY_TOKEN, { expiresIn: '1800s' });
}

module.exports=router;
