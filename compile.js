var walk = require('walk');
const { exec } = require('child_process');

var files = [];

const options = [
  '-o build/index.html',
  '-std=c++17',
  '-s --shell-file shell/shell.html',
  `-s EXPORTED_FUNCTIONS="['_main', '_set_win_dim', '_start_game', '_set_game_data', '_call_ui_rpc']"`,
  `-s EXTRA_EXPORTED_RUNTIME_METHODS="['cwrap', 'ccall']"`,
  `-lwebsocket.js`,
  `-lembind`,
  `-s NO_EXIT_RUNTIME=1`,
  `-s USE_SDL=2`,
  `-s USE_SDL_IMAGE=2`,
  `-s SDL2_IMAGE_FORMATS=["png"]`,
  `-s MAX_WEBGL_VERSION=2`,
  `--preload-file src/assets/textures`,
  `--preload-file src/assets/levels`,
  `--preload-file src/shaders`,
  '--preload-file src/network',
  '-s LLD_REPORT_UNDEFINED',
  '-s ALLOW_MEMORY_GROWTH=1',
  `--bind`,
  '--no-heap-copy',
];

var walker = walk.walk('./src', { followLinks: false, filters: ['glm'] });

walker.on('file', function (root, stat, next) {
  if (stat.name.endsWith('.cpp')) files.push(root + '/' + stat.name);
  next();
});

walker.on('end', function () {
  let command = 'em++ ';

  files.forEach((file) => {
    command = command + file + ' ';
  });

  options.forEach((option) => {
    command = command + option + ' ';
  });

  exec(command, (err, stdout, stderr) => {
    console.log(stderr);

    if (!err) {
      console.log(
        '++++++++++++++++++++++++++++++++++++++++++++++\n\n\nSUCSESS @ ',
        new Date(),
        '\n\n\n++++++++++++++++++++++++++++++++++++++++++++++\n'
      );
    }

    exec('node editIndex.js', (err, stdout, stderr) => {
      console.log(stderr);
    });
  });
  console.log(command);
});
