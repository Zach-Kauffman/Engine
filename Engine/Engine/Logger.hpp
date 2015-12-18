#pragma once

#include <cstddef>
#include <string>
#include <ostream>
#include <fstream>
#include <iomanip>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/sources/basic_logger.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/attributes/scoped_attribute.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>


//reserved namespaces
namespace logging = boost::log;
namespace src = boost::log::sources;
namespace expr = boost::log::expressions;
namespace sinks = boost::log::sinks;
namespace attrs = boost::log::attributes;
namespace keywords = boost::log::keywords;

// We define our own severity levels
enum severity_level
{
	DEBUG,
	INFO,
	WARNING,
	ERROR,
	FATAL
};

//attributes that can be set in logs are defined here
BOOST_LOG_ATTRIBUTE_KEYWORD(line_id, "LineID", unsigned int)
BOOST_LOG_ATTRIBUTE_KEYWORD(severity, "Severity", severity_level)
BOOST_LOG_ATTRIBUTE_KEYWORD(tag_attr, "Tag", std::string)
BOOST_LOG_ATTRIBUTE_KEYWORD(scope, "Scope", attrs::named_scope::value_type)
BOOST_LOG_ATTRIBUTE_KEYWORD(timeline, "Timeline", attrs::timer::value_type)

namespace logger
{
	//sets level for maximum level of output ex (level of INFO would not output DEBUG level statements)
	inline void setSeverityLevel(const severity_level &newLevel)
	{
		logging::core::get()->set_filter(expr::attr<severity_level>("Severity") >= newLevel);
	}

	//wrapper to return severity logger
	inline src::severity_logger<severity_level> getSLogger() //should return standard ref to class memeber?s 
	{
		src::severity_logger<severity_level> sl;
		return sl;
	}

	//initialization function
	inline void init()
	{
		typedef sinks::synchronous_sink< sinks::text_ostream_backend > text_sink;
		boost::shared_ptr< text_sink > sink = boost::make_shared< text_sink >();

		sink->locked_backend()->add_stream(
			boost::make_shared< std::ofstream >("sample.log"));

		sink->set_formatter	//setting formatting for log output based on attributes
			(
			expr::stream
			<< std::dec << std::setw(8) << std::setfill('0') << line_id << std::dec << std::setfill(' ')	//output types hardcoded here ie(std::dec)
			<< ": <" << severity << ">\t"
			<< "(" << scope << ") "
			<< expr::if_(expr::has_attr(tag_attr))
			[
				expr::stream << "[" << tag_attr << "] "
			]
		<< expr::if_(expr::has_attr(timeline))
			[
				expr::stream << "[" << timeline << "] "
			]
		<< expr::smessage
			);

		logging::core::get()->add_sink(sink);

		// Add attributes
		logging::add_common_attributes();
		logging::core::get()->add_global_attribute("Scope", attrs::named_scope());
	}
}




