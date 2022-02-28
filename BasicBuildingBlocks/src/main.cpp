/*
 * copyright Gerd Hirsch
 */
#include "ABASafeIndex/RingbufferPosition.h"
#include "ABASafeIndex/UniqueIndex.h"
#include "ABASafeIndex/ABASafeIndex.h"

#include <iostream>
#include <atomic>
using namespace std;



void demoCalculateMask();
void demoCalculateSplitBit();
void demoABASafeIndex();
void demoRingbufferPosition();
void demoUniqueIndex();
void demoIsPowerOfTwo();

void demoIsLockfree();
void demoCalculateMaxNumElementsForSizeT();
int main(){
	cout << "ABASafeIndex" << endl;
//	demoCalculateMask();
//	demoCalculateSplitBit();
//	demoABASafeIndex();
//	demoUniqueIndex();
//	demoIsPowerOfTwo();
	demoRingbufferPosition();

	//	demoIsLockfree();
//	demoCalculateMaxNumElementsForSizeT();

}
void demoRingbufferPosition(){
	RingbufferPosition<3> rp3;
	RingbufferPosition<4> rp4;
	cout << "rp3.isOptimized(): " << rp3.isOptimized() << endl;
	cout << "rp4.isOptimized(): " << rp4.isOptimized() << endl;
}
void demoIsPowerOfTwo(){
	cout << "IsPowerOfTwo(1): " << CalculateHelper<1>::isPowerOfTwo() << endl;
	cout << "IsPowerOfTwo(2): " << CalculateHelper<2>::isPowerOfTwo() << endl;
	cout << "IsPowerOfTwo(3): " << CalculateHelper<3>::isPowerOfTwo() << endl;
	cout << "IsPowerOfTwo(4): " << CalculateHelper<4>::isPowerOfTwo() << endl;
	cout << "IsPowerOfTwo(7): " << CalculateHelper<7>::isPowerOfTwo() << endl;
	cout << "IsPowerOfTwo(8): " << CalculateHelper<8>::isPowerOfTwo() << endl;
	cout << "IsPowerOfTwo(9): " << CalculateHelper<9>::isPowerOfTwo() << endl;
}

template<std::size_t NumElements>
struct MyIndex : UniqueIndex<NumElements>{
	using base_type = UniqueIndex<NumElements>;

	MyIndex(std::size_t index):base_type(index){}
	MyIndex(MyIndex&& rhs):base_type(std::move(rhs)){}
	MyIndex(base_type&& rhs):base_type(std::move(rhs)){}
};

void demoUniqueIndex(){
	cout << __PRETTY_FUNCTION__ << endl;
	constexpr auto MAX_Size_t = std::numeric_limits<std::size_t>::max();
	using Index = MyIndex<5>;
//	using BigIndex = UniqueIndex<MAX_Size_t>;
	using SmallIndex = UniqueIndex< (MAX_Size_t>>9) >;
	using BigIndex = UniqueIndex< (MAX_Size_t>>9)+1 >;
	using Unique = UniqueIndex<5>;
	cout << "sizeof(Index)   : " << sizeof(Index) << endl;
	cout << "sizeof(SmallIndex): " << sizeof(SmallIndex) << endl;
	cout << "sizeof(BigIndex): " << sizeof(BigIndex) << endl;

	Index index(4);

	cout <<"index.isValid(): " << index.isValid() << endl;
	Unique idx(std::move(index));
	cout <<"index.isValid(): " << index.isValid() << endl;
	cout <<"idx.isValid(): " << idx.isValid() << endl;
//	cout <<"idx.getIndex(): " << idx.getIndex() << endl;
	cout <<"idx: " << idx << endl;
	Index index2(std::move(idx));
	cout <<"idx.isValid(): " << idx.isValid() << endl;
//	cout <<"idx.getIndex(): " << idx.getIndex() << endl;
//	cout <<"idx: " << idx << endl;
	cout <<"index2.isValid(): " << index2.isValid() << endl;
//	cout <<"index2.getIndex(): " << index2.getIndex() << endl;
	cout <<"index2" << index2 << endl;


	// check static_assert
//	cout << "max size_t: " << std::numeric_limits<std::size_t>::max() << endl;
//	cout << "max ValueType: " << std::numeric_limits<ValueType>::max() << endl;
//	static constexpr ValueType toMuchElements = static_cast<ValueType>
//		(std::numeric_limits<std::size_t>::max()) +1;
//	using ToMuchElements = MyIndex<unsigned long long, toMuchElements>;
//	ToMuchElements assertIndex(0);
}
void demoABASafeIndex(){
	cout << __PRETTY_FUNCTION__ << endl;

	ABASafeIndex<3> index(4);
	cout << "index(4).getIndex(): " << index.getIndex() << endl;
}

void demoCalculateMask(){
	cout << __PRETTY_FUNCTION__ << endl;
	cout << std::hex;
	cout << "IndexMask(1): " << CalculateHelper<1>::IndexMask() << endl;
	cout << "IndexMask(2): " << CalculateHelper<2>::IndexMask() << endl;
	cout << "IndexMask(3): " << CalculateHelper<3>::IndexMask() << endl;
	cout << "IndexMask(4): " << CalculateHelper<4>::IndexMask() << endl;
	cout << "IndexMask(7): " << CalculateHelper<7>::IndexMask() << endl;
	cout << "IndexMask(8): " << CalculateHelper<8>::IndexMask() << endl;
	cout << "IndexMask(9): " << CalculateHelper<9>::IndexMask() << endl;
	cout << "IndexMask(15): " << CalculateHelper<15>::IndexMask() << endl;
	cout << "IndexMask(16): " << CalculateHelper<16>::IndexMask() << endl;
	cout << "IndexMask(31): " << CalculateHelper<31>::IndexMask() << endl;
	cout << "IndexMask(32): " << CalculateHelper<32>::IndexMask() << endl;
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
	cout << "SplitBit(7): " << CalculateHelper<7>::SplitBit() << endl;
	cout << "SplitBit(8): " << CalculateHelper<8>::SplitBit() << endl;
	cout << "SplitBit(9): " << CalculateHelper<9>::SplitBit() << endl;
	cout << "SplitBit(15): " << CalculateHelper<15>::SplitBit() << endl;
	cout << "SplitBit(16): " << CalculateHelper<16>::SplitBit() << endl;

}
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
