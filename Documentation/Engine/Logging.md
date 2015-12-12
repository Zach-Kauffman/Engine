# How to log stuff

Step 1 is to include Logger.h. This file will include all of the necessary boost libraries and has some handy built-in functionality.

### Creating a logger object

First create a severity_logger object in your scope.
This can be done in a few ways.
Through the wrapper... 

	auto logger_object = logger::getSLogger();
	
or manually...
	
	src::severity_logger<severity_level> logger_object;
			
### Setting the log level

Logs are creating with severity levels depending on their importance. The levels we have build in are as follows:

* DEBUG
* INFO
* WARNING
* ERROR
* FATAL

Setting a maximum levels tells the logger to only output logs of that level or more important.
Setting the level is done through one command:

	logger::setSeverityLevel(<YOUR_NEW_SEVERITY_LEVEL>);
	
### Creating Logs

Now we get to the good stuff. Creating a basic log is simple.

	BOOST_LOG(logger_object, ERROR) << "YOUR TEXT HERE";

This creates a new log with the severity level of an error and the text "YOUR TEXT HERE".
You can also input variables into logs, assuming they support the << operator.
	
	int var = 1;
	BOOST_LOG_SEV(logger_object, ERROR) << "THIS IS A VARIABLE " << var;
	
This log would also be a error level and the output would be "THIS IS A VARIABLE 1";

### Adding extra information to logs

### Notes and Debugging

###### Make sure you call the ` logger::init() ` function from somewhere
###### Make sure you `#include "Logger.h"`
