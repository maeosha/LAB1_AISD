#include <iostream> 
#include <cmath>
#include <complex>

template <class Ratio>

class Polynomial {
private:
	Ratio* container;
	size_t size;
public:
	Polynomial();
	Polynomial(const size_t& size);
	Polynomial(const Polynomial& _polynomial);
	~Polynomial();

	void Set_size(const size_t& new_size);
	size_t Get_size() const;

	Ratio* Get_container() const;

	Ratio operator[](const size_t& index) const;
	Polynomial operator+(Polynomial& summand);
	Polynomial operator*(const Ratio& multiplier);
	Polynomial operator-(Polynomial& deductible);
	void operator=(const Polynomial& _polynomial);



	void Add_element(const Ratio& elem, const size_t& index);
	void Add_element(const std::complex<Ratio>& elem, size_t index);
	void shrink_to_fit();
	void expand(const size_t& new_size); 
};

template <class Ratio>

Polynomial<Ratio>::Polynomial() {
	this->container = new Ratio[1]();
	this->size = 1;
}

template <class Ratio>

Polynomial<Ratio>::Polynomial(const size_t& size) {
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

Polynomial<Ratio>::~Polynomial() {
	delete[] container;
	container = nullptr;
	size = 0;
}

template <class Ratio>

void Polynomial<Ratio>::Set_size(const size_t& size) {

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
	if (index >= size) {
		Polynomial _tmp(index + 1);
		_tmp = *this;
		this->size = index + 1;
		*this = _tmp;
	}
	container[index] = elem;
}

template <class Ratio>

void Polynomial<Ratio>::Add_element(const std::complex<Ratio>& elem, size_t index) {
	if (index >= size) {
		Polynomial _tmp(index + 1);
		_tmp = *this;
		this->size = index + 1;
		*this = _tmp;
	}
	conteiner[index] = elem;
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

Ratio Ñalculating_a_polynomial(const Polynomial<Ratio> _polynomial, const Args& value_x) {
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
