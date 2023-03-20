var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');

var indexRouter = require('./routes/index');
var courseRouter = require('./routes/course');
var studentRouter = require('./routes/student');
var gradeRouter = require('./routes/grade');
var studentgradeRouter = require('./routes/studentgrade');

var app = express();

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false })); //<-- ottaa vastaan urlencoded
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

app.use('/', indexRouter);
app.use('/course', courseRouter);
app.use('/student', studentRouter);
app.use('/grade', gradeRouter);
app.use('/studentgrade', studentgradeRouter);


module.exports = app;
