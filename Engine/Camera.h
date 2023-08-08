#pragma once
#include "Component.h"

enum class PROJECTION_TYPE
{
	PERSPECTIVE,
	ORTHOGRAPHIC,
};

class Camera : public Component
{
public:
	Camera();
	virtual ~Camera();

	virtual void FinalUpdate() override;
	void Render();


private:
	PROJECTION_TYPE _type = PROJECTION_TYPE::PERSPECTIVE;

	float _near = 1.f;
	float _far = 1000.f;
	float _fov = XM_PI / 4.f; // 45 degree
	float _scale = 1.f; // 직교투영에서 활용

	Matrix _matView = {};
	Matrix _matProjection = {};

public:
	// TEMP
	static Matrix S_MatView;
	static Matrix S_MatProjection;
};

