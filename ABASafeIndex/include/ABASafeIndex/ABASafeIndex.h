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
//--------------------
template<std::size_t NumElements>
class UniqueIndex : protected ABASafeIndex<NumElements>{
public:

	using base_type = ABASafeIndex<NumElements>;
	using this_type = UniqueIndex<NumElements>;
	using typename base_type::ValueType;

	UniqueIndex(this_type &&rhs):base_type(rhs.value){
		rhs.invalidate();
	}
	bool isValid(){ return operator bool();}
	explicit operator bool(){ return value & SPLIT_BIT; }
	/** UniqueIndex to be used as index in an array */
	operator std::size_t(){
		assert(isValid());
		return getIndex();
	}
protected:
	UniqueIndex(std::size_t index):base_type(index & INDEX_MASK){
		validate();
	}
	using base_type::value;
	using base_type::INDEX_MASK;
	using base_type::SPLIT_BIT;
	using base_type::getIndex;

private:
	void validate(){
		value |= SPLIT_BIT;
	}
	void invalidate(){
		value &= ~SPLIT_BIT;
	}
};
/** Specialization for isPowerOfTwo(NumElements) is possible but not implemented yet */
template<std::size_t NumElements, bool = CalculateHelper<NumElements>::isPowerOfTwo()>
class RingbufferPosition;


template<std::size_t NumElements>
class RingbufferPosition<NumElements, true> : protected ABASafeIndex<NumElements>{
public:
	using this_type = RingbufferPosition<NumElements>;
	using base_type = ABASafeIndex<NumElements>;

	RingbufferPosition():base_type(0){}

	bool isOptimized(){ return true; }
	this_type& operator++(){
		++value;
		return *this;
	}
protected:
	using base_type::value;
};

template<std::size_t NumElements>
class RingbufferPosition<NumElements, false> : protected ABASafeIndex<NumElements>{
public:
	// Todo implement
	using this_type = RingbufferPosition<NumElements>;
	using base_type = ABASafeIndex<NumElements>;
	using ValueType = typename base_type::ValueType;

	RingbufferPosition():base_type(0){}
	bool isOptimized(){ return false; }
	this_type& operator++(){
		if(getIndex() >= NumElements){
			setIndex(0);
			value += SPLIT_BIT;
		}else{
			setIndex(getIndex()+1);
		}
		return *this;

	}
	ValueType getABACounter(){
		return value & ~INDEX_MASK;
	}
	void setABACounter(ValueType counter){
		value = value & INDEX_MASK + counter &~INDEX_MASK;
	}
protected:
	using base_type::value;
	using base_type::INDEX_MASK;
	using base_type::SPLIT_BIT;
	using base_type::getIndex;
	using base_type::setIndex;
};
template<std::size_t NumElements>
class StackHead : protected ABASafeIndex<NumElements>{
	// Todo implement

};

#endif /* INCLUDE_ABASAFEINDEX_H_ */
