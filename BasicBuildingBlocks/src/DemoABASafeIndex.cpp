
#include <BasicBuildingBlocks/ABASafeIndex.h>

#include <iostream>
using namespace std;

void demoABASafeIndex(){
	cout << __PRETTY_FUNCTION__ << endl;

	ABASafeIndex<3> index(4);
	cout << "index(4).getIndex(): " << index.getIndex() << endl;
}
