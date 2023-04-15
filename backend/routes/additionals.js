const express = require('express');
const router = express.Router();
const additionals = require('../models/additionals_model');
const jwt = require('jsonwebtoken');
const dotenv = require('dotenv');

router.get('/',function(request,response){
    jwt.verify(request.header('token'), process.env.MY_TOKEN);
    additionals.getAll(function(err,dbResult){
        if(err){
            response.json(err);
        }
        else{
            response.json(dbResult);
        }
    })
});

router.get('/ids/:cardowner', function (request, response) {
    console.log("request.params.cardowner: ", request.params.cardowner);
    console.log("request.token: ", request.header('token'));

    jwt.verify(request.header('token'), process.env.MY_TOKEN);
    
    additionals.getAdditionalAccountIDs(request.params.cardowner, function (err, dbResult) {
        if (err) {
            response.json(err);
        } else {
            response.json(dbResult);
        }
    })
});

router.get('/names/:cardowner', function (request, response) {
    jwt.verify(request.header('token'), process.env.MY_TOKEN);
    additionals.getAdditionalAccountNames(request.params.cardowner, function (err, dbResult) {
        if (err) {
            response.json(err);
        } else {
            response.json(dbResult);
        }
    })
});

router.get('/types/:cardowner', function (request, response) {
    jwt.verify(request.header('token'), process.env.MY_TOKEN);
    additionals.getAdditionalAccountTypes(request.params.cardowner, function (err, dbResult) {
        if (err) {
            response.json(err);
        } else {
            response.json(dbResult);
        }
    })
});

module.exports=router;