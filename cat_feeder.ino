#define BLYNK_TEMPLATE_ID "TMPL6bCd7gOAL"
#define BLYNK_TEMPLATE_NAME "PET Feeder"
#define BLYNK_AUTH_TOKEN "yehGV2eg9XzqPgFa-lP2FZAgqMc_jzTT"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <ESP32Servo.h>
#include <WiFiManager.h>

Servo myservo;
const int servoPin = 13;
int servoAngle = 90;

int StatusPakan = 0;
int lastStatusPakan = -1;
unsigned long waktuPakanMulai = 0;
bool timerAktif = false;
const unsigned long durasiPakan = 5000;

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  WiFiManager wm;
  wm.resetSettings();
  bool res = wm.autoConnect("PET_FEEDER");

  if (!res) {
    Serial.println("Gagal konek ke WiFi.");
    delay(3000);
    ESP.restart();
  }

  Serial.print("IP ESP32: http://");
  Serial.println(WiFi.localIP());

  Blynk.begin(BLYNK_AUTH_TOKEN, WiFi.SSID().c_str(), WiFi.psk().c_str());
  server.begin();

  myservo.attach(servoPin);
  myservo.write(servoAngle);
}

void BeriPakan() {
  myservo.write(180);
}

void MatikanPakan() {
  myservo.write(0);
}

BLYNK_WRITE(V0) {
  StatusPakan = param.asInt();
  if (StatusPakan == 1) {
    BeriPakan();
    waktuPakanMulai = millis();
    timerAktif = true;
  } else {
    MatikanPakan();
    timerAktif = false;
  }
}

void loop() {
  Blynk.run();

  if (timerAktif && millis() - waktuPakanMulai >= durasiPakan) {
    StatusPakan = 0;
    MatikanPakan();
    Blynk.virtualWrite(V0, 0);
    Serial.println("Pakan otomatis dimatikan setelah 5 detik.");
    timerAktif = false;
  }

  if (StatusPakan != lastStatusPakan) {
    Serial.print("Status Pakan: ");
    Serial.println(StatusPakan);
    lastStatusPakan = StatusPakan;
  }

  WiFiClient client = server.available();
  if (client) {
    String request = client.readStringUntil('\r');
    client.flush();

    if (request.indexOf("/servo?angle=") != -1) {
      int angleIndex = request.indexOf('=') + 1;
      int angle = request.substring(angleIndex).toInt();
      if (angle >= 0 && angle <= 180) {
        servoAngle = angle;
        myservo.write(servoAngle);
      }
    }

    client.println("HTTP/1.1 200 OK");
    client.println("Content-type:text/html");
    client.println();

    client.println("<!DOCTYPE html><html><head><meta name='viewport' content='width=device-width, initial-scale=1'>");
    client.println("<style>body { background:#0f172a; color:#f1f5f9; font-family:Segoe UI; text-align:center; padding-top:50px; } .slider { width:80%; } h1 { color:#38bdf8; } .footer { position:fixed; bottom:10px; width:100%; font-weight:bold; color:#60a5fa; }</style></head>");
    client.println("<body><h1>ESP32 Servo Control</h1>");
    client.print("<p>Angle: <span id='val'>"); client.print(servoAngle); client.println("</span>°</p>");
    client.print("<input type='range' min='0' max='180' value='"); client.print(servoAngle); client.println("' class='slider' id='servoRange'>");
    client.println("<script>let slider=document.getElementById('servoRange');let val=document.getElementById('val');slider.oninput=function(){val.innerHTML=this.value;fetch('/servo?angle='+this.value);}</script>");
    client.println("<div class='footer'>Global Institute</div></body></html>");

    client.stop();
  }
}
