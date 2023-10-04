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
	uint32 targetID = 0; // 0�� �켱 �ƹ��͵� �ȳ־�α�� �߽��ϴ�. ������ ���� ���
	ACTION act = ACTION::IDLE;
	float _speed = 10.f;
};

