#ifndef INCLUDE_BASICBUILDINGBLOCKS_CALCULATEHELPER_H_
#define INCLUDE_BASICBUILDINGBLOCKS_CALCULATEHELPER_H_

#include <cstddef>
#include <limits>
#include <type_traits>
#include <cassert>
//------------------
template<std::size_t NumElements_>
class CalculateHelper{
public:
	using this_type = CalculateHelper<NumElements_>;

	static constexpr std::size_t numElements = NumElements_;
	static_assert(NumElements_ > 0, "NumElements must be greater than zero!");
		static_assert(std::numeric_limits<std::size_t>::max() >= NumElements_,
					"to much elements, NumElements must be less than or equal std::numeric_limits<std::size_t>::max()");
enum ValueTypes{ SIZE_T, ULL};
inline
static constexpr ValueTypes getTypeEnum(std::size_t numElements){
	constexpr auto MAX_NUM_ELEMENTS_FOR_SIZE_T =
			static_cast<std::size_t>(-1) >> 9;

	if(numElements <= MAX_NUM_ELEMENTS_FOR_SIZE_T){
		// minimum 8 bits left for ABA with validBit or 9 bits left for ABA
		return SIZE_T;
	} else{
		return ULL;
	}
}
//------------------
template<std::size_t numElements, ValueTypes type>
struct CalculateValueTypeImpl;

template<std::size_t numElements>
struct CalculateValueTypeImpl<numElements, SIZE_T>{
	using type = std::size_t;
};
template<std::size_t numElements>
struct CalculateValueTypeImpl<numElements, ULL>{
	using type = unsigned long long;
};
using ValueType =
		typename CalculateValueTypeImpl<numElements, getTypeEnum(numElements)>::type;
//------------------
inline
static constexpr ValueType IndexMask(){
	using MaskType = ValueType;
	MaskType mask{1};
	while(mask < numElements-1){
		mask <<= 1;
		++mask;
	}
	return mask;
}
inline
static constexpr ValueType SplitBit(){

	ValueType retVal = 2;
	while(retVal < numElements)
		retVal <<= 1;
	return retVal;
}
inline
static constexpr bool isPowerOfTwo(){
	auto constexpr splitBit_RightShift = SplitBit() >> 1;

	return splitBit_RightShift == numElements;

}

};
#endif /* INCLUDE_BASICBUILDINGBLOCKS_CALCULATEHELPER_H_ */
