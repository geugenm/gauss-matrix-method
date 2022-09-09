#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <iomanip>

using double80_t = long double;

class Matrix {
public:
	Matrix() = default;

	explicit Matrix(const uint64_t& rows, const uint64_t& columns) : _rows(rows), _columns(columns) {
		this->_data.resize(rows);

		for (uint64_t i = 0; i < rows; i++) {
			this->_data[i].resize(columns);
		}
	}

	Matrix(const Matrix& source) = default;

	Matrix& operator = (const Matrix& source) = default;

	~Matrix() = default;

	std::vector<double80_t> const& operator[](const uint64_t& index) const {
		if (index >= _rows) {
			throw (std::out_of_range("Matrix out of range"));
		}
		return this->_data[index];
	}

	std::vector<double80_t>& operator[](const uint64_t& index) {
		if (index >= this->_rows) {
			throw (std::out_of_range("Matrix out of range"));
		}
		return this->_data[index];
	}

	[[nodiscard]] uint64_t GetRowsNumber() const {
		return this->_rows;
	}

	[[nodiscard]] uint64_t GetColumnsNumber() const {
		return this->_columns;
	}

	void SumRows(const uint64_t& rowToSumIndex, const uint64_t& rowToChangeIndex) {
		for (uint64_t i = 0; i < this->GetColumnsNumber(); i++) {
			this->_data[rowToChangeIndex][i] += this->_data[rowToSumIndex][i];
		}
	}

	void SubstractRows(const uint64_t& rowToSubstractIndex, const uint64_t& rowToChangeIndex) {
		for (uint64_t i = 0; i < this->GetColumnsNumber(); i++) {
			this->_data[rowToChangeIndex][i] -= this->_data[rowToSubstractIndex][i];
		}
	}

	void MultiplyRowBy(const uint64_t& targetRowIndex, const double80_t& multiplier) {
		for (uint64_t i = 0; i < this->GetColumnsNumber(); i++) {
			this->_data[targetRowIndex][i] *= multiplier;
		}
	}

	void SubstractMultipliedRow(const uint64_t& rowToSubstractIndex, const uint64_t& rowToChangeIndex, const double80_t& multiplier) {
		for (uint64_t i = 0; i < this->GetColumnsNumber(); i++) {
			this->_data[rowToChangeIndex][i] -= this->_data[rowToSubstractIndex][i] * multiplier;
		}
	}

	[[nodiscard]] uint64_t GetMaxColumnElementIndex(const uint64_t& columnIndex) {
		uint64_t resultIndex = NULL;
		double_t resultMax = NULL;

		for (uint64_t i = 0; i < this->GetRowsNumber(); i++) {
			const double_t currentComparableElement = std::abs(this->_data[i][columnIndex]);

			if (resultMax > currentComparableElement) {
				continue;
			}

			resultMax = currentComparableElement;
			resultIndex = i;
		}

		return resultIndex;
	}

	[[nodiscard]] uint64_t GetMaxRowElementIndex(const uint64_t& rowIndex) {
		const auto maxElementIterator = std::ranges::max_element(this->_data[rowIndex].begin(), this->_data[rowIndex].end(), [](double_t a, double_t b) {
			return abs(a) < abs(b);
		});

		return std::distance(this->_data[rowIndex].begin(), maxElementIterator);
	}

	void RandomInit() {
		const double80_t minRandom = -100000.0;
		const double80_t maxRandom = 100000.0;

		std::random_device randomDevice;
		std::mt19937 generate(randomDevice());
		std::uniform_real_distribution<double80_t> distribution(minRandom, maxRandom);

		for (uint64_t i = 0; i < this->GetRowsNumber(); i++) {
			for (uint64_t j = 0; j < this->GetColumnsNumber(); j++) {
				this->_data[i][j] = distribution(generate);
			}
		}
	}

	void Print() {
		const uint64_t precision = 2;
		const uint64_t width = 7;

		std::cout << std::setprecision(precision);
		std::cout.setf(std::ios::right);
		std::cout.setf(std::ios::fixed);

		for (uint64_t i = 0; i < this->GetRowsNumber(); i++) {
			for (uint64_t j = 0; j < this->GetColumnsNumber(); j++) {
				std::cout << std::setw(width) << this->_data[i][j] << " ";
			}
			std::cout << std::endl;
		}
	}

private:
	std::vector<std::vector<double80_t>> _data{};

	uint64_t _rows = NULL;

	uint64_t _columns = NULL;
};

int main() {
	// ...
}