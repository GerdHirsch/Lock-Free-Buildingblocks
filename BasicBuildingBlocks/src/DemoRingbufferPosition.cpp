
#include <BasicBuildingBlocks/RingbufferPosition.h>

#include <iostream>
using namespace std;


void demoRingbufferPosition(){
	constexpr std::size_t numElements{5};
	using RbP = RingbufferPosition<numElements>;
	RbP rbp;

	cout << std::hex;

	cout << "numElements: " << numElements << endl;
	cout << "INDEX_MASK : " << RbP::INDEX_MASK << endl;
	cout << "~INDEX_MASK : " << ~RbP::INDEX_MASK << endl;
	cout << "SPLIT_BIT  : " << RbP::SPLIT_BIT << endl;

	cout
	<< "rbp.getValue: " << rbp.getValue()
	<< " rbp.getIndex: " << rbp.getIndex()
	<< " rbp.getABACount: " << rbp.getABACounter() << endl;


	cout << "loop 1" << endl;

	for(std::size_t i=0; i<3*numElements;++i,++rbp){
		cout
		<< "rbp.getValue: " << rbp.getValue()
		<< " rbp.getIndex: " << rbp.getIndex()
		<< " rbp.getABACount: " << rbp.getABACounter() << endl;
	}

	rbp.setABACounter(~RbP::INDEX_MASK);

	cout << "loop 2" << endl;
	for(std::size_t i=0; i<2*numElements;++i,++rbp){
		cout
		<< "rbp.getValue: " << rbp.getValue()
		<< " rbp.getIndex: " << rbp.getIndex()
		<< " rbp.getABACount: " << rbp.getABACounter() << endl;
	}

	rbp.setABACounter(~RbP::INDEX_MASK - RbP::SPLIT_BIT);
	cout << "loop 3" << endl;
	for(std::size_t  i=0; i<4*numElements;++i,++rbp){
		cout
		<< "rbp.getValue: " << rbp.getValue()
		<< " rbp.getIndex: " << rbp.getIndex()
		<< " rbp.getABACount: " << rbp.getABACounter() << endl;
	}
}

void demoRingbufferPositionIsOptimized(){
	RingbufferPosition<3> rp3;
	RingbufferPosition<4> rp4;
	cout << "rp3.isOptimized(): " << rp3.isOptimized() << endl;
	cout << "rp4.isOptimized(): " << rp4.isOptimized() << endl;
}
