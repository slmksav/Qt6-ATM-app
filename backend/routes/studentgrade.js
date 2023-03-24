const express = require('express');
const router = express.Router();
const grade = require('../models/grade_model');

//tänne metodeja
router.get('/:id',
    function (request, response) {
        grade.getByStudentId(request.params.id, function (err, dbResult) { //1. id, 2. callback-funktio
            if (err) {
                response.json(err);
            } else {
                response.json(dbResult[0]); //<-- tulee pelkkä objekti, ei taulukkoa
            }
        })
    });

module.exports = router;