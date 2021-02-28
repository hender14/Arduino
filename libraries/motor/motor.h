#ifndef MOTOR_H
#define MOTOR_H

//------------------------------------------------


//------------------------------------------------
//  マクロ定義(Macro definition)
//------------------------------------------------


//------------------------------------------------
//  型定義(Type definition)
//------------------------------------------------


//------------------------------------------------
//  プロトタイプ宣言(Prototype declaration)
//------------------------------------------------
class motor
{
  public:
    motor();
    void drv_Motor (void);
    void Uturn_Motor_left (float output);
    void Uturn_Motor_right (float output);
    void avoid_Motor_left (void);
    void avoid_Motor_right (void);
    void stop_Motor (void);

  private:

};

//-----------------------------------------------------------------------------
//------------------------------------------------
#endif