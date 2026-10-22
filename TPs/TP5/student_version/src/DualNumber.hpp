#pragma once

#include <fstream>
#include <cmath>

template <typename T>
class DualNumber{

	private : 
		T m_real;
		T m_dual;

	public :

		// default constructor
		DualNumber() = default;

		// constructor by value
		DualNumber(const T& real, const T &dual) : m_real(real), m_dual(dual) {};

		// convert a scalar into a dual number		
		DualNumber(const T &value) : m_real(value), m_dual(static_cast<T>(0)) {}; 

		// copy constructor
		DualNumber(const DualNumber &dn) = default;

		// destructor
		~DualNumber() = default;

		// getter / setter
		inline T & real() {return m_real;};
		inline T & dual() {return m_dual;};
		inline const T & real() const {return m_real;};
		inline const T & dual() const {return m_dual;};


		// some operators
		DualNumber operator*(const DualNumber &dn) const;
		DualNumber operator+(const DualNumber &dn) const;
		DualNumber operator-(const DualNumber &dn) const;
		DualNumber operator/(const DualNumber &dn) const;
		inline DualNumber operator/(const T &value) const {return DualNumber(m_real / value, m_dual/value);}
		inline friend DualNumber operator*(const T &value, const DualNumber &dn) {return dn * value;}
		inline friend DualNumber operator/(const T &value, const DualNumber &dn) {return DualNumber(value)/dn;};
		inline friend DualNumber operator-(const DualNumber &dn) {return DualNumber(-dn.m_real,-dn.m_dual);}; // unary minus


		static DualNumber sin(const DualNumber & dn);	
		// static DualNumber cos(const DualNumber & dn);
		// static DualNumber tan(const DualNumber & dn);
		// static DualNumber exp(const DualNumber & dn);
		// static DualNumber log(const DualNumber & dn);
		// static DualNumber abs(const DualNumber & dn);
		// static DualNumber pow(const DualNumber & dn, const T &n);
		// static DualNumber sqrt(const DualNumber & dn);

		template<typename U>
        friend std::ostream& operator<< (std::ostream& stream, const DualNumber<U> &dn);
};


template<typename T>
std::ostream& operator<< (std::ostream& stream, const DualNumber<T> &dn){
	stream << "(" << dn.m_real << ", " << dn.m_dual << ")";
    return stream;
}


template <typename T>
DualNumber<T> DualNumber<T>::operator*(const DualNumber<T> &dn) const {
	return DualNumber<T>(this->m_real * dn.m_real, this->m_dual*dn.m_real + this->m_real*dn.m_dual);
}

/*
 * this->m_real : a1
 * dn.m_real : a2
 * this->m_dual : b1
 * dn.m_dual : b2
 *
 */


template <typename T>
DualNumber<T> DualNumber<T>::operator+(const DualNumber<T> &dn) const
{
	return DualNumber<T>(this->m_real + dn.m_real, this->m_dual + dn.m_dual);
}

// on met les valeurs sans le epsilon à gauche de la virgule dans le return, les trucs avec le epsilon, à droite
template <typename T>
DualNumber<T> DualNumber<T>::operator-(const DualNumber<T> &dn) const
{
	return DualNumber<T>(this->m_real - dn.m_real, this->m_dual - dn.m_dual);
}

template <typename T>
DualNumber<T> DualNumber<T>::operator/(const DualNumber<T> &dn) const {
	return DualNumber<T>(this->m_real / dn.m_real, (this->m_dual*dn.m_real - this->m_real*dn.m_dual) / pow(dn.m_real, 2));
}


template <typename T>
DualNumber<T> DualNumber<T>::sin(const DualNumber<T> & dn){
	return DualNumber<T>(std::sin(dn.m_real),dn.m_dual*std::cos(dn.m_real));
}
