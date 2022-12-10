#include <WiFi.h>
#include <HTTPClient.h>

const int buttonAPin = 0;
// const char* ssid     = "TP-LINK_77FF";//修改为你的WIFI账号与密码
// const char* password = "qwer02..";

// const char* mqtt_server = "124.223.103.23";//这是树莓的MQTT服务器地址

void wifiInit(void)//连接WIFI
{
    Serial.begin(115200);

    //Init WiFi as Station, start SmartConfig
    WiFi.mode(WIFI_AP_STA);
    WiFi.beginSmartConfig();

    //Wait for SmartConfig packet from mobile
    Serial.println("Waiting for SmartConfig.");
    while (!WiFi.smartConfigDone()) {
      delay(500);
      Serial.print(".");
    }

    Serial.println("");
    Serial.println("SmartConfig received.");

    // Wait for WiFi to connect to AP
    Serial.println("Waiting for WiFi");
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }

    Serial.println("WiFi Connected.");

    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
}

void httpTest() {
    HTTPClient http; // 声明HTTPClient对象

    http.begin("https://imlgw.top"); // 准备启用连接

    int httpCode = http.GET(); // 发起GET请求

    if (httpCode > 0) // 如果状态码大于0说明请求过程无异常
    {
      if (httpCode == HTTP_CODE_OK) // 请求被服务器正常响应，等同于httpCode == 200
      {
        String payload = http.getString(); // 读取服务器返回的响应正文数据
                                          // 如果正文数据很多该方法会占用很大的内存
        Serial.println(payload);
      }
    }
    else
    {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end(); // 结束当前连接

    delay(10000);
}



void setup() {
  // 初始化串口监视器
  Serial.begin(115200);
  wifiInit();
  httpTest();
  // 初始化按键 A 对应的引脚为输入模式
  pinMode(buttonAPin, INPUT_PULLUP);
  pinMode(2,OUTPUT);  //配置GPIO2端口模式为输出模式
  digitalWrite(2,HIGH);  //配置GPIO2端口为高电平，灯亮
}

void loop() {
  // 如果按键 A 被按下了，串口监视器输出信息
  if (digitalRead(buttonAPin) == LOW) {
    Serial.println("Button A pressed");
  }

  delay(100);
}