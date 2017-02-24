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


class Threadpool
{
	std::vector<std::thread> threads;
	std::map<int, int> result;
	std::mutex m;
	int toPrint;
public:
	Threadpool();
	virtual ~Threadpool();
	void complete(int result);
	void print();
	void endWork();
	bool end;
};

#endif /* Threadpool_h */
