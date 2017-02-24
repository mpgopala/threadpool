//
//  Threadpool.cpp
//  threadpool
//
//  Created by gsharma on 24/12/16.
//  Copyright © 2016 gsharma. All rights reserved.
//

#include <stdio.h>
#include "Threadpool.hpp"
#include <iostream>
#include <unistd.h>

using namespace std;

static int counter = 0;
std::mutex cMutex;
int getWork()
{
	int retVal = 0;
	cMutex.lock();
	retVal = counter;
	counter += 1;
	cMutex.unlock();
	return retVal;
}

void Threadpool::complete(int r)
{
	m.lock();
	result[r] = r;
	m.unlock();
}

void threadFunc(void *obj, int arg)
{
	Threadpool *ths = (Threadpool *)obj;
	while(!ths->end)
	{
		int work = getWork();
		for(int j = 0; j < 10; j++)
		{
			usleep(rand() * 100000.0/ RAND_MAX);
		}
		
		ths->complete(work + 1);
	}
}

void Threadpool::print()
{
	m.lock();
	while(result.find(toPrint) != result.end() && !result.empty())
	{
		cout<<toPrint<<endl;
		result.erase(toPrint);
		toPrint++;
	}
	m.unlock();
}

void Threadpool::endWork()
{
	end = true;
	
	for(size_t i = 0; i < threads.size();i++)
	{
		if(threads[i].joinable())
			threads[i].join();
	}
	
	while(!result.empty())
	{
		print();
	}
}

Threadpool::Threadpool() : end(false), toPrint(1)
{
	srand(NULL);
	unsigned numThreads = std::thread::hardware_concurrency();
	threads.reserve(numThreads);
	for(unsigned i = 0; i < numThreads; i++)
	{
		threads.push_back(std::thread(threadFunc, this, i));
	}
}

Threadpool::~Threadpool()
{

}
