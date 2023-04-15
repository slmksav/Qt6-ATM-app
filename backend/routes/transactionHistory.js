const express = require('express');
const router = express.Router();
const transactionHistory = require('../models/transactionHistory_model');
const jwt = require('jsonwebtoken');
const dotenv = require('dotenv');

router.get('/',function(request,response){
    jwt.verify(request.header('token'), process.env.MY_TOKEN);
    transactionHistory.getAll(function(err,dbResult){
        if(err){
            response.json(err);
        }
        else{
            response.json(dbResult);
        }
    })
});

router.get('/ids/:idaccount', function (request, response) {
    jwt.verify(request.header('token'), process.env.MY_TOKEN);
    transactionHistory.getTransactionIDs(request.params.idaccount, function (err, dbResult) {
        if (err) {
            response.json(err);
        } else {
            response.json(dbResult);
        }
    })
});

router.get('/dates/:idaccount', function (request, response) {
    jwt.verify(request.header('token'), process.env.MY_TOKEN);
    transactionHistory.getTransactionDates(request.params.idaccount, function (err, dbResult) {
        if (err) {
            response.json(err);
        } else {
            response.json(dbResult);
        }
    })
});

router.get('/amounts/:idaccount', function (request, response) {
    jwt.verify(request.header('token'), process.env.MY_TOKEN);
    transactionHistory.getTransactionAmounts(request.params.idaccount, function (err, dbResult) {
        if (err) {
            response.json(err);
        } else {
            response.json(dbResult);
        }
    })
});

module.exports=router;