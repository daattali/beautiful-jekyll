var weights = [];
var biases = [];
var embeddings = [];
var encoders = [];
var decoders = [];
var hidden_sizes = []
var state_sizes = [];
var depths = [];

function sigmoid(x){
    var result = [];
    for(var i = 0; i < x.length; i++){
        result.push(1/(1 + Math.pow(Math.E, -x[i])));
    }
    return result;
}

function tanh(x){
    var result = [];
    for(var i = 0; i < x.length; i++){
        result.push(Math.tanh(x[i]));
    }
    return result;
}

function pmul(a, b){
    var result = [];
    for(var i = 0; i < a.length; i++){
        result.push(a[i] * b[i]);
    }
    return result;
}

function padd(a, b){
    var result = [];
    for(var i = 0; i < a.length; i++){
        result.push(a[i] + b[i]);
    }
    return result;
}

function lstm(x, h, c, w, b, forget_bias=1.0){
    var input = x.concat(h);
    var i = [];
    var j = [];
    var f = [];
    var o = [];
    var out_size = b.length;
    for(var row_num = 0; row_num < out_size; row_num++){
        i.push(b[row_num]);
        j.push(b[row_num]);
        f.push(b[row_num]);
        o.push(b[row_num]);
        for(var n = 0; n < input.length; n++){
            i[i.length-1] += input[n] * w[row_num + out_size * 0][n];
            j[j.length-1] += input[n] * w[row_num + out_size * 1][n];
            f[f.length-1] += input[n] * w[row_num + out_size * 2][n] + forget_bias;
            o[o.length-1] += input[n] * w[row_num + out_size * 3][n];
        }
    }
    
    var new_c = padd(pmul(c, sigmoid(f)), pmul(sigmoid(i), tanh(j)));
    var new_h = pmul(tanh(new_c), sigmoid(o));
    
    return [new_h, new_c];  
}

function lstm_stack(x, h_array, c_array, w_array, b_array, forget_bias=1.0, num_layers=-1, in_place=false){
    var vector = x;
    if (!in_place){
        var h = [];
        var c = [];
    }
    for(var layer = 0; num_layers < 0 || layer < num_layers; layer++){
        var results = lstm(vector, h_array[layer], c_array[layer], w_array[layer], b_array[layer], forget_bias);
        if(in_place){
            h_array[layer] = results[0];
            c_array[layer] = results[1];
        } else {
            h.push(results[0]);
            c.push(results[1]);
        }
        vector = results[0];
    }
    if (in_place){
        return vector;   
    }
    return [vector, h, c];
}

function zero_state(layer_widths){
    var c = [];
    for(var width: layer_widths){
        c.push([]);
        for(var i = 0; i < width; i++){
            c[c.length - 1].push(0);
        }
    }
    return c;
}

function searchsorted(a, v){
    var min_index = 0;
    var max_index = a.length - 1;
    var index = (min_index + max_index) / 2 | 0;
    var val;
    
    while (min_index <= max_index){
        val = a[index];
        
        if (element < v) {
            min_index = index + 1;
        } else {
            max_index = index
        }
        index = (min_index + max_index) / 2 | 0;
    }
    return index
}

function sample(){
    var sample_type_select = document.getElementById("sample_type");
    var sample_type = sample_type_select.options[sample_type_select.selectedIndex].value;
    var sample_size = parseInt(document.getElementById("sample_size").value);
    var sample_seed = document.getElementById("sample_seed").value;
    var sample_array = [''];
    var embedding = embeddings[sample_type];
    var weight = weights[sample_type];
    var bias = biases[sample_type];
    var encoder = encoders[sample_type];
    var decoder = decoders[sample_type];
    var hidden_size = hidden_sizes[sample_type];
    var state_size = state_sizes[sample_type];
    var depth = depths[sample_type];
    var alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for(var chr: sample_seed.split('')){
        if(alphabet.includes(chr)){
            sample_array[sample_array.length - 1] = sample_array[sample_array.length - 1].concat(chr);
        } else {
            sample_array.push(chr);
            sample_array.push('');
        }
    }
    var sample_vectors = [];
    for(var str: sample_array){
        if(str != ''){
            sample_vectors.push(embedding[decoder[str]]);
        }
    }
    var sample = sample_seed;
    var h = zero_state(hidden_size);
    var c = zero_state(state_size);
    var result;
    for(var vec: sample_vectors){
        result = lstm_stack(vec, h, c, weight, bias, 1, -1, true);
    }
    var probs;
    var cum_probs;
    var sum;
    var chosen;
    var resnum;
    for(var i = 0; i < sample_size; i++){
        probs = lstm_stack(result, h, c, weight, bias, 1, -1, true);
        cum_probs = [probs[0]];
        sum = probs[0];
        for(var j = 1; j < probs.length; j++){
            sum += probs[j];
            cum_probs.push(sum);
        }
        chosen = Math.random() * sum;        
        resnum = searchsorted(cum_probs, chosen);
        result = embedding[resnum];
        sample.concat(decoder[resnum]);
    }
    return sample;
}

function init(){
    document.getElementById('sample-form').onsubmit = sample;
}

init();
