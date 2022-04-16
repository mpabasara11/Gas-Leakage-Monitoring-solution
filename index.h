const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<body>
<center><h1>Gas Meter Stats</h1></center>

<div id="demo1">
<h1>Meter 1</h1>
	<button type="button" onclick="meterOnePower(1)">ON</button>
	<button type="button" onclick="meterOnePower(0)">OFF</button><BR>


	Meter Reading Values : <span id="ADCValue1">0</span><br>
  Power State : <span id="meterOneState">NA</span>
</div>

<div id="demo2">
<h1>Meter 2</h1>
	<button type="button" onclick="meterTwoPower(1)">ON</button>
	<button type="button" onclick="meterTwoPower(0)">OFF</button><BR>



	Meter Reading Values: <span id="ADCValue2">0</span><br>
  Power State : <span id="meterTwoState">NA</span>
</div>
<style>
#demo1 {
    width: 100%;
    height: 200px;
    border: 1px solid #aaaaaa;
    background-color: #ffffff;
    
}
#demo2 {
    width: 100%;
    height: 200px;
    border: 1px solid #aaaaaa;
    background-color: #ffffff;
    
}
h1 {
font-family: Impact, sans-serif;
color: #CE5937;
}
</style>





<script>
function meterOnePower(led) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("meterOneState").innerHTML =
      this.responseText;
    }
  };
 xhttp.open("GET", "setLED1?MeterOneState="+led, true);
  xhttp.send();
}

function meterTwoPower(led) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("meterTwoState").innerHTML =
      this.responseText;
    }
  };
 xhttp.open("GET", "setLED2?MeterTwoState="+led, true);
  xhttp.send();
}






function getData1() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("ADCValue1").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "meter1", true);
  xhttp.send();
}

function getData2() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("ADCValue2").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "meter2", true);
  xhttp.send();
}


setInterval(function() {
  // Call a function repetatively with 2 Second interval
  getData1();
  getData2();

}, 1000); 


</script>
<br>
</body>
</html>
)=====";
