alert("abcdef");

function sample(){
  var values = {};
  $.each($('#myForm').serializeArray(), function(i, field) {
    values[field.name] = field.value;
  });
  alert("abcasdfasdf");
  alert(values);
}
