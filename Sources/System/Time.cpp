#include "Time.hpp"

#if NU_PLATFORM_WINDOWS
	#include <windows.h>
#else
	#pragma message("SystemTime() not defined")
#endif

namespace nu
{

const Time Time::Zero(0LL);
const Time Time::Second(Time::TicksPerSecond);

Time::Time()
	: mTicks(0LL)
{
}

Time::Time(I64 ticks)
	: mTicks(ticks)
{
}

Time::Time(I32 hours, I32 minutes, I32 seconds)
{
	set(0, hours, minutes, seconds, 0, 0);
}

Time::Time(I32 days, I32 hours, I32 minutes, I32 seconds)
{
	set(days, hours, minutes, seconds, 0, 0);
}

Time::Time(I32 days, I32 hours, I32 minutes, I32 seconds, I32 milliseconds, I32 microseconds)
{
	set(days, hours, minutes, seconds, milliseconds, microseconds);
}

Time& Time::set(I64 ticks)
{
	mTicks = ticks;
	return *this;
}

Time& Time::set(I32 hours, I32 minutes, I32 seconds)
{
	return set(0, hours, minutes, seconds, 0, 0);
}

Time& Time::set(I32 days, I32 hours, I32 minutes, I32 seconds)
{
	return set(days, hours, minutes, seconds, 0, 0);
}

Time& Time::set(I32 days, I32 hours, I32 minutes, I32 seconds, I32 milliseconds, I32 microseconds)
{
	mTicks = 0;
	mTicks += days * TicksPerDay;
	mTicks += hours * TicksPerHour;
	mTicks += minutes * TicksPerMinute;
	mTicks += seconds * TicksPerSecond;
	mTicks += milliseconds / TicksPerMillisecond;
	mTicks += microseconds / TicksPerMicrosecond;
	return *this;
}

Time Time::operator+(const Time& time) const
{
	return Time(mTicks + time.mTicks);
}

Time& Time::operator+=(const Time& time)
{
	mTicks += time.mTicks;
	return *this;
}

Time Time::operator-() const
{
	return Time(-mTicks);
}

Time Time::operator-(const Time& time) const
{
	return Time(mTicks - time.mTicks);
}

Time& Time::operator-=(const Time& time)
{
	mTicks -= time.mTicks;
	return *this;
}

Time Time::operator*(F32 scalar) const
{
	return Time(I64(F32(mTicks) * scalar));
}

Time& Time::operator*=(F32 scalar)
{
	mTicks = I64(F32(mTicks) * scalar);
	return *this;
}

Time Time::operator/(F32 scalar) const
{
	assert(scalar != 0.0f);
	return Time(I64(F32(mTicks) / scalar));
}

Time& Time::operator/=(F32 scalar)
{
	assert(scalar != 0.0f);
	mTicks = I64(F32(mTicks) / scalar);
	return *this;
}

Time Time::operator%(const Time& time) const
{
	return Time(mTicks % time.mTicks);
}

Time& Time::operator%=(const Time& time)
{
	mTicks %= time.mTicks;
	return *this;
}

bool Time::operator==(const Time& time) const
{
	return mTicks == time.mTicks;
}

bool Time::operator!=(const Time& time) const
{
	return mTicks != time.mTicks;
}

bool Time::operator>(const Time& time) const
{
	return mTicks > time.mTicks;
}

bool Time::operator>=(const Time& time) const
{
	return mTicks >= time.mTicks;
}

bool Time::operator<(const Time& time) const
{
	return mTicks < time.mTicks;
}

bool Time::operator<=(const Time& time) const
{
	return mTicks <= time.mTicks;
}

bool Time::isZero() const
{
	return mTicks == 0LL;
}

Time Time::getDuration() const
{
	return Time(mTicks >= 0 ? mTicks : -mTicks);
}

I32 Time::getDays() const
{
	return (I32)(mTicks / TicksPerDay);
}

I32 Time::getHours() const
{
	return (I32)((mTicks / TicksPerHour) % 24);
}

I32 Time::getMinutes() const
{
	return (I32)((mTicks / TicksPerMinute) % 60);
}

I32 Time::getSeconds() const
{
	return (I32)((mTicks / TicksPerSecond) % 60);
}

I32 Time::getMilliseconds() const
{
	return (I32)((mTicks / TicksPerMillisecond) % 1000);
}

I32 Time::getMicroseconds() const
{
	return (I32)((mTicks / TicksPerMicrosecond) % 1000);
}

I64 Time::getTicks() const
{
	return mTicks;
}

F32 Time::asSeconds() const
{
	return F32((double)mTicks / TicksPerSecond);
}

I32 Time::asMilliseconds() const
{
	return I32(mTicks / TicksPerMillisecond);
}

I64 Time::asMicroseconds() const
{
	return (mTicks / TicksPerMicrosecond);
}

Time Time::now()
{
	#if NU_PLATFORM_WINDOWS
		LARGE_INTEGER frequency;
		QueryPerformanceFrequency(&frequency);
		HANDLE currentThread = GetCurrentThread(); // Force the following code to run on first core (see http://msdn.microsoft.com/en-us/library/windows/desktop/ms644904(v=vs.85).aspx)
		DWORD_PTR previousMask = SetThreadAffinityMask(currentThread, 1);
		LARGE_INTEGER time; // Get the current time
		QueryPerformanceCounter(&time);
		SetThreadAffinityMask(currentThread, previousMask); // Restore the thread affinity
		return microseconds(1000000 * time.QuadPart / frequency.QuadPart);
	#endif
	return Time(0);
}

Time days(I32 amount)
{
	return Time(amount * Time::TicksPerDay);
}

Time hours(I32 amount)
{
	return Time(amount * Time::TicksPerHour);
}

Time minutes(I32 amount)
{
	return Time(amount * Time::TicksPerMinute);
}

Time seconds(F32 amount)
{
	return Time(I64(amount * F32(Time::TicksPerSecond)));
}

Time milliseconds(I32 amount)
{
	return Time(amount * Time::TicksPerMillisecond);
}

Time microseconds(I64 amount)
{
	return Time(amount * Time::TicksPerMicrosecond);
}

Clock::Clock()
	: mStart(Time::now())
{
}

Time Clock::getElapsedTime() const
{
	return Time::now() - mStart;
}

Time Clock::restart()
{
	Time now = Time::now();
	Time elapsed = now - mStart;
	mStart = now;
	return elapsed;
}

} // namespace nu
