//
//  Threadpool.hpp
//  threadpool
//
//  Created by gsharma on 24/12/16.
//  Copyright © 2016 gsharma. All rights reserved.
//

#ifndef Threadpool_h
#define Threadpool_h

#include <thread>
#include <vector>
#include <map>
#include <mutex>
#include <unistd.h>
#include <iostream>
using namespace std;

template <typename Key, typename Value>
class Threadpool
{
	std::vector<std::thread> threads;
	std::map<Key, Value> result;
	std::mutex m;
	Key toPrint;
	void threadFunc();
public:
	Threadpool();
	virtual ~Threadpool() {}
	void complete(int result);
	void print();
	void endWork();
	bool end;
};

template <typename Key>
Key getWork()
{
	static std::mutex cMutex;
	static Key counter = 0;
	Key retVal = 0;
	cMutex.lock();
	retVal = counter;
	counter += 1;
	cMutex.unlock();
	return retVal;
}

template <typename Key, typename Value>
void Threadpool<Key, Value>::complete(int r)
{
	m.lock();
	result[r] = r;
	m.unlock();
	print();
}

template <typename Key, typename Value>
void Threadpool<Key, Value>::threadFunc()
{
	while(!end)
	{
		int work = getWork<Key>();
		for(int j = 0; j < 10; j++)
		{
			usleep(rand() * 100000.0/ RAND_MAX);
		}

		complete(work + 1);
	}
}

template <typename Key, typename Value>
void Threadpool<Key, Value>::print()
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

template <typename Key, typename Value>
void Threadpool<Key, Value>::endWork()
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

template <typename Key, typename Value>
Threadpool<Key, Value>::Threadpool() : end(false), toPrint(1)
{
	srand(0);
	unsigned numThreads = std::thread::hardware_concurrency();
	threads.reserve(numThreads);
	for(unsigned i = 0; i < numThreads; i++)
	{
		threads.push_back(std::thread(&Threadpool<Key, Value>::threadFunc, this));
	}
}


#endif /* Threadpool_h */
