#include <SPI.h>
#include <WiFi.h>

#include "InsightsClient.h"

char insightsAccount[] = "<your NR account number>";
char insightsKey[]     = "<your Insights API key>";

// Initialize the Wifi and Insights client libraries
// On an Edison, this is all you need to do.  On an actual Arduino with a
// WiFi shield, you'll need to configure the client appropriately.
WiFiClient client;
InsightsClient insightsClient(&client, insightsAccount, insightsKey);

unsigned long lastConnectionTime = 0;        // last time we connected to the server, in milliseconds
const unsigned long postInterval = 5*1000;   // delay between updates, in milliseconds

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600); 
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
}

void loop() {
  Serial.println("Connecting...");
  
  // Construct an event...
  InsightsEvent event("ExampleEvent");
  event.addAttribute("platform", "Edison");
  event.addAttribute("cats", 100);
  
  // And send it!
  if (insightsClient.sendEvent(&event)) {
    Serial.println("Connection to Insights succeeded!");
  } else {
    Serial.println("Connection to Insights failed!");
  }
  
  delay(postInterval);
}
