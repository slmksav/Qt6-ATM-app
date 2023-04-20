const db = require('../database');

const login={
    checkPassword:function(login_username, callback){
        return db.query('select fourdigitpin from card where cardhexcode=?',login_username,callback);
    },
    checkAttempts:function(login_username, callback) {
        return db.query('select wrongAttempts from card where cardhexcode=?',login_username,callback);
    },
    decreaseAttempts:function(login_username, callback) {
        db.query('update card set wrongAttempts = wrongAttempts - 1 where cardhexcode=?',login_username,callback);
    },
    resetAttempts:function(login_username, callback) {
        db.query('update card set wrongAttempts=3 where cardhexcode=?',login_username,callback);
    }
}

module.exports=login;