const db = require('../database');

const card = {
  getAll: function(callback) {
    return db.query('select * from card', callback);
  },

  getById: function(id, callback) {
    return db.query('select * from card where idcard=?', [id], callback);
  },

  getCardIdByHexCode: function(cardhexcode, callback) {
    return db.query('SELECT idcard FROM card WHERE cardhexcode =?', [cardhexcode], callback);
  },

  delete: function(id, callback) {
    return db.query('delete from card where idcard=?', [id], callback);
  },

  update: function(id, card, callback) {
    const query = 'update card set wrongAttempts=? where idcard=?';
    db.query(query, [card.wrongAttempts, id], (error, result) => {
      if (error) throw error;
      callback(null, result);
    });
  }
};

module.exports = card;
