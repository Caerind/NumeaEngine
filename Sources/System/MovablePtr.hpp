#ifndef NU_MOVABLEPTR_HPP
#define NU_MOVABLEPTR_HPP

namespace nu
{
	
template<typename T>
class MovablePtr
{
	public:
		MovablePtr(T* value = nullptr);
		MovablePtr(const MovablePtr&) = default;
		MovablePtr(MovablePtr&& ptr) noexcept;
		~MovablePtr() = default;

		T* get() const;

		T* operator->() const;

		operator T*() const;

		MovablePtr& operator=(T* value);
		MovablePtr& operator=(const MovablePtr&) = default;
		MovablePtr& operator=(MovablePtr&& ptr) noexcept;

	private:
		T* mValue;
};	

template<typename T>
MovablePtr<T>::MovablePtr(T* value) 
	: mValue(value)
{
}

template<typename T>
MovablePtr<T>::MovablePtr(MovablePtr&& ptr) noexcept 
	: mValue(ptr.mValue)
{
	ptr.m_value = nullptr;
}

template<typename T>
inline T* MovablePtr<T>::get() const
{
	return mValue;
}

template<typename T>
T* MovablePtr<T>::operator->() const
{
	return mValue;
}

template<typename T>
MovablePtr<T>::operator T*() const
{
	return mValue;
}

template<typename T>
inline MovablePtr<T>& MovablePtr<T>::operator=(T* value)
{
	mValue = value;
	return *this;
}

template<typename T>
MovablePtr<T>& MovablePtr<T>::operator=(MovablePtr&& ptr) noexcept
{
	std::swap(mValue, ptr.mValue);
	return *this;
}
	
} // namespace nu

#endif // NU_MOVABLEPTR_HPP
