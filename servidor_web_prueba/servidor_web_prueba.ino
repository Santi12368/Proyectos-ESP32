#include <WebServer.h>
#include <WiFi.h>

const char* ssid = ""; // Nombre wi-fi
const char* password = ""; // Contraseña wi-fi

WebServer server(80);

byte led1 = 12;
byte led2 = 14;
byte led3 = 27;
byte led4 = 26;
byte led5 = 25;
byte led6 = 33;
const byte ledArraySize = 6;
byte ledArray[ledArraySize] = {led1, led2, led3, led4, led5, led6};

byte lastRangeVal = 0;
byte currentRangeVal = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);
  Serial.print("Intentando conectar a ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(""); Serial.println("WiFi conectado!");
  Serial.print("IP Asignada: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleOnConnect);
  server.on("/rangeInput1", handleRangeValue1);
  server.on("/rangeInput2", handleRangeValue2);
  server.on("/rangeInput3", handleRangeValue3);
  server.on("/rangeInput4", handleRangeValue4);
  server.on("/rangeInput5", handleRangeValue5);
  server.on("/rangeInput6", handleRangeValue6);
  server.on("/rangeInput0", handleOnConnect);
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("Servidor HTTP iniciado");
  delay(50);
}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();

  if (currentRangeVal != lastRangeVal) {
    lastRangeVal = currentRangeVal;
    for (byte i = 0; i < ledArraySize; i++) {
      if (i < currentRangeVal) {
        digitalWrite(ledArray[i], HIGH);
      }
      else {
        digitalWrite(ledArray[i], LOW);
      }
    }
  }
}

void handleOnConnect() {
  currentRangeVal = 0;
  Serial.println("Ningun led activado");
  server.send(200, "text/html", SendHTML("#FFF", currentRangeVal));
}

void handleRangeValue1() {
  currentRangeVal = 1;
  Serial.println("Led1 activado");
  server.send(200, "text/html", SendHTML("#0F0", currentRangeVal));
}

void handleRangeValue2() {
  currentRangeVal = 2;
  Serial.println("Led1 | Led2 activados");
  server.send(200, "text/html", SendHTML("#0F0", currentRangeVal));
}

void handleRangeValue3() {
  currentRangeVal = 3;
  Serial.println("Led1 | Led2 | Led3 activados");
  server.send(200, "text/html", SendHTML("#FF0", currentRangeVal));
}

void handleRangeValue4() {
  currentRangeVal = 4;
  Serial.println("Led1 | Led2 | Led3 | Led4 activados");
  server.send(200, "text/html", SendHTML("#FF0", currentRangeVal));
}

void handleRangeValue5() {
  currentRangeVal = 5;
  Serial.println("Led1 | Led2 | Led3 | Led4 | Led5 activados");
  server.send(200, "text/html", SendHTML("#F00", currentRangeVal));
}

void handleRangeValue6() {
  currentRangeVal = 6;
  Serial.println("Led1 | Led2 | Led3 | Led4 | Led5 | Led6 activados");
  server.send(200, "text/html", SendHTML("#F00", currentRangeVal));
}

void handle_NotFound() {
  server.send(404, "text/plain", "Not found");
}

