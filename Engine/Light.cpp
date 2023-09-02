#include "pch.h"
#include "Light.h"
#include "Transform.h"
#include "Engine.h"
#include "Resources.h"

Light::Light() : Component(COMPONENT_TYPE::LIGHT)
{
}

Light::~Light()
{
}

void Light::FinalUpdate()
{
	_lightInfo.position = GetTransform()->GetWorldPosition();
}

void Light::Render()
{
	assert(_lightIndex >= 0);

	GetTransform()->PushData();

	_lightMaterial->SetInt(0, _lightIndex);
	_lightMaterial->PushGraphicsData();

	switch (static_cast<LIGHT_TYPE>(_lightInfo.lightType))
	{
	case LIGHT_TYPE::POINT_LIGHT:
	case LIGHT_TYPE::SPOT_LIGHT:
		float scale = 2 * _lightInfo.range; // 기본 radius는 0.5이다. 이를 lightinfo의 range로 만들기 위해
		GetTransform()->SetLocalScale(Vec3(scale, scale, scale));
		break;
	}

	_volumeMesh->Render();
}

void Light::SetLightType(LIGHT_TYPE type)
{
	_lightInfo.lightType = static_cast<int32>(type);

	switch (type)
	{
	case LIGHT_TYPE::DIRECTIONAL_LIGHT:
		_volumeMesh = GET_SINGLE(Resources)->Get<Mesh>(L"Rectangle");
		_lightMaterial = GET_SINGLE(Resources)->Get<Material>(L"DirLight");
		break;
	case LIGHT_TYPE::POINT_LIGHT:
		_volumeMesh = GET_SINGLE(Resources)->Get<Mesh>(L"Sphere");
		_lightMaterial = GET_SINGLE(Resources)->Get<Material>(L"PointLight");
		break;
	case LIGHT_TYPE::SPOT_LIGHT: // 제대로 하기 위해서는 원뿔 모양의 메쉬를 만들어야 한다.
		_volumeMesh = GET_SINGLE(Resources)->Get<Mesh>(L"Sphere");
		_lightMaterial = GET_SINGLE(Resources)->Get<Material>(L"PointLight");
		break;
	}
}