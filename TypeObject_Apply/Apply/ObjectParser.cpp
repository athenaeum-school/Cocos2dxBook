/*
* ObjectParser.cpp
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#include "ObjectParser.h"
#include "Enemy.h"
#include "ObjectManager.h"

USING_NS_CC;
using namespace std;
using namespace tinyxml2;

bool ConfigParser::parseConfig(const char *configFile)
{
	TiXmlDocument xmlDoc;
	xmlDoc.LoadFile(configFile);
	std::cout << xmlDoc.ErrorDesc() << endl;

	TiXmlElement* pRoot = xmlDoc.RootElement();
	TiXmlElement* pConfigRoot = 0;
	for (TiXmlElement* el = pRoot->FirstChildElement(); el != NULL; el = el->NextSiblingElement())
	{
		if (el->Value() == string("LEVEL1"))
		{
			pConfigRoot = el;
			break;
		}
	}

	TiXmlElement* pObjectRoot = 0;
	for (TiXmlElement* el = pConfigRoot->FirstChildElement(); el != NULL; el = el->NextSiblingElement())
	{
		if (el->Value() == string("OBJECTS"))
		{
			pObjectRoot = el;
			break;
		}
	}

	parseObjects(pObjectRoot);
	return true;
}

void ConfigParser::parseObjects(TiXmlElement *pObjectRoot)
{
	for (TiXmlElement* el = pObjectRoot->FirstChildElement(); el != NULL; el = el->NextSiblingElement())
	{		
		if (el->Value() == string("object"))
		{
			int hp;
			int atkPower;
			double xPos;
			double yPos;
			int enemysType;
			string fileNameAfterImageID;
			string fileName;
			string id;

			el->Attribute("hp", &hp);
			el->Attribute("atkPower", &atkPower);
			el->Attribute("xPos", &xPos);
			el->Attribute("yPos", &yPos);
			el->Attribute("enemyType", &enemysType);
			fileNameAfterImageID = el->LastAttribute()->Value();

			for (TiXmlElement* el = pObjectRoot->FirstChildElement(); el != NULL; el = el->NextSiblingElement())
			{
				if (el->Value() == string("image"))
				{
					fileName = el->FirstAttribute()->Value();
					id = el->LastAttribute()->Value();
					if (fileNameAfterImageID == id)
					{
						fileNameAfterImageID = fileName;
					}
				}
			}
			
			EnemyTypeObject* enemyTypeObject = new EnemyTypeObject(hp, atkPower, xPos, yPos, enemysType, fileNameAfterImageID);
			Enemy* enemy = enemyTypeObject->createEnemy();
			OM::getInstance()->addGameObject(enemy);
		}
	}
}