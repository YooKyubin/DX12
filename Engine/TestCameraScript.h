#pragma once
#include "MonoBehaviour.h"

class TestCameraScript : public MonoBehaviour
{
public:
	TestCameraScript();
	virtual ~TestCameraScript();

	virtual void Start() override;
	virtual void LateUpdate() override; // 키보드 입력을 받아 카메라의 위치 변경

private:
	float		_speed = 100.f;
	POINT		_cursorPos;
	POINT		_preCursorPos;
};

