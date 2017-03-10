#include <iostream>
#include <boost/function.hpp>
#include <boost/bind.hpp>

using namespace std;

//test bosst bind

class bf_test
{
public:
	bf_test(){};
	~bf_test(){};

	void memberFunc(double d, int i, int j)
	{
		cout <<d<<endl;
		cout <<i<<endl;
		cout <<j<<endl;
	}
	
};

int main()
{
	bf_test foo;
	//three variable to one variable
	boost::function<void(int)> fp = boost::bind(&bf_test::memberFunc, &foo, 10,_1,20);
	fp(100);
	// used boost::ref
	boost::function<void(int,int)> fp2 = boost::bind(&bf_test::memberFunc, boost::ref(foo), 10,_1,_2);
	fp2(100,200);

}