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
	// pos = �������� �޾ƿ� ������ �ֱ�
	 //GetTransform()->SetLocalPosition(pos);
}