//
// Created by arnisfet on 10.05.2022.
//

#ifndef FT_CANTAINERS_FT_TYPE_TRAITS_H
#define FT_CANTAINERS_FT_TYPE_TRAITS_H


#include <iostream>
#include <cstddef>

namespace ft {
	/* Iterator Traits */
	template <class Iterator>
			class iterator_traits
	{
	public:
		typedef typename Iterator::difference_type difference_type;
		typedef typename Iterator::value_type value_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
		typedef typename Iterator::iterator_category iterator_category;
	};

	/* T* specialization: */
	template <class T>
			class iterator_traits <T *>
	{
	public:
		typedef ptrdiff_t diffrence_type;
		typedef T value_type;
		typedef T *pointer;
		typedef T &reference;
		typedef std::random_access_iterator_tag iterator_category;
	};

	/* const T* specialization: */
	template <class T>
	class iterator_traits <const T *>
	{
	public:
		typedef ptrdiff_t diffrence_type;
		typedef T value_type;
		typedef const T *pointer;
		typedef const T &reference;
		typedef std::random_access_iterator_tag iterator_category;
	};

	template <class Iterator>
	class ReverseIterator
	{
	public:
		typedef Iterator												iterator_type;
		typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
		typedef typename iterator_traits<Iterator>::value_type			value_type;
		typedef typename iterator_traits<Iterator>::difference_type		difference_type;
		typedef typename iterator_traits<Iterator>::pointer				pointer;
		typedef typename iterator_traits<Iterator>::reference			reference;
	private:
		pointer _it;
	public:

		/* Конструкторы и деструкторы */

		ReverseIterator() : _it(NULL){}
		ReverseIterator(pointer const &src) : _it(src){}
		ReverseIterator(ReverseIterator const &other)
		{*this = other;}
		~ReverseIterator(){}

		/* Гетер */

		iterator_type base() {return(_it);}

		/* Основные операторы получения значений */

		reference operator*(){return(*_it);}
		pointer	operator->(){return &(operator*());}
		reference	operator[](difference_type n){return(_it[n]);}

		/* Остальные операторы перегрузки */

		bool	operator==(ReverseIterator<Iterator> &src)
		{
			return(_it == src._it);
		}

		bool	operator!=(ReverseIterator<Iterator> &src)
		{
			return(_it != src._it);
		}

		ReverseIterator operator++()
		{
			_it--;
			return(*this);
		}

		ReverseIterator operator++(int)
		{
			ReverseIterator tmp;
			tmp = *this;
			_it--;
			return(tmp);
		}

		ReverseIterator operator--()
		{
			_it++;
			return(*this);
		}

		ReverseIterator operator--( int)
		{
			ReverseIterator tmp;
			tmp = *this;
			_it++;
			return(tmp);
		}

		ReverseIterator &operator+=(difference_type n)
		{
			return(_it -= n);
		}

		ReverseIterator &operator-=(difference_type n)
		{
			return(_it += n);
		}

		ReverseIterator operator-(difference_type n)
		{
			return(random_access_iterator(_it + n));
		}

		ReverseIterator operator+(difference_type n)
		{
			return(random_access_iterator(_it - n));
		}
	};

	/* Функции перегрузки операторов вне класса */

	template<class Iterator>
	bool operator==(ft::ReverseIterator<Iterator> const &src,
					ft::ReverseIterator<Iterator> const &dst)
	{
		return(src.base() == dst.base());
	}

	template<class Iterator>
	bool operator!=(ReverseIterator<Iterator> const &src,
					ReverseIterator<Iterator> const &dst)
	{
		return(src.base() != dst.base());
	}

	template<class Iterator>
	bool operator<(ft::ReverseIterator<Iterator> const &src,
				   ft::ReverseIterator<Iterator> const &dst)
	{
		return(src.base() > dst.base());
	}

	template<class Iterator>
	bool operator<=(ft::ReverseIterator<Iterator> const &src,
					ft::ReverseIterator<Iterator> const &dst)
	{
		return(src.base() >= dst.base());
	}

	template<class Iterator>
	bool operator>(ft::ReverseIterator<Iterator> const &src,
				   ft::ReverseIterator<Iterator> const &dst)
	{
		return(src.base() < dst.base());
	}

	template<class Iterator>
	bool operator>=(ft::ReverseIterator<Iterator> const &src,
					ft::ReverseIterator<Iterator> const &dst)
	{
		return(src.base() <= dst.base());
	}

	template<class Iterator>
	bool operator+(ft::ReverseIterator<Iterator> const &src,
				   ft::ReverseIterator<Iterator> const &dst)
	{
		return(src.base() - dst.base());
	}

	template<class Iterator>
	bool operator-(ft::ReverseIterator<Iterator> const &src,
				   ft::ReverseIterator<Iterator> const &dst)
	{
		return (src.base() + dst.base());
	}
	/* Почти самый крутой итератор в с++, может делать все кроме минета */

	template<class Iterator>
	class random_access_iterator{
	public:

		/* Элементы общего доступа*/

		typedef Iterator											value_type;
		typedef std::random_access_iterator_tag				iterator_category;
		typedef Iterator*											pointer;
		typedef Iterator&											reference;
		typedef ptrdiff_t									difference_type;

