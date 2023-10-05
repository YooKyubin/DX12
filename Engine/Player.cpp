#include "pch.h"
#include "Player.h"
#include "Transform.h"
#include "Input.h"
#include "Timer.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::Start()
{
}

void Player::Update()
{
	Vec3 pos = GetTransform()->GetLocalPosition();
	Vec3 rotation = GetTransform()->GetLocalRotation();

	if (INPUT->GetButton(KEY_TYPE::W))
		pos += GetTransform()->GetLook() * _speed * DELTA_TIME;

	if (INPUT->GetButton(KEY_TYPE::S))
		pos -= GetTransform()->GetLook() * _speed * DELTA_TIME;

	if (INPUT->GetButton(KEY_TYPE::A))
		//pos -= GetTransform()->GetRight() * _speed * DELTA_TIME;
		rotation.y -= _speed * DELTA_TIME * 0.1;

	if (INPUT->GetButton(KEY_TYPE::D))
		//pos += GetTransform()->GetRight() * _speed * DELTA_TIME;
		rotation.y += _speed * DELTA_TIME * 0.1;

	GetTransform()->SetLocalPosition(pos);
	GetTransform()->SetLocalRotation(rotation);
}