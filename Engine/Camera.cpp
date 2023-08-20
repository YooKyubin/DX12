#include "pch.h"
#include "Camera.h"
#include "Transform.h"
#include "Scene.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "Engine.h"
// static 변수 사용을 위한 구현부에서 선언
Matrix Camera::S_MatView;
Matrix Camera::S_MatProjection;

Camera::Camera() : Component(COMPONENT_TYPE::CAMERA)
{
}

Camera::~Camera()
{
}

void Camera::FinalUpdate() // 실질적 행렬 계산 항목
{
	_matView = GetTransform()->GetLocalToWorldMatrix().Invert(); // 카메라의 월드 행렬의 역행렬 => view 행렬

	float width = static_cast<float>(GEngine->GetWindow().width);
	float height = static_cast<float>(GEngine->GetWindow().height);

	if (_type == PROJECTION_TYPE::PERSPECTIVE)
		// Matrix::의 함수를 사용하여 perspective fov를 구할수도 있지만 Matrix::함수는 오른손 법칙을 사용한다. 따라서 우리는 직접 만든다.
		_matProjection = ::XMMatrixPerspectiveFovLH(_fov, width / height, _near, _far);
	else
		_matProjection = ::XMMatrixOrthographicLH(width * _scale, height * _scale, _near, _far);

	_frustum.FinalUpdate();
}

void Camera::Render()
{
	S_MatView = _matView;
	S_MatProjection = _matProjection;

	shared_ptr<Scene> scene = GET_SINGLE(SceneManager)->GetActiveScene();

	// TODO : Layer 구분
	const vector<shared_ptr<GameObject>>& gameObjects = scene->GetGameObjects();

	for (auto& gameObject : gameObjects)
	{
		if (gameObject->GetMeshRenderer() == nullptr)
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

		gameObject->GetMeshRenderer()->Render();
	}
}