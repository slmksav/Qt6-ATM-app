const db = require('../database');

const transactionHistory = {
    getAll: function(callback) {
        return db.query('select * from transactions', callback);
      },
      
  getTransactionIDs: function(idaccount, callback) {
    return db.query(
        'SELECT idtransactions FROM transactions WHERE id_accountRef = ? ORDER BY date_transactions DESC', 
    [idaccount], callback);
  },
  
  getTransactionDates: function(idaccount, callback) {
    return db.query(
        'SELECT date_transactions FROM transactions WHERE id_accountRef = ? ORDER BY date_transactions DESC', 
    [idaccount], callback);
  },

  getTransactionAmounts: function(idaccount, callback) {
    return db.query(
        'SELECT amount FROM transactions WHERE id_accountRef = ? ORDER BY date_transactions DESC;', 
    [idaccount], callback);
  }
};
module.exports = transactionHistory;