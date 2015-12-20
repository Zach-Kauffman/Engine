#include "UnitTester.hpp"
#ifdef RUN_TESTS



using namespace testing;

void UnitTester::runTests()
{
#ifdef RUN_ALL
	utilities();
	logging();
	resourceGroup();
	resourceManager();
	INIParser();
#elif
	#ifdef TEST_UTILITIES
		utilities();
	#endif
	#ifdef TEST_LOGGING
			logging();
	#endif
	#ifdef TEST_RESOURCE_GROUP
			resourceGroup();
	#endif
	#ifdef TEST_RESOURCE_MANAGER
			resourceMananager();
	#endif
	#ifdef TEST_INI_PARSER
			INIParser();
	#endif
#endif
}

//PRIVATE FUNCTIONS

void UnitTester::utilities()
{
#include "Utilities.hpp"

	BOOST_LOG_SEV(testLogger, INFO) << "Now testing: void util::swapChars(char& a, char& b);";
	char a = 'a', b = 'b';
	util::swapChars(a, b);
	if (a != 'b' || b != 'a') { BOOST_LOG_SEV(testLogger, ERROR) << "Input to util::swapChars failed."; }

	BOOST_LOG_SEV(testLogger, INFO) << "Now testing: std::string util::reverseString(const std::string& str);";
	if (util::reverseString("myString") != "gnirtSym") { BOOST_LOG_SEV(testLogger, ERROR) << "Input to util::reverseString failed.  IN: \"myString\""; }
	if (util::reverseString("MYSTRING ") != " GNIRTSYM") { BOOST_LOG_SEV(testLogger, ERROR) << "Input to util::reverseString failed.  IN: \"MYSTRING \""; }
	if (util::reverseString("aaaaaa") != "aaaaaa") { BOOST_LOG_SEV(testLogger, ERROR) << "Input to util::reverseString failed.  IN: \"aaaaaa\""; }
	if (util::reverseString("This Is An Extended TEST") != "TSET dednetxE nA sI sihT") { BOOST_LOG_SEV(testLogger, ERROR) << "Input to util::reverseString failed.  IN: \"This Is An Extended Test\""; }
	if (util::reverseString("\"\\\"Escape") != "epacsE\"\\\"") { BOOST_LOG_SEV(testLogger, ERROR) << "Input to util::reverseString failed.  IN: \"\"\\\"Escape\""; }

	BOOST_LOG_SEV(testLogger, INFO) << "Now testing: std::vector<std::string> splitStrAtSubstr(const std::string& str, const std::string& split)";
	std::vector<std::string> expected("One", "Two", "Three");
	std::vector<std::string> expected2("One", "Three");
	if (util::splitStrAtSubstr("One.Two.Three", ".") != expected) { BOOST_LOG_SEV(testLogger, ERROR) << "Input to util::splitStrAtSubstr failed. IN: \"One.Two.Three\", \".\""; }
	if (util::splitStrAtSubstr("One\"Two\"Three", "\"") != expected) { BOOST_LOG_SEV(testLogger, ERROR) << "Input to util::splitStrAtSubstr failed. IN: \"One\"Two\"Three\", \"\"\""; }
	if (util::splitStrAtSubstr("OneTwoThree", ".") != expected) { BOOST_LOG_SEV(testLogger, ERROR) << "Input to util::splitStrAtSubstr failed. IN: \"One.Two.Three\", \".\""; }
	if (util::splitStrAtSubstr("OneTwoThree", "Two") != expected) { BOOST_LOG_SEV(testLogger, ERROR) << "Input to util::splitStrAtSubstr failed. IN: \"OneTwoThree\", \"Two\""; }

}

void UnitTester::logging()
{
#include "Logger.hpp"
}

void UnitTester::resourceGroup()
{
#include "ResourceManager\ResourceGroup.hpp"
}

void UnitTester::resourceManager()
{
#include "ResourceManager\ResourceGroup.hpp"
}

void UnitTester::INIParser()
{
#include "INIParser.hpp"
}
#endif