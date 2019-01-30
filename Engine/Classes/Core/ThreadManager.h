#pragma once

#include "Core/EngineCore.h"

#include <atomic>
#include <mutex>

namespace MARS
{
	inline namespace THREAD
	{

	class SpinLock
	{
	public:

		void Lock();

		void Unlock();

		bool TryLock();

	private:

		std::atomic_flag _Lock = ATOMIC_FLAG_INIT;
	};


	class ThreadSafeManager
	{
	public:

		void Lock();
		void Unlock();
		bool TryLock();

		static void StaticLock();
		static void StaticUnlock();

	protected:

		static std::mutex _StaticMutex;
		std::mutex _Lock;
	};
	}
}