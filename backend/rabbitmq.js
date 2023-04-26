const amqplib = require('amqplib');

async function connectToRabbitMQ() {
  if (!process.env.RABBITMQ_HOST) {
  }

  // Connect to RabbitMQ server
  console.log('🔌  Yhdistetään RabbitMQ palvelimeen...');
  const connection = await amqplib.connect(
    {
      protocol: 'amqps',
      hostname: process.env.RABBITMQ_HOST,
      username: process.env.RABBITMQ_USERNAME,
      password: process.env.RABBITMQ_PASSWORD
    }
  );
  process.once('SIGTERM', () => connection.close());

  const channel = await connection.createChannel();
  const queue = 'card_wrongAttempts_queue';
  await channel.assertQueue(queue, { durable: false });

  console.log(`📭 lokitetaan jonoa ${queue}...`);
  channel.consume(
    queue,
    message => {
      console.log(`📬  viesti lisätty jonoon: "${queue}": "` + message.content.toString() + '"');
      console.log('✅  RabbitMQ yhdistetty REST API:in');
      process.exit(0);
    },
    { noAck: true }
  );

  // Sending message to queue
  const message = 'jos Renderissä näkyy tämä viesti niin message broker on yhdistettynä';
  console.log(`📮  lähetetään viestiä "${message}" jonolle "${queue}"`);
  await channel.sendToQueue(queue, Buffer.from(message));
}

module.exports = connectToRabbitMQ;
