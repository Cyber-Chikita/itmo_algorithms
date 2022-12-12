

#include <iostream>
#include <string> 
#include "CustomArray.h"

using namespace std;




int main()
{
	CustomArray<int> a = CustomArray<int>();

	cout << a.length() << endl;
	for (size_t i = 0; i != 20; ++i)
	{
		a.insert(i);
	}
	cout << "length " << a.length() << endl;

	a.insert(10, 30);
	a.remove(12);

	auto b = a.iterator();

	cout << b.hasNext() << " wait next " << endl;

	while (b.hasNext()) {
		cout << b.get() << " wait next " << endl;
		b.set(10);
		b.next();
	}
	

	for (size_t i = 0; i != a.length(); ++i)
	{
		cout << i << ": " << a[i] << endl;
	}


}

