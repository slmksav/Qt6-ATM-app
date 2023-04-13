const db = require('../database');

const getAccountID = {

  getAccountIDByCardID: function(cardID, callback) {
    return db.query('SELECT id_account FROM card WHERE idcard = ?', [cardID], callback);
  },

};
module.exports = getAccountID; 