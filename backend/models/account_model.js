const db = require('../database');

const account = {
  getAll: function(callback) {
    return db.query('select * from account', callback);
  },
  getById: function(id, callback) {
    return db.query('select * from account where idaccount=?', [id], callback);
  },
  add: function(account, callback) {
    return db.query(
      'insert into account (first_name,last_name) values(?,?)',
      [account.first_name, account.last_name],
      callback
    );
  },
  delete: function(id, callback) {
    return db.query('delete from account where idaccount=?', [id], callback);
  },
  update: function(id, amount, type, callback) {
    console.log("account update function");
    if(type == 'debit') {
      return db.query('update account set debitSaldo = debitSaldo - ? where idaccount=? and debitSaldo >= ?',
      [amount, id, amount],
      callback
    );
    } else if(type == 'credit') { 
      return db.query('update account set creditSaldo = creditSaldo + ? where idaccount=? and creditMax - creditSaldo >= ?;',
      [amount, id, amount],
      callback
    );
    }
  }
};
module.exports = account;