		/* Элементы вип доступа */

	private:
		pointer _it;

		/* Конструкторы и деструкторы */
	public:
		random_access_iterator() : _it(NULL) {}
		explicit random_access_iterator(value_type *it) : _it(it) {}
		random_access_iterator(random_access_iterator const &other)
		{*this = other;}

		random_access_iterator &operator=(random_access_iterator const &other)
			{
				_it = other._it;
				return (*this);
			}

		~random_access_iterator() {}
		reference operator*() const { return (*_it);}
		pointer operator->() const {return &(operator*());}
		reference operator[] (difference_type n) const { return (_it[n]);}
		pointer base() const{return (_it);}

		/* Булевые операторы */

		bool operator==(random_access_iterator<Iterator> &src)
		{
			return (_it == src._it);
		}

		bool operator!=(random_access_iterator<Iterator> &src)
		{
			return (_it != src._it);
		}

		/*Операторы инкремента, декремента итп*/

		random_access_iterator &operator++()
		{
			_it++;
			return(*this);
		}

		random_access_iterator operator++(int)
		{
			random_access_iterator tmp = *this;
			++(*this);
			return(tmp);
		}

		random_access_iterator &operator--()
		{
			_it--;
			return(*this);
		}

		random_access_iterator operator--(int)
		{
			random_access_iterator tmp = *this;
			--(*this);
			return (tmp);
		}

		random_access_iterator &operator+=(difference_type n)
		{
			_it += n;
			return (*this);
		}

		random_access_iterator &operator-=(difference_type n)
		{
			_it -= n;
			return(*this);
		}

		random_access_iterator operator-(difference_type n)
		{
			return(random_access_iterator(_it - n));
		}

		random_access_iterator operator+(difference_type n)
		{
			return(random_access_iterator(_it + n));
		}
	};
}
/* Функции перегрузки операторов random access operator вне класса(не влияют
 * на изначальное состояние переменных класса) */

template<class Iterator>
bool operator==(ft::random_access_iterator<Iterator> const &src,
				ft::random_access_iterator<Iterator> const &dst)
{
	return(src.base() == dst.base());
}

template<class Iterator>
bool operator!=(ft::random_access_iterator<Iterator> const &src,
				ft::random_access_iterator<Iterator> const &dst)
{
	return(src.base() != dst.base());
}

template<class Iterator>
bool operator<(ft::random_access_iterator<Iterator> const &src,
			   ft::random_access_iterator<Iterator> const &dst)
{
	return(src.base() < dst.base());
}

template<class Iterator>
bool operator<=(ft::random_access_iterator<Iterator> const &src,
				ft::random_access_iterator<Iterator> const &dst)
{
	return(src.base() <= dst.base());
}

template<class Iterator>
bool operator>(ft::random_access_iterator<Iterator> const &src,
			   ft::random_access_iterator<Iterator> const &dst)
{
	return(src.base() > dst.base());
}

template<class Iterator>
bool operator>=(ft::random_access_iterator<Iterator> const &src,
				ft::random_access_iterator<Iterator> const &dst)
{
	return(src.base() >= dst.base());
}

template<class Iterator>
bool operator+(ft::random_access_iterator<Iterator> const &src,
				ft::random_access_iterator<Iterator> const &dst)
{
	return(src.base() + dst.base());
}

template<class Iterator>
bool operator-(ft::random_access_iterator<Iterator> const &src,
				ft::random_access_iterator<Iterator> const &dst)
{
	return(src.base() - dst.base());
}

namespace ft {

	template <bool B, class T = void>
	struct enable_if;

	template <class T>
	struct enable_if <true, T> {
		typedef T type;
};

	template<class T, T v>
			struct integral_constant
					{
				static const T value = v;
				typedef T value_type;
				typedef integral_constant<T, v> type;
				operator T() {return (v);}
					};
	template <class T> struct is_integral: public integral_constant<bool, false> {};
	template<> struct is_integral<bool>: public integral_constant<bool, true> {} ;
	template<> struct is_integral<char>: public integral_constant<bool, true> {} ;
	template<> struct is_integral<wchar_t>: public integral_constant<bool, true> {} ;
	template<> struct is_integral<signed char>: public integral_constant<bool, true> {} ;
	template<> struct is_integral<short int>: public integral_constant<bool, true> {} ;
	template<> struct is_integral<int>: public integral_constant<bool, true> {} ;
	template<> struct is_integral<long int>: public integral_constant<bool, true> {} ;
	template<> struct is_integral<long long int>: public integral_constant<bool, true> {} ;
	template<> struct is_integral<unsigned char>: public integral_constant<bool, true> {} ;
	template<> struct is_integral<unsigned short int>: public integral_constant<bool, true> {} ;
	template<> struct is_integral<unsigned int>: public integral_constant<bool, true> {} ;
	template<> struct is_integral<unsigned long int>: public integral_constant<bool, true> {} ;
	template<> struct is_integral<unsigned long long int>: public integral_constant<bool, true> {} ;
}

#endif //FT_CANTAINERS_FT_TYPE_TRAITS_H
