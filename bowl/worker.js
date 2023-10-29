onmessage = function(e) {
    console.log('Worker: Message received from main script', e, e.data);
    const result = e.data[0];
    if (isNaN(result) || result <=0) {
      console.log('Worker: bad input');
    } else {
      var distance = result;
      setInterval(function () {
          // Display the result in the element with id="demo"
          distance -=1;
          // If the count down is finished, write some text
          if (distance <= 0) {
              distance = result
              postMessage('ding!');
          }
      }, 1000);
    }
}