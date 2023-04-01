const db = require('../database');

const account = {
  getAll: function(callback) {
    return db.query('select * from account', callback);
  },
  getById: function(id, callback) {
    return db.query('select * from account where idaccount=?', [id], callback);
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
  update: function(id, account, callback) {
    return db.query(
      'update account set first_name=?,last_name=? where idaccount=?',
      [account.first_name, account.last_name, id],
      callback
    );
  }
};
module.exports = account;