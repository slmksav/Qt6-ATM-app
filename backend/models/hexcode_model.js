const db = require('../database');

const hexcode = {

  getCardIdByHexCode: function(cardhexcode, callback) {
    return db.query('SELECT idcard FROM card WHERE cardhexcode =?', [cardhexcode], callback);
  },

};
module.exports = hexcode;