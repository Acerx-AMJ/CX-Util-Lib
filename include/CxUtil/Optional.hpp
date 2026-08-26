#ifndef CX_UTIL_OPTIONAL_HPP
#define CX_UTIL_OPTIONAL_HPP

#include "Config.hpp" // IWYU pragma: export
#include <cassert>
#include <utility>

namespace cx::util
{
   /// @brief Return a value or no value.
   template<typename T>
   class Optional
   {
   public:
      // Constructors

      /// @brief Create an invalid optional.
      constexpr Optional() noexcept
         : valid(false) {}

      /// @brief Create a valid optional.
      /// @param value Value.
      constexpr Optional(const T& value) noexcept
         : object(value), valid(true) {}

      constexpr Optional(const Optional&) = default;
      constexpr Optional(Optional&&) = default;
      ~Optional() = default;

      // Utility functions

      /// @brief Create a new optional.
      /// @return Optional.
      static constexpr Optional make() noexcept
      {
         return Optional();
      }

      /// @brief Create a new optional.
      /// @param value Value.
      /// @return Optional.
      static constexpr Optional make(const T& value) noexcept
      {
         return Optional(value);
      }

      /// @brief Emplace a value into the optional.
      /// @param value Value.
      /// @return Optional.
      constexpr Optional& emplace(const T& value) noexcept
      {
         object = value;
         valid = true;
         return *this;
      }

      /// @brief Emplace a value into the optional.
      /// @param value Value.
      /// @return Optional.
      template<typename... Args>
      constexpr Optional& emplace(Args&&... args) noexcept
      {
         object = T(std::forward<Args>(args)...);
         valid = true;
         return *this;
      }

      /// @brief Reset the value to be invalid.
      constexpr void reset() noexcept
      {
         if (valid)
         {
            object.~T();
            valid = false;
         }
      }

      // Access functions

      /// @brief Check if value is valid.
      /// @return True if valid.
      constexpr bool hasValue() const noexcept
      {
         return valid;
      }

      /// @brief Get value if it's valid.
      /// @return Value.
      constexpr T& value()
      {
         assert(valid && "cx::util::Optional tried to access invalid optional.");
         return object;
      }

      /// @brief Get value if it's valid.
      /// @return Value.
      constexpr const T& value() const
      {
         assert(valid && "cx::util::Optional tried to access invalid optional.");
         return object;
      }

      /// @brief Get value or default value if it's invalid.
      /// @param defaultValue Default value.
      /// @return Value.
      constexpr T& valueOr(T& defaultValue) noexcept
      {
         return (valid ? object : defaultValue);
      }

      /// @brief Get value or default value if it's invalid.
      /// @param defaultValue Default value.
      /// @return Value.
      constexpr const T& valueOr(const T& defaultValue) const noexcept
      {
         return (valid ? object : defaultValue);
      }

      /// @brief Get value or default value if it's invalid.
      /// @param defaultValue Default value.
      /// @return Value.
      template<typename U>
      constexpr T valueOr(U&& defaultValue) const noexcept
         requires(!std::is_same_v<std::remove_cvref_t<U>, T>)
      {
         return (valid ? object : std::forward<U>(defaultValue));
      }

      // Operator access functions

      /// @brief Check if value is valid.
      /// @return True if valid.
      constexpr operator bool() const noexcept
      {
         return valid;
      }

      // Assignment functions

      /// @brief Copy an optional.
      /// @param other Other optional.
      /// @return Copied optional.
      constexpr Optional& operator=(const Optional& other) noexcept
      {
         if (this == &other)
            return *this;

         valid = other.valid;
         if (valid)
            object = other.object;

         return *this;
      }

      /// @brief Move an optional.
      /// @param other Other optional.
      /// @return Moved optional.
      constexpr Optional& operator=(Optional&& other) noexcept
      {
         if (this == &other)
            return *this;

         valid = other.valid;
         if (valid)
            object = std::move(other.object);
         
         return *this;
      }

      // Comparison functions

      /// @brief Compare two optionals.
      /// @param other Other optional.
      /// @return True if both are identical.
      constexpr bool operator==(const Optional& other) const noexcept
      {
         return valid == other.valid && (!valid || object == other.object);
      }

      /// @brief Compare two optionals.
      /// @param other Other optional.
      /// @return True if both are different.
      constexpr bool operator!=(const Optional& other) const noexcept
      {
         return !(*this == other);
      }

   private:
      T object;
      bool valid;
   };
} // namespace cx::util

#endif // CX_UTIL_OPTIONAL_HPP
