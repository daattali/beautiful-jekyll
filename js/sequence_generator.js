function sample(){
    console.log('Form submitted!');
}

function init(){
    document.getElementById('sample-form').onsubmit = sample;
    console.log("init");
}

