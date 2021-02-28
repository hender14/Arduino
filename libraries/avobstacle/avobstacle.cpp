#include <obstacle.h> 
#include <avobstacle.h> 
/**********************************************************
 * 関数名 ： avoid_judge
 * 機能   ： 障害物の回避方法を検討する
 * 引数   ： 障害物の座標データ
 * 戻値   ： 回避走行状態
 * 備考   ： 
*********************************************************/
avoid::avoid();
{

}

void avoid::avoid_judge(void)
 {
    coordinate = run_receive.coor_rececive();
    if (coordinate[1] < 100) {
    return Run_stop;
    }
    else if (coordinate[1] > 100) {
        if (coordinate[2] < 300) {
            return Run_avoidleft;
        else if (coordinate[2] >= 300) {
            return Run_avoidright;
        }
    }

}