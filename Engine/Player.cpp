#include "pch.h"
#include "Player.h"
#include "Transform.h"
#include "Input.h"
#include "Timer.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "CreatureManager.h"

#include "ClientPacketHandler.h"
#include "Protocol.pb.h"
#include "ServerSession.h"


Player::Player(uint32 id)
{
	_id = id;
}

Player::~Player()
{
}

void Player::Start()
{
}

void Player::LateUpdate()
{
	shared_ptr<Creature> sendData = make_shared<Creature>();
	int32 playerID = GET_SINGLE(CreatureManager)->GetPlayerID();
	
	Vec3 pos = GET_SINGLE(CreatureManager)->GetCreatures(playerID)->location.position;
	Vec3 rotation = GET_SINGLE(CreatureManager)->GetCreatures(playerID)->location.rotation;
	Act curAct = Act::IDLE;

	if (INPUT->GetButton(KEY_TYPE::W))
	{
		curAct = Act::WALK;
		pos += GetTransform()->GetLook() * _speed * DELTA_TIME;
	}

	if (INPUT->GetButton(KEY_TYPE::S))
	{
		curAct = Act::WALK;
		pos -= GetTransform()->GetLook() * _speed * DELTA_TIME;
	}

	if (INPUT->GetButton(KEY_TYPE::A))
	{
		curAct = Act::WALK;
		//pos -= GetTransform()->GetRight() * _speed * DELTA_TIME;
		rotation.y -= _speed * DELTA_TIME * 0.2f;
	}

	if (INPUT->GetButton(KEY_TYPE::D))
	{
		curAct = Act::WALK;
		//pos += GetTransform()->GetRight() * _speed * DELTA_TIME;
		rotation.y += _speed * DELTA_TIME * 0.2f;
	}

	//GetTransform()->SetLocalPosition(pos);
	//GetTransform()->SetLocalRotation(rotation);

	
	uint32 targetID = 0;
	if (INPUT->GetButtonDown(KEY_TYPE::SPACE))
	{
		// picking
		targetID = newPick();
		curAct = Act::PICK; ////////////////////////////////////////

	}

	//sendData->location.position = pos;
	//sendData->location.rotation = rotation;
	//sendData->ID = playerID;
	//sendData->isComputer = false;
	//sendData->targetID = targetID;
	//sendData->act = GET_SINGLE(CreatureManager)->GetCreatures(playerID)->act;


	Protocol::Creature temp;

	Protocol::Transform* tempTransform = new Protocol::Transform();
	Protocol::vec3* tempPos = new Protocol::vec3();
	Protocol::vec3* tempRot = new Protocol::vec3();

	tempPos->set_x(pos.x);
	tempPos->set_y(pos.y);
	tempPos->set_z(pos.z);
		   
	tempRot->set_x(rotation.x);
	tempRot->set_y(rotation.y);
	tempRot->set_z(rotation.z);

	tempTransform->set_allocated_position(tempPos);
	tempTransform->set_allocated_rotation(tempRot);

	temp.set_allocated_transform(tempTransform);
	temp.set_act((Protocol::Act)curAct);
	temp.set_id(playerID);
	temp.set_iscomputer(false);
	temp.set_targetid(targetID);

	ClientPacketHandler::HandleSendPacket(temp);


	//GET_SINGLE(CreatureManager)->SetSendData(sendData);
}

uint32 Player::newPick()
{
	int32 length = GET_SINGLE(CreatureManager)->GetSize();
	int32 playerID = GET_SINGLE(CreatureManager)->GetPlayerID();
	float minDistance = FLT_MAX;
	uint32 picked = 0;

	Vec3 playerPos = GET_SINGLE(CreatureManager)->GetCreatures(playerID)->location.position;
	Vec3 rayDir = GetTransform()->GetLook();
	rayDir.Normalize();

	Vec3 detectionPoint = playerPos + rayDir * 10;

	{
		char buffer[100];
		sprintf_s(buffer, "detectionPos:% d, % d, % d \n playerPos : %d, %d, %d\n",
			(int)detectionPoint.x, (int)detectionPoint.y, (int)detectionPoint.z,
			(int)playerPos.x, (int)playerPos.y, (int)playerPos.z);
		OutputDebugStringA(buffer);
	}

	for (int32 i = 0; i < length; ++i)
	{

		if (i == playerID)
			continue;

		if (GET_SINGLE(CreatureManager)->GetCreatures(i) == nullptr)
			continue;

 
		Vec3 targetPos = GET_SINGLE(CreatureManager)->GetCreatures(i)->location.position;
		float radius = 15.f; // 하드코딩이긴한데 

		// WorldSpace에서 연산
		float distance = distance = (detectionPoint - targetPos).Length();
		if ( distance > radius)
			continue;



		if (distance < minDistance)
		{
			minDistance = distance;
			picked = i;
			{
				char buffer[100];
				sprintf_s(buffer, "distance : %d \n", (int)distance);
				OutputDebugStringA(buffer);
			}
		}
	}
	if (picked != 0)
	{
		Vec3 tPos = GET_SINGLE(CreatureManager)->GetCreatures(picked)->location.position;
		char buffer[100];
		sprintf_s(buffer, "targetPos : %d, %d, %d \n", (int)tPos.x, (int)tPos.y, (int)tPos.z);
		OutputDebugStringA(buffer);
	}

	return picked;

}

uint32 Player::Pick()
{
	int32 length = GET_SINGLE(CreatureManager)->GetSize();
	int32 playerID = GET_SINGLE(CreatureManager)->GetPlayerID();
	float minDistance = FLT_MAX;
	uint32 picked = 0;

	Vec3 rayOrigin = GET_SINGLE(CreatureManager)->GetCreatures(playerID)->location.position;
	Vec3 rayDir = GetTransform()->GetLook();
	rayDir.Normalize();

	for (int32 i=0; i<length; ++i)
	{

		if (i == playerID)
			continue;

		if (GET_SINGLE(CreatureManager)->GetCreatures(i) == nullptr)
			continue;

		Vec3 targetPos = GET_SINGLE(CreatureManager)->GetCreatures(i)->location.position;
		float radius = 20.f; // 하드코딩이긴한데 

		// WorldSpace에서 연산
		float distance = 0.f;
		if (CheckIntersects(rayOrigin, rayDir, targetPos, radius) == false)
			continue;


		char buffer[100];
		distance = (rayOrigin - targetPos).Length() - radius;
		sprintf_s(buffer, "distance : %d \n", (int)distance);
		OutputDebugStringA(buffer);

		//if (distance < minDistance)
		{
			minDistance = distance;
			picked = i;
		}
	}

	char buffer[100];
	sprintf_s(buffer, "targetID : %d \n", picked);
	OutputDebugStringA(buffer);

	return picked;
}

bool Player::CheckIntersects(Vec3 rayOrigin, Vec3 rayDir, Vec3 targetPos, float radius)
{
	Vec3 m = rayOrigin - targetPos;
	Vec3 u = rayDir;

	float a = u.Dot(u);
	float b = m.Dot(u);
	float c = m.Dot(m) - radius;

	return b * b - 4 * a * c >= 0;
}