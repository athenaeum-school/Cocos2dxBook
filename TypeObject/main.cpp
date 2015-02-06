//
//  main.cpp
//  Sample Design Pattern
//
//  Created by athenaeum on 2015/01/30.
//  Copyright (c) 2015年 Matsumura Soyu KK. All rights reserved.
//

#include <iostream>
#include "TypeObject.h"
#include "ObjectParser.h"

int main(int argc, const char * argv[])
{

    std::vector<GameObject*> pObjects(1);
    
    EnemyType* enemyType = new EnemyType(100);
    Enemy* enemy = enemyType->createEnemy();
    
    pObjects.push_back(enemy);
    ConfigParser* cp = new ConfigParser();
    cp->parseConfig("config.xml", &pObjects);
    Enemy* enemy0 = (Enemy*) pObjects.back();
    
    return 0;
}

