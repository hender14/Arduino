#include <angle.h> 
#include <JY901.h>  //Acc_Gyro_check
#include <Arduino.h>

Angle::Angle()
{
}
/**********************************************************
 * 関数名 ： 
 * 機能   ： 障害物の回避方法を検討する
 * 引数   ： 障害物の座標データ
 * 戻値   ： 回避走行状態
 * 備考   ： 
*********************************************************/
int Angle::Angle_check(void)
{
  Angle_read(Serial.read());
  angle = (float)JY901.stcAngle.Angle[2]/32768*180;
  return angle;
}

/**********************************************************
 * 関数名 ： 
 * 機能   ： 障害物の回避方法を検討する
 * 引数   ： 障害物の座標データ
 * 戻値   ： 回避走行状態
 * 備考   ： 
*********************************************************/
void Angle::Angle_read(unsigned char ucData)
{
  static unsigned char ucRxBuffer[250];
  static unsigned char ucRxCnt = 0; 
  
  ucRxBuffer[ucRxCnt++]=ucData;
  if (ucRxBuffer[0]!=0x55) 
  {
    ucRxCnt=0;
    return;
  }
  if (ucRxCnt<11) {return;}
  else
  {
    switch(ucRxBuffer[1])
    {
      case 0x53:  memcpy(&JY901.stcAngle,&ucRxBuffer[2],8);break;
    }
    ucRxCnt=0;
  }
}