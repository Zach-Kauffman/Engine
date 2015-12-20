#pragma once
#define RUN_TESTS
#define RUN_ALL
#ifdef RUN_TESTS

#include "Logger.hpp"

namespace testing
{

	class UnitTester
	{
	public:
		UnitTester();
		~UnitTester();
		void runTests();

	private:
		src::severity_logger<severity_level> testLogger;

		void utilities();
		void logging();
		void resourceGroup();
		void resourceManager();
		void INIParser();
	};

}
#endif