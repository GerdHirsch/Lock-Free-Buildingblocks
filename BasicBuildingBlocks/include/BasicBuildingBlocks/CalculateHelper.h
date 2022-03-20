#ifndef INCLUDE_BASICBUILDINGBLOCKS_CALCULATEHELPER_H_
#define INCLUDE_BASICBUILDINGBLOCKS_CALCULATEHELPER_H_

#include <cstddef>
#include <limits>
#include <type_traits>
#include <cassert>
//------------------
template<unsigned long long NumElements_>
class CalculateHelper{
public:
	static_assert(NumElements_ > 0, "NumElements must be greater than zero!");

	static_assert(std::numeric_limits<std::size_t>::max() >= NumElements_,
				"to much elements, NumElements must be less than or equal std::numeric_limits<std::size_t>::max()");

	static constexpr auto NumElements = NumElements_;
	using this_type = CalculateHelper<NumElements>;

	enum ValueTypes{ USHORT, SIZE_T, ULongLong};
inline
//static constexpr ValueTypes getTypeEnum(std::size_t numElements){
	static constexpr ValueTypes getTypeEnum(){

		constexpr auto MAX_NUM_ELEMENTS_FOR_Short =
				std::numeric_limits<unsigned short>::max() >> 9;
		constexpr auto MAX_NUM_ELEMENTS_FOR_SIZE_T =
				std::numeric_limits<std::size_t>::max() >> 9;

			// minimum 8 bits left for ABA with validBit or 9 bits left for ABA
		if(NumElements <= MAX_NUM_ELEMENTS_FOR_Short){
			return USHORT;
		}else if(NumElements <= MAX_NUM_ELEMENTS_FOR_SIZE_T){
			return SIZE_T;
		} else{
			return ULongLong;
		}
	}
//------------------
template<std::size_t numElements, ValueTypes type>
struct CalculateValueTypeImpl;

template<std::size_t numElements>
struct CalculateValueTypeImpl<numElements, USHORT>{
	using type = unsigned short;
};
template<std::size_t numElements>
struct CalculateValueTypeImpl<numElements, SIZE_T>{
	using type = std::size_t;
};
template<std::size_t numElements>
struct CalculateValueTypeImpl<numElements, ULongLong>{
	using type = unsigned long long;
};
using ValueType =
		typename CalculateValueTypeImpl<NumElements, getTypeEnum()>::type;
//------------------
inline
static constexpr ValueType IndexMask(){
	using MaskType = ValueType;
	MaskType mask{1};
	while(mask < NumElements-1){
		mask <<= 1;
		++mask;
	}
	return mask;
}
inline
static constexpr ValueType SplitBit(){
	return (IndexMask() << 1) & ~IndexMask();

//	ValueType retVal = 2;
//	while(retVal < numElements)
//		retVal <<= 1;
//	return retVal;
}
inline
static constexpr bool isPowerOfTwoWithoutOne(){
//	return numElements == 1 ? true : SplitBit() == numElements;
	return SplitBit() == NumElements;
}


};
#endif /* INCLUDE_BASICBUILDINGBLOCKS_CALCULATEHELPER_H_ */
