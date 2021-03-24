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