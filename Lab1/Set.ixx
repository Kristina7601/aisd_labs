export module Set;
import std;

export template <typename T>
class Set {
private:
	T* _data;
	size_t _size;
	size_t _capacity;
	static constexpr double _epsilon = 1e-9;

	void reallocate(size_t new_capacity) {
		T* new_data = new T[new_capacity]();
		size_t n = (new_capacity < _size) ? new_capacity : _size;
		for (size_t i = 0; i < n; ++i) {
			new_data[i] = _data[i];
		}
		delete[] _data;
		_data = new_data;
		_capacity = new_capacity;
	}

	static bool is_equal(const T& lhs, const T& rhs) {
		if constexpr (std::is_floating_point_v<T>) {
			double diff = static_cast<double>(lhs) - static_cast<double>(rhs);
			return std::abs(diff) < _epsilon;
		}
		else if constexpr (std::is_same_v<T, std::pair<int, double>>) {
			return lhs.first == rhs.first && std::abs(lhs.second - rhs.second) < _epsilon;
		}
		else {
			return lhs == rhs;
		}
	}

	size_t find_index(const T& value) const {
		for (size_t i = 0; i < _size; ++i) {
			if (is_equal(_data[i], value)) {
				return i;
			}
		}
		return _size;
	}

public:
	Set() : _data(new T[1]()), _size(0), _capacity(1) {}

	Set(const T* values, size_t count) : _data(new T[count > 0 ? count : 1]()), _size(0), _capacity(count > 0 ? count : 1) {
		if (values == nullptr && count > 0) {
			throw std::invalid_argument("Null pointer passed with non-zero count");
		}
		for (size_t i = 0; i < count; ++i) {
			*this += values[i];
		}
	}

	Set(size_t count, const T& min_value, const T& max_value) : _data(new T[count > 0 ? count : 1]()), _size(0), _capacity(count > 0 ? count : 1) {
		if constexpr (std::is_arithmetic_v<T>) {
			if (count > 0 && !(min_value < max_value)) {
				throw std::invalid_argument("Min value must be less than max value");
			}

			std::mt19937 gen(std::random_device{}());
			size_t attempts = 0;
			size_t max_attempts = count * 100 + 100;

			while (_size < count && attempts < max_attempts) {
				T val;
				if constexpr (std::is_integral_v<T>) {
					std::uniform_int_distribution<T> dist(min_value, max_value);
					val = dist(gen);
				}
				else {
					std::uniform_real_distribution<T> dist(min_value, max_value);
					val = dist(gen);
				}
				*this += val;
				++attempts;
			}
			if (_size < count) {
				throw std::runtime_error("Cannot generate enough unique values in range");
			}
		}
		else {
			throw std::invalid_argument("Random fill requires arithmetic type");
		}
	}

	Set(const Set& other) : _data(new T[other._capacity]()), _size(other._size), _capacity(other._capacity) {
		for (size_t i = 0; i < _size; ++i) {
			_data[i] = other._data[i];
		}
	}

	Set& operator=(const Set& other) {
		if (this != &other) {
			T* new_data = new T[other._capacity]();
			for (size_t i = 0; i < other._size; ++i) {
				new_data[i] = other._data[i];
			}
			delete[] _data;
			_data = new_data;
			_capacity = other._capacity;
			_size = other._size;
		}
		return *this;
	}

	~Set() {
		delete[] _data;
	}

	size_t size() const {
		return _size;
	}

	bool is_empty() const {
		return _size == 0;
	}

	T& operator[](size_t index) {
		if (index >= _size) {
			throw std::out_of_range("Index out of set bounds");
		}
		return _data[index];
	}

	const T& operator[](size_t index) const {
		if (index >= _size) {
			throw std::out_of_range("Index out of set bounds");
		}
		return _data[index];
	}

	bool contains(const T& value) const {
		return find_index(value) != _size;
	}

	Set& operator+=(const T& value) {
		if (!contains(value)) {
			if (_size == _capacity) {
				reallocate(_capacity == 0 ? 4 : _capacity * 2);
			}
			_data[_size++] = value;
		}
		return *this;
	}

	Set& operator-=(const T& value) {
		size_t index = find_index(value);
		if (index != _size) {
			_data[index] = _data[_size - 1];
			--_size;
		}
		return *this;
	}

	Set operator+(const T& value) const {
		Set result(*this);
		result += value;
		return result;
	}

	Set operator-(const T& value) const {
		Set result(*this);
		result -= value;
		return result;
	}

	Set operator+(const Set& other) const {
		Set result(*this);
		for (size_t i = 0; i < other._size; ++i) {
			result += other._data[i];
		}
		return result;
	}

	Set operator-(const Set& other) const {
		Set result;
		for (size_t i = 0; i < _size; ++i) {
			if (!other.contains(_data[i])) {
				result += _data[i];
			}
		}
		return result;
	}

	Set operator*(const Set& other) const {
		Set result;
		for (size_t i = 0; i < _size; ++i) {
			if (other.contains(_data[i])) {
				result += _data[i];
			}
		}
		return result;
	}

	bool operator==(const Set& other) const {
		if (_size != other._size) return false;
		for (size_t i = 0; i < _size; ++i) {
			if (!other.contains(_data[i])) return false;
		}
		return true;
	}

	bool operator!=(const Set& other) const {
		return !(*this == other);
	}
};

export inline std::ostream& operator<<(std::ostream& os, const std::pair<int, double>& val) {
	os << "(" << val.first << ", " << val.second << ")";
	return os;
}

export template <typename T>
std::ostream& operator<<(std::ostream& os, const Set<T>& set) {
	os << "{";
	for (size_t i = 0; i < set.size(); ++i) {
		if (i > 0) {
			os << ", ";
		}
		os << set[i];
	}
	os << "}";
	return os;
}

export template <typename T>
bool is_subset(const Set<T>& first, const Set<T>& second) {
	return (first - second).is_empty();
}
