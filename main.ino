#include "handler.h"
#include "connection.h"


boolean smsin = false;
String msgdata = "";
String no, ms;
String test = "yeyeyeyeyeye";
int tryagain = 0;
String buffersms="";
void setup()
{
  Serial.begin(9600);
  SIM900A.begin(9600);
  setupEthernet();
  Serial.println("ready");


}

void loop()
{
  
  if (smsin==false) {
//    Serial.println("reading....");
    buffersms = readSIM900A();
    delay(3000);
  }

  if (buffersms.startsWith("\r\n+CMT: ") && smsin==false)
  {
    Serial.println("*** RECEIVED A SMS ***");
    Serial.println(buffersms);
    String num = getValueSplit(buffersms, '"', 1);
    num.replace("+62", "0");
    no = num;
    String msg = getValueSplit(buffersms, '"', 6);
    msg.remove(0, 2);
    ms = msg;
    Serial.println(num + ',' + msg);
    Serial.println("*** END SMS ***");
    delay(300);
    smsin = true;
  }
 
  //send sms value by request get
  if (smsin) {
    delay(200);
    Serial.println("SENDING REQUEST....");
    delay(5000);
    String cd = "";
    int len = ms.length();
    ms.remove(len - 2, 2);
    ms.replace(" ", "-");
    if (ms.length() > 5) {

      cd = req_get("/api/test?param=" + no + ',' + ms);
      
    }
    else {
      Serial.println("not enought char");
      smsin = false;
      no = "";
      ms = "";
      buffersms = "";
    }
    if (cd != "" && cd != "0") {
      smsin = false;
      no = "";
      ms = "";
      buffersms = "";
    }
    delay(3000);

  }
  delay(100);
}
