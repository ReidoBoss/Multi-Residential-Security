const WebSocket = require('ws');

const ws = new WebSocket('ws://172.16.30.13/ws'); 

ws.on('open', function open() {
  console.log('Connected to WebSocket server');
  
  ws.send('Hello from WebSocket client!');
});

ws.on('message', function incoming(message) {
  const messageString = message.toString('utf8');
  
  console.log('Received message from server:', messageString);

});


ws.on('close', function close() {
  console.log('Disconnected from WebSocket server');
});
