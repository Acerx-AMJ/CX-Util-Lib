#ifndef CX_UTIL_TRIPLE_HPP
#define CX_UTIL_TRIPLE_HPP

#include "Config.hpp" // IWYU pragma: export
#include <utility>

namespace cx::util
{
   /// @brief 3 value container.
   template<typename T, typename Y, typename U>
   struct Triple
   {
      // Items

      /// @brief First item.
      T first;

      /// @brief Second item.
      Y second;

      /// @brief Third item.
      U third;

      // Constructors

      /// @brief Create default triple.
      constexpr Triple()
         : first{}, second{}, third{} {}

      /// @brief Create a new triple.
      /// @param first First element.
      /// @param second Second element.
      /// @param third Third element.
      constexpr Triple(const T& first, const Y& second, const U& third)
         : first(first), second(second), third(third) {}

      /// @brief Copy a triple.
      /// @param other Other triple.
      template<typename V, typename W, typename M>
      constexpr Triple(const Triple<V, W, M>& other)
         : first(static_cast<T>(other.first)),
         second(static_cast<Y>(other.second)),
         third(static_cast<U>(other.third)) {}
      
      constexpr Triple(const Triple&) = default;
      constexpr Triple(Triple&&) = default;
      ~Triple() = default;

      // Utility functions

      /// @brief Create a new triple.
      /// @param first First value.
      /// @param second Second value.
      /// @param third Third value.
      /// @return Created triple.
      template<typename V, typename W, typename M>
      static constexpr Triple make(V&& first, W&& second, M&& third)
      {
         return Triple(std::forward<V>(first), std::forward<W>(second),
            std::forward<M>(third));
      }

      /// @brief Swap two triples.
      /// @param other Other triple.
      constexpr void swap(Triple& other)
      {
         std::swap(first, other.first);
         std::swap(second, other.second);
         std::swap(third, other.third);
      }

      // Comparison functions

      /// @brief Compare two triples.
      /// @param other Other triple.
      /// @return True if both are identical.
      constexpr bool operator==(const Triple& other) const
      {
         return first == other.first && second == other.second
            && third == other.third;
      }

      /// @brief Compare two triples.
      /// @param other Other triple.
      /// @return True if both are different.
      constexpr bool operator!=(const Triple& other) const
      {
         return !(*this == other);
      }

      /// @brief Compare two triples.
      /// @param other Other triple.
      /// @return True if first is smaller than second.
      constexpr bool operator<(const Triple& other) const
      {
         return first < other.first || (!(other.first < first)
            && (second < other.second || (!(other.second < second)
            && third < other.third)));
      }

      /// @brief Compare two triples.
      /// @param other Other triple.
      /// @return True if first is bigger than second.
      constexpr bool operator>(const Triple& other) const
      {
         return other < *this;
      }

      /// @brief Compare two triples.
      /// @param other Other triple.
      /// @return True if first is smaller or equal second.
      constexpr bool operator<=(const Triple& other) const
      {
         return !(other < *this);
      }

      /// @brief Compare two triples.
      /// @param other Other triple.
      /// @return True if first is bigger or equal second.
      constexpr bool operator>=(const Triple& other) const
      {
         return !(*this < other);
      }

      // Conversion functions

      /// @brief Convert to a different pair.
      template<typename V, typename W, typename M>
      constexpr operator Triple<V, W, M>() const
      {
         return Triple<V, W, M>(first, second, third);
      }
   };
} // namespace cx::util

#endif // CX_UTIL_TRIPLE_HPP
