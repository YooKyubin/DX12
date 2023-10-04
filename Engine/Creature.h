#pragma once
#include "MonoBehaviour.h"

enum class ACTION : uint8
{
	IDLE,
	MOVE,
	ATTACK,
	FALL_DOWN,
};

class Creature : public MonoBehaviour
{
public:
	Creature();
	virtual ~Creature();

	virtual void Start() override;
	virtual void Update() override;

private:
	static uint32 IDCounter;

protected:
	uint32 ID;
	bool isComputer = true;
	uint32 targetID = 0; // 0은 우선 아무것도 안넣어두기로 했습니다. 적당한 값이 없어서
	ACTION act = ACTION::IDLE;
	float _speed = 10.f;
};

