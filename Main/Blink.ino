#include <Arduino_FreeRTOS.h>  // Include Arduino FreeRTOS library
#include <JY901.h>  //Acc_Gyro_check
#include <Main.h> 
#include <distance.h> 
#include <Mapping.h> 
#include <obstacle.h> 
#include <Drive.h> 
#include <event_groups.h> //イベントフラグライブラリ
//-----------------------------------------------------------------------------
//  グローバル変数定義(grobal variable definition)
//-----------------------------------------------------------------------------
int StartTime_vel;
int coord_x = 0;
int coord_y = 0;
int vel_x = 0;
int vel_y = 0;
//-----------------------------------------------------------------------------
//  ハンドラ定義(handler definition)
//-----------------------------------------------------------------------------
TaskHandle_t Task1_Handler;
TaskHandle_t Task2_Handler;
TaskHandle_t Task3_Handler;
//TaskHandle_t Task4_Handler;
EventGroupHandle_t event_group = NULL; //イベントフラグのハンドラ定義
//-----------------------------------------------------------------------------
/**********************************************************
 * 関数名 ： setup
 * 機能   ： 初期化
 * 引数   ： None
 * 戻値   ： None
 * 備考   ： 
*********************************************************/
void setup() { 
  Serial.begin(115200);
  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);
  pinMode(leftmotor, OUTPUT);
  pinMode(rightmotor, OUTPUT);
  pinMode(zeromotor, OUTPUT);

  xTaskCreate(Task1, "Main", 128, NULL, 1, &Task1_Handler);
  xTaskCreate(Task2, "Soner", 128, NULL, 2, &Task2_Handler);
  xTaskCreate(Task3, "Camera", 128, NULL, 2, &Task3_Handler);
//   xTaskCreate(Task4, "ACC", 128, NULL, 2, &Task4_Handler);
   event_group = xEventGroupCreate(); //イベントフラグタスク生成
   xEventGroupClearBits(event_group, 0x000000); //フラグ初期化
  
   vTaskStartScheduler();  // start scheduler, however, if it doesn't exist, it seems to work.
}


/**********************************************************
 * 関数名 ： loop
 * 機能   ：
 * 引数   ：
 * 戻値   ：
 * 備考   ： 
*********************************************************/
void loop() {
}
/**********************************************************
 * 関数名 ： 
 * 機能   ： 障害物の回避方法を検討する
 * 引数   ： 障害物の座標データ
 * 戻値   ： 回避走行状態
 * 備考   ： 
*********************************************************/


void Task1(void *pvParameters)
{
  (void) pvParameters;
  int NowState = Run_advance; //初期状態   
  while(1)
  {
    Drive run_Drive;
    int state_Event = input(); //入力データを変数へ入力
    if (state_Event != NIL)
    {
      NowState = state_func(NowState, state_Event); //状態遷移
//      Serial.print("NowState:");  //デバッグ用
//      Serial.println(NowState); //デバッグ用
      run_Drive.runmotor(NowState);
    }     
    vTaskDelay(100);
  }
   vTaskDelay(1); // one tick delay (15ms) in between reads for stability??
}

int input(void) //入力条件の決定
{
  EventGroupHandle_t event_group;
  EventBits_t eBits = xEventGroupWaitBits(event_group, 
  EVENT_init | EVENT_area_out | EVENT_obst_left | EVENT_obst_right | EVENT_emergency,
  pdTRUE, pdFALSE, 10);
  if ((eBits & EVENT_emergency) == EVENT_emergency)
    return emergency;
  else if ((eBits & EVENT_area_out) == EVENT_area_out)
    return area_out;
  else if ((eBits & EVENT_obst_left) == EVENT_obst_left)
      return obst_left;
  else if ((eBits & EVENT_obst_right) == EVENT_obst_right)
    return obst_right;
  else if ((eBits & EVENT_init) == EVENT_init)
    return initial;
  else
    return initial;
  
}
/**********************************************************
 * 関数名 ： 
 * 機能   ： 障害物の回避方法を検討する
 * 引数   ： 障害物の座標データ
 * 戻値   ： 回避走行状態
 * 備考   ： 
*********************************************************/
void Task2(void *pvParameters)
{
  (void) pvParameters;
  
  while(1)
  {
    distance run_distance;
    int width;
    width = run_distance.Measure_dis();
//    Serial.print("width:"); //デバッグ用
//    Serial.println(width);  //デバッグ用
      if (width > 100) 
        {xEventGroupSetBits(event_group, EVENT_emergency);}
      else
        {xEventGroupSetBits(event_group, EVENT_init);}
    vTaskDelay(50);
  }
  vTaskDelay(1); // one tick delay (15ms) in between reads for stability??
}

/**********************************************************
 * 関数名 ： 
 * 機能   ： 障害物の回避方法を検討する
 * 引数   ： 障害物の座標データ
 * 戻値   ： 回避走行状態
 * 備考   ： 
*********************************************************/
void Task3(void *pvParameters)
{
  (void) pvParameters;

  while(1)
  {
    receive run_receive;
    int obst_coord_x, obst_coord_y;

    int check = run_receive.coor_rececive(&obst_coord_x, &obst_coord_y);
    if (check == 1) {
      if (obst_coord_x < 320)
        {xEventGroupSetBits(event_group, EVENT_obst_left);}
      if (obst_coord_x >= 320)
        {xEventGroupSetBits(event_group, EVENT_obst_right);}
    }
    vTaskDelay(500);

  }
  vTaskDelay(1); // one tick delay (15ms) in between reads for stability??
}
/**********************************************************
 * 関数名 ： 
 * 機能   ： 障害物の回避方法を検討する
 * 引数   ： 障害物の座標データ
 * 戻値   ： 回避走行状態
 * 備考   ： 
*********************************************************/

void Task4(void *pvParameters)
{
  (void) pvParameters;

  while(1)
  { 
    coordinate run_coordinate;
    run_coordinate.coordinate_calc(StartTime_vel);

    if (coord_x < 0 || coord_x > 1 || coord_y < 0 || coord_y > 1) {
      xEventGroupSetBits(event_group, EVENT_area_out);
    }
  vTaskDelay(500);
  }
  vTaskDelay(1);
}
