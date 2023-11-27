#pragma once

#include <iostream> 
#include <cmath>
#include <complex>
#include <stdexcept>

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

template <class Ratio, typename Args>

Ratio Ñalculating_a_polynomial(const Polynomial<Ratio> _polynomial, const Args& value_x);

template <class Ratio>

std::complex<Ratio> calculating_a_polynomial(Polynomial<std::complex<Ratio>> _polynomial, const std::complex<Ratio>& value_x);

template <class Ratio>

Polynomial<Ratio>  calculating_derivative(const Polynomial<Ratio>& polynomial);

template <class Ratio>

Polynomial<std::complex<Ratio>>  calculating_derivative(const Polynomial<std::complex<Ratio>>& polynomial);

template <class Ratio>

std::ostream& operator<<(std::ostream& stream, Polynomial<Ratio>& _polynomial);

template <class Ratio>

std::ostream& operator<<(std::ostream& stream, Polynomial<std::complex<Ratio>>& _polynomial);