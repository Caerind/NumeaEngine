#ifndef NU_DISTRIBUTION_HPP
#define NU_DISTRIBUTION_HPP

#include <functional>
#include <type_traits>

#include "Random.hpp"

namespace nu
{

namespace priv
{
	template <typename T>
	struct Constant
	{
		explicit Constant(T value)
			: value(value)
		{
		}

		T operator()() const
		{
			return value;
		}

		T value;
	};
} // namespace priv

template <typename T>
class Distribution
{
	public:
        Distribution(T constant)
        : mFactory(priv::Constant<T>(constant))
		{
		}

        Distribution(std::function<T()> function)
		: mFactory(function)
		{
		}

		T operator()() const
		{
			return mFactory();
		}

	private:
		std::function<T()> mFactory;
};

} // namespace nu

#endif // NU_DISTRIBUTION_HPP
