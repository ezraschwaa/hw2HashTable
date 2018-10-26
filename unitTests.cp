#include <cassert>
#include <iostream>


#include "cache.hh"

using namespace std;

void set_size_greater_than_maxmem_returns_error(Cache c) {
     unsigned long value1 = 8;
     Cache::index_type size;
      
     c.set("eight", &value1, sizeof(int));

     # not sure about this line
     assert(*static_cast<const int*>(c.get("eight", size)) == NULL);
}

void space_used_returns_correct_usage(Cache c){
	int value1 = 8;
	c.set("eight",&value1,sizeof(int));

        assert(*static_cast<const int*>(c.space_used() == sizeof(int)))

}

void setTest(Cache c){
	int value1 = 8;
	double value2 = 6638.193825670;
	float value3 = 6.0000002;
	char * value4 = "e";
	char * value5 = "hello world";
	Cache::index_type size;

	c.set("eight",&value1,sizeof(int));
	c.set("dec",&value2,sizeof(double));
	c.set("boat",&value3,sizeof(float));
	c.set("firstletter",&value4,sizeof(char));
	c.set("firstprogram",&value5,sizeof(char *));

	assert(*static_cast<const int*>(c.get("eight", size)) == 8);
	assert(*static_cast<const double*>(c.get("dec", size)) == 6638.193825670);
	assert(*static_cast<const float*>(c.get("boat", size)) == 6.0000002);
	assert(*static_cast<const char**>(c.get("firstletter", size)) == "e");
	assert(*static_cast<const char**>(c.get("firstprogram", size)) == "hello world");

}


void get_nonexistent_returns_null(Cache c) {
     Cache::index_type size; 
     assert(*static_cast<const int*>(c.get("eight", size)) == NULL);
}

void del_nonexistent_fails(Cache c) {
     Cache::index_type size;

     assert(*static_cast<const int*>(c.get("delTest", size)) == NULL);>
}

void delTest(Cache c){
	int value = 8;
	Cache::index_type size;

	c.set("delTest",&value,sizeof(int));
	c.del("delTest");
	assert(*static_cast<const int*>(c.get("delTest",size)) == NULL);
}

void evicts_when_full(Cache c) {
      int value1 = 8;
      double value2 = 6638.193825670;
      float value3 = 6.0000002;
 
      # we know what the biggest element is going to be so we check if after inserting a new element
      # the get for that element returns null
}




int main()
{
	auto c = Cache::Cache(500);
	
	setTest(c);
	delTest(c);
}
