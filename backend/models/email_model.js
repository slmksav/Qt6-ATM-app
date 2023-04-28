const db = require('../database');
const amqplib = require('amqplib');

const email = {
    getEmail: function (idaccount, callback) {
      return db.query('select email from customer where idcustomer in (select id_customers from account where idaccount=?)', idaccount, (err, results) => {
        if (err) {
          callback(err, null);
        } else {
          // Publish a message to a RabbitMQ queue with the email details
          publishToQueue(results[0].email, callback);
        }
      });
    }
  }
  
async function publishToQueue(email, callback) {
    try {
      const connection = await amqplib.connect({
        protocol: 'amqps',
        hostname: process.env.RABBITMQ_HOST,
        username: process.env.RABBITMQ_USERNAME,
        password: process.env.RABBITMQ_PASSWORD
      });
  
      const channel = await connection.createChannel();
      const queue = 'email-handler-queue';
  
      await channel.assertQueue(queue, { durable: true });
      await channel.sendToQueue(queue, Buffer.from(email), { persistent: true });
  
      await channel.close();
      await connection.close();
  
      console.log(`Email "${email}" sent to RabbitMQ queue "${queue}"!`);
      callback(null, email);
    } catch (error) {
      console.error('Error sending email to RabbitMQ queue:', error);
      callback(error, null);
    }
  }

module.exports=email;