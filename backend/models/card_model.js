const db = require('../database');
const connectToRabbitMQ = require('./rabbitmq');

const card = {
  getAll: function(callback) {
    return db.query('select * from card', callback);
  },

  getById: function(id, callback) {
    return db.query('select * from card where idcard=?', [id], callback);
  },

  getCardIdByHexCode: function(cardhexcode, callback) {
    return db.query('SELECT idcard FROM card WHERE cardhexcode =?', [cardhexcode], callback);
  },

  delete: function(id, callback) {
    return db.query('delete from card where idcard=?', [id], callback);
  },

  update: function(id, card, callback) {
    const query = 'update card set wrongAttempts=? where idcard=?';
    db.query(query, [card.wrongAttempts, id], async (error, result) => {
      if (error) throw error;
      // lähettää viestin RabbitMQ:n jonoon kun kortin väärät yritykset päivitetään
      const channel = await connectToRabbitMQ();
      const queueName = 'card_wrongAttempts_queue';
      await channel.assertQueue(queueName, { durable: false });
      const message = `Card ${id} was updated`;
      channel.sendToQueue(queueName, Buffer.from(message));
      callback(null, result);
    });
  }
};

module.exports = card;
