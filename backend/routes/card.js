const express = require('express');
const router = express.Router();
const card = require('../models/card_model');

router.get('/', function(request, response) {
    card.getAll(function(err, dbResult) {
        if (err) {
            response.json(err);
        } else {
            response.json(dbResult);
        }
    })
});

router.get('/:id', function(request, response) {
    card.getById(request.params.id, function(err, dbResult) {
        if (err) {
            response.json(err);
        } else {
            response.json(dbResult[0]);
        }
    })
});

router.get('/:cardhexcode', (req, res) => {
    const cardhexcode = req.params.cardhexcode;
    pool.getConnection((err, connection) => {
      if (err) throw err;
      const query = 'SELECT idcard FROM card WHERE cardhexcode = ?';
      connection.query(query, [cardhexcode], (err, results) => {
        connection.release();
        if (err) throw err;
        if (results.length > 0) {
          res.json({ idcard: results[0].idcard });
        } else {
          res.status(404).json({ error: 'Card not found' });
        }
      });
    });
  });

router.post('/', function(request, response) {
    card.add(request.body, function(err, dbResult) {
        if (err) {
            response.json(err);
        } else {
            response.json(dbResult.affectedRows);
        }
    });
});

router.delete('/:id', function(request, response) {
    card.delete(request.params.id, function(err, dbResult) {
        if (err) {
            response.json(err);
        } else {
            response.json(dbResult.affectedRows);
        }
    });
});

router.put('/:id', function(request, response) {
    card.update(request.params.id, request.body, function(err, dbResult) {
        if (err) {
            response.json(err);
        } else {
            response.json(dbResult.affectedRows);
        }
    });
});

module.exports = router;
