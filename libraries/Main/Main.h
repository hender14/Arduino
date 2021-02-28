#ifndef MAIN_H
#define MAIN_H

//-----------------------------------------------------------------------------
//  マクロ定義(Macro definition)
//-----------------------------------------------------------------------------

#define TrigPin 3 //IRクロック調整
#define EchoPin 4 //IRデータ受信
#define leftmotor 5 //IRデータ受信
#define rightmotor 6 //IRデータ受信
#define zeromotor 7 //IRデータ受信
#define dht11_data 8 //温・湿度データ受信

//モデルベース開発
#define Run_advance 0 // 状態1
#define Run_Uturn 1 // 状態2
#define Run_avoidright 2 // 状態3
#define Run_avoidleft 3// 状態4
#define Run_stop 4// 状態5

#define NIL -1 //未定義
#define initial 0 //　入力記号0
#define area_out 1 //　入力記号1
#define obst_left 2// 入力記号2
#define obst_right 3// 入力記号3
#define emergency 4// 入力記号4

#define State_Num 5 //状態数
#define Input_Num 5//入力記号数

//-----------------------------------------------------------------------------
//  マクロ定義(Macro definition)
//-----------------------------------------------------------------------------

//イベントフラグ定義
#define EVENT_init (0x0001)
#define EVENT_area_out (0x0002)
#define EVENT_obst_left (0x0004)
#define EVENT_obst_right (0x0008)
#define EVENT_emergency (0x0010)
//#define EVENT_dis_U (0x0020)

//-----------------------------------------------------------------------------
//  型定義(Type definition)
//-----------------------------------------------------------------------------
/*
typedef struct
{
	runState_t state ;		//	走行状態
	int measure_data ;	//	測定値
} Statefunc_t;
*/

/*
typedef enum
{
	init,		//	前方
	area_out,			//	Uﾀｰﾝ
	obst_left,			//	右へ回避
	obst_right,			//	左へ回避
	emergency,			//	停止
} runEvent_t;
*/

//-----------------------------------------------------------------------------
//  プロトタイプ宣言(Prototype declaration)
//-----------------------------------------------------------------------------
void Task1(void *pvParameters);
void Task2(void *pvParameters);
void Task3(void *pvParameters);
void Task4(void *pvParameters);
//int input(void);
int state_func(int st, int c);
//-----------------------------------------------------------------------------
//  グローバル変数外部参照宣言
//-----------------------------------------------------------------------------

extern int coord_x;
extern int coord_y;
extern int vel_x;
extern int vel_y;
extern int StartTime_vel;
//-----------------------------------------------------------------------------
#endif