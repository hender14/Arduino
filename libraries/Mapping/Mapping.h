#ifndef DRIVE_H
#define DRIVE_H

//-----------------------------------------------------------------------------
//  マクロ定義(Macro definition)
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
//  型定義(Type definition)
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
//  プロトタイプ宣言(Prototype declaration)
//-----------------------------------------------------------------------------

class Acc_calc
{
  public:
    Acc_calc();
    int Acc_rec(unsigned char ucData);

    private:
};

class Accelarate
{
  public:
    Accelarate();
    void Accelarate_sum(float* pacc_x, float* pacc_y, float* pacc_z);
 
  private:
    int count_sum, count;
    Acc_calc run_Acc_calc;
};

class speed
{
  public:
    speed();
    void speed_calc(void);

  private:
    float acc_x, acc_y, acc_z;
    Accelarate run_Accelarate;
};

class coordinate
{
  public:
    coordinate();
    void coordinate_calc(int StartTime_vel);

  private:
    speed run_speed;
};
//-----------------------------------------------------------------------------

#endif