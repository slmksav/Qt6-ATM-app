var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');
const dotenv=require('dotenv');
const jwt = require('jsonwebtoken');
const cors=require('cors');

var indexRouter = require('./routes/index');
var customerRouter = require('./routes/customer');
var accountRouter = require('./routes/account');
var additionalsRouter = require('./routes/additionals');
var loginRouter = require('./routes/login');
var cardRouter = require('./routes/card');
var hexcodeRouter = require('./routes/hexcode');
var getAccountIDRouter = require('./routes/getAccountID');
var transactionHistoryRouter = require('./routes/transactionHistory');


var app = express();
dotenv.config();
app.use(cors());

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

//suojaamattomat endpointit
app.use('/', indexRouter);
app.use('/login', loginRouter);

//app.use(authenticateToken); ei käytössä
//suojatut endpointit
app.use('/customer', customerRouter);
app.use('/account', accountRouter);
app.use('/additionals', additionalsRouter);
app.use('/card', cardRouter);
app.use('/hexcode', hexcodeRouter);
app.use('/getAccountID', getAccountIDRouter);
app.use('/transactionHistory', transactionHistoryRouter);

function authenticateToken(req, res, next) {
    const authHeader = req.headers['authorization']
    const token = authHeader && authHeader.split(' ')[1]
  
    console.log("token = "+token);
    if (token == null) return res.sendStatus(401)
  
    jwt.verify(token, process.env.MY_TOKEN, (err, user) => {
      console.log(err)
  
      if (err) return res.sendStatus(403)
  
      req.user = user
  
      next()
    })
  }



module.exports = app;
