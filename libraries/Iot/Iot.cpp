#include <Arduino.h>
#include "Iot.h"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>
#include <SoftwareSerial.h>

Iot::Iot(eventCallback cb_)
	:isConnected(false), recvOffset(0), isSoftSerial(true), eventCb(cb_), isRunning(true)
{
  int i;
  for(i = 0; i < TOPIC_NUM; i++){
    memset(_subtopic[i],0,sizeof(_subtopic[i]));
    memset(_pubtopic[i],0,sizeof(_pubtopic[i]));
    cb[i] = NULL;
  }
  strcpy(serverIp,AIO_SERVER);
  serverPort = AIO_SERVERPORT;
}

Iot::~Iot()
{
}

bool Iot::setSerial(Stream &s_)
{
	s = &s_;
	#if defined(HAVE_HWSERIAL0)
	if((void*)(&Serial) == (void *)(s)){
		isSoftSerial = false;
	}
	#endif
	
	#if defined(HAVE_HWSERIAL1) || defined (SERIAL_PORT_HARDWARE1)
	if((void*)(&Serial1) == (void *)(s)){
		isSoftSerial = false;
	}
	#endif
	
	#if defined(HAVE_HWSERIAL2)
	if((void*)(&Serial2) == (void *)(s)){
		isSoftSerial = false;
	}
	#endif	
	isRunning = true;
	reset();
	return true;
}

bool Iot::setup(Stream & s, const char *wifiSsid, const char *wifiPasswd, const char *userName, const char * userPassword)
{
  setSerial(s);
  while(connectWifi(wifiSsid, wifiPasswd) == false){
    delay(1000);
  }

  while(query(CMD_QUERY_WIFI) == false){
    delay(1000);  
  }
  
  setServerIpPort(serverIp, serverPort);
  login(userName, userPassword);
  /*
  while(query(CMD_QUERY_SERVER) == false){
    delay(1000);
  }*/
  return true;
}

bool Iot::start( void )
{
	return connect();
}

bool Iot::ready( void )
{
	return query(CMD_QUERY_SERVER);
}

bool Iot::getVersion( String &version, int &platform )
{
  bool ret = false;
  cmdPacket = mallocPacket(CMD_GET_VERSION, NULL, 0, false);
  do{
    if((rspPacket = sendAndRecvDataPacket(cmdPacket)) == NULL)
      break;
    version = String((const char *)rspPacket->payload);
    platform = rspPacket->payload[version.length()+1];
	freePacket(rspPacket);
	rspPacket = NULL;
	ret = true;
  }while(0);
  return ret;
}

bool Iot::connectWifi(const char *ssid, const char * passwd)
{
  char * buf = (char *)malloc(strlen(ssid) + strlen(passwd) + 2);
  strcpy(buf, ssid);
  strcpy(&buf[strlen(ssid)+1], passwd);
  LDBG(ssid);
  LDBG(passwd);
  cmdPacket = mallocPacket(CMD_CONNECT_WIFI, buf, strlen(ssid)+strlen(passwd)+2, false);
  free(buf);
  return sendAndRecvCommPacket(cmdPacket);
}

bool Iot::upgrade(uint8_t platform, String version)
{
  char buf[10];
  strcpy(buf,version.c_str());
  buf[strlen(buf)+1] = platform;
  cmdPacket = mallocPacket(CMD_UPGRADE_FW, buf, strlen(buf)+2, false);
  isRunning = false;
  return sendAndRecvCommPacket(cmdPacket);
}

bool Iot::update(uint8_t platform, String version)
{
  return upgrade(platform, version);
}
  
bool Iot::setServer(const char *ip, uint16_t port)
{
  if(strlen(ip) > (sizeof(serverIp)-1)){
    return false;
  }
  strcpy(serverIp, ip);
  serverPort = port;
  return true;
}

bool Iot::setServerIpPort(const char *ip, uint16_t port)
{
  char * buf = (char *)malloc(strlen(ip) + 1 + 3);
  memset(buf, 0, strlen(ip) + 1 + 3);
  strcpy(buf, ip);
  memcpy(&buf[strlen(ip)+1], &port, 2);
  cmdPacket = mallocPacket(CMD_SET_SERVER, buf, strlen(ip)+2+2, false);
  free(buf);
  return sendAndRecvCommPacket(cmdPacket);
}

bool Iot::login(const char * userName, const char * passwd)
{
  delay(1000);
  char * buf = (char *)malloc(strlen(userName) + strlen(passwd) + 2);
  strcpy(buf, userName);
  strcpy(&buf[strlen(userName)+1], passwd);
  cmdPacket = mallocPacket(CMD_LOG_IN, buf, strlen(userName)+strlen(passwd)+2, false);
  free(buf);
  return sendAndRecvCommPacket(cmdPacket);	
}

bool Iot::subscribe(const char* topic,IotCb _cb)
{
  int i;
  for(i = 0; i < TOPIC_NUM; i++){
    if(strcmp(_subtopic[i],topic) == 0){
	  return false;
    }
  }
  
  for(i = 0; i < TOPIC_NUM; i++){
    if(_subtopic[i][0] == 0){
      strcpy(_subtopic[i],topic);
      cb[i] = _cb;
	  break;
    }
  }
  
  if(i == TOPIC_NUM){
    return false;
  }  
  cmdPacket = mallocPacket(CMD_SUBSCRIBE, topic, strlen(topic)+1, true);
  return sendAndRecvCommPacket(cmdPacket);
}

