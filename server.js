const express = require('express');
const bodyParser = require('body-parser');
const cors = require('cors');
require('dotenv').config();

const app = express();

var corsOptions = {
  origin: '*',
  optionsSuccessStatus: 200,
};

app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: true }));
app.use(cors(corsOptions));

app.use(express.static('./build'));
app.use(express.static('./'));

var pid = 400;
var gid = 600;

app.get('/pid', async (req, res, next) => {
  pid++;
  return res.json({ pid });
});

app.get('/gid', async (req, res, next) => {
  console.log(req.query);
  return res.json({ gid });
});

app.get('*', (req, res, next) => {
  res.sendFile(__dirname + '/build/index.html');
});

app.listen(3000, () => console.log('Express listening on port 3000'));

var port = 3001;
var queue = [];

const WebSocketServer = require('ws').Server;
// const HttpsServer = require('https').createServer;
// const fs = require('fs');

// const server = HttpsServer({
//   cert: fs.readFileSync(process.env.CERT_PATH || 'cert/cert.pem'),
//   key: fs.readFileSync(process.env.KEY_PATH || 'cert/key.pem'),
// });

// const wss = new WebSocketServer({ server });
const wss = new WebSocketServer({ port });
// server.listen(port);

console.log('Websocket listening on port: ' + port);

wss.on('connection', function connection(ws) {
  console.log('New client connected');

  ws.on('message', (message) => {
    var object = JSON.parse(message);

    if (object.start && object.pid) {
      ws.pid = object.pid;
      queue.push(ws);
    }

    if (queue.length >= 2) {
      if (queue[queue.length - 1].pid !== queue[queue.length - 2].pid) {
        queue[queue.length - 2].send(
          JSON.stringify({ start: true, player: true })
        );
        queue[queue.length - 1].send(
          JSON.stringify({ start: true, player: false })
        );

        queue = [];
      }
    }
  });
});
