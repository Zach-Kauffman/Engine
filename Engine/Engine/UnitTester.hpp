#pragma once

#include "Defines.hpp"	//global #defines

#define RUN_ALL
#ifdef RUN_TESTS

#include "Logger.hpp"
#include <string>
#include <vector>

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