const db = require('../database');

const email={
    getEmail:function(idaccount, callback){
        return db.query('select email from customer where idcustomer in (select id_customers from account where idaccount=?)',idaccount,callback);
    }
}

module.exports=email;