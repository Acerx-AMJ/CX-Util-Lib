#ifndef CX_UTIL_ARRAY_HPP
#define CX_UTIL_ARRAY_HPP

#include "Config.hpp" // IWYU pragma: export
#include <cassert>
#include <utility>
#include <cstddef>

namespace cx::util
{
   /// @brief Container containing N items.
   template<typename T, size_t __MAX_SIZE>
   struct Array
   {
   private:
      T rawdata[__MAX_SIZE] {};
   public:
      // Constructors

      /// @brief Create a default array.
      constexpr Array() noexcept
         : rawdata{} {}
      
      /// @brief Create a new array.
      /// @param value Value of all items.
      constexpr Array(const T& value) noexcept
      {
         for (size_t i {}; i < __MAX_SIZE; ++i)
            rawdata[i] = value;
      }

      /// @brief Create a new array.
      /// @param args Values.
      template<typename... Args>
      constexpr Array(Args&&... args)
      {
         assert(sizeof...(args) == __MAX_SIZE && "cx::util::Array argument count must match array size.");
         size_t i {};
         ((rawdata[i++] = std::forward<Args>(args)), ...);
      }

      /// @brief Create new array.
      /// @param list Initializer list.
      constexpr Array(const std::initializer_list<T>& list)
      {
         assert(list.size() == __MAX_SIZE && "cx::util::Array initializer list does not match array size.");
         size_t i {};

         for (const auto& element : list)
            rawdata[i++] = element;
      }

      /// @brief Copy an array.
      /// @param other Other array.
      constexpr Array(const Array& other) noexcept
      {
         for (size_t i {}; i < __MAX_SIZE; ++i)
            rawdata[i] = other[i];
      }

      /// @brief Move an array.
      /// @param other Other array.
      constexpr Array(Array&& other) noexcept
      {
         for (size_t i {}; i < __MAX_SIZE; ++i)
            rawdata[i] = std::move(other[i]);
      }

      /// @brief Create a new array from raw array.
      /// @param array Raw array.
      constexpr Array(const T(&arr)[__MAX_SIZE]) noexcept
      {
         for (size_t i {}; i < __MAX_SIZE; ++i)
            rawdata[i] = arr[i];
      }

      ~Array() = default;

      // Utility functions

      /// @brief Create a new array.
      /// @param value Value.
      /// @return Created array.
      static constexpr Array make(T&& value) noexcept
      {
         return Array(std::forward(value));
      }

      /// @brief Create a new array.
      /// @param args Values.
      /// @return Created array.
      template<typename... Args>
      static constexpr Array make(Args&&... args)
      {
         assert(sizeof...(args) == __MAX_SIZE && "cx::util::Array number of arguments must match array size.");
         return Array{std::forward<Args>(args)...};
      }

      /// @brief Create a new array.
      /// @param list Initializer list.
      /// @return Created array.
      static constexpr Array make(const std::initializer_list<T>& list)
      {
         assert(list.size() == __MAX_SIZE && "cx::util::Array initializer list does not match array size.");
         Array array;
         size_t i {};

         for (const auto& element : list)
            array[i++] = element;
         return array;
      }

      /// @brief Fill array with the value.
      /// @param value Value.
      constexpr void fill(const T& value) noexcept
      {
         for (size_t i {}; i < __MAX_SIZE; ++i)
            rawdata[i] = value;
      }

      /// @brief Clear array.
      constexpr void clear() noexcept
      {
         for (size_t i {}; i < __MAX_SIZE; ++i)
            rawdata[i] = T();
      }

      // Access functions

      /// @brief Get reference of an item.
      /// @param index Index of item.
      /// @return Item reference.
      constexpr T& operator[](size_t index)
      {
         assert(index < __MAX_SIZE && "cx::util::Array index out of bounds.");
         return rawdata[index];
      }

      /// @brief Get item.
      /// @param index Index of item.
      /// @return Item.
      constexpr const T& operator[](size_t index) const
      {
         assert(index < __MAX_SIZE && "cx::util::Array index out of bounds.");
         return rawdata[index];
      }

      /// @brief Get reference of an item.
      /// @param index Index of item.
      /// @return Item reference.
      constexpr T& at(size_t index)
      {
         assert(index < __MAX_SIZE && "cx::util::Array index out of bounds.");
         return rawdata[index];
      }

      /// @brief Get item.
      /// @param index Index of item.
      /// @return Item.
      constexpr const T& at(size_t index) const
      {
         assert(index < __MAX_SIZE && "cx::util::Array index out of bounds.");
         return rawdata[index];
      }

      /// @brief Get item.
      /// @param index Index of item.
      /// @return item.
      constexpr const T& cat(size_t index) const
      {
         assert(index < __MAX_SIZE && "cx::util::Array index out of bounds.");
         return rawdata[index];
      }

