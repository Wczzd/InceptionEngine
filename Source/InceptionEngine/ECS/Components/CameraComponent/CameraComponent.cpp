
#include "CameraComponent.h"


namespace inceptionengine
{
	CameraComponent::CameraComponent(CameraSystem& system)
		:mSystem(system)
	{
	}

	CameraComponent::CameraComponent(CameraSystem& system, Vec4f position, Vec4f forward)
		:mSystem(system), mPosition(position), mForwardPoint(forward)
	{
		;
	}

	void CameraComponent::SetPosAndForward(Vec4f position, Vec4f forward)
	{
		mPosition = position;
		mForwardPoint = forward;
	}

	Matrix4x4f CameraComponent::CameraMatrix() const
	{
		auto worldPosition = mPosition;
		auto worldForward = mForwardPoint;

		return LookAt(Vec3f(worldPosition.x, worldPosition.y, worldPosition.z), Vec3f(worldForward.x, worldForward.y, worldForward.z), Vec3f(0.0f, 1.0f, 0.0f));
	}

	void CameraComponent::RotateHorizontal(float degree)
	{
		mPosition = Rotate(mPosition, degree, Vec3f(0.0f, 1.0f, 0.0f));
		mForwardPoint = Rotate(mForwardPoint, degree, Vec3f(0.0f, 1.0f, 0.0f));
	}

	void CameraComponent::RotateVertical(float degree)
	{
		auto lookAtDirection = mForwardPoint - mPosition;
		auto rotateionAxis = CrossProduct(Vec3f(lookAtDirection.x, lookAtDirection.y, lookAtDirection.z), Vec3f(0.0f, 1.0f, 0.0f));
		mPosition = Rotate(mPosition, degree, rotateionAxis);
		mForwardPoint = Rotate(mForwardPoint, degree, rotateionAxis);
	}

	void CameraComponent::PrintCameraPramameter()
	{
		std::cout << "position: " << VecToString(mPosition) << std::endl;
		std::cout << "position: " << VecToString(mForwardPoint) << std::endl;
	}

	void CameraComponent::LiftUp(float amount)
	{
		mPosition.y += amount;
		mForwardPoint.y += amount;
	}

	Vec3f CameraComponent::GetForwardVec() const
	{
		auto temp = Vec3f(mForwardPoint - mPosition);
		temp.y = 0;
		return NormalizeVec(temp);
	}
}