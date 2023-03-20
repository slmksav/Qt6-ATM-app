const express = require('express');
const router = express.Router();
const grade = require('../models/grade_model');

//tänne metodeja
router.get('/', function(request, response) {
    grade.getAll(function(err, dbResult) {
        if (err) {
            response.json(err);
        } else {
            response.json(dbResult);
        }
    })
});

router.get('/:id',
    function (request, response) {
        grade.getById(request.params.id, function (err, dbResult) {
            if (err) {
                response.json(err);
            } else {
                response.json(dbResult[0]); //<-- tulee pelkkä objekti, ei taulukkoa
            }
        })
    });


router.post('/', 
function(request, response) {
  grade.add(request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      //response.json(dbResult);
      response.json(dbResult.affectedRows);
    }
  });
});


router.delete('/:id', 
function(request, response) {
  grade.delete(request.params.id, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult.affectedRows + " affected rows!")
    }
  });
});


router.put('/:id', 
function(request, response) {
  grade.update(request.params.id, request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult);
    }
  });
});

module.exports = router;