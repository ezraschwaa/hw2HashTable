#include <cassert>
#include <cache.hh>
using namespace std;

int main()
{
	auto c = new Cache(500);
	c.set("hello",5,1);
	c.get("hello")
}