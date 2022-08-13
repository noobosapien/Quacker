var canvas = null;
var ctx = null;
var setWinDim = null;
var startGame = null;
var setData = null;
var callRPC = null;
var ws = null;

function ModuleLoaded() {
  canvas = document.getElementById('canvas');
  ctx = canvas.getContext('2d');
  setWinDim = null;
  setWinDim = Module.cwrap('set_win_dim', 'undefined', ['int', 'int']);
  startGame = Module.cwrap('start_game', 'undefined', [
    'int',
    'string',
    'bool',
  ]);
  setData = Module.cwrap('set_game_data', 'undefined', ['string', 'string']);
  callRPC = Module.cwrap('call_ui_rpc', 'undefined', ['string']);

  //STRICTLY DEBUG!!!//
  if (document && setData) {
    document.setGameData = setData;
  }
  //STRICTLY DEBUG!!!//

  //UI RELATED//
  if (document && callRPC) {
    document.callRPC = callRPC;
  }
  //UI RELATED//

  if (setWinDim) {
    setWinDim(window.innerWidth, window.innerHeight);

    window.addEventListener('resize', () => {
      setWinDim(window.innerWidth, window.innerHeight);
      canvas.scrollIntoView({ block: 'center' });
    });
  }

  canvas.scrollIntoView({ block: 'center' });

  document.body.style['overflow-x'] = 'hidden';
  document.body.style['overflow-y'] = 'hidden';
}

var Module = {
  preRun: [],
  postRun: [ModuleLoaded],

  print: (function () {
    var element = document.getElementById('output');
    if (element) {
      element.value = '';
    }
    return function (text) {
      if (arguments.length > 1)
        text = Array.prototype.slice.call(arguments).join(' ');

      console.log(text);

      if (element) {
        element.value += text + '\n';
        element.scrollTop = element.scrollHeight;
      }
    };
  })(),

  printErr: function (text) {
    if (arguments.length > 1)
      text = Array.prototype.slice.call(arguments).join(' ');
    console.error(text);
  },

  canvas: (function () {
    var canvas = document.getElementById('canvas');
    canvas.addEventListener(
      'webglcontextlost',
      function (e) {
        alert('Please reload the page');
        e.preventDefault();
      },
      false
    );

    return canvas;
  })(),

  setStatus: function (text) {
    if (!Module.setStatus.last)
      Module.setStatus.last = { time: Date.now(), text: '' };
    if (text === Module.setStatus.last.text) return;

    var m = text.match(/([^(]+)\((\d+(\.\d+)?)\/(\d+)\)/);
    var now = Date.now();

    if (m && now - Module.setStatus.last.time < 30) return;
    Module.setStatus.last.time = now;
    Module.setStatus.last.text = text;

    if (m) {
      text = m[1];
    }
    console.log(text);
  },

  totalDependencies: 0,
  monitorRunDependencies: function (left) {
    this.totalDependencies = Math.max(this.totalDependencies, left);
    // Module.setStatus(left ? 'Preparing... (' + (this.totalDependencies - left) + '/' + this.totalDependencies + ')' : 'All downloads comeplete.');
  },
};

// Module.setStatus('Downloading...');
window.onerror = function () {
  Module.setStatus('Please refresh the page.');
  Module.setStatus = function (text) {
    if (text) Module.printErr('[post-execption status] ' + text);
  };
};

var pid = 0;
var plName = 'Gamer';

window.onload = async () => {
  try {
    const abortController = new AbortController();
    const signal = abortController.signal;

    let response = await fetch('/pid/', {
      method: 'GET',
      signal,
    });

    result = await response.json();
    pid = result.pid;

    //web socket stuff

    // ws = new WebSocket('ws://172.20.10.4:3001/');

    ws = new WebSocket('ws://192.168.8.101:3001/');
    // ws = new WebSocket('ws://3.104.94.74:3001/');

    ws.onopen = async function (e) {
      console.log('Connection to the index ws server opened');
    };

    ws.addEventListener('message', (message) => {
      const data = JSON.parse(message.data);
      console.log(data);

      if (data.start) {
        document.querySelector('#ui').style.zIndex = 0;
        document.querySelector('#ui').style.opacity = 0;
        document.getElementById('game').style.opacity = 1;
        document.getElementById('game').style.zIndex = 1;

        if (startGame) {
          startGame(pid, plName, data.player);
        }
      }
    });
  } catch (e) {
    console.log(e);
  }
};

const onStartClick = async (e) => {
  try {
    ws.send(JSON.stringify({ pid, start: true }));
  } catch (e) {
    console.log(e);
  }
};

document.getElementById('startButton').onclick = onStartClick;
