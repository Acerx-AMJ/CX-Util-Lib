#ifndef CX_UTIL_BITSET_HPP
#define CX_UTIL_BITSET_HPP

#include <cassert>
#include <cstddef>
#include <string>
#include <sstream>

namespace cx::util
{
   template<typename __NUMBERTYPE>
   concept Number = std::integral<__NUMBERTYPE> || std::floating_point<__NUMBERTYPE>;

   /// @brief Work with bits.
   template<size_t __SIZE, Number __NUMBERTYPE = signed char>
   class Bitset
   {
   public:
      // Constructors

      /// @brief Create default bitset.
      constexpr Bitset() noexcept
      {
         __BSIZE = sizeof(__NUMBERTYPE) * 8;
      }

      /// @brief Copy a bitset.
      /// @param other Other bitset.
      constexpr Bitset(const Bitset& other) noexcept
      {
         for (size_t i {}; i < numbercount(); ++i)
            __BITSET[i] = other.__BITSET[i];
         __BSIZE = sizeof(__NUMBERTYPE) * 8;
      }

      /// @brief Move a bitset.
      /// @param other Other bitset.
      constexpr Bitset(Bitset&& other) noexcept
      {
         for (size_t i {}; i < numbercount(); ++i)
            __BITSET[i] = other.__BITSET[i];
         __BSIZE = sizeof(__NUMBERTYPE) * 8;
      }

      ~Bitset() = default;

      // Utility functions

      /// @brief Set a bit to positive.
      /// @param index Bit index.
      constexpr void set(size_t index) noexcept
      {
         assert(index < __SIZE && "cx::util::Bitset index must be smaller than size.");
         __BITSET[index / __BSIZE] |= (1 << index % __BSIZE);
      }

      /// @brief Set all bits to be positive.
      constexpr void set() noexcept
      {
         for (size_t i {}; i < numbercount(); ++i)
            __BITSET[i] = ~__NUMBERTYPE();
      }

      /// @brief Set all bits in the range to positive.
      /// @param start Range start.
      /// @param end Range end.
      constexpr void setrange(size_t start, size_t end)
      {
         assert(start < end && end <= __SIZE && "cx::util::Bitset invalid range.");
         for (size_t i {start}; i < end; ++i) set(i);
      }

      /// @brief Set a bit to negative.
      /// @param index Bit index.
      constexpr void reset(size_t index) noexcept
      {
         assert(index < __SIZE && "cx::util::Bitset index must be smaller than size.");
         __BITSET[index / __BSIZE] &= ~(1 << index % __BSIZE);
      }

      /// @brief Set all bits to be negative.
      constexpr void reset() noexcept
      {
         for (size_t i {}; i < numbercount(); ++i)
            __BITSET[i] = 0;
      }

      /// @brief Set all bits in the range to negative.
      /// @param start Range start.
      /// @param end Range end.
      constexpr void resetrange(size_t start, size_t end)
      {
         assert(start < end && end <= __SIZE && "cx::util::Bitset invalid range.");
         for (size_t i {start}; i < end; ++i) reset(i);
      }

      /// @brief Flip a bit to opposite sign.
      /// @param index Bit index.
      constexpr void flip(size_t index) noexcept
      {
         assert(index < __SIZE && "cx::util::Bitset index must be smaller than size.");
         __BITSET[index / __BSIZE] ^= (1 << index % __BSIZE);
      }

      /// @brief Flip all bits in the range.
      /// @param start Range start.
      /// @param end Range end.
      constexpr void fliprange(size_t start, size_t end)
      {
         assert(start < end && end <= __SIZE && "cx::util::Bitset invalid range.");
         for (size_t i {start}; i < end; ++i) flip(i);
      }

      /// @brief Combine two bitsets together.
      /// @param other Other bitset.
      /// @return Combined bitset.
      constexpr Bitset unionwith(const Bitset& other) const noexcept
      {
         return *this | other;
      }

      // Access functions

      /// @brief Convert the bits to a string.
      /// @return Bits in string format.
      inline std::string tostring() const noexcept
      {
         std::stringstream stream;

         for (size_t i {}; i < __SIZE; ++i)
         {
            stream << (test(i) ? "1" : "0");
            if (i % __BSIZE == __BSIZE - 1)
               stream << " ";
         }
         return stream.str();
      }

