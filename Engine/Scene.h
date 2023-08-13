#pragma once

class GameObject;

class Scene
{
public:
	void Awake();
	void Start();
	void Update();
	void LateUpdate();
	void FinalUpdate();

	void Render();
private:
	void PushLightData();

public:	
	void AddGameObject(shared_ptr<GameObject> gameObject);
	void RemoveGameObject(shared_ptr<GameObject> gameObject);

	const vector<shared_ptr<GameObject>>& GetGameObjects() { return _gameObjects; }
private:
	vector<shared_ptr<GameObject>> _gameObjects;
	// 유니티에서는 레이어를 사용해서 한 Scene 안에 있는 게임 오브젝트를 찾기 쉽도록 했다.
	// 레이어를 32개로 만들어 vector의 vector 혹은 vector의 array로 관리한다.	
};


