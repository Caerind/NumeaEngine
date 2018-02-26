#include "Node.hpp"

namespace nu
{

Node::Node()
	: mParent(nullptr)
	, mChildren()
	, mLocalPosition(0.0f, 0.0f, 0.0f)
	, mLocalScale(1.0f, 1.0f, 1.0f)
	, mLocalRotation(Quaternionf::identity)
	, mLocalTransform(Matrix4f::identity)
	, mGlobalTransform(Matrix4f::identity)
	, mGlobalPosition(0.0f, 0.0f, 0.0f)
	, mLocalTransformUpdated(false)
	, mGlobalTransformUpdated(false)
{
}

void Node::attach(Node* child)
{
	if (child == nullptr || child->mParent == this)
	{
		return;
	}

	if (child->mParent != nullptr)
	{
		child->mParent->detach(child);
	}

	mChildren.push_back(child);

	child->mParent = this;
	child->invalidateNode();
}

void Node::detach(Node* child)
{
	auto itr = std::find(mChildren.begin(), mChildren.end(), child);
	if (itr != mChildren.end())
	{
		mChildren.erase(itr);
	}

	if (child != nullptr)
	{
		child->mParent = nullptr;
		child->invalidateNode();
	}
}

bool Node::hasChildren() const
{
	return mChildren.size() > 0;
}

bool Node::hasParent() const
{
	return mParent != nullptr;
}

const Vector3f& Node::getPosition() const
{
	return mLocalPosition;
}

const Vector3f& Node::getScale() const
{
	return mLocalScale;
}

const Quaternionf& Node::getRotation() const
{
	return mLocalRotation;
}

void Node::setPosition(F32 x, F32 y, F32 z)
{
	mLocalPosition.set(x, y, z);
	mLocalTransformUpdated = false;
	invalidateNode();
}

void Node::setPosition(const Vector3f& position)
{
	mLocalPosition.set(position);
	mLocalTransformUpdated = false;
	invalidateNode();
}

void Node::setScale(F32 s)
{
	mLocalScale.set(s);
	mLocalTransformUpdated = false;
	invalidateNode();
}

void Node::setScale(F32 x, F32 y, F32 z)
{
	mLocalScale.set(x, y, z);
	mLocalTransformUpdated = false;
	invalidateNode();
}

void Node::setScale(const Vector3f& scale)
{
	mLocalScale.set(scale);
	mLocalTransformUpdated = false;
	invalidateNode();
}

void Node::setRotation(const Quaternionf& rotation)
{
	mLocalRotation.set(rotation);
	mLocalTransformUpdated = false;
	invalidateNode();
}

void Node::move(F32 x, F32 y, F32 z)
{
	mLocalPosition += Vector3f(x, y, z);
	mLocalTransformUpdated = false;
	invalidateNode();
}

void Node::move(const Vector3f& movement)
{
	mLocalPosition += movement;
	mLocalTransformUpdated = false;
	invalidateNode();
}

void Node::scale(F32 s)
{
	mLocalScale *= s;
	mLocalTransformUpdated = false;
	invalidateNode();
}

void Node::scale(F32 x, F32 y, F32 z)
{
	mLocalScale *= Vector3f(x, y, z);
	mLocalTransformUpdated = false;
	invalidateNode();
}

void Node::scale(const Vector3f& scale)
{
	mLocalScale *= scale;
	mLocalTransformUpdated = false;
	invalidateNode();
}

void Node::rotate(const Quaternionf& rotation)
{
	mLocalRotation *= rotation;
	mLocalTransformUpdated = false;
	invalidateNode();
}

const Matrix4f& Node::getLocalTransform() const
{
	ensureUpdateLocalTransform();
	return mLocalTransform;
}

const Matrix4f& Node::getGlobalTransform() const
{
	ensureUpdateGlobalTransform();
	return mGlobalTransform;
}

const Vector3f& Node::getGlobalPosition() const
{
	ensureUpdateGlobalTransform();
	return mGlobalPosition;
}

void Node::ensureUpdateLocalTransform() const
{
	if (!mLocalTransformUpdated)
	{
		updateLocalTransform();
	}
}

void Node::ensureUpdateGlobalTransform() const
{
	if (!mLocalTransformUpdated || !mGlobalTransformUpdated)
	{
		updateGlobalTransform();
	}
}

void Node::invalidateNode()
{
	mGlobalTransformUpdated = false;
	for (Node* child : mChildren)
	{
		child->invalidateNode();
	}
	onNodeInvalidation(this);
}

void Node::updateLocalTransform() const
{
	mLocalTransform.makeTransform(mLocalPosition, mLocalRotation, mLocalScale);
	mLocalTransformUpdated = true;
}

void Node::updateGlobalTransform() const
{
	ensureUpdateLocalTransform();
	if (hasParent())
	{
		mGlobalTransform.set(mParent->getGlobalTransform() * mLocalTransform);
		mGlobalPosition.set(mGlobalTransform * Vector3f::zero);
	}
	else
	{
		mGlobalTransform.set(mLocalTransform);
		mGlobalPosition.set(mLocalPosition);
	}
	mGlobalTransformUpdated = true;
}

} // namespace nu
