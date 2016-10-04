#include <AnsiStream.h>

using namespace ANSI;

void setup() {
  Serial.begin(115200);
  while(!Serial);
  Serial<<home()<<defaultBackground()<<defaultForeground();
  Serial<<"ansi test "<<boldOn()<<"www.r-site.net"<<boldOff()<<endl;
  Serial<<xy(1,2)<<"Time:";
}

void loop() {
  Serial<<xy(7,2)<<setForegroundColor(RED)<<millis()/1000<<endl;
  delay(100);
}
