#include "pch.h"
#include "Game.h"
#include "Engine.h"
#include "SceneManager.h"
#include "ThreadManager.h"
#include "Service.h"
#include "Session.h"
#include "BufferReader.h"
#include "ClientPacketHandler.h"
#include "Protocol.pb.h"
#include "ServerSession.h"
#include "CreatureManager.h"

void Game::Init(const WindowInfo& info)
{
	GEngine->Init(info);

	ClientServiceRef service = MakeShared<ClientService>(
		NetAddress(L"127.0.0.1", 7777),
		MakeShared<IocpCore>(),
		MakeShared<ServerSession>, // TODO : SessionManager 등
		1);

	ASSERT_CRASH(service->Start());
	for (int32 i = 0; i < 2; i++)
	{
		GThreadManager->Launch([=]()
			{
				while (true)
				{
					service->GetIocpCore()->Dispatch();
				}
			});
	}
	//GThreadManager->Join();

	// echo

	while (GET_SINGLE(CreatureManager)->GetPlayerID() == 0)
	{
		OutputDebugString(L"check5\n");
	}
	GET_SINGLE(SceneManager)->LoadScene(L"TestScene");
	GEngine->GetGraphicsCmdQueue()->WaitSync(); // 혹시모를 동기화를 위해

}

void Game::Update()
{
	GEngine->Update();
}