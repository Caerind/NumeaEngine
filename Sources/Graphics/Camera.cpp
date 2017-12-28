#include "Camera.hpp"

namespace nu
{

Camera::Camera()
{
	perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	lookAt(Vector3f::zero(), Vector3f::zero());
}

Camera::~Camera()
{
}

void Camera::perspective(F32 fov, F32 ratio, F32 near, F32 far)
{
	mFov = fov;
	mRatio = ratio;
	mNear = near;
	mFar = far;
	updateProjection();
}

void Camera::setNear(F32 near)
{
	mNear = near;
	updateProjection();
}

void Camera::setFar(F32 far)
{
	mFar = far;
	updateProjection();
}

void Camera::setFOV(F32 fov)
{
	mFov = fov;
	updateProjection();
}

void Camera::setRatio(F32 ratio)
{
	mRatio = ratio;
	updateProjection();
}

const Matrix4f& Camera::getProjectionMatrix() const
{
	if (!mProjectionUpdated)
	{
		mProjection.makePerspective(mFov, mRatio, mNear, mFar);
		mProjectionUpdated = true;
	}
	return mProjection;
}

F32 Camera::getNear() const
{
	return mNear;
}

F32 Camera::getFar() const
{
	return mFar;
}

F32 Camera::getFOV() const
{
	return mFov;
}

F32 Camera::getRatio() const
{
	return mRatio;
}

void Camera::lookAt(const Vector3f& position, const Vector3f& target, const Vector3f& up)
{
	mPosition = position;
	mTarget = target;
	mUp = up;
	updateView();
}

void Camera::setPosition(const Vector3f& position)
{
	mPosition = position;
	updateView();
}

void Camera::setTarget(const Vector3f& target)
{
	mTarget = target;
	updateView();
}

void Camera::setUp(const Vector3f& up)
{
	mUp = up;
	updateView();
}

const Matrix4f& Camera::getViewMatrix() const
{
	if (!mViewUpdated)
	{
		mView.makeLookAt(mPosition, mTarget, mUp);
		mViewUpdated = true;
	}
	return mView;
}

const Vector3f& Camera::getPosition() const
{
	return mPosition;
}

const Vector3f& Camera::getTarget() const
{
	return mTarget;
}

const Vector3f& Camera::getUp() const
{
	return mUp;
}

void Camera::buildFrustum(Frustum& frustum) const
{
	frustum.build(mFov, mRatio, mNear, mFar, mPosition, mTarget, mUp);
}

Frustum Camera::buildFrustum() const
{
	Frustum frustum;
	frustum.build(mFov, mRatio, mNear, mFar, mPosition, mTarget, mUp);
	return frustum;
}

void Camera::updateProjection()
{
	mProjectionUpdated = false;
}

void Camera::updateView()
{
	mViewUpdated = false;
}

} // namespace nu
