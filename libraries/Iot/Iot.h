/*!
 * @file Iot.h
 * @brief DFRobot's Esp8266 iot
 * @n Header file for DFRobot's Esp8266 iot
 *
 * @copyright	[DFRobot](http://www.dfrobot.com), 2016
 * @copyright	GNU Lesser General Public License
 *
 * @author [](@dfrobot.com)
 * @version  V0.0.1
 * @date  2016-10-28
 */

#ifndef _IOT_H_
#define _IOT_H_

#include <HardwareSerial.h>

#define TOPIC_NUM 3
#define MAX_PAYLOAD_LEN 150

#define AIO_SERVER      "182.254.130.180"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL

#define CMD_CONNECT_WIFI        0x01
#define CMD_DISCONNECT_WIFI     0x02
#define CMD_LOG_IN              0x03
#define CMD_LOG_OUT             0x04
#define CMD_SET_SERVER          0x05
#define CMD_SUBSCRIBE           0x06
#define CMD_PUBLISH             0x07
#define CMD_UPGRADE_FW          0x08

#define CMD_MODULE_REPORT       0x10
#define CMD_MODULE_SUB_DATA     0x11
#define CMD_MODULE_CONNECT      0x12

#define CMD_QUERY_WIFI          0x20
#define CMD_QUERY_IP            0x21
#define CMD_QUERY_SERVER        0x22

#define CMD_RESET               0x30


#define CMD_GET_VERSION         0x40

#define CMD_RSPMASK             0x80

#define CHANNEL_COMMAND         0
#define CHANNEL_EVENT           1


//#define EVENT_CODE_WIFI            'W'
//#define EVENT_CODE_SERVER          'S'
//#define EVENT_CODE_NEW_VERSION     'V'
//#define EVENT_CODE_UPGRADE_PERCENT 'P'

//EVENT_CODE_WIFI               // 0:ssid或密码错误,1:已连接,2:已断开
//EVENT_CODE_SERVER             // 0:用户名或密码错误,1:已连接,2:已断开
//EVENT_CODE_NEW_VERSION        // 0:无更新,1:有更新
//EVENT_CODE_UPGRADE_PERCENT    // 0~100 更新进度
//EVENT_CODE_UART               // 0:异常,1:正常
//EVENT_CODE_UNKNOWN            // 0:未定义错误

#define	EVENT_CODE_WIFI            ((uint8_t)'W')
#define	EVENT_CODE_SERVER          ((uint8_t)'S')
#define	EVENT_CODE_NEW_VERSION     ((uint8_t)'V')
#define	EVENT_CODE_UPGRADE_PERCENT ((uint8_t)'P')
#define	EVENT_CODE_UART            ((uint8_t)'U')
#define	EVENT_CODE_UNKNOWN         ((uint8_t)0)


#define	PLATFORM_CURRENT   0
#define	PLATFORM_DFROBOT   1
#define	PLATFORM_AZURE     2
#define	PLATFORM_AWS       3
#define	PLATFORM_BLUEMIX   4


#define LDBG(...) if(dbg) {dbg->print("["); dbg->print(__FUNCTION__); dbg->print("(): "); dbg->print(__LINE__); dbg->print(" ] "); dbg->println(__VA_ARGS__);}

typedef void* (*IotCb)(const char *data, uint16_t len);
typedef void* (*eventCallback)(uint8_t type, const char *data, uint16_t len);

typedef struct{
	uint8_t header55;
	uint8_t headeraa;
	uint8_t frameNo;
	uint8_t length; //不包含cs
	uint8_t cmd;
	uint8_t payload[0];
}__attribute__ ((packed)) tPacketHeader,*pPacketHeader;

class Iot
{
public:
  Iot(eventCallback cb = NULL);
  ~Iot();
  bool setSerial(Stream &s_);
  bool setDbgSerial(Stream &s_){dbg = &s_; return true;}
  
  bool setup(Stream & s, const char *wifiSsid, const char *wifiPasswd, const char *userName, const char * userPassword);
  bool connectWifi(const char *ssid, const char * passwd);
  bool upgrade(uint8_t platform=PLATFORM_CURRENT, String version="0");
  bool update(uint8_t platform=PLATFORM_CURRENT, String version="0");  
  bool getVersion(String &version, int &platform);
  bool setServer(const char *ip, uint16_t port);
  bool setServerIpPort(const char *ip, uint16_t port);
  bool login(const char * userName, const char * passwd);
  bool subscribe(const char* topic, IotCb cb);
  bool publish(const char* topic,const char *data, uint8_t channel=CHANNEL_COMMAND);
  pPacketHeader mallocPacket( uint8_t cmd, const void *data, uint8_t len, bool isString );
  uint8_t getCS(pPacketHeader packet);
  void loop(void);

  bool start(void);
  bool ready(void);
  bool connect(void);
  bool connected();
  size_t readN(void* buf_, size_t len);
  int16_t readPacketPrefix( pPacketHeader header );
  int recvCommonRsp(void);
  bool sendAndRecvCommPacket(pPacketHeader packet);
  pPacketHeader sendAndRecvDataPacket(pPacketHeader packet);
  int16_t sendPacket(pPacketHeader packet);
  void freePacket(pPacketHeader packet);
  pPacketHeader recvRspPacket(uint8_t expectedFrameNo);
  void readAndPausePacket(void);
  void execPacket(void* arg);
  bool validPacket(void* arg);  
  bool query(int arg);
  bool reset(void);
  
private:
  Stream *s;
  Stream *dbg;
  bool isSoftSerial;
  unsigned long long timestamp;
  bool isConnected ;
  uint8_t frameNo;
  bool isRunning;
  pPacketHeader cmdPacket;
  pPacketHeader rspPacket;

  char _subtopic[TOPIC_NUM][30];
  char _pubtopic[TOPIC_NUM][30];
  IotCb cb[TOPIC_NUM];
  eventCallback eventCb;
  char commonData[MAX_PAYLOAD_LEN];
  uint16_t recvOffset; 
  char serverIp[16];
  uint16_t serverPort;
};

#endif
