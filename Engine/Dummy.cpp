#include "pch.h"
#include "Dummy.h"
#include "Transform.h"
#include "CreatureManager.h"
#include "Timer.h"

Dummy::Dummy(uint32 id) : _ID(id)
{
}

Dummy::~Dummy()
{
}

void Dummy::Start()
{
}

void Dummy::Update()
{
	auto dummy = GET_SINGLE(CreatureManager)->GetCreatures(_ID);

	Vec3 position = dummy->location.position;
	Vec3 rotation = dummy->location.rotation;
	GetTransform()->SetLocalPosition(position); // Transform 클래스랑 이름이 겹쳐서 문제가 생김
	GetTransform()->SetLocalRotation(rotation);

	float height = GetTransform()->GetLocalScale().y;
	if (height - _originalScale.y < 1.f && height != _originalScale.y * 0.1)
	{
		height = _originalScale.y;
	}
	else if (height > _originalScale.y)
	{
		height += (_originalScale.y - height) * GET_SINGLE(Timer)->GetDeltaTime(); // 원상복구 시간 1초
	}
	GetTransform()->SetLocalScale(Vec3(_originalScale.x, height, _originalScale.z));

	switch(dummy->act)
	{
	case Act::RUN:
		Run();
		break;

	case Act::PICK:
		Pick();
		break;

	case Act::FALL_DOWN:
		FallDown();
		break;

	default:
		break;
	}
}



void Dummy::Run()
{

}

void Dummy::Pick()
{
	Vec3 scale = Vec3(_originalScale.x, _originalScale.y * 2, _originalScale.z);
	GetTransform()->SetLocalScale(scale);
}

void Dummy::FallDown()
{
	GetTransform()->SetLocalScale(_originalScale * 0.1);
}