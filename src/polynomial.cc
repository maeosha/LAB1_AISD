#include <polynomial/polynomial.h>

template <class Ratio>

Polynomial<Ratio>::Polynomial(const size_t& size) {
	if (size < 0) {
		throw std::runtime_error("Size must be positive");
	}
	this->container = new Ratio[size]();
	this->size = size;
}

template <class Ratio>

Polynomial<Ratio>::Polynomial(const Polynomial& _polynomial) {
	this->container = new Ratio[_polynomial.Get_size()];
	for (size_t index = 0; index < _polynomial.Get_size(); index++) {
		container[index] = _polynomial[index];
	}
	this->size = _polynomial.Get_size();
}

template <class Ratio>

Polynomial<Ratio>::~Polynomial() {
	delete[] container;
	container = nullptr;
	size = 0;
}

template <class Ratio>

void Polynomial<Ratio>::Set_size(const size_t& size) {
	if (size < 0) {
		throw std::runtime_error("Size must be positive");
	}
	this->size = size;
}

template <class Ratio>

size_t Polynomial<Ratio>::Get_size() const {

	return size;
}

template <class Ratio>

Ratio* Polynomial<Ratio>::Get_container() const {

	return container;
}

template <class Ratio>

Ratio Polynomial<Ratio>::operator[](const size_t& index) const {
	if (index < 0 || index > size) {
		throw std::runtime_error("Degree must be positive and less, that degree polimomial");
	}
	return container[index];
}

template <class Ratio>

Polynomial<Ratio> Polynomial<Ratio>::operator+(Polynomial& summand) {
	size_t min_size = this->size;
	size_t max_size = summand.Get_size();
	bool smallest = 0;
	if (min_size > max_size) {
		std::swap(min_size, max_size);
		smallest = 1;
	}
	Polynomial value(max_size);
	for (size_t index = 0; index < min_size; index++) {
		value.Add_element(this->container[index] + summand[index], index);
	}
	for (size_t index = min_size; index < max_size; index++) {
		if (smallest == 0) {
			value.Add_element(summand[index], index);
		}
		else {
			value.Add_element(this->container[index], index);
		}
	}
	return value;
}

template <class Ratio>

Polynomial<Ratio> Polynomial<Ratio>::operator*(const Ratio& multiplier) {
	Polynomial value(this->size);
	for (size_t index = 0; index < this->size; index++) {
		value.Add_element(this->container[index] * multiplier, index);
	}
	return value;
}

template <class Ratio>

Polynomial<Ratio> Polynomial<Ratio>::operator-(Polynomial& deductible) {
	Polynomial value(1);
	Polynomial negative_polynomial(1);
	negative_polynomial = deductible * (-1);
	value = *this + negative_polynomial;
	return value;
}


template <class Ratio>

void Polynomial<Ratio>::operator=(const Polynomial& _polynomial) {
	delete[] container;
	this->container = new Ratio[_polynomial.Get_size()];
	for (size_t index = 0; index < _polynomial.Get_size(); index++) {
		container[index] = _polynomial[index];
	}
	this->size = _polynomial.Get_size();
}

template <class Ratio>

void Polynomial<Ratio>::Add_element(const Ratio& elem, const size_t& index) {
	if (index < 0 || index > size) {
		throw std::runtime_error("Degree must be positive and less, that degree polimomial");
	}
	container[index] = elem;
}

template <class Ratio>

void Polynomial<Ratio>::Add_element(const std::complex<Ratio>& elem, size_t index) {
	if (index < 0 || index > size) {
		throw std::runtime_error("Degree must be positive and less, that degree polimomial");
	}
	container[index] = elem;
}


template <class Ratio>

void Polynomial<Ratio>::shrink_to_fit() {
	size_t shrinked_size = size;
	size_t index = size - 1;

	while (container[index] == 0) {
		shrinked_size--;
		index--;
	}

	if (size != shrinked_size) {
		Ratio* shrinked_container = new Ratio[shrinked_size];

		for (size_t index = 0; index < shrinked_size; index++) {
			shrinked_container[index] = container[index];
		}

		delete[] container;
		container = new Ratio[shrinked_size];
		container = shrinked_container;
		size = shrinked_size;
	}
}

template <class Ratio>

void Polynomial<Ratio>::expand(const size_t& new_size) {
	if (new_size < 0) {
		throw std::runtime_error("Size must be positive");
	}
	Ratio* new_container = new Ratio[new_size]();
	for (size_t index = 0; index < size; index++) {
		new_container[index] = container[index];
	}

	container = new_container;
	size = new_size;
}

template <class Ratio>

