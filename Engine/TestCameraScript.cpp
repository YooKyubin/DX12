#include "pch.h"
#include "TestCameraScript.h"
#include "Transform.h"
#include "Camera.h"
#include "GameObject.h"
#include "Input.h"
#include "Timer.h"
#include "SceneManager.h"

#include "Engine.h"

TestCameraScript::TestCameraScript()
{
}

TestCameraScript::~TestCameraScript()
{
}

void TestCameraScript::Start()
{
	_preCursorPos = INPUT->GetMousePos();
	_cursorPos = _preCursorPos;

	Vec3 rotation = GetTransform()->GetLocalRotation() * XM_PI;
	char buffer[100];
	sprintf_s(buffer, "start Position : cur : ( %d, %d), pre : ( %d, %d )\n",
		(int)_cursorPos.x, (int)_cursorPos.y,
		(int)_preCursorPos.x, (int)_preCursorPos.y);
	OutputDebugStringA(buffer);

}

void TestCameraScript::LateUpdate()
{
	Vec3 pos = GetTransform()->GetLocalPosition();



	_cursorPos = INPUT->GetMousePos();
	if (INPUT->GetButton(KEY_TYPE::RBUTTON))
	{
		Vec3 rotation = GetTransform()->GetLocalRotation();
		rotation.y += (_cursorPos.x - _preCursorPos.x) * DELTA_TIME * 0.5;
		rotation.x += (_cursorPos.y - _preCursorPos.y) * DELTA_TIME * 0.5;

		if ((float)rotation.x > XM_PIDIV2)
			rotation.x = XM_PIDIV2;
		if ((float)rotation.x < -XM_PIDIV2)
			rotation.x = -XM_PIDIV2;
		GetTransform()->SetLocalRotation(rotation);

		//WCHAR text[100] = L"";
		//::wsprintf(text, L"rotation.x : %d", (int)rotation.x);

		//::SetWindowText(GEngine->GetWindow().hwnd, text);

			//char buffer[100];
			//sprintf_s(buffer, "cur : ( %d, %d), pre : ( %d, %d ) \n",
			//	(int)_cursorPos.x, (int)_cursorPos.y, 
			//	(int)_preCursorPos.x, (int)_preCursorPos.y);
			//OutputDebugStringA(buffer);

		//POINT temp;
		//temp.x = GEngine->GetWindow().width / 2;
		//temp.y = GEngine->GetWindow().height / 2;

		//::ClientToScreen(GEngine->GetWindow().hwnd, &temp);
		//::SetCursorPos(temp.x, temp.y);
	}
	_preCursorPos = _cursorPos;

	if (INPUT->GetButtonDown(KEY_TYPE::RBUTTON))
	{
		const POINT& pos = INPUT->GetMousePos();
		GET_SINGLE(SceneManager)->Pick(pos.x, pos.y);
	}

	GetTransform()->SetLocalPosition(pos);
}