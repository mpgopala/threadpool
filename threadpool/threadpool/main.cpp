//
//  main.cpp
//  threadpool
//
//  Created by gsharma on 24/12/16.
//  Copyright © 2016 gsharma. All rights reserved.
//

#include <iostream>
#include <unistd.h>
#include "Threadpool.hpp"

int main(int argc, const char * argv[]) {
	// insert code here...
	std::cout << "Hello, World!\n";
	Threadpool<int, int> t;
	usleep(3 * 1000000);
	cout<<"Ending work"<<endl;
	t.endWork();
	std::cout<<"Ending threadpool"<<endl;
	return 0;
}
