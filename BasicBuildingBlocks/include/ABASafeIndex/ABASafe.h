
/*
 * ABASave.h
 *
 *  Created on: Apr 26, 2019
 *      Author: user
 */

#ifndef INCLUDE_SKIPPYQUEUE_ABASAFE_H_
#define INCLUDE_SKIPPYQUEUE_ABASAFE_H_

#include <cstddef>
#include <iostream>
#include <cassert>
#include <type_traits>

namespace SkippyQueue{


//* @param NativeType: must be an unsigned type, overflow not defined for signed */
template<std::size_t MAXElements, class NativeType = std::size_t>
class Index;

template<class ElementType, class NativeType = std::size_t>
class Pointer;

/**
 * value type, no references must be stored
 */
template<class ABAType, std::size_t OwnerNo=0>
class ABASafe; // Primary not defined
//template<class ABAType, class Owner=void> // with Owner as type
//class ABASafe; // Primary not defined

/**
 * @param MAXElements, number of elements to calculate index bits
 * @param NativeType, used to manage ABACounter, VALIDBIT and index
 * @param Owner, to differentiate between indexes of different types
 */
template<std::size_t MAXElements_, class NativeType_, std::size_t Owner>
class ABASafe<Index<MAXElements_, NativeType_>, Owner>
{
public:
	static_assert(std::is_unsigned<NativeType_>::value, "NativeType must be an unsigned type, cause overflow is not defined for signed");
	static constexpr std::size_t MAXElements = MAXElements_;
	/** Bit Structure of NativeType is
	* ABACounter, ValidBit, index. index is stored in the LSBits
	* were ValidBit is the next power of 2 greater than MAXElements
	* the rest of the MSBits are used for the ABA counter
	*/
	using NativeType = NativeType_;
	using this_type = ABASafe<Index<MAXElements_, NativeType_>, Owner>;

	static constexpr NativeType VALIDBIT = this_type::calculateValidBit(1);
	static constexpr NativeType LSBitABACounter = VALIDBIT << 1;
	static constexpr NativeType ONEs = ~static_cast<NativeType>(0);
	static constexpr unsigned short numZEROBits = this_type::calculateZeroBits(0);
	static constexpr NativeType ABAMask = ONEs << numZEROBits;

	constexpr ABASafe()  noexcept : value(0){} // invalid index

	constexpr ABASafe(NativeType index)  noexcept
	: value(index | VALIDBIT)
	{
//		assert(index < MAXElements); //, "index must not be greater than MAXElements")
	}
	// -------------------------------
	// valid/invalid
	void invalidate()noexcept{
		value = 0;
	}
	explicit operator bool()const noexcept{ return value & VALIDBIT;}
	// -------------------------------
	// index
	NativeType getIndex() const noexcept{return value & ~(ABAMask|VALIDBIT);}
	void setIndex(NativeType value) /** assert(value < MAXElements) */{
		assert(value < MAXElements);
		NativeType abaValidBit = this->value & (ABAMask|VALIDBIT);
		this->value = value | abaValidBit;
	}
	// -------------------------------
	// ABACounter
	//* the cheaper alternative for ABACounter */
	this_type& operator++() noexcept {
		value += LSBitABACounter;
		return *this;
	}
	NativeType getABACounter() const noexcept { return value & ABAMask;}
	// -------------------------------
	NativeType getValue() const noexcept{ return value; }

private:
	static constexpr NativeType calculateValidBit(NativeType retVal=1) noexcept{
		static_assert(sizeof(NativeType) >= sizeof(std::size_t),
				"NativeType must be >= size_t");

		return retVal < MAXElements ? calculateValidBit(retVal<<1) : retVal;

//
//		while(retVal < MAXElements)
//			retVal <<= 1;
//		return retVal;
	}
	static constexpr std::uint16_t calculateZeroBits(std::uint16_t retVal=0, NativeType bits=1) noexcept{

		return bits < LSBitABACounter ? calculateZeroBits(retVal+1, bits<<1) : retVal;


//		unsigned short retVal=0;
//		NativeType bits = 1;
//		while(bits < LSBitABACounter){
//			bits <<= 1;
//			++retVal;
//		}
//		return retVal;
	}

	template<std::size_t MAXElements, class NativeType, std::size_t TheOwner>
	friend
	std::ostream& operator<<(std::ostream& out, ABASafe<Index<MAXElements, NativeType>, TheOwner> const & idx) noexcept;

	std::ostream& print(std::ostream& out) const noexcept
	{
		using ABAType = this_type;
			out
			<< "index: " << this->getIndex()
			<< " ABA: " << (this->value & ABAType::ABAMask)
			<< " Valid: " << std::boolalpha << static_cast<bool>(*this);
			return out;
	}

	NativeType value;
};
//template<class Index, class Owner>
//std::ostream& operator<<(std::ostream& out, ABASafe<Index, Owner> idx){
template<std::size_t MAXElements, class NativeType, std::size_t Owner>
std::ostream& operator<<(std::ostream& out, ABASafe<Index<MAXElements, NativeType>, Owner> const & idx) noexcept{
	return idx.print(out);
}

}// namespace
#endif /* INCLUDE_SKIPPYQUEUE_ABASAFE_H_ */
