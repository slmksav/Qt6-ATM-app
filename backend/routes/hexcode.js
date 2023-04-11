const express = require('express');
const router = express.Router();
const hexcode = require('../models/hexcode_model');

router.get('/hex/:cardhexcode', (request, response) => {
    hexcode.getCardIdByHexCode(request.params.cardhexcode, function(err, dbResult) {
        if (err) {
            response.json(err);
        } else {
            response.json(dbResult[0]);
        }
    })
});

module.exports = router;
