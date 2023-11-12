#include "pch.h"
#include "ClientPacketHandler.h"
#include "BufferReader.h"
#include "Protocol.pb.h"
#include "ServerSession.h"
#include "CreatureManager.h"

void ClientPacketHandler::HandleRecvPacket(BYTE* buffer, int32 len)
{
	BufferReader br(buffer, len);

	PacketHeader header;
	br >> header;

	Protocol::Creature pkt;

	ASSERT_CRASH(pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)));

	if (header.id == Protocol::Act::INIT)
	{
		HandleSendPacket(pkt);
	}

	// 패킷에 들어온정보를 아래와 같이 설정하면 됩니다.
	//int32 id;
	{
		float pX = pkt.transform().position().x();
		float pY = pkt.transform().position().y();
		float pZ = pkt.transform().position().z();

		float rX = pkt.transform().rotation().x();
		float rY = pkt.transform().rotation().y();
		float rZ = pkt.transform().rotation().z();

		shared_ptr<Creature> temp = make_shared<Creature>();
		temp->ID = pkt.id();
		temp->isComputer = pkt.iscomputer();
		temp->location = { {pX, pY, pZ}, {rX, rY, rZ} };
		temp->targetID = pkt.targetid();
		temp->act = (형변환) pkt.act();
		GET_SINGLE(CreatureManager)->SetCreature(temp, /*id*/);
	}


	//TODO : 후속처리 코드들 여기다가 넣어야 함
	//switch (header.id)
	//{
	//case Protocol::Act::INIT:
	//	HandleSendPacket(pkt);
	//	break;
	//case Protocol::Act::WALK:
	//	Handle_Recv_WALK(buffer, len);
	//	break;
	//case Protocol::Act::IDLE:
	//	Handle_Recv_IDLE(buffer, len);
	//	break;
	//case Protocol::Act::PICK:
	//	Handle_Recv_PICK(buffer, len);
	//	break;
	//case Protocol::Act::FALL_DOWN:
	//	Handle_Recv_FALL_DOWN(buffer, len);
	//	break;
	//}

	
}

//Send를 위한 함수
void ClientPacketHandler::HandleSendPacket(Protocol::Creature packet)
{
	SendBufferRef sendBuffer = _MakeSendBuffer(packet, packet.act());
	GSeverSession->Send(sendBuffer);


	// 이거 이제 어캄?
	shared_ptr<Creature> data = GET_SINGLE(CreatureManager)->GetSendData();
}


//후속처리 코드
void ClientPacketHandler::Handle_Recv_WALK(BYTE* buffer, int32 len)
{
	Protocol::Creature pkt;

	ASSERT_CRASH(pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)));


	//TODO : 규빈이가 아래 작성
	if (pkt.iscomputer() == false)
	{
		cout << "Player" << endl;
	}

	cout << pkt.transform().position().x() << " " << pkt.transform().position().z() << endl;

}


void ClientPacketHandler::Handle_Recv_IDLE(BYTE* buffer, int32 len)
{
	Protocol::Creature pkt;

	ASSERT_CRASH(pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)));


	//TODO : 규빈이가 아래 작성

	if (pkt.iscomputer() == false)
	{
		cout << "Player" << endl;
	}

	cout << pkt.transform().position().x() << " " << pkt.transform().position().z() << endl;
}

void ClientPacketHandler::Handle_Recv_FALL_DOWN(BYTE* buffer, int32 len)
{
	Protocol::Creature pkt;

	ASSERT_CRASH(pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)));
	//TODO
	cout << "FALL_DOWN" << endl;
}

void ClientPacketHandler::Handle_Recv_PICK(BYTE* buffer, int32 len)
{
	Protocol::Creature pkt;

	ASSERT_CRASH(pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)));
	//TODO

	cout << "PICK" << endl;
}
