#ifndef CX_UTIL_RESULT_HPP
#define CX_UTIL_RESULT_HPP

#include "Config.hpp" // IWYU pragma: export
#include <cassert>
#include <utility>

namespace cx::util
{
   template<typename T, typename E>
   struct Result
   {
   private:
      bool okay = false;
      union
      {
         T value;
         E error;
      };
   public:

      // Constructors

      /// @brief Create a new result.
      /// @param value Value.
      constexpr Result(const T& value)
         : okay(true), value(value) {}
      
      /// @brief Create a new result.
      /// @param error Error.
      constexpr Result(const E& error)
         : okay(false), error(error) {}
      
      /// @brief Move the result.
      /// @param value Value.
      constexpr Result(T&& value) noexcept
         : okay(true), value(std::move(value)) {}

      /// @brief Move the result.
      /// @param error Error.
      constexpr Result(E&& error) noexcept
         : okay(false), error(std::move(error)) {}
      
      /// @brief Move the result.
      /// @param other Other result.
      constexpr Result(Result&& other) noexcept
         : okay(other.okay)
      {
         if (okay)
            new (&value) T(std::move(other.value));
         else
            new (&error) E(std::move(other.error));
      }

      /// @brief Destroy the result.
      ~Result()
      {
         if (okay)
            value.~T();
         else
            error.~E();
      }

      // Emplace functions

      /// @brief Emplace new value.
      /// @param args Arguments of the value.
      template<typename... Args>
      constexpr void emplaceValue(Args&&... args) noexcept
      {
         if (!okay)
            error.~E();
         new (&value) T(std::forward<Args>(args)...);
         okay = true;
      }

      /// @brief Emplace new error.
      /// @param args Arguments of the error.
      template<typename... Args>
      constexpr void emplaceError(Args&&... args) noexcept
      {
         if (okay)
            value.~T();
         new (&error) E(std::forward<Args>(args)...);
         okay = false;
      }

      // Access functions

      /// @brief Check if result is okay.
      /// @return True if okay.
      constexpr bool ok() const noexcept
      {
         return okay;
      }

      /// @brief Get result value.
      /// @return Value.
      constexpr T& unwrap()
      {
         assert(okay && "cx::util::Result attempted to get value of an error result.");
         return value;
      }

      /// @brief Get result value.
      /// @return Value.
      constexpr const T& unwrap() const
      {
         assert(okay && "cx::util::Result attempted to get value of an error result.");
         return value;
      }

      /// @brief Get result value or default value if it's not okay.
      /// @param defaultValue Default value.
      /// @return Value.
      constexpr T& unwrapOr(T& defaultValue) noexcept
      {
         return (okay ? value : defaultValue);
      }

      /// @brief Get result value or default value if it's not okay.
      /// @param defaultValue Default value.
      /// @return Value.
      constexpr const T& unwrapOr(const T& defaultValue) const noexcept
      {
         return (okay ? value : defaultValue);
      }

      /// @brief Get result value or default value if it's not okay.
      /// @param defaultValue Default value.
      /// @return Value.
      template<typename U>
      constexpr T unwrapOr(U&& defaultValue) const noexcept
         requires(!std::is_same_v<std::remove_cvref_t<U>, T>)
      {
         return (okay ? defaultValue : std::forward<U>(defaultValue));
      }

      /// @brief Get result error.
      /// @return Error.
      constexpr E& getError()
      {
         assert(!okay && "cx::util::Result attempted to get error of a value result.");
         return error;
      }

      /// @brief Get result error.
      /// @return Error.
      constexpr const E& getError() const
      {
         assert(!okay && "cx::util::Result attempted to get error of a value result.");
         return error;
      }

      // Comparison functions

      /// @brief Compare two results.
      /// @param other Other result.
      /// @return True if both are equal.
      constexpr bool operator==(const Result& other) const noexcept
      {
         if (okay != other.okay) return false;
         return (okay ? value == other.value : error == other.error);
      }

      /// @brief Compare two results.
      /// @param other Other result.
      /// @return True if both are different.
      constexpr bool operator!=(const Result& other) const noexcept
      {
         return !(*this == other);
      }

      // Operator access functions

      /// @brief Check if result is okay.
      /// @return True if okay.
      constexpr operator bool() const noexcept
      {
         return okay;
      }

      // Assignment operator

      /// @brief Move a result.
      /// @param other Other result.
      constexpr Result& operator=(Result&& other) noexcept
      {
         if (this == &other)
            return *this;

         if (okay)
            value.~T();
         else
            error.~E();

         okay = other.okay;

         if (okay)
            new (&value) T(std::move(other.value));
         else
            new (&error) E(std::move(other.error));

         return *this;
      }
   };
} // namespace cx::util

#endif // CX_UTIL_RESULT_HPP
