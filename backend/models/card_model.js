const db = require('../database');

const card = {
  getAll: function(callback) {
    return db.query('select * from card', callback);
  },
  getById: function(id, callback) {
    return db.query('select * from card where idcard=?', [id], callback);
  },
  getById: function(id, callback) {
    return db.query('select * from card where idcard=?', [id], callback);
  },
  delete: function(id, callback) {
    return db.query('delete from card where idcard=?', [id], callback);
  },
  update: function(id, card, callback) {
    return db.query(
      'update card set wrongAttempts=? where idcard=?',
      [card.first_name, card.last_name, id],
      callback
    );
  }
};
module.exports = card;