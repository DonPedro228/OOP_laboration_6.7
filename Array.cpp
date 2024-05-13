#include "Array.h"
#include <iostream>
#include <stdexcept>
#include <exception>
#include <algorithm>
using namespace std;
Array::Array(const Array::size_type& n)
throw(bad_alloc, invalid_argument)
{
	First = 0;
	Count = Size = n;
	elems = new value_type[Size];
	for (UINT i = 0; i < Size; i++)
		elems[i] = 0;
}

Array::Array(const iterator first, const iterator last)
throw(bad_alloc, invalid_argument)
{
	First = 0;
	if (first <= last) {
		Count = Size = (last - first) + 1;
		elems = new value_type[Size];
		for (UINT i = 0; i < Size; ++i)
			elems[i] = 0;
	}
	else
		throw invalid_argument("!!!");
}
Array::Array(const size_type first, const size_type last)
throw(bad_alloc, invalid_argument)
{
	if (first <= last) {
		First = first;
		Count = Size = (last - first) + 1;
		elems = new value_type[Size];
		for (UINT i = 0; i < Size; ++i)
			elems[i] = 0;
	}
	else
		throw invalid_argument("!!!");
}
Array::Array(const Array& t) throw(bad_alloc)
	: Size(t.Size), Count(t.Count), First(t.First), elems(new value_type[Size])
{
	for (UINT i = 0; i < Size; ++i)
		elems[i] = t.elems[i];
}
Array& Array::operator =(const Array& t)
{
	Array tmp(t);
	swap(tmp);
	return *this;
}

Array::~Array()
{
	delete[]elems;
	elems = 0;
}

void Array::push_back(const value_type& v)
{
	if (Count == Size)
		resize(Size * 2);
	elems[Count++] = v;
}
Array::reference Array::operator [](size_type index) throw(out_of_range)
{
	if (index < 0 || index >= Size) {
		throw out_of_range("Index out of range!");
	}
	return elems[index];
}


Array::const_reference Array::operator [](size_type index) const
throw(out_of_range)
{
	if ((First <= index) && (index < First + Size))
		return elems[index - First];
	else
		throw out_of_range("Index out of range!");
}
void Array::resize(size_type newsize) throw(bad_alloc)
{
	if (newsize > capacity())
	{
		value_type* data = new value_type[newsize];
		for (size_type i = 0; i < Count; ++i)
			data[i] = elems[i];
		delete[] elems;
		elems = data;
		Size = newsize;
	}
}
void Array::swap(Array& other)
{
	std::swap(elems, other.elems);
	std::swap(Size, other.Size);
}
Array::size_type Array::capacity() const
{
	return Size;
}
Array::size_type Array::size() const
{
	return Count;
}
bool Array::empty() const
{
	return Count == 0;
}
ostream& operator <<(ostream& out, const Array& tmp)
{
	for (size_t j = 0; j < tmp.Count; j++)
		out << tmp[j] << " ";
	out << endl;
	return out;
}
istream& operator >>(istream& in, Array& tmp)
{
	for (Array::size_type i = 0; i < tmp.size(); ++i)
	{
		cout << "Enter value for element " << i << ": ";
		in >> tmp[i];
	}
	return in;
}void Array::assign(const value_type& v)
{
	for (size_type i = 0; i < Count; ++i)
		elems[i] = v;
}

void Array::pop_back()
{
	if (Count > 0)
	{
		--Count;
	}
}

void Array::sumAverage(const double* arr, size_type size) {
	double sum = 0;
	double abs_sum = 0;

	for (size_type i = 0; i < size; ++i) {
		sum += arr[i];
		abs_sum += fabs(arr[i]);
	}

	push_back(sum);
	push_back(abs_sum / size);
}



void Array::square_min(const double* arr, size_type size) {
	Array::value_type min_positive = std::numeric_limits<Array::value_type>::max();
	for (size_type i = 0; i < size; ++i) {
		if (arr[i] > 0 && arr[i] < min_positive) {
			min_positive = arr[i];
		}
	}

	if (min_positive == std::numeric_limits<Array::value_type>::max()) {
		cout << "No positive number!\n";
		return;
	}

	for (size_type i = 0; i < size; ++i) {
		if ((*this)[i] > 0) {
			(*this)[i] = min_positive * min_positive;
		}
	}
}

