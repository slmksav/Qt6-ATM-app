const db = require('../database');

const additionals = {
    getAll: function(callback) {
        return db.query('select * from account', callback);
      },
      
  getAdditionalAccountIDs: function(cardowner, callback) {
    return db.query(
        'SELECT idaccount FROM account WHERE idaccount IN (SELECT id_account FROM card WHERE id_cardowner=?) ORDER BY id_customers ASC', 
    [cardowner], callback);
  },
  
  getAdditionalAccountNames: function(cardowner, callback) {
    return db.query(
        'SELECT first_name, last_name FROM customer where idcustomer IN (SELECT idaccount FROM account WHERE idaccount IN (SELECT id_account FROM card WHERE id_cardowner=?))  ORDER BY idcustomer ASC', 
    [cardowner], callback);
  },

  getAdditionalAccountTypes: function(cardowner, callback) {
    return db.query(
        'SELECT accNumDebit, accNumCredit FROM account WHERE idaccount IN (SELECT id_account FROM card WHERE id_cardowner=?) ORDER BY id_customers DESC', 
    [cardowner], callback);
  },
};
module.exports = additionals;