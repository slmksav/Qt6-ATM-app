const db = require('../database');

const card = {
  getAll: function(callback) {
    return db.query('select * from card', callback);
  },

  getById: function(id, callback) {
    return db.query('select * from card where idcard=?', [id], callback);
  },

  getCardIdByHexCode: function(cardhexcode) {
    return new Promise((resolve, reject) => {
      const query = 'SELECT idcard FROM card WHERE cardhexcode = ?';
      db.query(query, [cardhexcode], (err, results) => {
        if (err) reject(err);
        if (results.length > 0) {
          resolve(results[0].idcard);
        } else {
          reject(new Error('Card not found'));
        }
      });
    });
  },

  delete: function(id, callback) {
    return db.query('delete from card where idcard=?', [id], callback);
  },

  update: function(id, card, callback) {
    return db.query(
      'update card set wrongAttempts=? where idcard=?',
      [card.wrongAttempts, id],
      callback
    );
  }
};
module.exports = card;