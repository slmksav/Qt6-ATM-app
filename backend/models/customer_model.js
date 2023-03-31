const db = require('../database');

const customer = {
  getAll: function(callback) {
    return db.query('select * from customer', callback);
  },
  getById: function(id, callback) {
    return db.query('select * from customer where idcustomer=?', [id], callback);
  },
  add: function(customer, callback) {
    return db.query(
      'insert into customer (first_name,last_name) values(?,?)',
      [customer.first_name, customer.last_name],
      callback
    );
  },
  delete: function(id, callback) {
    return db.query('delete from customer where idcustomer=?', [id], callback);
  },
  update: function(id, customer, callback) {
    return db.query(
      'update customer set first_name=?,last_name=? where idcustomer=?',
      [customer.first_name, customer.last_name, id],
      callback
    );
  }
};
module.exports = customer;