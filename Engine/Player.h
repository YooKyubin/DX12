#pragma once
#include "Creature.h"

class Player : public Creature
{
public:
	Player();
	~Player();

	virtual void Start() override;
	virtual void Update() override;


};

