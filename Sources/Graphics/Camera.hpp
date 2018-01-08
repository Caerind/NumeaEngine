#ifndef NU_CAMERA_HPP
#define NU_CAMERA_HPP

#include "../Math/Matrix4.hpp"
#include "../Math/Frustum.hpp"

// TODO : Add Transformable
// TODO : Direction and distance
// TODO : FreeCam

namespace nu
{

class Camera
{
	public:
		enum ProjectionMode
		{
			Perspective = 0,
			Orthographic
		};

	public:
		Camera(ProjectionMode projMode = ProjectionMode::Perspective);
		~Camera();

		const Matrix4f& getViewProjectionMatrix() const;

		void setProjectionMode(ProjectionMode projMode);
		ProjectionMode getProjectionMode() const;

		const Matrix4f& getProjectionMatrix() const;

		void perspective(F32 fov, F32 ratio, F32 near, F32 far);
		void setNear(F32 near);
		void setFar(F32 far);
		void setFOV(F32 fov);
		void setRatio(F32 ratio);
		F32 getFOV() const;
		F32 getRatio() const;
		F32 getNear() const;
		F32 getFar() const;

		void ortho(F32 left, F32 right, F32 top, F32 bottom, F32 zNear, F32 zFar);
		void setLeft(F32 left);
		void setRight(F32 right);
		void setTop(F32 top);
		void setBottom(F32 bottom);
		F32 getLeft() const;
		F32 getRight() const;
		F32 getTop() const;
		F32 getBottom() const;

		const Matrix4f& getViewMatrix() const;

		void lookAt(const Vector3f& position, const Vector3f& target, const Vector3f& up = Vector3f(0.0f, 1.0f, 0.0f));
		void setPosition(const Vector3f& position);
		void setTarget(const Vector3f& target);
		void setUp(const Vector3f& up);
		const Vector3f& getPosition() const;
		const Vector3f& getTarget() const;
		const Vector3f& getUp() const;

		void buildFrustum(Frustum& frustum) const;
		Frustum buildFrustum() const;

	protected:
		void updateProjection();
		void updateView();

	protected:
		mutable Matrix4f mViewProjection;
		mutable Matrix4f mProjection;
		mutable Matrix4f mView;

		Vector3f mPosition;
		Vector3f mTarget;
		Vector3f mUp;

		F32 mFov;
		F32 mRatio;
		F32 mNear;
		F32 mFar;

		F32 mLeft;
		F32 mRight;
		F32 mTop;
		F32 mBottom;

		ProjectionMode mProjectionMode;

		mutable bool mViewProjectionUpdated;
		mutable bool mProjectionUpdated;
		mutable bool mViewUpdated;
};

} // namespace nu

#endif // NU_CAMERA_HPP