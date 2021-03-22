#include <obstacle.h>
#include <Arduino.h>
/**********************************************************
 * 関数名 ： coor_rececive
 * 機能   ： 障害物の座標データを受信する
 * 引数   ： なし
 * 戻値   ： 座標データ
 * 備考   ： 
*********************************************************/
receive::receive()
{

}

int receive::coor_rececive(int* pobst_coord_x, int* pobst_coord_y) 
{
//  int obst_coord_x, obst_coord_y;
  if (Serial.available() == 4) {
    Serial.readBytes(coordinate, 4);
    if (coordinate[0] == 's' && coordinate[3] == 'e') {
      //ここに送信処理を記述ポインタを定義
    *pobst_coord_x = coordinate[1];
    *pobst_coord_y = coordinate[2];
    return 1;
    }
    else {
//      while (Serial.available() > 0)
//        Serial.read();
        Serial.print("missMatch");
    }
  }
  else if (Serial.available() > 5) {
//    while (Serial.available() > 0)
//      Serial.read();
      Serial.print("overflow");
  }
}