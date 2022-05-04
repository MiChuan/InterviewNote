#include <iostream>
using namespace std;

int func(int *p)
{
    int y = *p;
    return y;
}

int add(int const& a, int const& b)
{
	return a + b;
}

int main()
{
	cout<< add(4, 6) <<endl;
    int *p = NULL;
    return func(p);
}
