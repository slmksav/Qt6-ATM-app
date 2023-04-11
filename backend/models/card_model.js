const db = require('../database');

const card = {
  getAll: function(callback) {
    return db.query('select * from card', callback);
  },

  getById: function(id, callback) {
    return db.query('select * from card where idcard=?', [id], callback);
  },

  getCardIdByHexCode: function(cardhexcode) {
    return db.query('SELECT idcard FROM card WHERE cardhexcode = ?', [cardhexcode]);
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