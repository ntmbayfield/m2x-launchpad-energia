#include "SPI.h"
#include "WiFi.h"
#include <jsonlite.h>

#include "M2XStreamClient.h"

char ssid[] = "<ssid>"; //  your network SSID (name)
char pass[] = "<WPA password>";    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;            // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;

char feedId[] = "<feed id>"; // Feed you want to read
char m2xKey[] = "<M2X access key>"; // Your M2X access key

char name[] = "<location name>"; // Name of current location of datasource
double latitude = -37.97884;
double longitude = -57.54787; // You can also read those values from a GPS
double elevation = 15;

WiFiClient client;
M2XStreamClient m2xClient(&client, m2xKey);

void setup() {
   Serial.begin(115200);

  // Setup pins of CC3000 BoosterPack
  WiFi.setCSpin(18);  // 18: P2_2 @ F5529, PE_0 @ LM4F/TM4C
  WiFi.setENpin(2);   //  2: P6_5 @ F5529, PB_5 @ LM4F/TM4C
  WiFi.setIRQpin(19); // 19: P2_0 @ F5529, PB_2 @ LM4F/TM4C

  delay(10);
  // Connect to an AP with WPA/WPA2 security
  Serial.println("Connecting to WiFi....");
  WiFi.begin(ssid, pass); // Use this if your wifi network requires a password
  // WiFi.begin(ssid);    // Use this if your wifi network is unprotected.

  Serial.println("Connect success!");
  Serial.println("Waiting for DHCP address");
  // Wait for DHCP address
  delay(5000);
  // Print WiFi status
  printWifiStatus();
}

void loop() {
  // generate some random locations.  Replace this with your code for reading values from a GPS
  float offset1 = random(-100, 100);
  float offset2 = random(-100, 100);
  double latitude = -37.97884 + (offset1/1000);
  double longitude = -57.54787 + (offset2/1000); // You can also read those values from a GPS
  
  Serial.print("Latitude: ");
  Serial.print(latitude);
  Serial.print("  Longitude: ");
  Serial.print(longitude);
  Serial.print("  Elevation: ");
  Serial.println(elevation);
  
  int response = m2xClient.updateLocation(feedId, name, latitude, longitude,
                                          elevation);
  Serial.print("M2x client response code: ");
  Serial.println(response);

  if (response == -1) while(1) ;

  delay(30000);

}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
}