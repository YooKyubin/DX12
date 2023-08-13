#pragma once
#include "Object.h"

enum class COMPONENT_TYPE : uint8
{
	TRANSFORM,
	MESH_RENDERER,
	CAMERA,
	LIGHT,
	// ...
	MONO_BEHAVIOUR, // �� �������� �ð�
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
	virtual ~Component(); // component�� �θ� Ŭ������ Ȱ��� ���̱� ������ �� virtual�� �����ؾ� �޸� ���� ������ �� �ִ�.

public:
	virtual void Awake() { }
	virtual void Start() { }
	virtual void Update() { }
	virtual void LateUpdate() { } // ��� ������Ʈ�� ���� ���� �������� ����ϱ� ����
	virtual void FinalUpdate() { } // �������� ��� �۾� �� ��¥ ������ ��� ���� �۾��� �ϴ� �κ�

public:
	COMPONENT_TYPE GetType() { return _type; }
	bool IsValid() { return _gameObject.expired() == false; }

	shared_ptr<GameObject> GetGameObject();
	shared_ptr<Transform> GetTransform();

private:
	friend class GameObject; // GameObject���Ը� private ���� ������ �ο� -> �ڽ��� �ش� ������Ʈ�� �������� ����
	void SetGameObject(shared_ptr<GameObject> gameObject) { _gameObject = gameObject; }


protected:
	COMPONENT_TYPE _type;
	weak_ptr<GameObject> _gameObject; // shared ptr�� ������ ��� _gameObject������ �ش� component Ŭ������ �����ϱ� ������ ��ȯ ������ �߻��� ref count �� 0�� ���� �ʴ� ��Ȳ�� �߻��Ѵ�.
};

