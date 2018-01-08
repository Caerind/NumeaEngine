#include "Camera.hpp"

namespace nu
{

Camera::Camera(ProjectionMode projMode)
{
	perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	ortho(0.0f, 0.0f, 0.0f, 0.0f, 0.1f, 100.0f);
	lookAt(Vector3f::zero(), Vector3f::zero());
	mProjectionMode = projMode;
}

Camera::~Camera()
{
}

const Matrix4f& Camera::getViewProjectionMatrix() const
{
	if (!mViewProjectionUpdated)
	{
		mViewProjection = getProjectionMatrix() * getViewMatrix();
		mViewProjectionUpdated = true;
	}
	return mViewProjection;
}

void Camera::setProjectionMode(ProjectionMode projMode)
{
	mProjectionMode = projMode;
	updateProjection();
}

Camera::ProjectionMode Camera::getProjectionMode() const
{
	return mProjectionMode;
}

const Matrix4f& Camera::getProjectionMatrix() const
{
	if (!mProjectionUpdated)
	{
		if (mProjectionMode == ProjectionMode::Perspective)
		{
			mProjection.makePerspective(mFov, mRatio, mNear, mFar);
		}
		else if (mProjectionMode == ProjectionMode::Orthographic)
		{
			mProjection.makeOrtho(mLeft, mRight, mTop, mBottom, mNear, mFar);
		}
		mProjectionUpdated = true;
	}
	return mProjection;
}

void Camera::perspective(F32 fov, F32 ratio, F32 near, F32 far)
{
	mProjectionMode = ProjectionMode::Perspective;
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

F32 Camera::getFOV() const
{
	return mFov;
}

F32 Camera::getRatio() const
{
	return mRatio;
}

F32 Camera::getNear() const
{
	return mNear;
}

F32 Camera::getFar() const
{
	return mFar;
}

void Camera::ortho(F32 left, F32 right, F32 top, F32 bottom, F32 zNear, F32 zFar)
{
	mProjectionMode = ProjectionMode::Orthographic;
	mLeft = left;
	mRight = right;
	mTop = top;
	mBottom = bottom;
	updateProjection();
}

void Camera::setLeft(F32 left)
{
	mLeft = left;
	updateProjection();
}

void Camera::setRight(F32 right)
{
	mRight = right;
	updateProjection();
}

void Camera::setTop(F32 top)
{
	mTop = top;
	updateProjection();
}

void Camera::setBottom(F32 bottom)
{
	mBottom = bottom;
	updateProjection();
}

F32 Camera::getLeft() const
{
	return mLeft;
}

F32 Camera::getRight() const
{
	return mRight;
}

F32 Camera::getTop() const
{
	return mTop;
}

F32 Camera::getBottom() const
{
	return mBottom;
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
	mViewProjectionUpdated = false;
}

void Camera::updateView()
{
	mViewUpdated = false;
	mViewProjectionUpdated = false;
}

} // namespace nu
