


#include <atomic>
#include <iostream>
using namespace std;


void demoIsLockfree(){
	struct BigStruct{
		unsigned long long m1;
//		unsigned long long m2;
	};
	atomic<BigStruct> lockFree{};
	cout << "is always lock free: " << lockFree.is_always_lock_free << endl;
	cout << "is lock free: " << lockFree.is_lock_free() << endl;

}

void demoCalculateMaxNumElementsForSizeT(){
	cout << __PRETTY_FUNCTION__ << endl;

	cout << "UI:     " << sizeof(unsigned int) << endl;
	cout << "size_t: " << sizeof(std::size_t) << endl;
	cout << "UL:     " << sizeof(unsigned long) << endl;
	cout << "ULL:    " << sizeof(unsigned long long) << endl;
	cout << "size_t = -1: " << std::hex << static_cast<std::size_t>(-1) << endl;
	constexpr auto MAX_NUM_ELEMENTS_FOR_SIZE_T =
				static_cast<std::size_t>(-1) >> 9;
	cout << "MAX_NUM_ELEMENTS_FOR_SIZE_T: " << MAX_NUM_ELEMENTS_FOR_SIZE_T << endl;


}
