#pragma once
#include "MonoBehaviour.h"


class Dummy : public MonoBehaviour
{
public:
	Dummy(uint32 id);
	virtual ~Dummy();

	virtual void Start() override;
	virtual void Update() override;

private:
	void Run();
	void Pick();
	void FallDown();

private:
	uint32 _ID;
	Vec3 _originalScale = Vec3(10.f, 10.f, 10.f);
};

