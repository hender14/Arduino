#include <Main.h> 
#include <Arduino_FreeRTOS.h>  // Include Arduino FreeRTOS library
#include <event_groups.h> //イベントフラグライブラリ
//-----------------------------------------------------------------------------
//  変数定義(variable definition)
//-----------------------------------------------------------------------------
int Delta[State_Num][Input_Num] = {{Run_advance, Run_Uturn, Run_avoidright, Run_avoidleft, Run_stop},
 {Run_advance, Run_Uturn, Run_avoidright, Run_avoidleft, Run_stop}, 
 {Run_advance, Run_Uturn, Run_avoidright, Run_avoidleft, Run_stop},
 {Run_advance, Run_Uturn, Run_avoidright, Run_avoidleft, Run_stop},
 {Run_advance, Run_Uturn, Run_avoidright, Run_avoidleft, Run_stop}}; //状態関数
//char Omega[State_Num][6] = {"dis_A","dis_B"}; //出力関数

/**********************************************************
 * 関数名 ： input
 * 機能   ： イベントの決定
 * 引数   ： なし
 * 戻値   ： イベント
 * 備考   ： 
*********************************************************/

int input(void) //入力条件の決定
{
  EventGroupHandle_t event_group;
  EventBits_t eBits = xEventGroupWaitBits(event_group, 
  EVENT_init | EVENT_area_out | EVENT_obst_left | EVENT_obst_right | EVENT_emergency,
  pdTRUE, pdFALSE, portMAX_DELAY);
  xEventGroupSetBits(event_group, EVENT_init);
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
  
}

/**********************************************************
 * 関数名 ： state_func
 * 機能   ： 走行状態を決定する
 * 引数   ： 状態変数、イベント
 * 戻値   ： 状態変数
 * 備考   ： 
*********************************************************/

int state_func(int st, int c)
{
  return Delta[st][c];
}