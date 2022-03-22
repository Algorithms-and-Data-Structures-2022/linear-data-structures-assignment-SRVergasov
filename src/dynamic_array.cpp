#include "assignment/dynamic_array.hpp"

#include <algorithm>  // copy, fill
#include <stdexcept>  // invalid_argument (НЕЛЬЗЯ ИСПОЛЬЗОВАТЬ)

namespace assignment {

  DynamicArray::DynamicArray(int capacity) {

    // выбрасываем ошибку, если указана неположительная емкость массива
    if (capacity <= 0) {
      throw std::invalid_argument("capacity is not positive");
    }

    capacity_ = capacity;
    data_ = new int[capacity_];
    for (int i = 0; i < capacity; i++) {
      data_[i] = 0;
    }
  }

  DynamicArray::~DynamicArray() {
    delete[] data_;
    data_ = nullptr;
    capacity_ = 0;
    size_ = 0;
  }

  void DynamicArray::Add(int value) {
    if (size_ < capacity_) {
      data_[size_++] = value;
    } else {
      Resize(capacity_ + kCapacityGrowthCoefficient);
      data_[size_++] = value;
    }
  }

  bool DynamicArray::Insert(int index, int value) {
    if (index < 0 || index > size_) {
      return false;
    }

    if (size_ >= capacity_) {
      Resize(capacity_ + kCapacityGrowthCoefficient);
    }

    for (int i = size_ - 1; i >= index; i--) {
      data_[i + 1] = data_[i];
    }
    data_[index] = value;
    size_++;
    return true;
  }

  bool DynamicArray::Set(int index, int new_value) {
    if (index < 0 || index >= size_) {
      return false;
    }
    data_[index] = new_value;
    return true;
  }

  std::optional<int> DynamicArray::Remove(int index) {
    if (index < 0 || index >= size_) {
      return std::nullopt;
    }

    int value = data_[index];
    for (int i = index; i < size_; i++) {
      data_[i] = data_[i + 1];
    }
    size_--;
    return value;
  }

  void DynamicArray::Clear() {
    size_ = 0;
  }

  std::optional<int> DynamicArray::Get(int index) const {
    if (index < 0 || index >= size_) {
      return std::nullopt;
    }
    return data_[index];
  }

  std::optional<int> DynamicArray::IndexOf(int value) const {
    for (int i = 0; i < size_; i++) {
      if (data_[i] == value) {
        return i;
      }
    }
    return std::nullopt;
  }

  bool DynamicArray::Contains(int value) const {
    for (int i = 0; i < size_; i++) {
      if (data_[i] == value) {
        return true;
      }
    }
    return false;
  }

  bool DynamicArray::IsEmpty() const {
    return size() == 0;
  }

  int DynamicArray::size() const {
    return size_;
  }

  int DynamicArray::capacity() const {
    return capacity_;
  }

  bool DynamicArray::Resize(int new_capacity) {
    if (new_capacity <= capacity_) {
      return false;
    }

    int* newData = new int[new_capacity];
    for (int i = 0; i < size_; i++) {
      newData[i] = data_[i];
    }

    delete[] data_;
    data_ = newData;
    newData = nullptr;
    capacity_ = new_capacity;

    return true;
  }

  // ДЛЯ ТЕСТИРОВАНИЯ
  DynamicArray::DynamicArray(const std::vector<int>& values, int capacity) {

    size_ = static_cast<int>(values.size());
    capacity_ = capacity;

    data_ = new int[capacity]{};

    std::copy(values.data(), values.data() + size_, data_);
  }

  std::vector<int> DynamicArray::toVector(std::optional<int> size) const {

    if (capacity_ == 0 || data_ == nullptr) {
      return {};
    }

    if (size.has_value()) {
      return {data_, data_ + size.value()};
    }

    return {data_, data_ + capacity_};
  }

}  // namespace assignment