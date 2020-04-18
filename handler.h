#include <SoftwareSerial.h>
SoftwareSerial SIM900A(7, 8);


String readSIM900A()
{
    String buffersms;

    while (SIM900A.available())
    {
        String c = SIM900A.readString();
        Serial.println(c);
        buffersms.concat(c);
        
    }

    return buffersms;
}

String getValueSplit(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = { 0, -1 };
  int maxIndex = data.length();

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

String convertnum(String num){
  String temp;
  
  for(int i=1;i<num.length();i++){
    temp += num[i];
  }

  return "+62"+temp;
}
