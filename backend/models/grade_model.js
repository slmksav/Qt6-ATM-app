const db = require('../database');

const grade = {
  getAll: function(callback) {
    return db.query('select idgrade, DATE_FORMAT(date,"%d.%m.%Y") as date from grade', callback); //huom ei date_grade
  },

  getById: function(id, callback) {
    return db.query('select * from grade where idgrade=?', [id], callback);
  },

  getByStudentId: function(id, callback) {
    return db.query('select name, grade from course inner join grade on course.idcourse=grade.idcourse where idstudent=?', [id], callback);
    },

  add: function(grade, callback) {
    return db.query(
      'insert into grade (date, idstudent, idcourse, grade) values(?,?,?,?)',
      [grade.date, grade.idstudent, grade.idcourse, grade.grade],
      callback
    );
  },

  delete: function(id, callback) {
    return db.query('delete from grade where idgrade=?', [id], callback);
  },

  update: function(id, grade, callback) {
    return db.query(
      'update grade set date=?, idstudent=?, idcourse=?, grade=? where idgrade=?',
      [grade.date, grade.idstudent, grade.idcourse, grade.grade, id],
      callback
    );
  }
};
module.exports = grade;