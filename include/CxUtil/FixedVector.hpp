#ifndef CX_UTIL_STATIC_VECTOR_HPP
#define CX_UTIL_STATIC_VECTOR_HPP

#include "Config.hpp" // IWYU pragma: export
#include <utility>
#include <cassert>
#include <cstddef>

namespace cx::util
{
   /// @brief Container containing N items.
   template<typename __CTYPE, size_t __MAX_SIZE>
   struct FixedVector
   {
   private:
      __CTYPE __DATA[__MAX_SIZE] {};
      size_t __INDEX {};
   public:
      // Constructors

      /// @brief Create a default vector.
      constexpr FixedVector() noexcept
         : __DATA{}, __INDEX{} {}
      
      /// @brief Create a new vector.
      /// @param args Values.
      template<typename... __ARGS>
      constexpr FixedVector(__ARGS&&... args)
      {
         assert(sizeof...(args) <= __MAX_SIZE && "cx::util::FixedVector argument count cannot be bigger than vector size.");
         size_t i {};
         ((__DATA[i++] = std::forward<__ARGS>(args)), ...);
         __INDEX = sizeof...(args) - 1;
      }

      /// @brief Create a new vector.
      /// @param list Initializer list.
      constexpr FixedVector(const std::initializer_list<__CTYPE>& list)
      {
         assert(list.size() <= __MAX_SIZE && "cx::util::FixedVector initializer list size cannot be bigger than vector size.");
         size_t i {};

         for (const auto& element : list)
            __DATA[i++] = element;
         __INDEX = list.size() - 1;
      }

      /// @brief Copy a vector.
      /// @param other Other vector.
      constexpr FixedVector(const FixedVector& other) noexcept
      {
         __INDEX = other.__INDEX;
         for (size_t i {}; i < __MAX_SIZE; ++i)
            __DATA[i] = other.__DATA[i];
      }

      /// @brief Move a vector.
      /// @param other Other array.
      constexpr FixedVector(FixedVector&& other) noexcept
      {
         __INDEX = other.__INDEX;
         for (size_t i {}; i < __MAX_SIZE; ++i)
            __DATA[i] = std::move(other.__DATA[i]);
      }

      /// @brief Create a new vector from raw array.
      /// @param array Raw array.
      constexpr FixedVector(const __CTYPE(&arr)[__MAX_SIZE]) noexcept
      {
         for (size_t i {}; i < __MAX_SIZE; ++i)
            __DATA[i] = arr[i];
      }

      /// @brief Clean up the leftover values.
      ~FixedVector()
      {
         for (size_t i {}; i < __MAX_SIZE; ++i)
            __DATA[i].~__CTYPE();
      }

      // Utility functions

      /// @brief Create a new vector.
      /// @param args Values.
      /// @return Created vector.
      template<typename... __ARGS>
      static constexpr FixedVector make(__ARGS&&... args)
      {
         assert(sizeof...(args) <= __MAX_SIZE && "cx::util::FixedVector argument count cannot be bigger than vector size.");
         return FixedVector{std::forward<__ARGS>(args)...};
      }

      /// @brief Create a new vector.
      /// @param list Initializer list.
      /// @return Created vector.
      static constexpr FixedVector make(const std::initializer_list<__CTYPE>& list)
      {
         assert(list.size() <= __MAX_SIZE && "cx::util::FixedVector initializer list size cannot be bigger than vector size.");
         FixedVector vector;
         size_t i {};

         for (const auto& element : list)
            vector.__DATA[i++] = element;

         vector.__INDEX = list.size() - 1;
         return std::move(vector);
      }

      /// @brief Fill vector with the value.
      /// @param value Value.
      constexpr void fill(const __CTYPE& value) noexcept
      {
         __INDEX = __MAX_SIZE - 1;
         for (size_t i {}; i < __MAX_SIZE; ++i)
            __DATA[i] = value;
      }

      /// @brief Clear vector.
      constexpr void clear() noexcept
      {
         for (size_t i {}; i <= __INDEX; ++i)
            __DATA[i].~__CTYPE();
         __INDEX = 0;
      }

