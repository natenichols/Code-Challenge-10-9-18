//Nathan Nichols
//ON Semiconductor Problem 1
//lockGuard.h implimentation

#ifndef LOCK_GUARD
#define LOCK_GUARD

namespace myGuard{
	template <class T_Mutex>
	class lock_guard
	{
		public:
		//mutex passed by reference and m_mu is assigned to the mutex upon constuction
		lock_guard<T_Mutex>(T_Mutex &toLock) : m_mu(toLock){
	
			//mutex is locked
			m_mu.lock();
		}
		~lock_guard<T_Mutex>(){
			
			//mutex is unlocked when lockguard leaves scope
			m_mu.unlock();
		}
		private:
		T_Mutex& m_mu;

	};
}
#endif

