#include "pch.h"
#include "Camera.h"
#include "Transform.h"
#include "Scene.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "Engine.h"
#include "Material.h"
#include "Shader.h"
#include "ParticleSystem.h"
#include "InstancingManager.h"
// static ���� ����� ���� �����ο��� ����
Matrix Camera::S_MatView;
Matrix Camera::S_MatProjection;

Camera::Camera() : Component(COMPONENT_TYPE::CAMERA)
{
	_width = static_cast<float>(GEngine->GetWindow().width);
	_height = static_cast<float>(GEngine->GetWindow().height);
}

Camera::~Camera()
{
}

void Camera::FinalUpdate() // ������ ��� ��� �׸�
{
	_matView = GetTransform()->GetLocalToWorldMatrix().Invert(); // ī�޶��� ���� ����� ����� => view ���

	if (_type == PROJECTION_TYPE::PERSPECTIVE)
		// Matrix::�� �Լ��� ����Ͽ� perspective fov�� ���Ҽ��� ������ Matrix::�Լ��� ������ ��Ģ�� ����Ѵ�. ���� �츮�� ���� �����.
		_matProjection = ::XMMatrixPerspectiveFovLH(_fov, _width / _height, _near, _far);
	else
		_matProjection = ::XMMatrixOrthographicLH(_width * _scale, _height * _scale, _near, _far);

	_frustum.FinalUpdate();
}

void Camera::SortGameObject()
{
	shared_ptr<Scene> scene = GET_SINGLE(SceneManager)->GetActiveScene();
	const vector<shared_ptr<GameObject>>& gameObjects = scene->GetGameObjects();

	_vecForward.clear(); // ���� �����ӿ��� ����ϴ� �͵��� �����ֱ�
	_vecDeferred.clear();
	_vecParticle.clear();

	for (auto& gameObject : gameObjects)
	{
		if (gameObject->GetMeshRenderer() == nullptr && gameObject->GetParticleSystem() == nullptr)
			continue;

		if (IsCulled(gameObject->GetLayerIndex()))
			continue;

		if (gameObject->GetCheckFrustum())
		{
			if (_frustum.ContainsSphere(
				gameObject->GetTransform()->GetWorldPosition(),
				gameObject->GetTransform()->GetBoundingSphereRadius()) == false)
			{
				continue;
			}
		}

		if (gameObject->GetMeshRenderer()) // meshRenderer�� �ִ� ���� ������Ʈ
		{
			SHADER_TYPE shaderType = gameObject->GetMeshRenderer()->GetMaterial()->GetShader()->GetShaderType();
			switch (shaderType)
			{
			case SHADER_TYPE::DEFERRED:
				_vecDeferred.push_back(gameObject);
				break;
			case SHADER_TYPE::FORWARD:
				_vecForward.push_back(gameObject);
				break;
			}
		}
		else // �Ϲ� ��ƼŬ
		{
			_vecParticle.push_back(gameObject);
		}
	}
}

void Camera::SortShadowObject()
{
	shared_ptr<Scene> scene = GET_SINGLE(SceneManager)->GetActiveScene();
	const vector<shared_ptr<GameObject>>& gameObjects = scene->GetGameObjects();

	_vecShadow.clear();

	for (auto& gameObject : gameObjects)
	{
		if (gameObject->GetMeshRenderer() == nullptr)
			continue;

		if (gameObject->IsStatic()) // static ������Ʈ�� �̸� �׸��ڸ� ����ϸ� �ȴ�. ���� �ǽð��� �� �ʿ����
			continue;

		if (IsCulled(gameObject->GetLayerIndex()))
			continue;

		if (gameObject->GetCheckFrustum())
		{
			if (_frustum.ContainsSphere(
				gameObject->GetTransform()->GetWorldPosition(),
				gameObject->GetTransform()->GetBoundingSphereRadius()) == false)
			{
				continue;
			}
		}

		_vecShadow.push_back(gameObject);
	}
}

void Camera::Render_Deferred()
{
	S_MatView = _matView;
	S_MatProjection = _matProjection;

	GET_SINGLE(InstancingManager)->Render(_vecDeferred);
}

void Camera::Render_Forward()
{
	S_MatView = _matView;
	S_MatProjection = _matProjection;

	GET_SINGLE(InstancingManager)->Render(_vecForward);

	for (auto& gameObject : _vecParticle)
	{
		gameObject->GetParticleSystem()->Render();
	}
}

void Camera::Render_Shadow()
{
	S_MatView = _matView;
	S_MatProjection = _matProjection;

	for (auto& gameObject : _vecShadow)
	{
		gameObject->GetMeshRenderer()->RenderShadow();
	}
}