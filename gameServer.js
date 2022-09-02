const WebSocketServer = require('ws');

const port = 3002;
const wss = new WebSocketServer.Server({ port });

var players = [];

setInterval(() => {
  for (var i = 0; i < players.length; i++) {
    if (i == 0 && players.length === 2) {
      sendStats(players[0], players[1]);
    } else if (i == 1) {
      sendStats(players[1], players[0]);
    }
  }

  // console.log(players);
}, 33);

function changeEndianness(val) {
  return (
    (val << 24) |
    ((val << 8) & 0x00ff0000) |
    ((val >> 8) & 0x0000ff00) |
    ((val >> 24) & 0x000000ff)
  );
}

wss.on('connection', (ws, req) => {
  console.log(
    'New client connected to Game ws server: ',
    req.socket.remoteAddress
  );

  // players.push(ws);

  ws.onmessage = (event) => {
    let data = event.data;
    let comp = new Uint8Array(data);
    // console.log(`Client has sent us: ${comp}`);

    let buf = Buffer.from(comp.buffer, 0, 4);
    let out = Buffer.from(buf, 'hex');

    //HELO
    if (out.toString() === 'OLEH') {
      var player = {};

      buf = Buffer.from(comp.buffer, 4, 4);
      let len = changeEndianness(buf.readUInt32BE());

      buf = Buffer.from(comp.buffer, 8, len);
      out = Buffer.from(buf, 'hex');
      player.id = Number(out.toString());

      buf = Buffer.from(comp.buffer, 8 + len, 4);
      let len2 = changeEndianness(buf.readUInt32BE());

      buf = Buffer.from(comp.buffer, 12 + len, len2);
      out = Buffer.from(buf, 'hex');

      player.name = out.toString();

      const arr = players.filter((pl) => pl.id === player.id);

      if (arr.length === 0) {
        player.ws = ws;
        players.push(player);
      }

      //send thee welcomed package to the player
      sendWelcome(player);
    }

    //STATE
    else if (out.toString() === 'TDPU') {
      buf = Buffer.from(comp.buffer, 4, 4);
      let len = changeEndianness(buf.readUInt32BE());

      buf = Buffer.from(comp.buffer, 8, len);
      out = Buffer.from(buf, 'hex');
      var pID = Number(out.toString());

      var arr = players.filter((pl) => pl.id === pID);

      if (arr.length > 0) {
        buf = Buffer.from(comp.buffer, 8 + len, 4);
        let len2 = changeEndianness(buf.readUInt32BE());
        buf = Buffer.from(comp.buffer, 12 + len, len2);
        out = Buffer.from(buf, 'hex');

        // //out will be the type of stat : 1 for xPos
        let type = Number(out.toString('utf-8'));
        // console.log(type);

        switch (type) {
          case 1:
            buf = Buffer.from(comp.buffer, 12 + len + len2, 4);
            out = Buffer.from(buf, 'hex');
            let len3 = changeEndianness(out.readUInt32BE());

            buf = Buffer.from(comp.buffer, 16 + len + len2, len3);

            out = Buffer.from(buf, 'hex');

            let xPos = Number(out.toString('utf-8'));
            players.forEach((pl, i) => {
              if (pl.id === pID) {
                // console.log(xPos);
                players[i].xPos = xPos;
                players[i].pID = pID;
              }
            });
            break; //xPos
          default:
            break;
        }
      }
    }
  };

  ws.on('close', () => {
    console.log('the client has disconnected');
    players = []; //find player from list and remove that player
  });

  ws.onerror = function () {
    console.log('Some Error occurred');
  };
});

function sendWelcome(player) {
  var WLCM = new Uint32Array([1464615757, player.id]);
  player.ws.send(WLCM);
}

function sendStats(player, enemy) {
  var STAT = new Int32Array([1398030676, 0, enemy.xPos]);
  player.ws.send(STAT);
}

console.log('Game ws server running on port ' + port);
