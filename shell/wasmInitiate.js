async function instantiateAsync() {
    if (!wasmBinary &&
        typeof WebAssembly.instantiateStreaming === 'function' &&
        !isDataURI(wasmBinaryFile) &&
        // Don't use streaming for file:// delivered objects in a webview, fetch them synchronously.
        !isFileURI(wasmBinaryFile) &&
        typeof fetch === 'function') {

      try{
        let response = await fetch(wasmBinaryFile);

        const reader = response.body.getReader();
        const contentLength =+ response.headers.get('Content-Length');

        let receivedLength = 0;
        let chunks = [];
        while(true) {
          const {done, value} = await reader.read();
        
          if (done) {
            break;
          }
        
          chunks.push(value);
          receivedLength += value.length;

          const loaded = Math.ceil((receivedLength / contentLength) * 100);

          document.getElementById("progressBar").style.width = `${loaded}%`;

          if(loaded === 100){
            document.getElementById("startButton").disabled = 0;
          }
        
          console.log(`Received ${(Math.ceil((receivedLength / contentLength) * 100))} of ${contentLength}`);
        }

        let chunksAll = new Uint8Array(receivedLength);
        let position = 0;
        for(let chunk of chunks) {
          chunksAll.set(chunk, position);
          position += chunk.length;
        }
        var result = await WebAssembly.instantiate(chunksAll, info);

        receiveInstantiatedSource(result);

      }catch(e){
        err('wasm streaming compile failed: ' + e);
        err('falling back to ArrayBuffer instantiation');
        return instantiateArrayBuffer(receiveInstantiatedSource);
      }
      

    } else {
      return instantiateArrayBuffer(receiveInstantiatedSource);
    }
  }