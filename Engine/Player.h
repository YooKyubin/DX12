#pragma once
#include "MonoBehaviour.h"

class Player : public MonoBehaviour
{
public:
	Player(uint32 id);
	~Player();

	virtual void Start() override;
	//virtual void Update() override;
	virtual void LateUpdate() override;

	uint32 _id;

private:
	uint32 Pick();
	uint32 newPick();
	bool CheckIntersects(Vec3 rayOrigin, Vec3 rayDir, Vec3 targetPos, float radius);

private:
	//temp
	int32 _speed = 10;
};

