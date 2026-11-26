#include <WiFi.h>
#include <WebSocketsServer.h>
#include <SPI.h>
#include <MFRC522.h>

const char* ssid = "PokeCenter Connecter";
const char* password = "pokepass";

WebSocketsServer webSocket(81);

#define SCK_PIN 18
#define MISO_PIN 19
#define MOSI_PIN 23

#define RST_PIN 22
#define SS1_PIN 27
#define SS2_PIN 26

MFRC522 reader1(SS1_PIN, RST_PIN);
MFRC522 reader2(SS2_PIN, RST_PIN);

String getUID(MFRC522::Uid* uid) {
  String result = "";

  for (byte i = 0; i < uid->size; i++) {
    if (uid->uidByte[i] < 0x10) {
      result += "0";
    }

    result += String(uid->uidByte[i], HEX);

    if (i < uid->size - 1) {
      result += ":";
    }
  }

  result.toUpperCase();
  return result;
}

void sendTag(MFRC522& reader, int slot) {

  if (!reader.PICC_IsNewCardPresent()) {
    return;
  }

  if (!reader.PICC_ReadCardSerial()) {
    return;
  }

  String uid = getUID(&reader.uid);

  Serial.print("Reader ");
  Serial.print(slot);
  Serial.print(" detected: ");
  Serial.println(uid);

  String message = String(slot) + " " + uid;

  webSocket.broadcastTXT(message);

  Serial.print("Sent: ");
  Serial.println(message);

  // Finish reading
  reader.PICC_HaltA();
  reader.PCD_StopCrypto1();
}

void onWebSocketEvent(uint8_t client,
                      WStype_t type,
                      uint8_t* payload,
                      size_t length) {

  if (type == WStype_CONNECTED) {
    Serial.println("Device connected!");
  }

  if (type == WStype_DISCONNECTED) {
    Serial.println("Device disconnected.");
  }

  if (type == WStype_TEXT) {
    String message = "";

    for (size_t i = 0; i < length; i++) {
      message += (char)payload[i];
    }

    Serial.print("Received: ");
    Serial.println(message);

    webSocket.sendTXT(client, message);
  }
}

void setup() {

  Serial.begin(115200);

  SPI.begin(SCK_PIN, MISO_PIN, MOSI_PIN);

  reader1.PCD_Init();
  reader2.PCD_Init();

  Serial.println("NFC readers initialized!");

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);

  Serial.println("Wireless device started!");
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());

  webSocket.begin();
  webSocket.onEvent(onWebSocketEvent);

  Serial.println("WebSocket server ready!");
}

void loop() {

  webSocket.loop();

  // Check both readers
  sendTag(reader1, 1);
  sendTag(reader2, 2);
}
