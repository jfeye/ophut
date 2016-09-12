const char html_index[] PROGMEM = R"=====(
  <!DOCTYPE HTML>
  <html><head>
  <title> Ein Test </title>
  <style>
  div {
    position: relative;
    float: left;
    height: 100px;
    width: 200px;
    padding: 40px;
    margin: 30px;
    text-align: center;
    font-family: arial;
    font-size: 30px;
    border: solid 3px black;
  }

  input {
    width: 180px;
    height: 25px;
  }

  </style>
  <script>

  function httpGetAsync(theUrl, callback){
      var xmlHttp = new XMLHttpRequest();
      xmlHttp.onreadystatechange = function() {
          if (xmlHttp.readyState == 4 && xmlHttp.status == 200)
              callback(xmlHttp.responseText);
      }
      xmlHttp.open("GET", theUrl, false); // true for asynchronous
      xmlHttp.send(null);
  }

  function callback(response){
    console.log(response);
  }


  // functions to calc rgb from hue
  function getRed(hue){
    if(hue<43)  return 255;
    else if(hue<85) return 255-((255*(hue-43))/42);
    else if(hue<171) return 0;
    else if(hue<213) return 255*(hue-171)/42;
    else return 255;
  }

  function getGreen(hue){
    if(hue<43)  return 255*(hue)/42;
    else if(hue<128) return 255;
    else if(hue<171) return 255-((255*(hue-128))/43);
    else return 0;
  }

  function getBlue(hue){
    if(hue<85)  return 0;
    else if(hue<128)  return 255*(hue-85)/43;
    else if(hue<213) return 255;
    else if(hue<255) return 255-((255*(hue-213))/42);
    else return 0;
  }

  function outputUpdate(vol) {
    document.querySelector('#a').value = vol;
    httpGetAsync("set?brightness="+vol, callback)
  }

    function outputColor(hue,  color) {
      console.log("h: " + hue +  " c: " + color);
      console.log("r: " + getRed(hue) +  " g: " + getGreen(hue) + "b: " + getBlue(hue));
      document.querySelector("#color"+color).value = hue;
      document.querySelector("#dc"+color).style.background = "rgb("+getRed(hue)+","+getGreen(hue)+","+getBlue(hue)+")";
      httpGetAsync("set?color="+color+"&r="+getRed(hue)+"&g="+getGreen(hue)+"&b="+getBlue(hue), callback)
    }
    </script>
    </head>
    <body>
    <div>
      A<br>
      <input type="range" min="0" max="255" value="128" id="fadera" step="1" oninput="outputUpdate(value)">
      <output for="fadera" id="a">128</output>
    </div>

    <div id="dc0">
      c0<br>
      <input type="range" min="0" max="255" value="128" id="faderc0" step="1" oninput="outputColor(value,0)">
      <output for="faderc0" id="color0">128</output>
    </div>

    <div id="dc1">
      c1<br>
      <input type="range" min="0" max="255" value="128" id="faderc1" step="1" oninput="outputColor(value,1)">
      <output for="faderc1" id="color1">128</output>
    </div>

    <div id="dc2">
      c2<br>
      <input type="range" min="0" max="255" value="128" id="faderc2" step="1" oninput="outputColor(value,2)">
      <output for="faderc2" id="color2">128</output>
    </div>
    </body>
    </html>

)=====";
