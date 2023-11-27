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




