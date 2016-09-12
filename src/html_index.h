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


    </script>
    </head>
    <body>

    <div onclick="httpGetAsync('set?led=0&b=0&led=1&b=0&led=2&b=0&led=3&b=0&led=4&b=0', callback)">
      OFF<br>
    </div>

  <div onclick="httpGetAsync('set?led=0&b=255&led=1&b=255&led=2&b=255&led=3&b=255&led=4&b=255', callback)">
    ON<br>
  </div>

    </body>
    </html>


)=====";
