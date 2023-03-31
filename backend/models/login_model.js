const db = require('../database');

const login={
    checkPassword:function(login_username, callback){
        return db.query('select fourdigitpin from card where idcard=?',login_username,callback);
    }
}

module.exports=login;