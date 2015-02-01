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

#include "SimpleAudioEngine.h"

struct node
{
	char fileName;
	struct node *next;
};

class AudioQueue : public CocosDenshion::SimpleAudioEngine
{
public:

	void init();
	void enqueue(const char *fileName);
	void dequeue();
	void playAudio(const char *fileName);
	void stopAudio();

	AudioQueue();
	~AudioQueue();

private:

	node *front;
	node *tail;
	
};

#endif /*defined(__WillYard__AudioQueue__)*/
