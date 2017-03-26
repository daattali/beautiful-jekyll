function sample(){
    alert('Form submitted!');
}

function init(){
    document.getElementById('sample-form').onsubmit = sample;
}

