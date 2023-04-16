const db = require('../database');

const transactionHistory = {
    getAll: function(callback) {
        return db.query('select * from transactions', callback);
      },
      
  getTransactionIDs: function(idaccount, callback) {
    return db.query(
        'SELECT idtransactions FROM transactions WHERE id_accountRef = ? ORDER BY date_transactions, idtransactions ASC', 
    [idaccount], callback);
  },
  
  getTransactionDates: function(idaccount, callback) {
    return db.query(
        'SELECT date_transactions FROM transactions WHERE id_accountRef = ? ORDER BY date_transactions, idtransactions ASC', 
    [idaccount], callback);
  },

  getTransactionAmounts: function(idaccount, callback) {
    return db.query(
        "SELECT amount FROM transactions WHERE id_accountRef = ? ORDER BY date_transactions, idtransactions ASC", 
    [idaccount], callback);
  },

  insert: function(id, amount, type, callback) {
    console.log("transaction put function");
    if(type == 'debit') {
      return db.query("INSERT INTO transactions (date_transactions, amount, transactionscol, id_accountRef) VALUES (CURRENT_TIMESTAMP, ?, 'debit', ?)",
      [amount, id],
      callback
    );
    } else if(type == 'credit') { 
      return db.query("INSERT INTO transactions (date_transactions, amount, transactionscol, id_accountRef) VALUES (CURRENT_TIMESTAMP, ?, 'credit', ?)",
      [amount, id],
      callback
    );
    }
  }
};
module.exports = transactionHistory;