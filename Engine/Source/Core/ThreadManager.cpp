#include "Core/ThreadManager.h"

namespace MARS
{
	inline namespace THREAD
	{
		void SpinLock::Lock()
		{
			while (!TryLock())
			{
			}
		}

		void SpinLock::Unlock()
		{
			_Lock.clear(std::memory_order_release);
		}

		bool SpinLock::TryLock()
		{
			return !_Lock.test_and_set(std::memory_order_acquire);
		}

		/*||===================================================================*/
		/*|| Begin Thread Manager                                                             
		/*||===================================================================*/
	
		std::mutex ThreadSafeManager::_StaticMutex;
	
		void ThreadSafeManager::Lock()
		{
			_Lock.lock();
		}

		void ThreadSafeManager::Unlock()
		{
			_Lock.unlock();
		}

		bool ThreadSafeManager::TryLock()
		{
			return _Lock.try_lock();
		}

		void ThreadSafeManager::StaticLock()
		{
			_StaticMutex.lock();
		}

		void ThreadSafeManager::StaticUnlock()
		{
			_StaticMutex.unlock();
		}
	}
}