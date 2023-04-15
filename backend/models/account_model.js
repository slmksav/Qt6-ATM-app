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
      return db.query('update account set debitSaldo = debitSaldo - ? where idaccount=?',
      [amount, id],
      callback
    );
    } else if(type == 'credit') { 
      return db.query('update account set creditSaldo = creditSaldo - ? where idaccount=?',
      [amount, id],
      callback
    );
    }
  }
};
module.exports = account;