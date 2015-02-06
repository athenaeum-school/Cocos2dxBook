//
//  ObjectParser.h
//  Sample Design Pattern
//
//  Created by athenaeum on 2015/01/31.
//  Copyright (c) 2015年 Matsumura Soyu KK. All rights reserved.
//

#ifndef __Sample_Design_Pattern__ObjectParser__
#define __Sample_Design_Pattern__ObjectParser__

#include <iostream>
#include <vector>
#include "tinyxml.h"

class GameObject;

class ConfigParser
{
public:
    
    ConfigParser();
    ~ConfigParser();
    
    bool parseConfig(const char* configFile, std::vector<GameObject*> *pObjects);
    
private:
    
    void parseObjects(TiXmlElement* pObjectRoot, std::vector<GameObject*> *pObjects);

};

#endif /* defined(__Sample_Design_Pattern__ObjectParser__) */