      /// @brief Get front item.
      /// @return Front item.
      constexpr T& front() noexcept
      {
         return rawdata[0];
      }

      /// @brief Get front item.
      /// @return Front item.
      constexpr const T& front() const noexcept
      {
         return rawdata[0];
      }

      /// @brief Get back item.
      /// @return Back item.
      constexpr T& back() noexcept
      {
         return rawdata[__MAX_SIZE - 1];
      }

      /// @brief Get back item.
      /// @return Back item.
      constexpr const T& back() const noexcept
      {
         return rawdata[__MAX_SIZE - 1];
      }

      /// @brief Get raw array.
      /// @return Raw array.
      constexpr T* data() const noexcept
      {
         return rawdata;
      }

      /// @brief Get array size.
      /// @return Size.
      constexpr size_t size() const noexcept
      {
         return __MAX_SIZE;
      }

      /// @brief Check if array is empty.
      /// @return True if empty.
      constexpr bool empty() const noexcept
      {
         return __MAX_SIZE == 0;
      }

      // Arithmetic functions

      /// @brief Add two arrays together.
      /// @param other Other array.
      /// @return Sum.
      constexpr Array operator+(const Array& other) const noexcept
      {
         Array<T, __MAX_SIZE> array;

         for (size_t i {}; i < __MAX_SIZE; ++i)
            array[i] = rawdata[i] + other[i];
         return array;
      }

      /// @brief Subtract two arrays apart.
      /// @param other Other array.
      /// @return Difference.
      constexpr Array operator-(const Array& other) const noexcept
      {
         Array<T, __MAX_SIZE> array;

         for (size_t i {}; i < __MAX_SIZE; ++i)
            array[i] = rawdata[i] - other[i];
         return array;
      }

      /// @brief Multiply array by factor.
      /// @param factor Factor.
      /// @return Product.
      constexpr Array operator*(const T& factor) const noexcept
      {
         Array<T, __MAX_SIZE> array;

         for (size_t i {}; i < __MAX_SIZE; ++i)
            array[i] = rawdata[i] * factor;
         return array;
      }

      /// @brief Multiply two arrays.
      /// @param other Other array.
      /// @return Product.
      constexpr Array operator*(const Array& other) const noexcept
      {
         Array<T, __MAX_SIZE> array;

         for (size_t i {}; i < __MAX_SIZE; ++i)
            array[i] = rawdata[i] * other[i];
         return array;
      }

      /// @brief Divide array by factor.
      /// @param factor Factor.
      /// @return Quotient.
      constexpr Array operator/(const T& factor) const
      {
         assert(factor != T(0) && "cx::util::Array division by zero is undefined.");
         Array<T, __MAX_SIZE> array;

         for (size_t i {}; i < __MAX_SIZE; ++i)
            array[i] = rawdata[i] / factor;
         return array;
      }

      /// @brief Divide two arrays apart.
      /// @param other Other array.
      /// @return Quotient.
      constexpr Array operator/(const Array& other) const
      {
         Array<T, __MAX_SIZE> array;

         for (size_t i {}; i < __MAX_SIZE; ++i)
         {
            assert(other[i] != T(0) && "cx::util::Array division by zero is undefined.");
            array[i] = rawdata[i] / other[i];
         }
         return array;
      }

      /// @brief Negate array.
      /// @return Negated array.
      constexpr Array operator-() const
      {
         Array<T, __MAX_SIZE> array;

         for (size_t i {}; i < __MAX_SIZE; ++i)
            array[i] = -rawdata[i];
         return array;
      } 

      // Compound arithmetic functions

      /// @brief Add two arrays together.
      /// @param other Other array.
      /// @return Sum.
      constexpr Array& operator+=(const Array& other) noexcept
      {
         for (size_t i {}; i < __MAX_SIZE; ++i)
            rawdata[i] += other[i];
         return *this;
      }

      /// @brief Subtract two arrays apart.
      /// @param other Other array.
      /// @return Difference.
      constexpr Array& operator-=(const Array& other) noexcept
      {
         for (size_t i {}; i < __MAX_SIZE; ++i)
            rawdata[i] -= other[i];
         return *this;
      }

      /// @brief Multiply array by factor.
      /// @param factor Factor.
      /// @return Product.
      constexpr Array& operator*=(const T& factor) noexcept
      {
         for (size_t i {}; i < __MAX_SIZE; ++i)
            rawdata[i] *= factor;
         return *this;
      }

      /// @brief Multiply two arrays.
      /// @param other Other array.
      /// @return Product.
      constexpr Array& operator*=(const Array& other) noexcept
      {
         for (size_t i {}; i < __MAX_SIZE; ++i)
            rawdata[i] *= other[i];
         return *this;
      }

