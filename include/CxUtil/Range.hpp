#ifndef CX_UTIL_RANGE_HPP
#define CX_UTIL_RANGE_HPP

#include "Config.hpp" // IWYU pragma: export

namespace cx::util
{
   template<typename T>
   struct Range
   {
      // Items

      /// @brief Start of the range.
      T start {};

      /// @brief End of the range.
      T endp {};

      /// @brief Amount to step by.
      T step {};

      // Constructors

      /// @brief Create a new range.
      /// @param start Start of the range.
      /// @param end End of the range.
      /// @param step Amount to step by.
      constexpr Range(T start, T end, T step = T(1)) noexcept
         : start(start), endp(end), step(step) {}
      
      struct Iterator
      {
         // Items

         /// @brief Current item.
         T current {};

         /// @brief Amount to step by.
         T step {};

         // Constructors

         /// @brief Create a new iterator.
         /// @param start Start of the iterator.
         constexpr Iterator(T start, T step) noexcept
            : current(start), step(step) {}
         
         // Operator overload functions

         /// @brief Get the current value.
         /// @return Current value.
         constexpr T operator*() const noexcept
         {
            return current;
         }

         /// @brief Increment the current by one.
         /// @return Iterator.
         constexpr Iterator& operator++() noexcept
         {
            current += step;
            return *this;
         }

         /// @brief Increment the current by the given number.
         /// @param amount Amount to increment by.
         /// @return Iterator.
         constexpr Iterator& operator+=(T amount) noexcept
         {
            current += amount;
            return *this;
         }

         /// @brief Decrement the current by one.
         /// @return Iterator.
         constexpr Iterator& operator--() noexcept
         {
            current -= step;
            return *this;
         }

         /// @brief Decrement the current by the given number.
         /// @param amount Amount to decrement by.
         /// @return Iterator.
         constexpr Iterator& operator-=(T amount) noexcept
         {
            current -= amount;
            return *this;
         }

         // Comparison functions

         /// @brief Compare two iterators.
         /// @param other Other iterator.
         /// @return True if both are equal.
         constexpr bool operator==(const Iterator& other) const noexcept
         {
            return current == other.current;
         }

         /// @brief Compare two iterators.
         /// @param other Other iterator.
         /// @return True if both are different.
         constexpr bool operator!=(const Iterator& other) const noexcept
         {
            return (step > 0 ? current < other.current : current > other.current);
         }

         /// @brief Compare two iterators.
         /// @param other Other iterator.
         /// @return True if first is smaller than second.
         constexpr bool operator<(const Iterator& other) const noexcept
         {
            return current < other.current;
         }

         /// @brief Compare two iterators.
         /// @param other Other iterator.
         /// @return True if first is bigger than second.
         constexpr bool operator>(const Iterator& other) const noexcept
         {
            return other.current < current;
         }

         /// @brief Compare two iterators.
         /// @param other Other iterator.
         /// @return True if first is second or equal second.
         constexpr bool operator<=(const Iterator& other) const noexcept
         {
            return !(other.current < current);
         }

         /// @brief Compare two iterators.
         /// @param other Other iterator.
         /// @return True if first is bigger or equal second.
         constexpr bool operator>=(const Iterator& other) const noexcept
         {
            return !(current < other.current);
         }
      };

      // Iterator functions

      /// @brief Get iterator begin.
      /// @return Begin.
      constexpr Iterator begin() const noexcept
      {
         return Iterator(start, step);
      }

      /// @brief Get iterator end.
      /// @return End.
      constexpr Iterator end() const noexcept
      {
         return Iterator(endp + 1, step);
      }

      /// @brief Get iterator reverse begin.
      /// @return Reverse begin.
      constexpr Iterator rbegin() const noexcept
      {
         return Iterator(endp + 1, step);
      }

      /// @brief Get iterator reverse end.
      /// @return Reverse end.
      constexpr Iterator rend() const noexcept
      {
         return Iterator(start, step);
      }
   };
} // namespace cx::util

#endif // CX_UTIL_RANGE_HPP
