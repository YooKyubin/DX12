#pragma once
#include <mutex>

enum class Act : int32
{
	IDLE,
	WALK,
	RUN,
	PICK,
	FALL_DOWN,
	INIT,
};

struct Location
{
	Vec3 position = Vec3(0.f);
	Vec3 rotation = Vec3(0.f);
};

struct Creature
{
	uint32 ID;
	Location location;
	bool isComputer = true;
	uint32 targetID = 0; // 0은 우선 아무것도 안넣어두기로 했습니다. 적당한 값이 없어서
	Act act = Act::IDLE;
};

class CreatureManager
{
	private:					
		CreatureManager() {}
		~CreatureManager() {}
	public:						
		static CreatureManager* volatile GetInstance()
		{							
			static CreatureManager instance;
			return &instance;			
		}

	void Init();
	void Update();

public:
	const shared_ptr<Creature> GetCreatures(uint32 idx) { return _creatures[idx]; }
	void SetCreature(shared_ptr<Creature> creature, int32 idx) { m.lock(); _creatures[idx] = creature; m.unlock(); }

	const int32 GetSize() { return _length; }
	const int32 GetPlayerID() { return _playerID; }
	void SetPlayerID(int32 id) { _playerID = id; }

	shared_ptr<Creature> GetSendData() { return sendData; }
	void SetSendData(shared_ptr<Creature> input) { sendData = input; }

private:
	std::mutex m;
	vector<shared_ptr<Creature>> _creatures;
	int32 _length = 101;
	int32 _playerID = 0;
	shared_ptr<Creature> sendData;
};

