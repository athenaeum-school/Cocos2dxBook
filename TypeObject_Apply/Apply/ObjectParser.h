/*
* ObjectParser.h
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#ifndef __WillYard__ObjectParser__
#define __WillYard__ObjectParser__

#include <iostream>
#include <vector>
#include "tinyxml.h"

class GameObject;

class ConfigParser
{
public:

	bool parseConfig(const char *configFile);
	
	ConfigParser() {}
	~ConfigParser() {}

private:

	void parseObjects(TiXmlElement *pObjectRoot);

};


#endif /* defined(__WillYard__ObjectParser__) */