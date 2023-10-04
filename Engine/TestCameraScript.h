#pragma once
#include "MonoBehaviour.h"

class TestCameraScript : public MonoBehaviour
{
public:
	TestCameraScript();
	virtual ~TestCameraScript();

	virtual void Start() override;
	virtual void LateUpdate() override; // Ű���� �Է��� �޾� ī�޶��� ��ġ ����

private:
	float		_speed = 100.f;
	POINT		_cursorPos;
	POINT		_preCursorPos;
};

