const express = require('express');
const router = express.Router();
const getAccountID = require('../models/getAccountID_model');

router.get('/withcardID/:cardID', (request, response) => {
    getAccountID.getAccountIDByCardID(request.params.cardID, function(err, dbResult) {
        if (err) {
            response.json(err);
        } else {
            response.json(dbResult[0]);
        }
    })
});

module.exports = router;
