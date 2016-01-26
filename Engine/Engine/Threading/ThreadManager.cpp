#include "ThreadManager.hpp"


ThreadManager::ThreadManager()
{
}


ThreadManager::~ThreadManager()
{
	joinAllThreads();
}


void ThreadManager::joinAllThreads()
{
	for (unsigned int i = 0; i < threads.size(); i++)
	{
		if (threads[i].joinable())
		{
			threads[i].join();
		}
	}
}