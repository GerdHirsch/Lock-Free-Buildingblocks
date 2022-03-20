

#include <BasicBuildingBlocks/CalculateHelper.h>

#include <iostream>
#include <limits>
using namespace std;

void demoIsPowerOfTwo(){
	cout << "IsPowerOfTwo(1): " << CalculateHelper<1>::isPowerOfTwoWithoutOne() << endl;
	cout << "IsPowerOfTwo(2): " << CalculateHelper<2>::isPowerOfTwoWithoutOne() << endl;
	cout << "IsPowerOfTwo(3): " << CalculateHelper<3>::isPowerOfTwoWithoutOne() << endl;
	cout << "IsPowerOfTwo(4): " << CalculateHelper<4>::isPowerOfTwoWithoutOne() << endl;
	cout << "IsPowerOfTwo(5): " << CalculateHelper<5>::isPowerOfTwoWithoutOne() << endl;
	cout << "IsPowerOfTwo(6): " << CalculateHelper<6>::isPowerOfTwoWithoutOne() << endl;
	cout << "IsPowerOfTwo(7): " << CalculateHelper<7>::isPowerOfTwoWithoutOne() << endl;
	cout << "IsPowerOfTwo(8): " << CalculateHelper<8>::isPowerOfTwoWithoutOne() << endl;
	cout << "IsPowerOfTwo(9): " << CalculateHelper<9>::isPowerOfTwoWithoutOne() << endl;
	cout << "IsPowerOfTwo(10): " << CalculateHelper<10>::isPowerOfTwoWithoutOne() << endl;
	cout << "IsPowerOfTwo(12): " << CalculateHelper<12>::isPowerOfTwoWithoutOne() << endl;
	cout << "IsPowerOfTwo(15): " << CalculateHelper<15>::isPowerOfTwoWithoutOne() << endl;
	cout << "IsPowerOfTwo(16): " << CalculateHelper<16>::isPowerOfTwoWithoutOne() << endl;
	cout << "IsPowerOfTwo(17): " << CalculateHelper<17>::isPowerOfTwoWithoutOne() << endl;
	cout << "IsPowerOfTwo(31): " << CalculateHelper<31>::isPowerOfTwoWithoutOne() << endl;
	cout << "IsPowerOfTwo(32): " << CalculateHelper<32>::isPowerOfTwoWithoutOne() << endl;
	cout << "IsPowerOfTwo(33): " << CalculateHelper<33>::isPowerOfTwoWithoutOne() << endl;
}

void demoCalculateValueType(){
	constexpr unsigned long long maxShort = numeric_limits<unsigned short>::max();
	constexpr unsigned long long maxSize_t = numeric_limits<std::size_t>::max();

	cout << "sizeof(ValueType) 1: " << sizeof(CalculateHelper<1>::ValueType) << endl;

	cout << "sizeof(ValueType) maxShort>>9:  " << sizeof(CalculateHelper<(maxShort>>9)>::ValueType)
			<< " maxShort>>9: " << (maxShort>>9)<< endl;

	cout << "sizeof(ValueType) maxShort>>8:  " << sizeof(CalculateHelper<(maxShort>>8)>::ValueType)
			<< " maxShort>>8: " << (maxShort>>8)<< endl;

	cout << "sizeof(ValueType) maxSize_t>>9: " << sizeof(CalculateHelper<(maxSize_t>>9)>::ValueType)
			<< " maxSize_t>>9: " << (maxSize_t>>9)<< endl;

	cout << "sizeof(ValueType) maxSize_t>>8: " << sizeof(CalculateHelper<(maxSize_t>>8)>::ValueType)
			<< " maxSize_t>>8: " << (maxSize_t>>8)<< endl;

// static_assert
//	cout << "sizeof(ValueType) maxSize_t + 1: " << sizeof(CalculateHelper<(maxSize_t + 1)>::ValueType)
//			<< " maxSize_t + 1: " << (maxSize_t + 1) << endl;

}

void demoCalculateMask(){
	cout << __PRETTY_FUNCTION__ << endl;
	cout << std::hex;
	cout << "IndexMask(1): " << CalculateHelper<1>::IndexMask() << endl;
	cout << "IndexMask(2): " << CalculateHelper<2>::IndexMask() << endl;
	cout << "IndexMask(3): " << CalculateHelper<3>::IndexMask() << endl;
	cout << "IndexMask(4): " << CalculateHelper<4>::IndexMask() << endl;
	cout << "IndexMask(5): " << CalculateHelper<5>::IndexMask() << endl;
	cout << "IndexMask(7): " << CalculateHelper<7>::IndexMask() << endl;
	cout << "IndexMask(8): " << CalculateHelper<8>::IndexMask() << endl;
	cout << "IndexMask(9): " << CalculateHelper<9>::IndexMask() << endl;
	cout << "IndexMask(15): " << CalculateHelper<15>::IndexMask() << endl;
	cout << "IndexMask(16): " << CalculateHelper<16>::IndexMask() << endl;
	cout << "IndexMask(17): " << CalculateHelper<17>::IndexMask() << endl;
	cout << "IndexMask(31): " << CalculateHelper<31>::IndexMask() << endl;
	cout << "IndexMask(32): " << CalculateHelper<32>::IndexMask() << endl;
	cout << "IndexMask(33): " << CalculateHelper<33>::IndexMask() << endl;
}
void demoCalculateSplitBit(){
	cout << __PRETTY_FUNCTION__ << endl;

//	cout << std::hex;
	cout << std::dec;
//	cout << "SplitBit(0): " << SplitBit(0U) << endl;
	cout << "SplitBit(1): " << CalculateHelper<1>::SplitBit() << endl;
	cout << "SplitBit(2): " << CalculateHelper<2>::SplitBit() << endl;
	cout << "SplitBit(3): " << CalculateHelper<3>::SplitBit() << endl;
	cout << "SplitBit(4): " << CalculateHelper<4>::SplitBit() << endl;
	cout << "SplitBit(5): " << CalculateHelper<5>::SplitBit() << endl;
	cout << "SplitBit(6): " << CalculateHelper<6>::SplitBit() << endl;
	cout << "SplitBit(7): " << CalculateHelper<7>::SplitBit() << endl;
	cout << "SplitBit(8): " << CalculateHelper<8>::SplitBit() << endl;
	cout << "SplitBit(9): " << CalculateHelper<9>::SplitBit() << endl;
	cout << "SplitBit(15): " << CalculateHelper<15>::SplitBit() << endl;
	cout << "SplitBit(16): " << CalculateHelper<16>::SplitBit() << endl;
	cout << "SplitBit(17): " << CalculateHelper<17>::SplitBit() << endl;
	cout << "SplitBit(31): " << CalculateHelper<31>::SplitBit() << endl;
	cout << "SplitBit(32): " << CalculateHelper<32>::SplitBit() << endl;
	cout << "SplitBit(33): " << CalculateHelper<33>::SplitBit() << endl;

}
