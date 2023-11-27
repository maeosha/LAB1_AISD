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