      /// @brief Count the amount of true bits.
      /// @return True bit count.
      constexpr size_t count() const noexcept
      {
         size_t total {};

         for (size_t i {}; i < numbercount(); ++i)
         {
            __NUMBERTYPE value = __BITSET[i];

            while (value)
            {
               total += value & 1;
               value >>= 1;
            }
         }
         return total;
      }

      /// @brief Check if any bits are set to true.
      /// @return True if any bit is true.
      constexpr bool any() const noexcept
      {
         for (size_t i {}; i < numbercount(); ++i)
            if (__BITSET[i] != 0)
               return true;
         return false;
      }

      /// @brief Check if no bits are set to true.
      /// @return True if no bits are true.
      constexpr bool none() const noexcept
      {
         return !any();
      }

      /// @brief Check if all bits are set to true.
      /// @return True if all bits are true.
      constexpr bool all() const noexcept
      {
         const size_t number = numbercount();

         for (size_t i {}; i < number; ++i)
         {
            if (i == number - 1)
            {
               const size_t remaining = __SIZE % __BSIZE;
               if (remaining && (__BITSET[i] & ((1 << remaining) - 1)) != ((1 << remaining) - 1)) 
                  return false;
            }
            else if (__BITSET[i] != ~__NUMBERTYPE(0))
               return false;
         }
         return true;
      }

      /// @brief Get bit value.
      /// @param index Bit index.
      /// @return Bit value.
      constexpr bool test(size_t index) const noexcept
      {
         assert(index < __SIZE && "cx::util::Bitset index must be smaller than size.");
         return (__BITSET[index / __BSIZE] & (1 << index % __BSIZE)) != 0;
      }

      /// @brief Find first true bit.
      /// @return Index if found, -1 if not.
      constexpr signed long findfirst() const noexcept
      {
         for (size_t i {}; i < __SIZE; ++i)
            if (test(i)) return static_cast<signed long>(i);
         return -1;
      }

      /// @brief Find last true bit.
      /// @return Index if found, -1 if not.
      constexpr signed long findlast() const noexcept
      {
         for (size_t i {__SIZE - 1}; i >= 0; --i)
            if (test(i)) return static_cast<signed long>(i);
         return -1;
      }

      /// @brief Get data.
      /// @return Data.
      constexpr const __NUMBERTYPE* data() const noexcept
      {
         return __BITSET;
      }

      /// @brief Get bit size.
      /// @return Bit size.
      constexpr size_t size() const noexcept
      {
         return __SIZE;
      }

      /// @brief Get number count.
      /// @return Number count.
      constexpr size_t numbercount() const noexcept
      {
         return (__SIZE + __BSIZE - 1) / __BSIZE;
      }

      /// @brief Get number size.
      /// @return Number size.
      constexpr size_t numbersize() const noexcept
      {
         return __BSIZE;
      }

      // Assignment functions

      /// @brief Copy a bitset.
      /// @param other Other bitset.
      /// @return Copied bitset.
      constexpr Bitset& operator=(const Bitset& other) noexcept
      {
         if (this == &other) return *this;

         for (size_t i {}; i < numbercount(); ++i)
            __BITSET[i] = other.__BITSET[i];
         return *this;
      }

      // Comparison functions

      /// @brief Compare two bitsets.
      /// @param other Other bitset.
      /// @return True if both are equal.
      constexpr bool operator==(const Bitset& other) const noexcept
      {
         for (size_t i {}; i < numbercount(); ++i)
            if (__BITSET[i] != other.__BITSET[i])
               return false;
         return true;
      }

      /// @brief Compare two bitsets.
      /// @param other Other bitset.
      /// @return True if both are different.
      constexpr bool operator!=(const Bitset& other) const noexcept
      {
         return !(*this == other);
      }

      // Bitwise functions

      /// @brief Bitwise and operator.
      /// @param other Other bitset.
      /// @return Result.
      constexpr Bitset operator&(const Bitset& other) const noexcept
      {
         Bitset<__SIZE, __NUMBERTYPE> temp;
         
         for (size_t i {}; i < numbercount(); ++i)
            temp.__BITSET[i] = __BITSET[i] & other.__BITSET[i];
         return temp; 
      }