      /// @brief Push back a value.
      /// @param value Value.
      constexpr void push(const __CTYPE& value)
      {
         assert(__INDEX + 1 < __MAX_SIZE && "cx::util::FixedVector cannot push value as vector is full.");
         __DATA[++__INDEX] = value;
      }

      /// @brief Push back a value.
      /// @param value Value.
      constexpr void push(__CTYPE&& value)
      {
         assert(__INDEX + 1 < __MAX_SIZE && "cx::util::FixedVector cannot push value as vector is full.");
         __DATA[++__INDEX] = std::forward<__CTYPE>(value);
      }

      /// @brief Push back a value.
      /// @param args Arguments.
      template<typename... __ARGS>
      constexpr void push(__ARGS&&... args)
      {
         assert(__INDEX + 1 < __MAX_SIZE && "cx::util::FixedVector cannot push value as vector is full.");
         __DATA[++__INDEX] = __CTYPE((std::forward<__ARGS>(args), ...));
      }

      /// @brief Emplace a value.
      /// @param args Arguments.
      template<typename... __ARGS>
      constexpr void emplace(__ARGS&&... args)
      {
         assert(__INDEX + 1 < __MAX_SIZE && "cx::util::FixedVector cannot emplace value as vector is full.");
         new (&__DATA[++__INDEX]) __CTYPE(std::forward<__ARGS>(args)...);
      }

      /// @brief Pop back a value.
      constexpr void pop()
      {
         assert(__INDEX > 0 && "cx::util::FixedVector cannot pop from empty vector.");
         __DATA[__INDEX].~__CTYPE();
         --__INDEX;
      }

      // Access functions

      /// @brief Get item by index.
      /// @param index Index of item.
      /// @return Item.
      constexpr __CTYPE& operator[](size_t index)
      {
         assert(index <= __INDEX && "cx::util::FixedVector index out of bounds.");
         return __DATA[index];
      }

      /// @brief Get item by index.
      /// @param index Index of item.
      /// @return Item.
      constexpr const __CTYPE& operator[](size_t index) const
      {
         assert(index <= __INDEX && "cx::util::FixedVector index out of bounds.");
         return __DATA[index];
      }

      /// @brief Get item by index.
      /// @param index Index of item.
      /// @return Item.
      constexpr __CTYPE& at(size_t index)
      {
         assert(index <= __INDEX && "cx::util::FixedVector index out of bounds.");
         return __DATA[index];
      }

      /// @brief Get item by index.
      /// @param index Index of item.
      /// @return Item.
      constexpr const __CTYPE& at(size_t index) const
      {
         assert(index <= __INDEX && "cx::util::FixedVector index out of bounds.");
         return __DATA[index];
      }

      /// @brief Get item by index.
      /// @param index Index of item.
      /// @return Item.
      constexpr const __CTYPE& cat(size_t index) const
      {
         assert(index <= __INDEX && "cx::util::FixedVector index out of bounds.");
         return __DATA[index];
      }

      /// @brief Get front item.
      /// @return Front item.
      constexpr __CTYPE& front() noexcept
      {
         return __DATA[0];
      }

      /// @brief Get front item.
      /// @return Front item.
      constexpr const __CTYPE& front() const noexcept
      {
         return __DATA[0];
      }

      /// @brief Get back item.
      /// @return Back item.
      constexpr __CTYPE& back() noexcept
      {
         return __DATA[__INDEX];
      }

      /// @brief Get back item.
      /// @return Back item.
      constexpr const __CTYPE& back() const noexcept
      {
         return __DATA[__INDEX];
      }

      /// @brief Get raw array.
      /// @return Raw array.
      constexpr __CTYPE* data() const noexcept
      {
         return __DATA;
      }

      /// @brief Get vector size.
      /// @return Size.
      constexpr size_t size() const noexcept
      {
         return __INDEX + 1;
      }

      /// @brief Get vector maximum size.
      /// @return Maximum size.
      constexpr size_t capacity() const noexcept
      {
         return __MAX_SIZE;
      }

      /// @brief Check if vector is empty.
      /// @return True if empty.
      constexpr bool empty() const noexcept
      {
         return __INDEX == 0;
      }

      // Assignment functions

