#include <Mapping.h> 
#include <Arduino_FreeRTOS.h> 
#include <Main.h> 
#include <math.h>
#include <JY901.h> 
#include <Arduino.h>

/**********************************************************
 * 関数名 ： Acc_calc
 * 機能   ： ﾓｰﾀを駆動する
 * 引数   ： なし
 * 戻値   ： 車間距離
 * 備考   ： 
*********************************************************/
Acc_calc::Acc_calc()
{
}

int Acc_calc::Acc_rec(unsigned char ucData)
{
  static unsigned char ucRxBuffer[250];
  static unsigned char ucRxCnt = 0;
  
  ucRxBuffer[ucRxCnt++]=ucData;
  if (ucRxBuffer[0]!=0x55) 
  {
    ucRxCnt=0;
    return 0;
  }
  if (ucRxCnt<11) {return 0;}
  else
  {
    switch(ucRxBuffer[1])
    {
      case 0x51:  memcpy(&JY901.stcAcc,&ucRxBuffer[2],8);;break;
    }
    ucRxCnt=0;
    return 1;
  }
}
/**********************************************************
 * 関数名 ： Accelarate
 * 機能   ： 加速度を計測する
 * 引数   ：なし
 * 戻値   ： 加速度
 * 備考   ： 
*********************************************************/
Accelarate::Accelarate()
{
  count_sum = 0;
}

void Accelarate::Accelarate_sum(float* pacc_x, float* pacc_y, float* pacc_z)
{
    while(1) {
//        JY901.CopeSerialData(Serial.read());
        count = run_Acc_calc.Acc_rec(Serial.read()); //Call JY901 data cope function
        if (count == 1) {
            *pacc_x = *pacc_x + (float)JY901.stcAcc.a[0]/32768*16;
            *pacc_y = *pacc_y + (float)JY901.stcAcc.a[1]/32768*16;
            *pacc_z = *pacc_z + (float)JY901.stcAcc.a[2]/32768*16;
            count_sum = count_sum + 1;
        }
        if (count_sum == 10)
        { return; }
    }
}
/**********************************************************
 * 関数名 ： Run_Corrdinate
 * 機能   ： 座標位置を計算する
 * 引数   ： 速度(x, y))
 * 戻値   ： 速度
 * 備考   ： 
*********************************************************/
speed::speed()
{

}

void speed::speed_calc(void)
{
    TickType_t StartTime_acc, EndTime_acc, diffTime_acc;

    StartTime_acc = xTaskGetTickCount();
    run_Accelarate.Accelarate_sum(&acc_x, &acc_y, &acc_z);
    EndTime_acc = xTaskGetTickCount();
    diffTime_acc = EndTime_acc - StartTime_acc;

    vel_x = vel_x + acc_x * diffTime_acc;
    vel_y = vel_y + acc_y * diffTime_acc;
    Serial.print("vx,vy:");
    Serial.print(vel_x);
    Serial.print(",");
    Serial.print(vel_y);
    Serial.println(" ");
    coord_x = coord_x + acc_x * pow(diffTime_acc, 2.0) / 2;
    coord_x = coord_y + acc_y * pow(diffTime_acc, 2.0) / 2;
    Serial.print("coor_x, coor_y:");
    Serial.print(coord_x);
    Serial.print(",");
    Serial.print(coord_y);
    Serial.println(" ");
}
/**********************************************************
 * 関数名 ： coordinate_calc
 * 機能   ： 座標を計算する
 * 引数   ： 計測開始時間
 * 戻値   ： 座標
 * 備考   ： 
*********************************************************/
coordinate::coordinate()
{

}

void coordinate::coordinate_calc(int StartTime_vel)
{
    TickType_t EndTime_vel, diffTime_vel;

    EndTime_vel = xTaskGetTickCount();
    run_speed.speed_calc();
    diffTime_vel = EndTime_vel - StartTime_vel;
    
    coord_x = (vel_x * diffTime_vel);
    coord_y = (vel_y * diffTime_vel);    
}