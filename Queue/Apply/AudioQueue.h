/*
* AudioQueue.h
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#ifndef __WillYard__AudioQueue__
#define __WillYard__AudioQueue__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

struct node
{
	std::string name;
	struct node *next;
};

class AudioQueue : public CocosDenshion::SimpleAudioEngine
{
public:

	void init();
	void enqueue(const std::string &name);
	void dequeue();
	void playAudio(const std::string &name);
	void playBGM();
	void stopAudio();

	AudioQueue();
	~AudioQueue();

private:

	node *front;
	node *tail;
	
};

#endif /*defined(__WillYard__AudioQueue__)*/