bool Iot::publish(const char* topic, const char* data,uint8_t channel)
{
  char * buf = (char *)malloc(strlen(topic) + strlen(data) + 3);
  strcpy(buf, topic);
  strcpy(&buf[strlen(topic)+1], data);
  buf[strlen(topic)+strlen(data)+2]=channel;
  cmdPacket = mallocPacket(CMD_PUBLISH, buf, strlen(topic)+strlen(data)+3, false);
  free(buf);
  return sendAndRecvCommPacket(cmdPacket);
}

bool Iot::connected()
{
  return isConnected;
}

bool Iot::connect(void)
{
  cmdPacket = mallocPacket(CMD_MODULE_CONNECT, NULL, 0, false);
  return sendAndRecvCommPacket(cmdPacket);	
}

void Iot::loop()
{
  readAndPausePacket();
}

void Iot::readAndPausePacket(void)
{
	if(isSoftSerial){
		((SoftwareSerial*)s)->listen();
	}
	if(s->available()){
		commonData[recvOffset++] = s->read();
		//LDBG((uint8_t)commonData[recvOffset-1],HEX);
		if(((uint8_t)commonData[0]) != 0x55){
			//LDBG((uint8_t)commonData[recvOffset-1],HEX);
			recvOffset = 0;
		}
		if((recvOffset == 2) && (((uint8_t)commonData[1]) != 0xAA)){
			//LDBG((uint8_t)commonData[1],HEX);
			recvOffset = 0;
		}
	}
	if(validPacket(commonData)){
		execPacket(commonData);
		memset(commonData,0,sizeof(commonData));
		recvOffset = 0;
	}
}

void Iot::execPacket(void* arg)
{
	pPacketHeader packet = (pPacketHeader)arg;
	LDBG(packet->cmd);
	if(packet->cmd == CMD_MODULE_SUB_DATA){
		for(int i = 0; i < TOPIC_NUM; i++){
			if(strcmp((const char *)packet->payload, (const char *)_subtopic[i]) == 0){
				int topicLen = strlen((const char *)packet->payload);
			    int dataLen = strlen((const char *)&packet->payload[topicLen+1]);
				cb[i]((const char *)&packet->payload[topicLen+1], dataLen);
			}
		}
	}else if(packet->cmd == CMD_MODULE_REPORT){
		if(eventCb != NULL){
			LDBG(packet->cmd);
			eventCb(packet->payload[0],(const char *)(&packet->payload[1]), (uint16_t)packet->length);
		}
	}else{
		LDBG("cmd=");LDBG(packet->cmd, HEX);
	}
}

bool Iot::validPacket(void* arg)
{
	bool ret = true;
	pPacketHeader packet = (pPacketHeader)arg;
	if((packet->header55 != 0x55) || (packet->headeraa != 0xaa)
		||(recvOffset != (packet->length + 5 + 1))/* || (getCS(packet) != packet->payload[packet->length])*/){
			if(recvOffset != (packet->length + 5 + 1))
			ret = false;
	}
	return ret;
}

size_t Iot::readN(void* buf_, size_t len)
{
    size_t offset = 0,left = len;
	uint8_t *buf = (uint8_t*)buf_;
	long long curr = millis();
	while(left){
		if(isSoftSerial){
			((SoftwareSerial*)s)->listen();
		}
		if(s->available()){
			buf[offset++] = s->read();
			LDBG(buf[offset-1], HEX);
		    left--;
		}
		if(millis() - curr > 10000){
			LDBG("----------!!!!!!!!!recv timeout----------");
			break;
		}
	}
	return offset;
}

int16_t Iot::readPacketPrefix( pPacketHeader header )
{
	int16_t ret = 0;
	uint8_t ch;
	typedef enum{
		RECV_HEADER_INIT,
		RECV_HEADER_55,
		RECV_HEADER_AA,
		RECV_HEADER_FRAMENO,
		RECV_HEADER_LENGTH,
		RECV_HEADER_CMD,
		RECV_HEADER_OK
	}eRecvHeaderState;
	eRecvHeaderState state = RECV_HEADER_INIT;
	
	while(state != RECV_HEADER_OK){
		if(readN(&ch, 1) != 1){
			ret = -1;
			break;
		}

		if((ch == 0x55) && (state == RECV_HEADER_INIT)){
			header->header55 = 0x55;
			state = RECV_HEADER_55;
			continue;
		}else if((ch == 0xaa) && (state == RECV_HEADER_55)){
			header->headeraa = 0xaa;
			state = RECV_HEADER_AA;
			continue;
		}else if(state == RECV_HEADER_AA){
			header->frameNo = ch;
			state = RECV_HEADER_FRAMENO;
			continue;
		}else if(state == RECV_HEADER_FRAMENO){
			header->length = ch;
			state = RECV_HEADER_LENGTH;
			continue;
		}else if(state == RECV_HEADER_LENGTH){
			header->cmd = ch;
			state = RECV_HEADER_OK;
			continue;
		}else{LDBG(ch,HEX);
			state = RECV_HEADER_INIT;
		}
	}
	return ret;
}

