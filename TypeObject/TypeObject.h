//
//  TypeObject.h
//  Sample Design Pattern
//
//  Created by athenaeum on 2015/01/31.
//  Copyright (c) 2015年 Matsumura Soyu KK. All rights reserved.
//

#ifndef Sample_Design_Pattern_TypeObject_h
#define Sample_Design_Pattern_TypeObject_h

#include "GameObject.h"

class EnemyType;

class Enemy : public GameObject
{
public:
    Enemy(){}
    ~Enemy(){}
    Enemy(EnemyType* enemyType) {
    }
private:
    int m_health;
};

class EnemyType
{
public:
    Enemy* createEnemy() { return new Enemy(this); }
    
    EnemyType(int health)
    : health_(health)
    {}
    int getHealth() { return health_; }
    
private:
    int health_;
};

#endif
