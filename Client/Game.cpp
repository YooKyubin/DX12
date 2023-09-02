#include "pch.h"
#include "Game.h"
#include "Engine.h"
#include "SceneManager.h"

void Game::Init(const WindowInfo& info)
{
	GEngine->Init(info);

	GET_SINGLE(SceneManager)->LoadScene(L"TestScene");
	GEngine->GetGraphicsCmdQueue()->WaitSync(); // 혹시모를 동기화를 위해
}

void Game::Update()
{
	GEngine->Update();
}