#pragma once
#include "Component.h"

class Mesh;
class Material;

class MeshRenderer : public Component
{
public:
	MeshRenderer();
	virtual ~MeshRenderer();

	void SetMesh(shared_ptr<Mesh> mesh) { _mesh = mesh; }
	void SetMaterial(shared_ptr<Material> material) { _material = material; }

	virtual void Update() override { Render(); } // 렌더는 보통 모든 업데이트(위치)가 끝난 뒤에 업데이트한다

	void Render();

private:
	shared_ptr<Mesh> _mesh;
	shared_ptr<Material> _material;
};

