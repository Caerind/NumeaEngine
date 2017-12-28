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
		Camera();
		~Camera();

		void perspective(F32 fov, F32 ratio, F32 near, F32 far);

		void setNear(F32 near);
		void setFar(F32 far);
		void setFOV(F32 fov);
		void setRatio(F32 ratio);

		const Matrix4f& getProjectionMatrix() const;

		F32 getFOV() const;
		F32 getRatio() const;
		F32 getNear() const;
		F32 getFar() const;

		void lookAt(const Vector3f& position, const Vector3f& target, const Vector3f& up = Vector3f(0.0f, 1.0f, 0.0f));

		void setPosition(const Vector3f& position);
		void setTarget(const Vector3f& target);
		void setUp(const Vector3f& up);

		const Matrix4f& getViewMatrix() const;

		const Vector3f& getPosition() const;
		const Vector3f& getTarget() const;
		const Vector3f& getUp() const;

		void buildFrustum(Frustum& frustum) const;
		Frustum buildFrustum() const;

	protected:
		void updateProjection();
		void updateView();

	protected:	
		mutable Matrix4f mProjection;
		mutable Matrix4f mView;

		Vector3f mPosition;
		Vector3f mTarget;
		Vector3f mUp;

		F32 mFov;
		F32 mRatio;
		F32 mNear;
		F32 mFar;

		mutable bool mProjectionUpdated;
		mutable bool mViewUpdated;
};

} // namespace nu

#endif // NU_CAMERA_HPP