#include <Arduino.h>
#include <SPI.h>
#include <LoRa.h>

#define BAND 915E6  // Fréquence LoRa (exemple pour 915 MHz, ajustez selon votre région)
#define SS_PIN 18   // Broche CS du module LoRa
#define RST_PIN 14  // Broche RST du module LoRa
#define DI0_PIN 26  // Broche DIO0 du module LoRa

// Déclaration de la fonction onReceive
void onReceive(int packetSize);

void setup() {
    Serial.begin(115200);
    while (!Serial);

    // Initialisation du module LoRa
    LoRa.setPins(SS_PIN, RST_PIN, DI0_PIN);
    if (!LoRa.begin(BAND)) {
        Serial.println("Erreur d'initialisation du module LoRa !");
        while (1);
    }
    Serial.println("Module LoRa prêt.");

    // Démarrez l'écoute des paquets LoRa reçus
    LoRa.onReceive(onReceive);
    LoRa.receive();
}

void loop() {
  Serial.println("waiting for incoming LoRa packets...");
    delay(5000);
}

// Définition de la fonction onReceive
void onReceive(int packetSize) {
    if (packetSize == 0) return;  // Aucun paquet reçu

    // Lecture des données reçues
    while (LoRa.available()) {
        String data = LoRa.readString();
        Serial.print("Données reçues: ");
        Serial.println(data);
    }

    // Réactivez l'écoute pour recevoir d'autres paquets
    LoRa.receive();
}