String SendHTML(String color, byte value) {
  String webPageString = "<!DOCTYPE html>\n<html lang=\"en\">\n<head>\n    <meta charset=\"UTF-8\">\n    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n    <title>SERVIDOR ESP32 | MODO ESTACION</title>\n\n    <style>\n        body {\n            margin: 0px auto;\n            text-align: center;\n            font-family: Arial, Helvetica, sans-serif;\n        }\n\n        #title {\n            margin-top: 50px;\n            margin-bottom: 10px;\n            color: rgb(14, 14, 14);\n        }\n\n        #subtitle {\n            margin-top: 0;\n            margin-bottom: 10px;\n            color: dimgray;\n        }\n\n        #colorLabel {\n            width: 50px;\n            height: 27px;\n            border: solid black 1px;\n            background-color: " + color + ";\n            display: inline-block;\n        }\n\n        .slidecontainer {\n            margin-left: 25%;\n            width: 50%;\n        }\n\n        input[type=range] {\n            height: 26px;\n            -webkit-appearance: none;\n            margin: 10px 0;\n            width: 100%;\n        }\n\n        input[type=range]:focus {\n            outline: none;\n        }\n\n        input[type=range]::-webkit-slider-runnable-track {\n            width: 100%;\n            height: 14px;\n            cursor: pointer;\n            animate: 0.2s;\n            box-shadow: 1px 1px 1px #50555C;\n            background: #50555c;\n            border-radius: 14px;\n            border: 0px solid #000000;\n        }\n\n        input[type=range]::-webkit-slider-thumb {\n            box-shadow: 0px 0px 0px #000000;\n            border: 0px solid #000000;\n            height: 20px;\n            width: 40px;\n            border-radius: 12px;\n            background: #529DE1;\n            cursor: pointer;\n            -webkit-appearance: none;\n            margin-top: -3px;\n        }\n\n        input[type=range]:focus::-webkit-slider-runnable-track {\n            background: #50555C;\n        }\n\n        input[type=range]::-moz-range-track {\n            width: 100%;\n            height: 14px;\n            cursor: pointer;\n            animate: 0.2s;\n            box-shadow: 1px 1px 1px #50555C;\n            background: #50555C;\n            border-radius: 14px;\n            border: 0px solid #000000;\n        }\n\n        input[type=range]::-moz-range-thumb {\n            box-shadow: 0px 0px 0px #000000;\n            border: 0px solid #000000;\n            height: 20px;\n            width: 40px;\n            border-radius: 12px;\n            background: #529DE1;\n            cursor: pointer;\n        }\n\n        input[type=range]::-ms-track {\n            width: 100%;\n            height: 14px;\n            cursor: pointer;\n            animate: 0.2s;\n            background: transparent;\n            border-color: transparent;\n            color: transparent;\n        }\n\n        input[type=range]::-ms-fill-lower {\n            background: #50555C;\n            border: 0px solid #000000;\n            border-radius: 28px;\n            box-shadow: 1px 1px 1px #50555C;\n        }\n\n        input[type=range]::-ms-fill-upper {\n            background: #50555C;\n            border: 0px solid #000000;\n            border-radius: 28px;\n            box-shadow: 1px 1px 1px #50555C;\n        }\n\n        input[type=range]::-ms-thumb {\n            margin-top: 1px;\n            box-shadow: 0px 0px 0px #000000;\n            border: 0px solid #000000;\n            height: 20px;\n            width: 40px;\n            border-radius: 12px;\n            background: #529DE1;\n            cursor: pointer;\n        }\n\n        input[type=range]:focus::-ms-fill-lower {\n            background: #50555C;\n        }\n\n        input[type=range]:focus::-ms-fill-upper {\n            background: #50555C;\n        }\n    </style>\n</head>\n<body>\n    <div>\n        <h1 id=\"title\">SERVIDOR WEB ESP32</h1>\n        <h3 id=\"subtitle\">Modo Estacion (STA)</h3>\n    </div>\n    <div class=\"slidecontainer\">\n        <input type=\"range\" min=\"0\" max=\"6\" value=\"" + value + "\" class=\"slider\" id=\"myRange\">\n    </div>\n\n    <div>\n        <p>VALOR: <strong id=\"value\">0</strong></p>\n        <label style=\"vertical-align:super;\">ESTADO: </label><div id=\"colorLabel\"></div>\n    </div>\n\n    <script>\n        let slider = document.getElementById(\"myRange\");\n        let output = document.getElementById(\"value\");\n        output.innerHTML = slider.value;\n\n        slider.oninput = function() {\n            output.innerHTML = this.value;\n            let url = \"/\";\n            switch (this.value) {\n                case '0':\n                    url = \"/rangeInput0\"\n                    break;\n                case '1':\n                    url = \"/rangeInput1\"\n                    break;\n                case '2':\n                    url = \"/rangeInput2\"\n                    break;\n                case '3':\n                    url = \"/rangeInput3\"\n                    break;\n                case '4':\n                    url = \"/rangeInput4\"\n                    break;\n                case '5':\n                    url = \"/rangeInput5\"\n                    break;\n                case '6':\n                    url = \"/rangeInput6\"\n                    break;\n                default:\n                    break;\n            }\n            window.location.href = url;\n        }\n    </script>\n</body>\n</html>";
  return webPageString;
}