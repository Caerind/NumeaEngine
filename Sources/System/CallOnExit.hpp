#ifndef NU_CALLONEXIT_HPP
#define NU_CALLONEXIT_HPP

#include <functional>

namespace nu
{

class CallOnExit
{
	public:
		using Func = std::function<void()>;

		CallOnExit(Func func = nullptr);
		CallOnExit(const CallOnExit&) = delete;
		CallOnExit(CallOnExit&&) = delete;
		~CallOnExit();
		
		void call();
		void reset(Func func = nullptr);
		bool isValid() const;
		Func getFunction() const;

		CallOnExit& operator=(const CallOnExit&) = delete;
		CallOnExit& operator=(CallOnExit&&) = default;

	private:
		Func mFunc;
};

} // namespace nu

#endif // NU_CALLONEXIT_HPP
