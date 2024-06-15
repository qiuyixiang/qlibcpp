#ifndef QLIBC___0_0_2_QLIBC_ITERATOR_H
#define QLIBC___0_0_2_QLIBC_ITERATOR_H

#include "./qlibc_iterator_base.h"
#include "../utility/qlibc_move.h"
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
    /// Back Insert Iterator
    template<typename _Container>
    class back_insert_iterator
            : public qlibc::iterator<void, qlibc::output_iterator_tag, void, void, void>{
    private:
        _Container* _M_Base;
    public:
        using container_type = _Container;
        explicit back_insert_iterator(_Container& __container);
        ~back_insert_iterator() = default;
        back_insert_iterator& operator=(const typename _Container::value_type& __value);
        back_insert_iterator& operator=(typename _Container::value_type&& __value);
        back_insert_iterator& operator++();
        back_insert_iterator operator++(int);
        back_insert_iterator& operator*();
    };
    template<typename _Container>
    back_insert_iterator<_Container> &back_insert_iterator<_Container>::operator*() {
        return *this;
    }
    template<typename _Container>
    back_insert_iterator<_Container> back_insert_iterator<_Container>::operator++(int) {
        return *this;
    }
    template<typename _Container>
    back_insert_iterator<_Container> &back_insert_iterator<_Container>::operator++() {
        return *this;
    }
    template<typename _Container>
    back_insert_iterator<_Container> &back_insert_iterator<_Container>
    ::operator=(typename _Container::value_type && __value) {
        _M_Base->push_back(qlibc::move(__value));
        return *this;
    }
    template<typename _Container>
    back_insert_iterator<_Container> &back_insert_iterator<_Container>
    ::operator=(const typename _Container::value_type &__value) {
        _M_Base->push_back(__value);
        return *this;
    }
    template<typename _Container>
    back_insert_iterator<_Container>::
            back_insert_iterator(_Container &__container) : _M_Base(qlibc::address_of(__container)) { }
    /// Helper Function For Back Insert Iterator
    template<typename _Container>
    inline QLIBC_CONSTEXPR back_insert_iterator<_Container> back_inserter(_Container& __container){
        return back_insert_iterator<_Container>(__container);
    }
    /// Front Insert Iterator
    template<typename _Container>
    class front_insert_iterator
            : public qlibc::iterator<void, qlibc::output_iterator_tag, void, void, void>{
    private:
        _Container* _M_Base;
    public:
        using container_type = _Container;
        explicit front_insert_iterator(_Container& __container);
        ~front_insert_iterator() = default;
        front_insert_iterator& operator=(const typename _Container::value_type& __value);
        front_insert_iterator& operator=(typename _Container::value_type&& __value);
        front_insert_iterator& operator++();
        front_insert_iterator operator++(int);
        front_insert_iterator& operator*();
    };
    template<typename _Container>
    front_insert_iterator<_Container> &front_insert_iterator<_Container>::operator*() {
        return *this;
    }
    template<typename _Container>
    front_insert_iterator<_Container> front_insert_iterator<_Container>::operator++(int) {
        return *this;
    }
    template<typename _Container>
    front_insert_iterator<_Container> &front_insert_iterator<_Container>::operator++() {
        return *this;
    }
    template<typename _Container>
    front_insert_iterator<_Container> &front_insert_iterator<_Container>
    ::operator=(typename _Container::value_type && __value) {
        _M_Base->push_front(qlibc::move(__value));
        return *this;
    }
    template<typename _Container>
    front_insert_iterator<_Container> &front_insert_iterator<_Container>
    ::operator=(const typename _Container::value_type &__value) {
        _M_Base->push_front(__value);
        return *this;
    }
    template<typename _Container>
    front_insert_iterator<_Container>::
    front_insert_iterator(_Container &__container) : _M_Base(qlibc::address_of(__container)) { }
    /// Helper Function For Front Insert Iterator
    template<typename _Container>
    inline QLIBC_CONSTEXPR front_insert_iterator<_Container> front_inserter(_Container& __container){
        return front_insert_iterator<_Container>(__container);
    }
    /// Insert Iterator
    template<typename _Container>
    class insert_iterator : public qlibc::iterator<void, qlibc::output_iterator_tag, void, void, void>{
    private:
        _Container* _M_Base;
        typename _Container::iterator _M_Iter;
    public:
        using container_type = _Container;
        insert_iterator(_Container& __container, typename _Container::iterator __iter);
        ~insert_iterator() = default;
        insert_iterator<_Container>& operator=(const typename _Container::value_type& __value);
        insert_iterator<_Container>& operator=(typename _Container::value_type&& __value);
        insert_iterator<_Container>& operator++();
        insert_iterator<_Container> operator++(int);
        insert_iterator<_Container>& operator*();
    };
    template<typename _Container>
    insert_iterator<_Container> &insert_iterator<_Container>::operator*() {
        return *this;
    }
    template<typename _Container>
    insert_iterator<_Container> insert_iterator<_Container>::operator++(int) {
        return *this;
    }
    template<typename _Container>
    insert_iterator<_Container> &insert_iterator<_Container>::operator++() {
        return *this;
    }
    template<typename _Container>
    insert_iterator<_Container> &insert_iterator<_Container>::operator=(typename _Container::value_type && __value) {
        _M_Iter = _M_Base->insert(_M_Iter, qlibc::move(__value));
        ++_M_Iter;
        return *this;
    }
    template<typename _Container>
    insert_iterator<_Container> &insert_iterator<_Container>::operator=(const typename _Container::value_type&__value) {
        _M_Iter = _M_Base->insert(_M_Iter, __value);
        ++_M_Iter;
        return *this;
    }
    template<typename _Container>
    insert_iterator<_Container>::
    insert_iterator(_Container &__container, typename _Container::iterator __iter)
    : _M_Base(qlibc::address_of(__container)), _M_Iter(__iter) { }
    /// Helper Function For Insert Iterator
    template<typename _Container>
    inline QLIBC_CONSTEXPR insert_iterator<_Container>
    inserter(_Container& __container, typename _Container::iterator __iter){
        return insert_iterator<_Container>(__container, __iter);
    }
}
#endif //QLIBC___0_0_2_QLIBC_ITERATOR_H
