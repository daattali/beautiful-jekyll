function sample(){
    var sample_type_select = document.getElementById("sample_type");
    var sample_type = sample_type_select.options[sample_type_select.selectedIndex].value;
    var sample_size = parseInt(document.getElementById("sample_size").value);
    var sample_seed = document.getElementById("sample_seed").value;
    console.log(sample_type);
    console.log(sample_size);
    console.log(sample_seed);
}

function init(){
    document.getElementById('sample-form').onsubmit = sample;
}

init();
