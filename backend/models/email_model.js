const db = require('../database');
const amqplib = require('amqplib');

const email = {
  getEmail: async function (idaccount, callback) {
    try {
      const results = await db.query('select email from customer where idcustomer in (select id_customers from account where idaccount=?)', idaccount);

      // Publish a message to a RabbitMQ queue with the email details
      const email = results[0].email;
      const publishedEmail = await publishToQueue(email);
      callback(null, results);
    } catch (error) {
      callback(error, null);
    }
  }
};
  
  async function publishToQueue(email) {
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
      return email;
    } catch (error) {
      console.error('Error sending email to RabbitMQ queue:', error);
      throw error;
    }
  }
  

module.exports=email;