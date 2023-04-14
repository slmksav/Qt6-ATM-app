const express = require('express');
const router = express.Router();
const transactionHistory = require('../models/transactionHistory_model');

router.get('/',function(request,response){
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
    transactionHistory.getTransactionIDs(request.params.idaccount, function (err, dbResult) {
        if (err) {
            response.json(err);
        } else {
            response.json(dbResult);
        }
    })
});

router.get('/dates/:idaccount', function (request, response) {
    transactionHistory.getTransactionDates(request.params.idaccount, function (err, dbResult) {
        if (err) {
            response.json(err);
        } else {
            response.json(dbResult);
        }
    })
});

router.get('/amounts/:idaccount', function (request, response) {
    transactionHistory.getTransactionAmounts(request.params.idaccount, function (err, dbResult) {
        if (err) {
            response.json(err);
        } else {
            response.json(dbResult);
        }
    })
});

module.exports=router;