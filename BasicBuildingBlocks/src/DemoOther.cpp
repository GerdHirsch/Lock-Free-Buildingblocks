


#include <atomic>
#include <iostream>
#include <limits>
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
	cout << "numeric_limits<std::size_t:  " << std::hex << std::numeric_limits<std::size_t>::max() << endl;
	cout << "MAX_NUM_ELEMENTS_FOR_SIZE_T: " << std::hex << MAX_NUM_ELEMENTS_FOR_SIZE_T << endl;
	cout << "numeric_limits<std::size_t:  " << std::hex << (std::numeric_limits<std::size_t>::max() >> 9) << endl;


}
