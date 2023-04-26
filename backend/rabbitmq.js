const amqp = require('amqplib');

async function connect() {
  const connection = await amqp.connect(
    {
      protocol: 'amqps',
      hostname: process.env.RABBITMQ_HOST,
      username: process.env.RABBITMQ_USERNAME,
      password: process.env.RABBITMQ_PASSWORD
    }
  );
  process.once('SIGTERM', () => connection.close());
  return connection.createChannel();
}

module.exports = connect;