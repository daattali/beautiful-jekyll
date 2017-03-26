function sample(){
    alert('Form submitted!');
}

function init(){
    document.getElementById('form').onsubmit = sample;
}

