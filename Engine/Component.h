#pragma once
#include "Object.h"

enum class COMPONENT_TYPE : uint8
{
	TRANSFORM,
	MESH_RENDERER,
	CAMERA,
	LIGHT,
	// ...
	MONO_BEHAVIOUR, // 꼭 마지막에 올것
	END,
};

enum
{
	FIXED_COMPONENT_COUNT = static_cast<uint8>(COMPONENT_TYPE::END) - 1
};

class GameObject;
class Transform;

class Component : public Object
{
public:
	Component(COMPONENT_TYPE type);
	virtual ~Component(); // component는 부모 클래스로 활용될 것이기 때문에 꼭 virtual로 선언해야 메모리 릭을 방지할 수 있다.

public:
	virtual void Awake() { }
	virtual void Start() { }
	virtual void Update() { }
	virtual void LateUpdate() { } // 모든 업데이트가 끝난 후의 시점에서 사용하기 위함
	virtual void FinalUpdate() { } // 엔진에서 모든 작업 후 진짜 마지막 행렬 관련 작업을 하는 부분

public:
	COMPONENT_TYPE GetType() { return _type; }
	bool IsValid() { return _gameObject.expired() == false; }

	shared_ptr<GameObject> GetGameObject();
	shared_ptr<Transform> GetTransform();

private:
	friend class GameObject; // GameObject에게만 private 접근 권한을 부여 -> 자신을 해당 컴포넌트의 주인으로 설정
	void SetGameObject(shared_ptr<GameObject> gameObject) { _gameObject = gameObject; }


protected:
	COMPONENT_TYPE _type;
	weak_ptr<GameObject> _gameObject; // shared ptr로 선언할 경우 _gameObject에서도 해당 component 클래스를 참조하기 때문에 순환 참조가 발생해 ref count 가 0이 되지 않는 상황이 발생한다.
};

