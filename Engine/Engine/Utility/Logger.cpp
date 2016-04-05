#include "Logger.hpp"


// The operator puts a human-friendly representation of the severity level to the stream
std::ostream& operator<< (std::ostream& strm, severity_level level)
{
	static const char* strings[] =
	{
		"debug",
		"info",
		"warning",
		"error",
		"fatal"
	};

	if (static_cast< std::size_t >(level) < sizeof(strings) / sizeof(*strings))
		strm << strings[level];
	else
		strm << static_cast< int >(level);

	return strm;
}

void logger::setSeverityLevel(const severity_level& newLevel)
{
	logging::core::get()->set_filter(expr::attr<severity_level>("Severity") >= newLevel);
}

src::severity_logger<severity_level> logger::getSLogger()
{
	src::severity_logger<severity_level> sl;
	return sl;
}

void logger::init()
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

