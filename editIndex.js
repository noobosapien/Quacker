var fs = require('fs');

const indexFile = './build/index.js';
const wasminit = './shell/wasmInitiate.js'

fs.readFile(indexFile, 'utf8', function (err, data) {
  if (err) {
    return console.log(err);
  }
  
  data = data.replace('function instantiateAsync', 'function instantiateAsync2');

  fs.readFile(wasminit, 'utf8', function(err, wasm){
      data = data.replace("instantiateAsync();", `instantiateAsync();\n${wasm}`);

      fs.writeFile(indexFile, data, { flag: 'w+' }, err => {
          if(err)
            console.log(err);
      })
  });
});