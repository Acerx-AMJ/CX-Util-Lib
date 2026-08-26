#ifndef CX_UTIL_PAIR_HPP
#define CX_UTIL_PAIR_HPP

#include "Config.hpp" // IWYU pragma: export
#include <utility>

namespace cx::util
{
   /// @brief 2 value container.
   template<typename T, typename U>
   struct Pair
   {
      // Items

      /// @brief First element.
      T first;

      /// @brief Second element.
      U second;

      // Constructors

      /// @brief Create default pair.
      constexpr Pair()
         : first{}, second{} {}

      /// @brief Create a new pair.
      /// @param first First element.
      /// @param second Second element.
      constexpr Pair(const T& first, const U& second)
         : first(first), second(second) {}

      /// @brief Copy a pair.
      /// @param other Other pair.
      template<typename V, typename W>
      constexpr Pair(const Pair<V, W>& other)
         : first(static_cast<T>(other.first)),
         second(static_cast<U>(other.second)) {}

      constexpr Pair(const Pair&) = default;
      constexpr Pair(Pair&&) = default;
      ~Pair() = default;

      // Utility functions

      /// @brief Create a new pair.
      /// @param first First value.
      /// @param second Second value.
      /// @return Created pair.
      template<typename V, typename W>
      static constexpr Pair make(V&& first, W&& second)
      {
         return Pair(std::forward<V>(first), std::forward<W>(second));
      }

      /// @brief Swap two pairs.
      /// @param other Other pair.
      constexpr void swap(Pair& other)
      {
         std::swap(first, other.first);
         std::swap(second, other.second);
      }

      // Comparison functions

      /// @brief Compare two pairs.
      /// @param other Other pair.
      /// @return True if both are identical.
      constexpr bool operator==(const Pair& other) const
      {
         return first == other.first && second == other.second;
      }

      /// @brief Compare two pairs.
      /// @param other Other pair.
      /// @return True if both are different.
      constexpr bool operator!=(const Pair& other) const
      {
         return !(*this == other);
      }

      /// @brief Compare two pairs.
      /// @param other Other pair.
      /// @return True if first is smaller than second.
      constexpr bool operator<(const Pair& other) const
      {
         return first < other.first || (!(other.first < first) && second
            < other.second);
      }

      /// @brief Compare two pairs.
      /// @param other Other pair.
      /// @return True if first is bigger than second.
      constexpr bool operator>(const Pair& other) const
      {
         return other < *this;
      }

      /// @brief Compare two pairs.
      /// @param other Other pair.
      /// @return True if first is smaller or equal second.
      constexpr bool operator<=(const Pair& other) const
      {
         return !(other < *this);
      }

      /// @brief Compare two pairs.
      /// @param other Other pair.
      /// @return True if first is bigger or equal second.
      constexpr bool operator>=(const Pair& other) const
      {
         return !(*this < other);
      }

      // Conversion functions

      /// @brief Convert to a different pair.
      template<typename V, typename W>
      constexpr operator Pair<V, W>() const
      {
         return Pair<V, W>(first, second);
      }
   };
} // namespace cx::util

#endif // CX_UTIL_PAIR_HPP
