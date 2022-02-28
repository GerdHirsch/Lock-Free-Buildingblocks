
#include <BasicBuildingBlocks/RingbufferPosition.h>

#include <iostream>
using namespace std;

void demoRingbufferPosition(){
	RingbufferPosition<3> rp3;
	RingbufferPosition<4> rp4;
	cout << "rp3.isOptimized(): " << rp3.isOptimized() << endl;
	cout << "rp4.isOptimized(): " << rp4.isOptimized() << endl;
}
