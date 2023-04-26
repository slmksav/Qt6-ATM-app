var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');
const dotenv = require('dotenv');
const jwt = require('jsonwebtoken');
const cors = require('cors');
const nodemailer = require('nodemailer');


var indexRouter = require('./routes/index');
var customerRouter = require('./routes/customer');
var accountRouter = require('./routes/account');
var additionalsRouter = require('./routes/additionals');
var loginRouter = require('./routes/login');
var cardRouter = require('./routes/card');
var hexcodeRouter = require('./routes/hexcode');
var getAccountIDRouter = require('./routes/getAccountID');
var transactionHistoryRouter = require('./routes/transactionHistory');
var email = require('./routes/email');
  
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

app.use(authenticateToken);
//suojatut endpointit
app.use('/card', cardRouter); //move this back under auth when pincode issues resolved
app.use('/hexcode', hexcodeRouter); //move this back under auth when pincode issues resolved
app.use('/customer', customerRouter);
app.use('/account', accountRouter);
app.use('/additionals', additionalsRouter);
app.use('/getAccountID', getAccountIDRouter);
app.use('/transactionHistory', transactionHistoryRouter);
app.use('/email', email);

function authenticateToken(req, res, next) {
  const authHeader = req.headers['authorization']
  const token = authHeader && authHeader.split('.')[1]

  //console.log("token = " + token);
  if (token == null) return res.sendStatus(401)

  jwt.verify(authHeader, process.env.MY_TOKEN, (err, user) => {

    if (err) {
      console.log(err);
      return res.sendStatus(403);
    }

    req.user = user

    next()
  })
}



module.exports = app;
