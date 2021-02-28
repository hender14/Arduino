#include <Main.h> 
#include <Drive.h>
#include <motor.h>  
#include <angle.h>  
#include <Arduino_FreeRTOS.h> 
#include <Arduino.h> 

/**********************************************************
 * 関数名 ： runmotor
 * 機能   ： ﾓｰﾀを駆動する
 * 引数   ： runState_t　(走行状態)
 * 戻値   ： なし
 * 備考   ： 
 *********************************************************/
Drive::Drive()
{

}

void Drive::runmotor(int st) //switch分による分岐
{
  motor run_motor;   
  switch (st) { 
    case Run_advance  :  run_motor.drv_Motor();
      break;
    case Run_Uturn  :  Uturn_Motor();
      break;
    case Run_avoidright  : run_motor.avoid_Motor_left();
      StartTime_vel = xTaskGetTickCount();
      break;
    case Run_avoidleft  : run_motor.avoid_Motor_right();
      StartTime_vel = xTaskGetTickCount();
      break;
    case Run_stop  : run_motor.stop_Motor();
      StartTime_vel = xTaskGetTickCount();
      delay(2000);
      break;
    default : break;
  } 
}

void Drive::Uturn_Motor(void)
{
  motor run_motor;   
  Angle run_Angle;
  Angle_Now = run_Angle.Angle_check();
  if (Angle_Now > 180) {
    Angle_Tar = Angle_Now - 180;
    while( (Angle_Now - Angle_Tar) > 10 ) {
      Angle_Now = run_Angle.Angle_check();
      if ( (Angle_Now - Angle_Tar) > 20)
        run_motor.Uturn_Motor_left(0.2);
      run_motor.Uturn_Motor_left(0.5);
    }
  }
  else {
    Angle_Tar = Angle_Now + 180;
    while( (Angle_Tar - Angle_Now) > 10 ) {
      Angle_Now = run_Angle.Angle_check();
      if ( (Angle_Tar - Angle_Now) > 20)
        run_motor.Uturn_Motor_right(0.2);
      run_motor.Uturn_Motor_right(0.5);
    }
  }
  run_motor.stop_Motor();
}