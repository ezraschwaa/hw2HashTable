#include <cassert>
#include <iostream>

#include "cache.hh"

using namespace std;

int main()
{
	int value1 = 8;
	double value2 = 6638.193825670;
	float value3 = 6.0000002;
	char value4 = "e";
	char * value5 = "hello world"
	Cache::index_type size;

	auto c = Cache(500);
	c.set("eight",&value1,sizeof(int));
	c.set("dec",&value2,sizeof(double));
	c.set("boat",&value3,sizeof(float));
	c.set("firstletter",&value4,sizeof(char));
	c.set("firstprogram",&value5,sizeof(char *))


	assert(*static_cast<const int*>(c.get("hello", size)) == 8);
	c.del("hello");
	assert(*static_cast<const int*>(c.get("hello", size)) == NULL);
}