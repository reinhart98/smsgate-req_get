#include <ArduinoHttpClient.h>
#include <Ethernet.h>
#include <EthernetClient.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

char serverAddress[] = "10.0.52.118";  // server address
int port = 10000;

EthernetClient c;
HttpClient client = HttpClient(c, serverAddress, port);

void setupEthernet() {
  while (Ethernet.begin(mac) != 1)
  {
    Serial.println("Error getting IP address via DHCP, trying again...");
    delay(5000);
  }
}

String req_get(String route) {
  Serial.println("making GET request");
  client.get(route);

  // read the status code and body of the response
  int statusCode = client.responseStatusCode();
  String response = client.responseBody();

  Serial.print("Status code: ");
  Serial.println(statusCode);
  Serial.print("Response: ");
  Serial.println(response);
  if (statusCode == 200) {
    return response;
  }
  else {
    return "0";

  }

}

String reqwithparam(String route, String data) {
  Serial.println("making GET request with Parameters");
  client.get(route + "?param=" + data);

  // read the status code and body of the response
  int statusCode = client.responseStatusCode();
  String response = client.responseBody();

  Serial.print("Status code: ");
  Serial.println(statusCode);
  Serial.print("Response: ");
  Serial.println(response);

  if (statusCode == 200) {
    return "OK";
  }
  else {
    return "fail";

  }

}
