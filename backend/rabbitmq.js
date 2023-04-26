const amqplib = require('amqplib');

(async () => {
  if (!process.env.RABBITMQ_HOST) {
    throw Error('error: RABBITMQ_HOST not found');
  }

  const message = 'Connected to RabbitMQ on: ' + Date();
  const queue = 'connection-amqp';

  const connection = await amqplib.connect(
    {
      protocol: 'amqps',
      hostname: process.env.RABBITMQ_HOST,
      username: process.env.RABBITMQ_USERNAME,
      password: process.env.RABBITMQ_PASSWORD
    }
  );
  console.log('Connected!');
  process.once('SIGTERM', () => connection.close());

  const channel = await connection.createChannel();
  await channel.assertQueue(queue, { durable: false });
  await channel.sendToQueue(queue, Buffer.from(message), {});
  console.log(`Sent message "${message}" to ${queue}`);

  await channel.close();
  await connection.close();

})().catch(error => {
  console.error('');
  console.error('error: Failed to connect to RabbitMQ');
  console.error(error);
  process.exit(1);
});