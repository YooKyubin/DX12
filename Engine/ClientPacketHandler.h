#pragma once
#include "Protocol.pb.h"

class ClientPacketHandler
{
public:
	static void HandleRecvPacket(BYTE* buffer, int32 len);
	static void HandleSendPacket(Protocol::Creature packet);

	static void Handle_Recv_WALK(BYTE* buffer, int32 len);
	static void Handle_Recv_IDLE(BYTE* buffer, int32 len);
	static void Handle_Recv_FALL_DOWN(BYTE* buffer, int32 len);
	static void Handle_Recv_PICK(BYTE* buffer, int32 len);
};

template<typename T>
SendBufferRef _MakeSendBuffer(T& pkt, uint16 pktId)
{
	const uint16 dataSize = static_cast<uint16>(pkt.ByteSizeLong());
	const uint16 packetSize = dataSize + sizeof(PacketHeader);

	SendBufferRef sendBuffer = GSendBufferManager->Open(packetSize);
	PacketHeader* header = reinterpret_cast<PacketHeader*>(sendBuffer->Buffer());
	header->size = packetSize;
	header->id = pktId;
	ASSERT_CRASH(pkt.SerializeToArray(&header[1], dataSize));
	sendBuffer->Close(packetSize);

	return sendBuffer;
}