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
}, 60);

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
    var totalBytes = comp.length;
    var bytesRead = 0;

    let buf = Buffer.from(comp.buffer, 0, 4);
    let out = Buffer.from(buf, 'hex');

    bytesRead += 4;

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
      player.bullets = [];

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
      buf = Buffer.from(comp.buffer, bytesRead, 4);
      let len = changeEndianness(buf.readUInt32BE());
      bytesRead += 4;

      buf = Buffer.from(comp.buffer, bytesRead, len);
      out = Buffer.from(buf, 'hex');
      bytesRead += len;

      var time = Number(out.toString());
      // console.log(time);

      buf = Buffer.from(comp.buffer, bytesRead, 4);
      len = changeEndianness(buf.readUInt32BE());
      bytesRead += 4;

      buf = Buffer.from(comp.buffer, bytesRead, len);
      out = Buffer.from(buf, 'hex');
      bytesRead += len;

      var pID = Number(out.toString());
      var arr = players.filter((pl) => pl.id === pID);

      players.forEach((pl, i) => {
        if (pl.id === pID) {
          players[i].pID = pID;
        }
      });

      if (arr.length > 0) {
        while (bytesRead < totalBytes) {
          // console.log(bytesRead, '   ', totalBytes);
          buf = Buffer.from(comp.buffer, bytesRead, 4);
          let len2 = changeEndianness(buf.readUInt32BE());
          bytesRead += 4;

          buf = Buffer.from(comp.buffer, bytesRead, len2);
          out = Buffer.from(buf, 'hex');
          bytesRead += len2;

          // //out will be the type of stat : 1 for xPos
          let type = Number(out.toString('utf-8'));
          // console.log(type);

          switch (type) {
            case 1: {
              buf = Buffer.from(comp.buffer, bytesRead, 4);
              out = Buffer.from(buf, 'hex');
              bytesRead += 4;

              let len3 = changeEndianness(out.readUInt32BE());
              buf = Buffer.from(comp.buffer, bytesRead, len3);
              out = Buffer.from(buf, 'hex');
              bytesRead += len3;

              let xPos = Number(out.toString('utf-8'));
              players.forEach((pl, i) => {
                if (pl.id === pID) {
                  players[i].xPos = xPos;
                }
              });

              break; //xPos
            }

            case 2: {
              buf = Buffer.from(comp.buffer, bytesRead, 4);
              out = Buffer.from(buf, 'hex');
              bytesRead += 4;

              let len3 = changeEndianness(out.readUInt32BE());
              buf = Buffer.from(comp.buffer, bytesRead, len3);
              out = Buffer.from(buf, 'hex');
              bytesRead += len3;

              let rotation = Number(out.toString('utf-8'));

              players.forEach((pl, i) => {
                if (pl.id === pID) {
                  players[i].rotation = rotation;
                }
              });

              break; //Rotation
            }

            case 3: {
              //number of bullets
              //for each bullet
              //start time
              //shoot time
              //decide to keep
              //pos.x
              //pos.y
              //rot
              //push to player's bullet array

              buf = Buffer.from(comp.buffer, bytesRead, 4);
              out = Buffer.from(buf, 'hex');
              bytesRead += 4;

              let len3 = changeEndianness(out.readUInt32BE());
              buf = Buffer.from(comp.buffer, bytesRead, len3);
              out = Buffer.from(buf, 'hex');
              bytesRead += len3;

              let noOfBullets = Number(out.toString('utf-8'));
              let bullets = [];
              // console.log(noOfBullets);

              for (var i = 0; i < noOfBullets; i++) {
                buf = Buffer.from(comp.buffer, bytesRead, 4);
                out = Buffer.from(buf, 'hex');
                bytesRead += 4;

                len3 = changeEndianness(out.readUInt32BE());
                buf = Buffer.from(comp.buffer, bytesRead, len3);
                out = Buffer.from(buf, 'hex');
                bytesRead += len3;

                let startTime = Number(out.toString('utf-8'));

                buf = Buffer.from(comp.buffer, bytesRead, 4);
                out = Buffer.from(buf, 'hex');
                bytesRead += 4;

                len3 = changeEndianness(out.readUInt32BE());
                buf = Buffer.from(comp.buffer, bytesRead, len3);
                out = Buffer.from(buf, 'hex');
                bytesRead += len3;

                let shootTime = Number(out.toString('utf-8'));

                if (shootTime - startTime < 2950) break;

                buf = Buffer.from(comp.buffer, bytesRead, 4);
                out = Buffer.from(buf, 'hex');
                bytesRead += 4;

                len3 = changeEndianness(out.readUInt32BE());
                buf = Buffer.from(comp.buffer, bytesRead, len3);
                out = Buffer.from(buf, 'hex');
                bytesRead += len3;

                let bulletPosX = Number(out.toString('utf-8')); //position X
                // console.log(bulletPosX);

                buf = Buffer.from(comp.buffer, bytesRead, 4);
                out = Buffer.from(buf, 'hex');
                bytesRead += 4;

                len3 = changeEndianness(out.readUInt32BE());
                buf = Buffer.from(comp.buffer, bytesRead, len3);
                out = Buffer.from(buf, 'hex');
                bytesRead += len3;

                let bulletPosY = Number(out.toString('utf-8')); //position Y
                // console.log(bulletPosY);

                buf = Buffer.from(comp.buffer, bytesRead, 4);
                out = Buffer.from(buf, 'hex');
                bytesRead += 4;

                len3 = changeEndianness(out.readUInt32BE());
                buf = Buffer.from(comp.buffer, bytesRead, len3);
                out = Buffer.from(buf, 'hex');
                bytesRead += len3;

                let bulletRot = Number(out.toString('utf-8')); //rotation

                //create an object and push it into bullets array
                var bullet = {
                  posX: bulletPosX,
                  posY: bulletPosY,
                  rot: bulletRot,
                };

                bullets.push(bullet);
              }

              players.forEach((pl, i) => {
                if (pl.id === pID && bullets.length > 0) {
                  players[i].bullets = [...bullets];
                }
              });

              break;
            }

            default:
              break;
          }
        }

        bytesRead = 0;
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
  var numOfBullets = enemy.bullets instanceof Array ? enemy.bullets.length : 0;
  var bulletsArray = [];

  if (numOfBullets > 0) {
    for (var i = 0; i < numOfBullets; i++) {
      bulletsArray.push(enemy.bullets[i].posX);
      bulletsArray.push(enemy.bullets[i].posY);
      bulletsArray.push(enemy.bullets[i].rot);
    }

    enemy.bullets = [];
  }

  var STAT = new Int32Array([
    1398030676,
    0,
    enemy.xPos,
    1,
    enemy.rotation,
    2,
    numOfBullets,
    ...bulletsArray,
  ]);

  player.ws.send(STAT);
}

console.log('Game ws server running on port ' + port);