      /// @brief Bitwise or operator.
      /// @param other Other bitset.
      /// @return Result.
      constexpr Bitset operator|(const Bitset& other) const noexcept
      {
         Bitset<__SIZE, __NUMBERTYPE> temp;

         for (size_t i {}; i < numbercount(); ++i)
            temp.__BITSET[i] = __BITSET[i] | other.__BITSET[i];
         return temp;
      }

      /// @brief Bitwise xor operator.
      /// @param other Other bitset.
      /// @return Result.
      constexpr Bitset operator^(const Bitset& other) const noexcept
      {
         Bitset<__SIZE, __NUMBERTYPE> temp;

         for (size_t i {}; i < numbercount(); ++i)
            temp.__BITSET[i] = __BITSET[i] ^ other.__BITSET[i];
         return temp;
      }

      /// @brief Shift left operator.
      /// @param shift Amount to shift by.
      /// @return Result.
      constexpr Bitset operator<<(size_t shift) const noexcept
      {
         Bitset<__SIZE, __NUMBERTYPE> temp;
         const size_t numberShift = shift / __BSIZE;
         const size_t bitShift = shift % __BSIZE;
         const size_t number = numbercount();

         for (size_t i {}; i < number; ++i)
            if (i + numberShift < number)
            {
               temp.__BITSET[i + numberShift] |= __BITSET[i] << bitShift;
               if (bitShift > 0 && i + numberShift + 1 < number)
                  temp.__BITSET[i + numberShift + 1] |= __BITSET[i] >> (__BSIZE - bitShift);
            }
         return temp;
      }

      /// @brief Shift right operator.
      /// @param shift Amount to shift by.
      /// @return Result.
      constexpr Bitset operator>>(size_t shift) const noexcept
      {
         Bitset<__SIZE, __NUMBERTYPE> temp;
         const size_t numberShift = shift / __BSIZE;
         const size_t bitShift = shift % __BSIZE;
         const size_t number = numbercount();

         for (size_t i {}; i < number; ++i)
            if (i + numberShift < number)
            {
               temp.__BITSET[i] = __BITSET[i + numberShift] >> bitShift;
               if (bitShift > 0 && i + numberShift + 1 < number)
                  temp.__BITSET[i] |= __BITSET[i + numberShift + 1] << (__BSIZE - bitShift);
            }
         return temp;
      }

      /// @brief Bitwise not operator.
      /// @return Result.
      constexpr Bitset operator~() const noexcept
      {
         Bitset<__SIZE, __NUMBERTYPE> temp;

         for (size_t i {}; i < numbercount(); ++i)
            temp.__BITSET[i] = ~__BITSET[i];
         return temp;
      }

      // Compound bitwise functions

      /// @brief Compound bitwise and operator.
      /// @param other Other bitset.
      /// @return Result.
      constexpr Bitset& operator&=(const Bitset& other) noexcept
      {
         for (size_t i {}; i < numbercount(); ++i)
            __BITSET[i] &= other.__BITSET[i];
         return *this;
      }

      /// @brief Compound bitwise or operator.
      /// @param other Other bitset.
      /// @return Result.
      constexpr Bitset& operator|=(const Bitset& other) noexcept
      {
         for (size_t i {}; i < numbercount(); ++i)
            __BITSET[i] |= other.__BITSET[i];
         return *this;
      }

      /// @brief Compound bitwise xor operator.
      /// @param other Other bitset.
      /// @return Result.
      constexpr Bitset& operator^=(const Bitset& other) noexcept
      {
         for (size_t i {}; i < numbercount(); ++i)
            __BITSET[i] ^= other.__BITSET[i];
         return *this;
      }

      /// @brief Compound shift left operator.
      /// @param shift Amount to shift by.
      /// @return Result.
      constexpr Bitset& operator<<=(size_t shift) noexcept
      {
         *this = *this << shift;
         return *this;
      }

      /// @brief Compound shift right operator.
      /// @param shift Amount to shift by.
      /// @return Result.
      constexpr Bitset& operator>>=(size_t shift) noexcept
      {
         *this = *this >> shift;
         return *this;
      }

   private:
      size_t __BSIZE {};
      __NUMBERTYPE __BITSET[(__SIZE + sizeof(__NUMBERTYPE) * 8 - 1) / (sizeof(__NUMBERTYPE) * 8)] {}; 
   };
} // namespace cx::util

#endif // CX_UTIL_BITSET_HPP
