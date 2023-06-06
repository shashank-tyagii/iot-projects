var temp = document.getElementById("temperature");
var hum = document.getElementById("humidity");
// var response =  fetch("http://localhost:8000/sensor_data");
// console.log(response);
// temp.innerHTML = response.temperature;
// hum.innerHTML = response.humidity;
const host = "http://localhost:8000/LEDcontrol";
var state_slider_red = 0;
var state_slider_green = 0;
var state_slider_blue = 0;

$('#slider_red').on('change', function(){
    state_slider_red = $('#slider_red').val();
    
    $('#status1').html(state_slider_red + ' %');

    $.ajax({
      url: host ,
      type: 'POST',
      data: {red: state_slider_red,
             green : state_slider_green,
             blue : state_slider_blue}
    });
});

$('#slider_green').on('change', function(){
    state_slider_green = $('#slider_green').val();
    
    $('#status2').html(state_slider_green + ' %');

    $.ajax({
      url: host ,
      type: 'POST',
      data: {red: state_slider_red,
             green : state_slider_green,
             blue : state_slider_blue}
    });
});

$('#slider_blue').on('change', function(){
    state_slider_blue = $('#slider_blue').val();
    
    $('#status3').html(state_slider_blue + ' %');

    $.ajax({
      url: host ,
      type: 'POST',
      data: {red: state_slider_red,
             green : state_slider_green,
             blue : state_slider_blue}
    });
});