bool Iot::query(int arg)
{
	pPacketHeader packet = mallocPacket(arg, NULL, 0, false);
	return sendAndRecvCommPacket(packet);
}

pPacketHeader Iot::sendAndRecvDataPacket(pPacketHeader packet)
{
	int retry = 3;
	pPacketHeader rp = NULL;
	if(  !isRunning ){
	  return NULL;
	}

	while(retry--){
		sendPacket(packet);
		rp = recvRspPacket(packet->frameNo);
		if(rp != NULL){
			break;
		}
	}
	freePacket(packet);
	return rp;
}

bool Iot::sendAndRecvCommPacket(pPacketHeader packet)
{
	bool ret = false;
	int retry = 3;
	if(  !isRunning ){
	  goto out;
	}
	while(retry--){
		sendPacket(packet);
		int err = recvCommonRsp();
		if(err == 0){
			ret = true;
			break;
		}else if(err == -1){
			break;
		}
	}
out:
	freePacket(packet);
	return ret;
}

bool Iot::reset(void)
{
	bool ret;
	pPacketHeader packet = mallocPacket(CMD_RESET, NULL, 0, false);
	ret = sendAndRecvCommPacket(packet);
	long long curr = millis();
	while(millis()-curr < 
	#if defined(ARDUINO_ARCH_ARC32)
	8*1000
	#else
	8000*1000
	#endif
	){
		if(isSoftSerial){
			((SoftwareSerial*)s)->listen();
		}
		if(s->available())
			s->read();
	}
    return ret;
}

int Iot::recvCommonRsp(void)
{
	int ret = 0;
	rspPacket = recvRspPacket(frameNo);

	if(rspPacket == NULL){
		ret = -1;
	}else{
		if(rspPacket->payload[0] != 0){
			ret = -2;
		}
		memcpy(commonData, rspPacket->payload, rspPacket->length);
		commonData[rspPacket->length] = 0;
		free(rspPacket);
	}
	LDBG("recvCommonRsp OK");
	return ret;
}

pPacketHeader Iot::mallocPacket( uint8_t cmd, const void *data, uint8_t len, bool isString )
{
	const char *str = (const char *)data;
	if(isString){
		if(strlen(str) > MAX_PAYLOAD_LEN){
			return NULL;
		}
	}

	pPacketHeader packet = (pPacketHeader)malloc(sizeof(tPacketHeader) + len + 1);
	if(packet == NULL){
		while(1);
	}
    memset(packet, 0, sizeof(tPacketHeader) + len + 1);
	packet->header55 = 0x55;
	packet->headeraa = 0xaa;
	packet->length = len;
	packet->cmd = cmd;
	packet->frameNo = 0;//++frameNo;
	if(frameNo == 0xfd){
		frameNo = 0;
	}
	memcpy(packet->payload,data,len);
	packet->payload[packet->length] = getCS(packet);
	return packet;
}

uint8_t Iot::getCS(pPacketHeader packet)
{
	uint8_t cs = 0;
	uint8_t *p = (uint8_t*)packet;
	
	for(int i=0; i < packet->length + 5; i++){
		cs += p[i];
	}
	return cs;
}

int16_t Iot::sendPacket(pPacketHeader packet)
{
	uint8_t *p = (uint8_t *)packet;
	uint8_t len = sizeof(tPacketHeader) + packet->length + 1;
	for(int i=0; i < len; i++){
		LDBG(p[i],HEX);
		s->write(p[i]);
	}
	return len;
}

void Iot::freePacket(pPacketHeader packet)
{
	free(packet);
}

pPacketHeader Iot::recvRspPacket(uint8_t expectedFrameNo)
{
	pPacketHeader packet;
	do{
		tPacketHeader header;
		if(readPacketPrefix(&header) < 0){
			LDBG("--readPacketPrefix error---");
			return NULL;
		}
		packet = (pPacketHeader)malloc(sizeof(header) + header.length + 1);
		if(packet == NULL){
			while(1);
		}
		memcpy(packet, &header, sizeof(header));
		if(readN(packet->payload, packet->length + 1 ) != (size_t)(packet->length + 1)){
			LDBG("--recvRspPacket length error---");LDBG("\n");
			free(packet);LDBG("\n");
			packet = NULL;
		}else if(getCS(packet) != packet->payload[packet->length]){
			LDBG("--recvRspPacket cs error--- expect:");LDBG(getCS(packet), HEX);LDBG("  actual_get");LDBG(packet->payload[packet->length],HEX);
			free(packet);
			packet = NULL;
		}LDBG("\n");
		if(packet->cmd == CMD_MODULE_REPORT){
			if(eventCb){
				eventCb(packet->payload[0],(const char *)(&packet->payload[1]), (uint16_t)packet->length);
			}
			freePacket(packet);
			continue;
		}else{
			break;
		}
	}while(1);
	return packet;
}