Polynomial<Ratio> operator*(Ratio _multiplier, const Polynomial<Ratio>& _polynomial) {
	Polynomial<Ratio> value(_polynomial.Get_size());
	for (size_t index = 0; index < _polynomial.Get_size(); index++) {
		value.Add_element(_polynomial[index] * _multiplier, index);
	}
	return value;
}

template <class Ratio>

Polynomial<std::complex<Ratio>> operator*(Ratio _multiplier, const Polynomial<std::complex<Ratio>>& _polynomial) {
	Polynomial<std::complex<Ratio>> value(_polynomial.Get_size());
	for (size_t index = 0; index < _polynomial.Get_size(); index++) {
		value.Add_element(_polynomial[index] * _multiplier, index);
	}
	return value;
}

template <class Ratio, typename Args>

Ratio calculating_a_polynomial(const Polynomial<Ratio> _polynomial, const Args& value_x) {
	Args summary = 0;
	for (size_t index = 0; index < _polynomial.Get_size(); index++) {
		summary += _polynomial[index] * pow(value_x, index);
	}
	return Ratio(summary);
}

template <class Ratio>

std::complex<Ratio> calculating_a_polynomial(Polynomial<std::complex<Ratio>> _polynomial, const std::complex<Ratio>& value_x) {
	Ratio summary_re = 0;
	Ratio summary_im = 0;
	for (size_t index = 0; index < _polynomial.Get_size(); index++) {
		summary_re += _polynomial[index].real() * std::pow(value_x.real(), index);
		summary_im += _polynomial[index].imag() * std::pow(value_x.imag(), index);
	}
	std::complex<Ratio> summary(summary_re, summary_im);
	return summary;
}

template <class Ratio>

Polynomial<Ratio>  calculating_derivative(const Polynomial<Ratio>& polynomial) {
	size_t size = polynomial.Get_size();
	Polynomial<Ratio> derivative_polynomial(size - 1);
	Ratio derivative_ratio;
	for (size_t index = 1; index < size; index++) {
		derivative_ratio = polynomial[index] * index;
		derivative_polynomial.Add_element(derivative_ratio, index - 1);
	}
	return derivative_polynomial;
}

template <class Ratio>

Polynomial<std::complex<Ratio>>  calculating_derivative(const Polynomial<std::complex<Ratio>>& polynomial) {
	size_t size = polynomial.Get_size();
	Polynomial<std::complex<Ratio>> derivative_polynomial(size - 1);
	std::complex<Ratio> derivative_ratio;
	for (size_t index = 1; index < size; index++) {
		derivative_ratio = polynomial[index] * Ratio(index);
		derivative_polynomial.Add_element(derivative_ratio, index - 1);
	}
	return derivative_polynomial;
}

template <class Ratio>

std::ostream& operator<<(std::ostream& stream, Polynomial<Ratio>& _polynomial) {
	if (_polynomial.Get_size() == 0) {
		stream << "NONE";
		return stream;
	}
	if (_polynomial[0] != 0) {
		stream << _polynomial[0];
	}
	for (size_t index = 1; index < _polynomial.Get_size(); index++) {
		if (_polynomial[index] == 0) {
			continue;
		}
		if (_polynomial[index] > 0) {
			stream << " + ";
		}
		if (_polynomial[index] < 0) {
			stream << " - ";
		}
		stream << abs(_polynomial[index]) << "*x^" << index;
	}
	return stream;
}

template <class Ratio>

std::ostream& operator<<(std::ostream& stream, Polynomial<std::complex<Ratio>>& _polynomial) {
	std::complex<Ratio> zero_elem(0, 0);
	Ratio complex_re;
	Ratio complex_im;
	if (_polynomial.Get_size() == 0) {
		stream << "NONE";
		return stream;
	}

	if (_polynomial[0] != zero_elem) {
		complex_re = _polynomial[0].real();
		complex_im = _polynomial[0].imag();

		if (complex_re == 0) {
			stream << complex_im;
		}
		if (complex_im == 0) {
			stream << complex_re;
		}
		if (complex_re != 0 && complex_im != 0) {
			if (complex_im > 0) {
				stream << complex_re << " + " << complex_im << "i";
			}
			if (complex_im < 0) {
				stream << complex_re << " - " << abs(complex_im) << "i";
			}
		}
	}

	for (size_t index = 1; index < _polynomial.Get_size(); index++) {
		complex_re = _polynomial[index].real();
		complex_im = _polynomial[index].imag();
		if (_polynomial[index] == zero_elem) {
			continue;
		}
		if (index != _polynomial.Get_size()) {
			stream << " + ";

		}
		if (complex_re == 0) {
			stream << complex_im << "i" << "*x^" << index;
		}
		if (complex_im == 0) {
			stream << complex_re << "*x^" << index;
		}

		if (complex_re != 0 && complex_im != 0) {
			if (complex_im > 0) {
				stream << "(" << complex_re << " + " << complex_im << "i)" << "*x^" << index;
			}
			if (complex_im < 0) {
				stream << "(" << complex_re << " - " << abs(complex_im) << "i)" << "*x^" << index;
			}
		}

	}
	return stream;
}


