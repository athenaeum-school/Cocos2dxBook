/*
* AudioQueue.cpp
* willYard
*
* All Rights Reserved by Athenaeum Society
*
* Written by Nadd3564 on 2015/01/04.
*
*/


#include "AudioQueue.h"

//キューの始めに追加する
const std::string INIT_QUEUE = "initQueue";

AudioQueue::AudioQueue()
{
	init();
}

AudioQueue::~AudioQueue(){}

void AudioQueue::init()
{
	front = NULL;
	tail = NULL;
	this->preloadEffect("se_maoudamashii_element_fire07.mp3");
	this->preloadEffect("se_maoudamashii_system48.mp3");
	this->preloadEffect("se_maoudamashii_system45.mp3");
	this->preloadEffect("se_maoudamashii_element_fire06.mp3");
	this->preloadEffect("se_maoudamashii_explosion04.mp3");
	this->preloadEffect("se_maoudamashii_magical23.mp3");
	this->preloadEffect("se_maoudamashii_system28.mp3");
	this->preloadEffect("se_maoudamashii_retro18.mp3");
	this->preloadEffect("se_maoudamashii_battle18.mp3");
	this->preloadBackgroundMusic("game_maoudamashii_7_rock46.mp3");
	enqueue(INIT_QUEUE);
}

void AudioQueue::enqueue(const std::string &name)
{
	if (tail == NULL)
	{
		tail = new node;
		tail->next = NULL;
		tail->name = name;
		front = tail;
	}
	else
	{
		node* tmp = new node;
		tail->next = tmp;
		tmp->name = name;
		tmp->next = NULL;

		tail = tmp;
	}
}

void AudioQueue::dequeue()
{
	node* tmp = front;

	if (tmp == NULL)
	{
		//キューに待ち（要素）はなし
		return;
	}
	else
	{
		if (tmp->next != NULL)
		{
			tmp = tmp->next;
			delete front;
			front = tmp;
		}
		else
		{
			delete front;
			front = NULL;
			tail = NULL;
		}
	}
}

void AudioQueue::playAudio(const std::string &name)
{
	if (front == tail)
	{
		return;
	}
	node *p = front;
	while (p != NULL)
	{
		if (p->name == name)
		{
			//同じファイル名の音源を見つけたら中断
			break;
		}
		p = p->next;
	}
	
	this->playEffect(front->name.c_str());
	dequeue();
}

void AudioQueue::playBGM()
{
	//背景音は繰り返し再生を行なうため、
	//dequeue()が反映されないように専用処理
	this->playBackgroundMusic("game_maoudamashii_7_rock46.mp3", true);
}

void AudioQueue::stopAudio()
{
	this->stopBackgroundMusic();
}
