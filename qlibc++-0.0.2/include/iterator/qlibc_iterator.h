#ifndef QLIBC___0_0_2_QLIBC_ITERATOR_H
#define QLIBC___0_0_2_QLIBC_ITERATOR_H

#include "./qlibc_iterator_base.h"

namespace qlibc{

    /// Iterator Adaptor
    /// Create On : 2024-06-14

    /// Reverse Iterator
    template<typename _Iterator>
    class reverse_iterator : public iterator<
            typename qlibc::iterator_traits<_Iterator>::value_type,
            typename qlibc::iterator_traits<_Iterator>::iterator_category,
            typename qlibc::iterator_traits<_Iterator>::difference_type,
            typename qlibc::iterator_traits<_Iterator>::pointer,
            typename qlibc::iterator_traits<_Iterator>::reference>{
    public:
        using iterator_type = _Iterator;
        using _Self = reverse_iterator<iterator_type>;

        typedef typename qlibc::iterator_traits<_Iterator>::value_type value_type;
        typedef typename qlibc::iterator_traits<_Iterator>::iterator_category iterator_category;
        typedef typename qlibc::iterator_traits<_Iterator>::difference_type difference_type;
        typedef typename qlibc::iterator_traits<_Iterator>::pointer pointer;
        typedef typename qlibc::iterator_traits<_Iterator>::reference reference;
    protected:
        iterator_type _M_current;
    public:
        QLIBC_CONSTEXPR reverse_iterator() QLIBC_NOTHROW : _M_current() { }
        explicit QLIBC_CONSTEXPR reverse_iterator(iterator_type& _Other) : _M_current(_Other) { }
        QLIBC_CONSTEXPR reverse_iterator(const iterator_type& _Other) : _M_current(_Other) { }
        reverse_iterator(const reverse_iterator& _Other) : _M_current(_Other.base()) { }
        reverse_iterator& operator=(const reverse_iterator& _Other);
        ~reverse_iterator() = default;

        iterator_type base() const QLIBC_NOTHROW;
        reference operator*() const;
        pointer operator->() const;
        reference operator[](difference_type __n) const;

        reverse_iterator& operator++();
        reverse_iterator operator++(int);
        reverse_iterator& operator+=(difference_type __n);
        reverse_iterator operator+(difference_type __n);

        reverse_iterator& operator--();
        reverse_iterator operator--(int);
        reverse_iterator& operator-=(difference_type __n);
        reverse_iterator operator-(difference_type __n);
    };
    template<typename _Iterator>
    reverse_iterator<_Iterator> reverse_iterator<_Iterator>::
            operator-(reverse_iterator::difference_type __n) {
        return reverse_iterator<_Iterator>(_M_current + __n);
    }
    template<typename _Iterator>
    reverse_iterator<_Iterator> &reverse_iterator<_Iterator>::
            operator-=(reverse_iterator::difference_type __n) {
        _M_current += __n;
        return *this;
    }
    template<typename _Iterator>
    reverse_iterator<_Iterator> reverse_iterator<_Iterator>::operator--(int) {
        reverse_iterator<_Iterator> __Temp = *this;
        _M_current++;
        return __Temp;
    }
    template<typename _Iterator>
    reverse_iterator<_Iterator> &reverse_iterator<_Iterator>::operator--() {
        _M_current++;
        return *this;
    }
    template<typename _Iterator>
    reverse_iterator<_Iterator> reverse_iterator<_Iterator>::
            operator+(reverse_iterator::difference_type __n) {
        return reverse_iterator<_Iterator>(_M_current - __n);
    }
    template<typename _Iterator>
    reverse_iterator<_Iterator> &reverse_iterator<_Iterator>::
            operator+=(reverse_iterator::difference_type __n) {
        _M_current -= __n;
        return *this;
    }
    template<typename _Iterator>
    reverse_iterator<_Iterator> reverse_iterator<_Iterator>::operator++(int) {
        reverse_iterator<_Iterator> __Temp = *this;
        --_M_current;
        return __Temp;
    }
    template<typename _Iterator>
    reverse_iterator<_Iterator> &reverse_iterator<_Iterator>::operator++() {
        --_M_current;
        return *this;
    }
    template<typename _Iterator>
    typename reverse_iterator<_Iterator>::reference reverse_iterator<_Iterator>::
            operator[](reverse_iterator::difference_type __n) const {
        return *((*this) + __n);
    }
    template<typename _Iterator>
    typename reverse_iterator<_Iterator>::pointer reverse_iterator<_Iterator>::operator->() const {
        return &(this->operator*());
    }
    /// Every Time Dereference The Inner Pointer It Will Decrease The Pointer Automatically
    template<typename _Iterator>
    typename reverse_iterator<_Iterator>::reference reverse_iterator<_Iterator>::operator*() const {
        iterator_type Iter_temp = _M_current;
        return *(--Iter_temp);
    }
    template<typename _Iterator>
    reverse_iterator<_Iterator> &reverse_iterator<_Iterator>::operator=(const reverse_iterator &_Other) {
        this->_M_current = _Other.base();
        return *this;
    }
    template<typename _Iterator>
    typename reverse_iterator<_Iterator>::iterator_type
    reverse_iterator<_Iterator>::base() const QLIBC_NOTHROW {
        return this->_M_current;
    }
    /// Non-Member Function For Reverse Iterator
    template<typename _Iterator>
    reverse_iterator<_Iterator> make_reverse_iterator(_Iterator _Iter){
        return reverse_iterator<_Iterator>(_Iter);
    }
    template<typename _Iterator>
    QLIBC_CONSTEXPR inline bool
    operator==(const reverse_iterator<_Iterator>& __lhs, const reverse_iterator<_Iterator>& __rhs){
        return __lhs.base() == __rhs.base();
    }
    template<typename _Iterator>
    QLIBC_CONSTEXPR inline bool
    operator!=(const reverse_iterator<_Iterator>& __lhs, const reverse_iterator<_Iterator>& __rhs){
        return __lhs.base() != __rhs.base();
    }
    template<typename _Iterator>
    QLIBC_CONSTEXPR inline bool
    operator>(const reverse_iterator<_Iterator>& __lhs, const reverse_iterator<_Iterator>& __rhs){
        return __lhs.base() > __rhs.base();
    }
    template<typename _Iterator>
    QLIBC_CONSTEXPR inline bool
    operator<(const reverse_iterator<_Iterator>& __lhs, const reverse_iterator<_Iterator>& __rhs){
        return __lhs.base() < __rhs.base();
    }
    template<typename _Iterator>
    QLIBC_CONSTEXPR inline bool
    operator>=(const reverse_iterator<_Iterator>& __lhs, const reverse_iterator<_Iterator>& __rhs){
        return __lhs.base() >= __rhs.base();
    }
    template<typename _Iterator>
    QLIBC_CONSTEXPR inline bool
    operator<=(const reverse_iterator<_Iterator>& __lhs, const reverse_iterator<_Iterator>& __rhs){
        return __lhs.base() <= __rhs.base();
    }
}
#endif //QLIBC___0_0_2_QLIBC_ITERATOR_H
