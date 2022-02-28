#ifndef INCLUDE_ABASAFEINDEX_H_
#define INCLUDE_ABASAFEINDEX_H_

#include <ABASafeIndex/CalculaterHelper.hpp>

template<std::size_t NumElements_>
class ABASafeIndex{
public:
	static auto constexpr  NumElements = NumElements_;
	using Helper = CalculateHelper<NumElements>;
	using ValueType = typename Helper::ValueType;

	static_assert(NumElements > 0, "NumElements must be greater than zero!");
	static_assert(std::numeric_limits<std::size_t>::max() >= NumElements_,
				"to much elements, NumElements must be less than or equal std::numeric_limits<std::size_t>::max()");

	using this_type = ABASafeIndex<NumElements>;

	/** bits=1 needed for the index values*/
	static auto constexpr INDEX_MASK = Helper::IndexMask();
	/** first bit=1 from LSB that not belongs to the INDEX_MASK */
	static auto constexpr SPLIT_BIT = Helper::SplitBit();

	constexpr ABASafeIndex(ValueType value)
	: value(value)
	{}

	std::size_t getIndex(){
		return value & INDEX_MASK;
	}
	void setIndex(std::size_t index){
		assert(index < NumElements);

		value = value &~INDEX_MASK + index & INDEX_MASK;
	}
protected:
	ValueType value;
};


#endif /* INCLUDE_ABASAFEINDEX_H_ */
