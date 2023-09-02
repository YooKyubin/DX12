#include "pch.h"
#include "Game.h"
#include "Engine.h"
#include "SceneManager.h"

void Game::Init(const WindowInfo& info)
{
	GEngine->Init(info);

	GET_SINGLE(SceneManager)->LoadScene(L"TestScene");
	GEngine->GetGraphicsCmdQueue()->WaitSync(); // Ȥ�ø� ����ȭ�� ����
}

void Game::Update()
{
	GEngine->Update();
}