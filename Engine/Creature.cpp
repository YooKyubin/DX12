#include "pch.h"
#include "Creature.h"
#include "Transform.h"

uint32 Creature::IDCounter = 0;

Creature::Creature()
{
	ID = ++IDCounter;
}

Creature::~Creature()
{
}

void Creature::Start()
{
}

void Creature::Update()
{
	// Vec3 pos = GetTransform()->GetLocalPosition();
	// pos = 서버에서 받아온 데이터 넣기
	 //GetTransform()->SetLocalPosition(pos);
}