int main() {
	{
		std::cout << "TEST 1'st: Test Add_elemend\n" << std::endl;
		Polynomial<int> pol1(5);
		pol1.Add_element(24, 0);
		pol1.Add_element(23, 1);
		pol1.Add_element(0, 2);
		pol1.Add_element(3, 3);
		pol1.Add_element(5, 4);
		std::cout << pol1 << std::endl << std::endl << std::endl;
	}

	{
		std::cout << "TEST 2'nd: Test Add_element(complex)\n" << std::endl;
		Polynomial<std::complex<double>> pol1(5);
		std::complex<double> elem1(1, 3);
		std::complex<double> elem2(0, 2);
		std::complex<double> elem3(0, 0);
		pol1.Add_element(elem1, 0);
		pol1.Add_element(elem2, 1);
		pol1.Add_element(elem3, 2);
		pol1.Add_element(elem1, 3);
		pol1.Add_element(elem1, 4);
		std::cout << pol1 << std::endl << std::endl << std::endl;
	}

	{
		std::cout << "TEST 3'rd: Test operator+\n" << std::endl;
		Polynomial<int> pol1(5);
		Polynomial<int> pol2(3);
		Polynomial<int> pol_summer(1);
		for (size_t index = 0; index < pol1.Get_size(); index++) {
			pol1.Add_element(rand() % 10, index);
		}

		for (size_t index = 0; index < pol2.Get_size(); index++) {
			pol2.Add_element(rand() % 10, index);
		}

		std::cout << "Polynomial 1: " << pol1 << std::endl << std::endl;
		std::cout << "Polynomial 2: " << pol2 << std::endl << std::endl;

		pol_summer = pol1 + pol2;
		std::cout << "Pol1 + Pol2 = " << pol_summer << std::endl << std::endl << std::endl;
	}

	{
		std::cout << "TEST 4'th: Test operator+(complex)\n" << std::endl;
		Polynomial<std::complex<double>> pol1(5);
		Polynomial<std::complex<double>> pol2(3);
		Polynomial<std::complex<double>> pol_summer(1);
		for (size_t index = 0; index < pol1.Get_size(); index++) {
			std::complex<double> elem(rand() % 10, rand() % 10);
			pol1.Add_element(elem, index);
		}

		for (size_t index = 0; index < pol2.Get_size(); index++) {
			std::complex<double> elem(rand() % 10, rand() % 10);
			pol2.Add_element(elem, index);
		}

		std::cout << "Polynomial 1: " << pol1 << std::endl << std::endl;
		std::cout << "Polynomial 2: " << pol2 << std::endl << std::endl;

		pol_summer = pol1 + pol2;
		std::cout << "Pol1 + Pol2 = " << pol_summer << std::endl << std::endl << std::endl;
	}

	{
		std::cout << "TEST 5'th: Test operator*\n" << std::endl;
		Polynomial<int> pol1(5);
		int mult = rand() % 10;
		Polynomial<int> pol_mult(1);
		for (size_t index = 0; index < pol1.Get_size(); index++) {
			pol1.Add_element(rand() % 10, index);
		}

		std::cout << "Polynomial: " << pol1 << std::endl << std::endl;
		std::cout << "multiplier: " << mult << std::endl << std::endl;

		pol_mult = pol1 * mult;
		std::cout << "Pol * mult = " << pol_mult << std::endl << std::endl;

		pol_mult = mult * pol1;
		std::cout << "mult * Pol = " << pol_mult << std::endl << std::endl << std::endl;
	}

	{
		std::cout << "TEST 6'th: Test operator*(complex)\n" << std::endl;
		Polynomial<std::complex<double>> pol1(5);
		std::complex<double> mult(rand() % 10, rand() % 10);
		Polynomial<std::complex<double>> pol_mult(1);

		for (size_t index = 0; index < pol1.Get_size(); index++) {
			std::complex<double> elem(rand() % 10, rand() % 10);
			pol1.Add_element(elem, index);
		}

		std::cout << "Polynomial: " << pol1 << std::endl << std::endl;
		std::cout << "multiplier: " << mult << std::endl << std::endl;

		pol_mult = pol1 * mult;
		std::cout << "Pol * mult = " << pol_mult << std::endl << std::endl;

		pol_mult = mult * pol1;
		std::cout << "mult * Pol = " << pol_mult << std::endl << std::endl << std::endl;
	}

	{
		std::cout << "TEST 7'th: Test operator-\n" << std::endl;
		Polynomial<int> pol1(5);
		Polynomial<int> pol2(3);
		Polynomial<int> pol_ded(1);
		for (size_t index = 0; index < pol1.Get_size(); index++) {
			pol1.Add_element(rand() % 10, index);
		}

		for (size_t index = 0; index < pol2.Get_size(); index++) {
			pol2.Add_element(rand() % 10, index);
		}

		std::cout << "Polynomial 1: " << pol1 << std::endl << std::endl;
		std::cout << "Polynomial 2: " << pol2 << std::endl << std::endl;

		pol_ded = pol1 - pol2;
		std::cout << "Pol1 - Pol2 = " << pol_ded << std::endl << std::endl << std::endl;
	}

	{
		std::cout << "TEST 8'th: Test operator-(complex)\n" << std::endl;
		Polynomial<std::complex<double>> pol1(5);
		Polynomial<std::complex<double>> pol2(3);
		Polynomial<std::complex<double>> pol_ded(1);
		for (size_t index = 0; index < pol1.Get_size(); index++) {
			std::complex<double> elem(rand() % 10, rand() % 10);
			pol1.Add_element(elem, index);
		}

		for (size_t index = 0; index < pol2.Get_size(); index++) {
			std::complex<double> elem(rand() % 10, rand() % 10);
			pol2.Add_element(elem, index);
		}

		std::cout << "Polynomial 1: " << pol1 << std::endl << std::endl;
		std::cout << "Polynomial 2: " << pol2 << std::endl << std::endl;

		pol_ded = pol1 - pol2;
		std::cout << "Pol1 - Pol2 = " << pol_ded << std::endl << std::endl << std::endl;
	}

	{
		std::cout << "TEST 9'th: Test calculating_the_polynomial\n" << std::endl; 
		Polynomial<int> pol(5);
		int right_result = 31;
		int arg = 2;
		int result;

		for (size_t index = 0; index < pol.Get_size(); index++) {
			pol.Add_element(1, index);
		}

		std::cout << "Polynomial: " << pol << std::endl << std::endl;
		std::cout << "Argument: " << arg << std::endl << std::endl;
		
		result = calculating_a_polynomial<int>(pol, arg);

		std::cout << "Polynomial(Argument) = " << result << std::endl;
		std::cout << "Right result: " << right_result << std::endl << std::endl << std::endl;
	}

	{
		std::cout << "TEST 10'th: Test calculating_the_polynomial(complex)\n" << std::endl;
		Polynomial<std::complex<double>> pol(5);
		std::complex<double> right_result(5, 10);
		std::complex<double> arg(1, 1);
		std::complex<double> result;

		for (size_t index = 0; index < pol.Get_size(); index++) {
			std::complex<double> elem(1, index);
			pol.Add_element(elem, index);
		}

		std::cout << "Polynomial: " << pol << std::endl << std::endl;
		std::cout << "Argument: " << arg << std::endl << std::endl;

		result = calculating_a_polynomial(pol, arg);

		std::cout << "Polynomial(Argument) = " << result << std::endl;
		std::cout << "Right result: " << right_result << std::endl << std::endl << std::endl;
	}

	{
		std::cout << "TEST 11'th: Test calculating_the_derivative\n" << std::endl;
		Polynomial<int> pol(5);
		Polynomial<int> derivative_pol(5);

		for (size_t index = 0; index < pol.Get_size(); index++) {
			pol.Add_element(1, index);
		}

		std::cout << "Polynomial: " << pol << std::endl << std::endl;

		derivative_pol = calculating_derivative<int>(pol);

		std::cout << "(Pol)' = " << derivative_pol << std::endl;
	}

	{
		std::cout << "TEST 12'th: Test calculating_the_derivative\n" << std::endl;
		Polynomial<std::complex<double>> pol(5);
		Polynomial<std::complex<double>> derivative_pol(5);

		for (size_t index = 0; index < pol.Get_size(); index++) {
			std::complex<double> elem(1, index);
			pol.Add_element(elem, index);
		}

		std::cout << "Polynomial: " << pol << std::endl << std::endl;

		derivative_pol = calculating_derivative(pol);

		std::cout << "(Pol)' = " << derivative_pol << std::endl;
	}
}