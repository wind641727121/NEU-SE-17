#pragma once
#include <winsock2.h>
#include <WS2tcpip.h>
#pragma comment(lib, "WS2_32")  
//在默认windows.h会包含winsock.h，当你包含winsock2.h就会冲突，因此在包含windows.h前需要定义一个宏,#define WIN32_LEAN_AND_MEAN ;去除winsock.h
//要么将#include <winsock2.h>放在#include<windows.h>前面或者直接去掉#include<windows.h>




#define DEF_PACKET_SIZE 32 //默认包大小
#define ECHO_REQUEST 8 //type=8表示响应请求报文
#define ECHO_REPLY 0 //type=0表示响应应答报文

struct IPHeader
{
	BYTE m_byVerHLen; //4位版本+4位首部长度 //unsigned char 
	BYTE m_byTOS; // 服务类型
	USHORT m_usTotalLen;//总长度 //unsigned short
	USHORT m_usID; //标识
	USHORT m_usFlagFragOffset;//3位标志+13位片偏移
	BYTE m_byTTL;//TTL
	BYTE m_byProtocol;//协议
	USHORT m_usHChecksum;//首部校验和
	ULONG m_ulSrcIP; //源IP地址 //unsigned long
	ULONG m_ulDestIP; //目的IP地址
};

struct ICMPHeader
{
	BYTE m_byType; //类型
	BYTE m_byCode; //代码
	USHORT m_usChecksum; //检验和 
	USHORT m_usID; //标识符
	USHORT m_usSeq; //序号
	ULONG m_ulTimeStamp; //时间戳
};

struct PingReply
{
	USHORT m_usSeq;
	DWORD m_dwRoundTripTime; //unsigned long 
	DWORD m_dwBytes;
	DWORD m_dwTTL;
};

class ping
{
public:
	ping();
	~ping();
	BOOL Ping(DWORD dwDestIP, PingReply* pPingReply = NULL, DWORD dwTimeout = 2000);
	BOOL Ping(const char* szDestIP, PingReply* pPingReply = NULL, DWORD dwTimeout = 2000);
private:
	BOOL PingCore(const char* dwDestIP, PingReply* pPingReply, DWORD dwTimeout);
	USHORT CalCheckSum(USHORT* pBuffer, int nSize);
	ULONG GetTickCountCalibrate();
private:
	SOCKET m_sockRaw;
	WSAEVENT m_event;
	USHORT m_usCurrentProcID;
	char* m_szICMPData;
	BOOL m_bIsInitSucc;
	static USHORT s_usPacketSeq;
};