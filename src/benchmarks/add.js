(function(log) {
  var vectorious = require('../../vectorious'),
      vector = require('../../build/Release/vector');
  
  log();
  log('Vector addition');
  log('---------------');
  
  var repetitions = 8192,
      size = 4096;
  
  var buffers = [
    new ArrayBuffer(size * 8),
    new ArrayBuffer(size * 8)
  ];
  
  var a = new Float64Array(buffers[0]),
      b = new Float64Array(buffers[1]);
  
  var i;
  for(i = 0; i < a.length; i++) {
    a[i] = 1;
    b[i] = 1;
  }
  
  var time = process.hrtime(),
      diff,
      res;
  
  for(i = 0; i < repetitions; i++) {
    a[Math.floor(Math.random() * a.length)] = Math.random();
    b[Math.floor(Math.random() * b.length)] = Math.random();
    res = vector.add(a, b);
  }
  
  diff = process.hrtime(time);
  
  log('C++ with typed arrays:', diff);
  
  a = vectorious.Vector.ones(size);
  b = vectorious.Vector.ones(size);
  
  time = process.hrtime();
  
  for(i = 0; i < repetitions; i++) {
    a.set(Math.floor(Math.random() * a.length), Math.random());
    b.set(Math.floor(Math.random() * b.length), Math.random());
    res = vectorious.Vector.add(a, b);
  }
  
  diff = process.hrtime(time);
  
  log('Vectorious v2:', diff);
})(console.log);