      /// @brief Copy a vector.
      /// @param other Other vector.
      /// @return Copied vector.
      constexpr FixedVector& operator=(const FixedVector& other) noexcept
      {
         if (this == &other) return *this;

         __INDEX = other.__INDEX;
         for (size_t i {}; i < __MAX_SIZE; ++i)
            __DATA[i] == other.__DATA[i];
         return *this;
      }

      // Comparison functions

      /// @brief Compare two vectors.
      /// @param other Other vector.
      /// @return True if both are identical.
      constexpr bool operator==(const FixedVector& other) const noexcept
      {
         for (size_t i {}; i < __MAX_SIZE; ++i)
            if (__DATA[i] != other.__DATA[i])
               return false;
         return true;
      }

      /// @brief Compare two vectors.
      /// @param other Other vector.
      /// @return True if both are different.
      constexpr bool operator!=(const FixedVector& other) const noexcept
      {
         return !(*this == other);
      }

      /// @brief Compare two vectors.
      /// @param other Other vector.
      /// @return True if first is smaller than second.
      constexpr bool operator<(const FixedVector& other) const noexcept
      {
         for (size_t i {}; i < __MAX_SIZE; ++i)
         {
            if (__DATA[i] < other.__DATA[i])
               return true;
            else if (other.__DATA[i] < __DATA[i])
               return false;
         }
         return false;
      }

      /// @brief Compare two vectors.
      /// @param other Other vector.
      /// @return True if first is bigger than second.
      constexpr bool operator>(const FixedVector& other) const noexcept
      {
         return other < *this;
      } 

      /// @brief Compare two vectors.
      /// @param other Other vector.
      /// @return True if first is smaller or equal second.
      constexpr bool operator<=(const FixedVector& other) const noexcept
      {
         return !(other < *this);
      }

      /// @brief Compare two vectors.
      /// @param other Other vector.
      /// @return True if first is bigger or equal second.
      constexpr bool operator>=(const FixedVector& other) const noexcept
      {
         return !(*this < other);
      }

      // Iterator functions

      /// @brief Get iterator begin.
      /// @return Begin.
      constexpr __CTYPE* begin() noexcept
      {
         return __DATA;
      }

      /// @brief Get iterator begin.
      /// @return Begin.
      constexpr const __CTYPE* begin() const noexcept
      {
         return __DATA;
      }

      /// @brief Get iterator end.
      /// @return End.
      constexpr __CTYPE* end() noexcept
      {
         return __DATA + __INDEX + 1;
      }

      /// @brief Get iterator end.
      /// @return End.
      constexpr const __CTYPE* end() const noexcept
      {
         return __DATA + __INDEX + 1;
      }

      /// @brief Get constant iterator begin.
      /// @return Begin.
      constexpr const __CTYPE* cbegin() const noexcept
      {
         return __DATA;
      }

      /// @brief Get constant iterator end.
      /// @return End.
      constexpr const __CTYPE* cend() const noexcept
      {
         return __DATA + __INDEX + 1;
      }

      /// @brief Get iterator reverse begin.
      /// @return Reverse begin.
      constexpr __CTYPE* rbegin() noexcept
      {
         return __DATA + __INDEX;
      }

      /// @brief Get iterator reverse begin.
      /// @return Reverse begin.
      constexpr const __CTYPE* rbegin() const noexcept
      {
         return __DATA + __INDEX;
      }

      /// @brief Get iterator reverse end.
      /// @return Reverse end.
      constexpr __CTYPE* rend() noexcept
      {
         return __DATA - 1;
      }

      /// @brief Get iterator reverse end.
      /// @return Reverse end.
      constexpr const __CTYPE* rend() const noexcept
      {
         return __DATA - 1;
      }

      /// @brief Get constant iterator reverse begin.
      /// @return Reverse begin.
      constexpr const __CTYPE* crbegin() const noexcept
      {
         return __DATA + __INDEX;
      }

      /// @brief Get constant iterator reverse end.
      /// @return Reverse end.
      constexpr const __CTYPE* crend() const noexcept
      {
         return __DATA - 1;
      }
   };
} // namespace cx::util

#endif // CX_UTIL_STATIC_VECTOR_HPP
