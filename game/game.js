const { EventEmitter } = require('events');

module.exports = class Game extends EventEmitter {
  constructor(ws1, ws2, gid) {
    super();
    this.player1 = ws1;
    this.player2 = ws2;
    this.gid = gid;
    this.loop = true;

    this.player1.send(JSON.stringify({ gid }));
    this.player2.send(JSON.stringify({ gid }));
  }

  start() {
    this.player1.send(JSON.stringify({ start: true, player: true }));
    this.player2.send(JSON.stringify({ start: true, player: false }));
  }

  emitEnded() {
    return this.emit('ended', { end: true, gid: this.gid });
  }

  gameLoop() {
    return new Promise((resolve, reject) => {
      try {
        while (this.loop) {
          break;
        }
        this.emitEnded();
        return resolve();
      } catch (e) {
        console.log(e);
        return reject(e);
      }
    });
  }
};
