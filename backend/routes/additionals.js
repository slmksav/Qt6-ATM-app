const express = require('express');
const router = express.Router();
const additionals = require('../models/additionals_model');
const jwt = require('jsonwebtoken');
const dotenv = require('dotenv');

router.get('/',function(request,response){
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
    
    additionals.getAdditionalAccountIDs(request.params.cardowner, function (err, dbResult) {
        if (err) {
            response.json(err);
        } else {
            response.json(dbResult);
        }
    })
});

router.get('/names/:cardowner', function (request, response) {
    additionals.getAdditionalAccountNames(request.params.cardowner, function (err, dbResult) {
        if (err) {
            response.json(err);
        } else {
            response.json(dbResult);
        }
    })
});

router.get('/types/:cardowner', function (request, response) {
    additionals.getAdditionalAccountTypes(request.params.cardowner, function (err, dbResult) {
        if (err) {
            response.json(err);
        } else {
            response.json(dbResult);
        }
    })
});

module.exports=router;