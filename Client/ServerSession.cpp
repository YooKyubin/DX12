#include "pch.h"
#include "ServerSession.h"
#include "ClientPacketHandler.h"

ServerSession* GSeverSession;

ServerSession::~ServerSession()
{
	cout << "~ServerSession" << endl;
}

void ServerSession::OnConnected()
{
	cout << "Connected To Server" << endl;
	GSeverSession = this;
}

void ServerSession::OnRecvPacket(BYTE* buffer, int32 len)
{
	ClientPacketHandler::HandleRecvPacket(buffer, len);
}

void ServerSession::OnSend(int32 len)
{
	cout << "OnSend Len = " << len << endl;
}

void ServerSession::OnDisconnected()
{
	cout << "Disconnected" << endl;
}
