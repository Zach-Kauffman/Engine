#pragma once
#include <boost/thread.hpp>
#include "../NameSearchable/NameSearchable.hpp"

class ThreadManager : public NameSearchable
{
public:
	ThreadManager();
	~ThreadManager();

	boost::thread* getNewThread(std::string name);
	boost::thread* getThread(std::string name);
	void makeThread()

	void joinAllThreads();

private:

	boost::thread_group;
};

