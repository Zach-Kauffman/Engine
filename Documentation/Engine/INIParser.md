# What is the purpose of INIParser?

INIParser handles the reading and writing .ini files. It can handle any data type or _maps_, as well as vectors of any given data type. 
.ini files allow us to transfer data (variables) from from file to file without using excessive #include statements.

# How do I use INIParser?

### 1. MAKE SURE THAT INIParser::hpp IS INCLUDED!

### 2. Declare a new INIParser class with the file path to your file (optional)

### 3. If you did not declare the file path yet, use INIParser::setFilePath( filePath ) 

### 4. If you would like to **READ** a file (which is not a _map_):

Set your variable equal to INIParser::readValue< string >( **EXAMPLE**.value ). If your file could not be loaded, readValue will return NULL.

**EXAMPLE**:

	int myInt = INIParser.readValue<std::string>( "CookieJar.remainingCookies" );
	
**RESULT**:

	myInt = CookieJar.remainingCookies

###	 If you would like to **WRITE** to a file (which is not a _map_):

Use INIParser::writeValue<variableType>("Header","Value")

**EXAMPLE**:

	INIParser.writeValue<std::string>("CookieJar","chocolateChipCookie");
	
**RESULT**:

	[CookieJar]
	chocolateChipCookie

###	 If you would like to **READ** a _map_:

Use INIParser::readMap(std::map< std::string, variableType* >& myMap)
You can also define a map and pass readMap() your map and nothing else, as shown.

**EXAMPLE**:

	std::map<std::string, Cookie*> myCookies;
	int chocolateChip = 1;
	myCookies["Chocolate"] = &chocolateChip;
	INIParser.readMap(myCookies);
	
**RESULT**:

	The value of chocolateChip is set to the value found in the .ini file.

###	 If you would like to **WRITE** to a _map_:

Use INIParser::writeMap(std::map < std::string, variableType* >& listOfValues)
You can also define a map and pass writeMap() your map and nothing else, as shown.

**EXAMPLE**:

	std::map<std::string, Cookie*> myCookies;
	int chocolateChip = 1;
	myCookies["Chocolate"] = &chocolateChip;
	INIParser.writeMap(myCookies);
	
**RESULT**:

	A map has been written to a .ini file.

###	 If you would like to **READ** a vector:

Set your vector equal to INIParser::readVector(const std::vector< std::string > &listOfValues), where listOfValues is a .ini file

**EXAMPLE**:

	CookieJar = INIParser::readVector(const std::vector<std::string> &listOfCookies);
	
**RESULT**:

	CookieJar now contains all Cookies listed in listOfCookies.