      /// @brief Divide array by factor.
      /// @param factor Factor.
      /// @return Quotient.
      constexpr Array& operator/=(const T& factor)
      {
         assert(factor != T(0) && "cx::util::Array division by zero is undefined.");

         for (size_t i {}; i < __MAX_SIZE; ++i)
            rawdata[i] /= factor;
         return *this;
      }

      /// @brief Divide two arrays apart.
      /// @param other Other array.
      /// @return Quotient.
      constexpr Array& operator/=(const Array& other)
      {
         for (size_t i {}; i < __MAX_SIZE; ++i)
         {
            assert(other[i] != T(0) && "cx::util::Array division by zero is undefined.");
            rawdata[i] /= other[i];
         }
         return *this;
      }

      // Assignment functions

      /// @brief Copy an array.
      /// @param other Other array.
      /// @return Copied array.
      constexpr Array& operator=(const Array& other) noexcept
      {
         if (this == &other)
            return *this;

         for (size_t i {}; i < __MAX_SIZE; ++i)
            rawdata[i] = other[i];
         return *this;
      }

      // Comparison functions

      /// @brief Compare two arrays.
      /// @param other Other array.
      /// @return True if both are identical.
      constexpr bool operator==(const Array& other) const noexcept
      {
         for (size_t i {}; i < __MAX_SIZE; ++i)
            if (rawdata[i] != other[i])
               return false;
         return true;
      }

      /// @brief Compare two arrays.
      /// @param other Other array.
      /// @return True if both are different.
      constexpr bool operator!=(const Array& other) const noexcept
      {
         return !(*this == other);
      }

      /// @brief Compare two arrays.
      /// @param other Other array.
      /// @return True if first is smaller than second.
      constexpr bool operator<(const Array& other) const noexcept
      {
         for (size_t i {}; i < __MAX_SIZE; ++i)
         {
            if (rawdata[i] < other.data[i])
               return true;
            else if (other.data[i] < rawdata[i])
               return false;
         }
         return false;
      }

      /// @brief Compare two arrays.
      /// @param other Other array.
      /// @return True if first is bigger than second.
      constexpr bool operator>(const Array& other) const noexcept
      {
         return other < *this;
      }

      /// @brief Compare two arrays.
      /// @param other Other array.
      /// @return True if first is smaller or equal second.
      constexpr bool operator<=(const Array& other) const noexcept
      {
         return !(other < *this);
      }

      /// @brief Compare two arrays.
      /// @param other Other array.
      /// @return True if first is bigger or equal second.
      constexpr bool operator>=(const Array& other) const noexcept
      {
         return !(*this < other);
      }

      // Iterator functions

      /// @brief Get begin iterator.
      /// @return Begin iterator.
      constexpr T* begin() noexcept
      {
         return rawdata;
      }

      /// @brief Get begin iterator.
      /// @return Begin iterator.
      constexpr const T* begin() const noexcept
      {
         return rawdata;
      }

      /// @brief Get end iterator.
      /// @return End iterator.
      constexpr T* end() noexcept
      {
         return rawdata + __MAX_SIZE;
      }

      /// @brief Get end iterator.
      /// @return End iterator.
      constexpr const T* end() const noexcept
      {
         return rawdata + __MAX_SIZE;
      }

      /// @brief Get constant begin iterator.
      /// @return Begin iterator.
      constexpr const T* cbegin() const noexcept
      {
         return rawdata;
      }

      /// @brief Get constant end iterator.
      /// @return End iterator.
      constexpr const T* cend() const noexcept
      {
         return rawdata + __MAX_SIZE;
      }

      /// @brief Get reverse begin iterator.
      /// @return Reverse begin iterator.
      constexpr T* rbegin() noexcept
      {
         return rawdata + __MAX_SIZE - 1;
      }

      /// @brief Get reverse begin iterator.
      /// @return Reverse begin iterator.
      constexpr const T* rbegin() const noexcept
      {
         return rawdata + __MAX_SIZE - 1;
      }

      /// @brief Get reverse end iterator.
      /// @return Reverse end iterator.
      constexpr T* rend() noexcept
      {
         return rawdata - 1;
      }

      /// @brief Get reverse end iterator.
      /// @return Reverse end iterator.
      constexpr const T* rend() const noexcept
      {
         return rawdata - 1;
      }

      /// @brief Get constant reverse begin iterator.
      /// @return Reverse begin iterator.
      constexpr const T* crbegin() const noexcept
      {
         return rawdata + __MAX_SIZE - 1;
      }

      /// @brief Get constant reverse end iterator.
      /// @return Reverse end iterator.
      constexpr const T* crend() const noexcept
      {
         return rawdata - 1;
      }
   };
} // namespace cx::util

#endif // CX_UTIL_ARRAY_HPP
