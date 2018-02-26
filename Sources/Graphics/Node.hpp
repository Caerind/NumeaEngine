#ifndef NU_NODE_HPP
#define NU_NODE_HPP

#include "../Math/Matrix4.hpp"
#include "../System/Signal.hpp"

namespace nu
{

class Node
{
	public:
		Node();

		void attach(Node* child);
		void detach(Node* child);
		bool hasChildren() const;
		bool hasParent() const;

		const Vector3f& getPosition() const;
		const Vector3f& getScale() const;
		const Quaternionf& getRotation() const;

		void setPosition(F32 x, F32 y, F32 z);
		void setPosition(const Vector3f& position);
		void setScale(F32 s);
		void setScale(F32 x, F32 y, F32 z);
		void setScale(const Vector3f& scale);
		void setRotation(const Quaternionf& rotation);

		void move(F32 x, F32 y, F32 z);
		void move(const Vector3f& movement);
		void scale(F32 s);
		void scale(F32 x, F32 y, F32 z);
		void scale(const Vector3f& scale);
		void rotate(const Quaternionf& rotation);

		const Matrix4f& getLocalTransform() const;
		const Matrix4f& getGlobalTransform() const;
		const Vector3f& getGlobalPosition() const;

		void ensureUpdateLocalTransform() const;
		void ensureUpdateGlobalTransform() const;

		// TODO : Convert position in Local/Global space

		NuSignal(onNodeInvalidation, const Node*);

	protected:
		virtual void invalidateNode();
		virtual void updateLocalTransform() const;
		virtual void updateGlobalTransform() const;

	private:
		Node* mParent;
		std::vector<Node*> mChildren;

		Vector3f mLocalPosition;
		Vector3f mLocalScale;
		Quaternionf mLocalRotation;
		mutable Matrix4f mLocalTransform;

		mutable Matrix4f mGlobalTransform;
		mutable Vector3f mGlobalPosition;

		mutable bool mLocalTransformUpdated;
		mutable bool mGlobalTransformUpdated;
		
};

} // namespace nu

#endif // NU_NODE_HPP