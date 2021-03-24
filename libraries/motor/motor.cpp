#include <Main.h>
#include <motor.h>  
#include <Arduino.h> 

motor::motor()
{
  
}
/**********************************************************
 * 関数名 ： drv_Motor
 * 機能   ： 前進する
 * 引数   ： なし
 * 戻値   ： なし
 * 備考   ： 
 *********************************************************/
void motor::drv_Motor (void) {
  analogWrite(leftmotor, 255*0.5);
  analogWrite(rightmotor, 255*0.6);
  analogWrite(zeromotor, 0);
}

/**********************************************************
 * 関数名 ： Uturn_Motor
 * 機能   ： Uﾀｰﾝする
 * 引数   ： 型
 * 戻値   ： なし
 * 備考   ： ジャイロの値も参照
 *********************************************************/
void motor::Uturn_Motor_left (float output) {
  analogWrite(leftmotor, 255 * output);
  analogWrite(rightmotor, 0);
  analogWrite(zeromotor, 0);

  }

/**********************************************************
 * 関数名 ： Uturn_Motor
 * 機能   ： Uﾀｰﾝする
 * 引数   ： 型
 * 戻値   ： なし
 * 備考   ： ジャイロの値も参照
 *********************************************************/
void motor::Uturn_Motor_right (float output) {
  analogWrite(leftmotor, 0);
  analogWrite(rightmotor, 255 * output);
  analogWrite(zeromotor, 0);

  }
/**********************************************************
 * 関数名 ： avoid_Motor_left
 * 機能   ： 障害物を左側へ回避する
 * 引数   ： 型 障害物座標
 * 戻値   ： なし
 * 備考   ： 
 *********************************************************/
void motor::avoid_Motor_left (void) {
  analogWrite(leftmotor, 255*0.5);
  analogWrite(rightmotor, 0);
  analogWrite(zeromotor, 0);
  }

/**********************************************************
 * 関数名 ： avoid_Motor_right
 * 機能   ： 障害物を右側へ回避する
 * 引数   ： 型 障害物座標
 * 戻値   ： なし
 * 備考   ： 
 *********************************************************/
void motor::avoid_Motor_right (void) {
  analogWrite(leftmotor, 0);
  analogWrite(rightmotor, 255*0.5);
  analogWrite(zeromotor, 0);
  }

/**********************************************************
 * 関数名 ： stop_Motor
 * 機能   ： 停止する
 * 引数   ： なし
 * 戻値   ： なし
 * 備考   ： 
 *********************************************************/
void motor::stop_Motor (void) {  
  analogWrite(leftmotor, 0);
  analogWrite(rightmotor, 0);
  analogWrite(zeromotor, 0);
  }