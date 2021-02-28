#include <Main.h> 
#include <Arduino.h>
#include <distance.h>
/**********************************************************
 * 関数名 ： vei_distance
 * 機能   ： ﾓｰﾀを駆動する
 * 引数   ： なし
 * 戻値   ： 車間距離
 * 備考   ： 
*********************************************************/
distance::distance()
{

}

int distance::Measure_dis(void)
{
  digitalWrite(TrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);

  wave = pulseIn(EchoPin, HIGH) / 58.0; //The echo time is converted into cm
  wave = (int(wave * 100.0)) / 100.0; //Keep two decimal places

  return wave;
}
/*
    if  (wave < 20)      
      {xEventGroupSetBits(event_group, EVENT_dis_U);

      Serial.write(cm);}
    else if (wave < 150)
      {xEventGroupSetBits(event_group, EVENT_0);

      Serial.write(wave);} 

    else
      return NIL; //no input
*/
