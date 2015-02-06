//
//  ObjectParser.cpp
//  Sample Design Pattern
//
//  Created by athenaeum on 2015/01/31.
//  Copyright (c) 2015年 Matsumura Soyu KK. All rights reserved.
//

#include "ObjectParser.h"
#include "TypeObject.h"

using namespace std;

ConfigParser::ConfigParser() {
    
}

ConfigParser::~ConfigParser() {
    
}

bool ConfigParser::parseConfig(const char *configFile, vector<GameObject *> *pObjects)
{
    TiXmlDocument xmlDoc;
    xmlDoc.LoadFile(configFile);
    std::cout << xmlDoc.ErrorDesc() << endl;
    
    TiXmlElement* pRoot = xmlDoc.RootElement();
    TiXmlElement* pConfigRoot = 0;
    for(TiXmlElement* el = pRoot->FirstChildElement(); el != NULL; el = el->NextSiblingElement())
    {
        if(el->Value() == string("NORMAL"))
        {
            pConfigRoot = el;
			break;
        }
    }
    
    TiXmlElement* pObjectRoot = 0;
    for(TiXmlElement* el = pConfigRoot->FirstChildElement(); el != NULL; el = el->NextSiblingElement())
    {
        if(el->Value() == string("OBJECTS"))
        {
            pObjectRoot = el;
			break;
        }
    }
    
    parseObjects(pObjectRoot, pObjects);
    return true;
}

void ConfigParser::parseObjects(TiXmlElement *pObjectRoot, std::vector<GameObject *> *pObjects)
{
    
    for(TiXmlElement* el = pObjectRoot->FirstChildElement(); el != NULL; el = el->NextSiblingElement())
    {
        int health;
        el->Attribute("health", &health);
        
        EnemyType* enemyType = new EnemyType(health);
        Enemy* enemy = enemyType->createEnemy();
        pObjects->push_back(enemy);
    }
}