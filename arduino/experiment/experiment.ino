//https://github.com/sparkfun/LSM9DS1_Breakout を参考に
#include <Wire.h>
#include <SparkFunLSM9DS1.h> //Arduino IDEのLIBRARY MANAGERから「Sparkfun LSM9DS1」で検索してインストール
LSM9DS1 imu;// LSM9DS1 Library Init
#define LSM9DS1_M 0x1C // コンパスのI2C初期アドレス
#define LSM9DS1_AG 0x6A // 加速度とジャイロのI2C初期アドレス
// Sketch Output Settings //
#define PRINT_SPEED 1 // nms毎にデータを出力
static unsigned long lastPrint = 0; // 最後の出力時刻をキープ
// 以下を利用して利用値の地磁気補正?を行う
// http://www.ngdc.noaa.gov/geomag-web/#declination
#define DECLINATION 7.46 // 東京はたぶんこの値？
//取得した数値を格納する行列
float imu_9dof[13];//ax,ay,az,gx,gy,gz,mx,my,mz,Cap,press

int prevt = 0;
int t = 0;
int threshold = 5;

void setup()
{
  Serial.begin(115200);
  
  //IMUの設定
  Wire.begin();
  if (imu.begin(LSM9DS1_AG, LSM9DS1_M, Wire) == false)//IMUの起動を判定
  {
    Serial.println("Failed to communicate with LSM9DS1.");
    while (1);
  }
  
  //圧力センサの設定
  pinMode(2,OUTPUT);
  pinMode(3,INPUT);
  pinMode(13,OUTPUT);

  delay(100);
}

void loop()
{
  getIMU();//IMUの値を取得する関数を実行

  t = 0;

  // パルスの立ち上げ
  digitalWrite(2, HIGH);

  // 立ち上がりまでの時間計測
  while (digitalRead(3)!=HIGH) t++;

  // 放電するまで待つ
  digitalWrite(2, LOW);  
  delay(1);

  // ローパスフィルタ
  t = 0.8 * prevt + 0.2 * t;
  prevt = t;

  // LED点灯
  if( t > threshold ){
    digitalWrite(13, HIGH);
  } else {
    digitalWrite(13, LOW);
  }

  if ((lastPrint + PRINT_SPEED) < millis())//更新タイミングが来たらデータを表示
  {
    // Serial.print("ax:" + String(imu_9dof[0]) + "," + "ay:" + String(imu_9dof[1]) + "," + "az:" + String(imu_9dof[2]) + ",");
    // Serial.print("gx:" + String(imu_9dof[3]/100) + "," + "gy:" + String(imu_9dof[4]/100) + "," + "gz:" + String(imu_9dof[5]/100) + ",");
    // Serial.print("mx:" + String(imu_9dof[6]) + "," + "my:" + String(imu_9dof[7]) + "," + "mz:" + String(imu_9dof[8]) + ",");
    // Serial.println("Cap:" + String(t) + "," + "press:" + String(analogRead(A0)) + ",");
    Serial.print(String(imu_9dof[0]) + "," + String(imu_9dof[1]) + "," + String(imu_9dof[2]) + ",");
    Serial.print(String(imu_9dof[3]/100) + "," + String(imu_9dof[4]/100) + "," + String(imu_9dof[5]/100) + ",");
    Serial.print(String(imu_9dof[6]) + "," + String(imu_9dof[7]) + "," + String(imu_9dof[8]) + ",");
    Serial.println(String(t) + "," + String(analogRead(A0)) + ",");
    lastPrint = millis(); // 次回出力時刻を設定
  }

  delay(25);
}

void getIMU() {//IMUの値を取得する関数
  if ( imu.gyroAvailable() )
  {
    imu.readGyro();
  }
  if ( imu.accelAvailable() )
  {
    imu.readAccel();
  }
  if ( imu.magAvailable() )
  {
    imu.readMag();
  }
  if ( imu.tempAvailable() )
  {
    imu.readTemp();
  }

  //取得したデータを配列に格納する。roll, pitch, yawの計算は適当
  imu_9dof[0] = imu.calcAccel(imu.ax);
  imu_9dof[1] = imu.calcAccel(imu.ay);
  imu_9dof[2] = imu.calcAccel(imu.az);
  imu_9dof[3] = imu.calcGyro(imu.gx);
  imu_9dof[4] = imu.calcGyro(imu.gy);
  imu_9dof[5] = imu.calcGyro(imu.gz);
  imu_9dof[6] = imu.calcMag(imu.mx);
  imu_9dof[7] = imu.calcMag(imu.my);
  imu_9dof[8] = imu.calcMag(imu.mz);
  imu_9dof[9] = imu.temperature;

  //※以下の算出方法はすごく適当な仮の値なので全く参考にしないでください。
  //imu_9dof[10] = atan2(imu.ay, imu.az) * 180.0 / PI; //roll
  //imu_9dof[11] = atan2(-imu.ax, sqrt(imu.ay * imu.ay + imu.az * imu.az)) * 180.0 / PI; //pitch
  //imu_9dof[12] = atan2(imu.mx, imu.my) * 180.0 / PI; //yaw
}
