#ifndef QLIBC___0_0_1_QLIBC_VECTOR_H
#define QLIBC___0_0_1_QLIBC_VECTOR_H

#include "../_C_dep.h"

namespace __qlibc__{

    /// Vector Implementation
    template<typename _Tp, typename _Allocator>
    struct _Vector_Imp{
        /// Base Type Allocator
        using _Allocator_Tp_Traits = qlibc::allocator_traits<_Allocator>;
        using _Allocator_Ele_Traits = typename _Allocator_Tp_Traits::template rebind_allocator_type<_Tp>;

        using allocator_type =  typename _Allocator_Tp_Traits::allocator_type;
        using size_type = typename _Allocator_Ele_Traits::size_type;
    protected:
        /// Protected Data Member Variables
        _Tp * _M_start;
        _Tp * _M_finish;
        _Tp * _M_end_of_storage;
        QLIBC_CONSTEXPR allocator_type _M_get_allocator() const QLIBC_NOEXCEPT;
    public:
        QLIBC_CONSTEXPR _Vector_Imp() QLIBC_NOEXCEPT
        : _M_start{nullptr}, _M_finish{nullptr}, _M_end_of_storage{nullptr} { }
        explicit  _Vector_Imp(qlibc::size_t __n)
        : _Vector_Imp(){
            this->_M_start = this->_M_get_allocator().allocate(__n);
            this->_M_finish = this->_M_start + __n;
            this->_M_end_of_storage = this->_M_finish;
            qlibc::uninitialized_fill(this->_M_start, this->_M_finish, _Tp());
        }
        _Vector_Imp(const std::initializer_list<_Tp>& __li) : _Vector_Imp(__li.size()){
            qlibc::uninitialized_copy(__li.begin(), __li.end(), this->_M_start);
        }
        _Vector_Imp(qlibc::size_t __n, const _Tp& __val)
                : _Vector_Imp(){
            this->_M_start = this->_M_get_allocator().allocate(__n);
            this->_M_finish = this->_M_start + __n;
            this->_M_end_of_storage = this->_M_finish;
            qlibc::uninitialized_fill(this->_M_start, this->_M_finish, __val);
        }
        ~_Vector_Imp(){
            /// Judge Whether the Vector is Empty
            if (this->_M_start != this->_M_finish){
                __qlibc__::_Destroy(this->_M_start, this->_M_finish);
                this->_M_get_allocator().deallocate(this->_M_start);
            }
        }
    };
    template<typename _Tp, typename _Allocator>
    QLIBC_CONSTEXPR typename _Vector_Imp<_Tp, _Allocator>::allocator_type
    _Vector_Imp<_Tp, _Allocator>::_M_get_allocator() const QLIBC_NOEXCEPT{
        return typename _Allocator_Tp_Traits::allocator_type();
    }
    template<typename _Tp>
    struct _vector_iterator;

    template<typename _Tp>
    QLIBC_CONSTEXPR bool operator==(const _vector_iterator<_Tp>& __lhs, const _vector_iterator<_Tp>& __rhs);
    template<typename _Tp>
    QLIBC_CONSTEXPR  qlibc::ptrdiff_t
    operator-(const _vector_iterator<_Tp>& __lhs, const _vector_iterator<_Tp>& __rhs);

    /// Vector Iterator
    template<typename _Tp>
    struct _vector_iterator
            : public qlibc::iterator<qlibc::random_access_iterator_tag, _Tp>{
        template<typename _Up>
        friend QLIBC_CONSTEXPR bool operator==(const _vector_iterator<_Up>&, const _vector_iterator<_Up>&);
        template<typename _Up>
        friend QLIBC_CONSTEXPR qlibc::ptrdiff_t
        operator-(const _vector_iterator<_Tp>& , const _vector_iterator<_Tp>&);
        using _element_type = _Tp;
    protected:
        _element_type * M_base;
    public:
        /// constructor
        QLIBC_CONSTEXPR _vector_iterator() QLIBC_NOEXCEPT : M_base{nullptr} { }
        QLIBC_CONSTEXPR _vector_iterator(_Tp* ptr) QLIBC_NOEXCEPT : M_base{ptr} { }

        _vector_iterator(const _vector_iterator& _other) : M_base(_other.M_base) { }
        _vector_iterator& operator=(const _vector_iterator& _other);
        ~_vector_iterator() = default;

        _element_type& operator*() const QLIBC_NOEXCEPT { return *(this->M_base); }
        _element_type * operator->() const QLIBC_NOEXCEPT { return this->M_base; }
        _element_type & operator[](qlibc::ptrdiff_t __n) const QLIBC_NOEXCEPT { return this->M_base[__n]; }
        _element_type* base()  const QLIBC_NOEXCEPT { return this->M_base; }

        _vector_iterator& operator++() QLIBC_NOEXCEPT;
        _vector_iterator operator++(int) QLIBC_NOEXCEPT;
        _vector_iterator operator+(qlibc::ptrdiff_t __n) const QLIBC_NOEXCEPT;
        _vector_iterator& operator+=(qlibc::ptrdiff_t __n) QLIBC_NOEXCEPT;

        _vector_iterator& operator--() QLIBC_NOEXCEPT;
        _vector_iterator operator--(int) QLIBC_NOEXCEPT;
        _vector_iterator operator-(qlibc::ptrdiff_t __n) const QLIBC_NOEXCEPT;
        _vector_iterator& operator-=(qlibc::ptrdiff_t __n) QLIBC_NOEXCEPT;
    };
    template<typename _Tp>
    _vector_iterator<_Tp>& _vector_iterator<_Tp>::operator=(const _vector_iterator&_other) {
        if (this != &_other)
            this->M_base = _other->M_base;
        return *this;
    }
    template<typename _Tp>
    _vector_iterator<_Tp> &_vector_iterator<_Tp>::operator++() noexcept {
        ++this->M_base;
        return *this;
    }
    template<typename _Tp>
     _vector_iterator<_Tp> _vector_iterator<_Tp>::operator++(int) noexcept{
        return _vector_iterator<_Tp>(this->M_base++);
    }
    template<typename _Tp>
    _vector_iterator<_Tp> _vector_iterator<_Tp>::operator+(qlibc::ptrdiff_t n) const noexcept {
        return _vector_iterator<_Tp>(this->M_base + n);
    }
    template<typename _Tp>
    _vector_iterator<_Tp>& _vector_iterator<_Tp>::operator+=(qlibc::ptrdiff_t n) noexcept {
        this->M_base += n;
        return *this;
    }
    template<typename _Tp>
    _vector_iterator<_Tp>& _vector_iterator<_Tp>::operator--() noexcept {
        --this->M_base;
        return *this;
    }
    template<typename _Tp>
    _vector_iterator<_Tp> _vector_iterator<_Tp>::operator--(int) noexcept {
        return _vector_iterator<_Tp>(this->M_base--);
    }
    template<typename _Tp>
    _vector_iterator<_Tp> _vector_iterator<_Tp>::operator-(qlibc::ptrdiff_t n) const noexcept {
        return _vector_iterator<_Tp>(this->M_base - n);
    }
    template<typename _Tp>
    _vector_iterator<_Tp>& _vector_iterator<_Tp>::operator-=(qlibc::ptrdiff_t n) noexcept {
        this->M_base -= n;
        return *this;
    }
    /// Operator Overload
    template<typename _Tp>
    QLIBC_CONSTEXPR inline bool operator==(const _vector_iterator<_Tp>& __lhs, const _vector_iterator<_Tp>& __rhs){
        return __lhs.M_base == __rhs.M_base;
    }
    template<typename _Tp>
    QLIBC_CONSTEXPR inline bool operator!=(const _vector_iterator<_Tp>& __lhs, const _vector_iterator<_Tp>& __rhs){
        return !(__lhs == __rhs);
    }
    template<typename _Tp>
    QLIBC_CONSTEXPR inline qlibc::ptrdiff_t operator-(const _vector_iterator<_Tp>& __lhs, const _vector_iterator<_Tp>& __rhs){
        return (__lhs.base()) - (__rhs.base());
    }
}
namespace qlibc{
    template<typename _Up>
    using normal_iterator = __qlibc__::_vector_iterator<_Up>;

    /// qlibc::vector
    template<typename _Tp, typename _Alloc = qlibc::allocator<_Tp>>
    class vector : protected __qlibc__::_Vector_Imp<_Tp, _Alloc>{
        using _Base_Vector = __qlibc__::_Vector_Imp<_Tp, _Alloc>;
        using __qlibc__::_Vector_Imp<_Tp, _Alloc>::_M_get_allocator;
    public:
        typedef typename __qlibc__::_Vector_Imp<_Tp, _Alloc>::allocator_type            allocator_type;
        typedef typename __qlibc__::_Vector_Imp<_Tp, _Alloc>::size_type                 size_type;
        typedef typename __qlibc__::_Vector_Imp<_Tp, _Alloc>::_Allocator_Tp_Traits      allocator_traits_type;

        typedef typename allocator_traits_type::value_type          value_type;
        typedef typename allocator_traits_type::pointer             pointer;
        typedef typename allocator_traits_type::const_pointer       const_pointer;
        typedef typename allocator_traits_type::difference_type     difference_type;
        typedef typename allocator_traits_type::reference           reference;
        typedef typename allocator_traits_type::const_reference     const_reference;

        using iterator = normal_iterator<_Tp>;
        using const_iterator = normal_iterator<const _Tp>;
    public:
        QLIBC_CONSTEXPR vector() QLIBC_NOEXCEPT : _Base_Vector() { }
        explicit vector(size_type n) : _Base_Vector(n) { }
        vector(size_type n, const value_type& _value) : _Base_Vector(n, _value) { }
        vector(const std::initializer_list<_Tp>& _li) : _Base_Vector(_li) { }

        ~vector() = default;
    public:
        iterator begin() QLIBC_NOEXCEPT;
        iterator end() QLIBC_NOEXCEPT;

        const_iterator begin() const QLIBC_NOEXCEPT;
        const_iterator end() const QLIBC_NOEXCEPT;

        const_iterator cbegin() const QLIBC_NOEXCEPT;
        const_iterator cend() const QLIBC_NOEXCEPT;

        QLIBC_CONSTEXPR size_type size() const QLIBC_NOEXCEPT;
        QLIBC_CONSTEXPR bool empty() const QLIBC_NOEXCEPT;
        QLIBC_CONSTEXPR size_type capacity() const QLIBC_NOEXCEPT;
        reference operator[](difference_type __n) const QLIBC_NOEXCEPT;
    };
    template<typename _Tp, typename _Alloc>
    typename vector<_Tp, _Alloc>::iterator vector<_Tp, _Alloc>::end() QLIBC_NOEXCEPT {
        return iterator (this->_M_finish);
    }
    template<typename _Tp, typename _Alloc>
    typename vector<_Tp, _Alloc>:: iterator vector<_Tp, _Alloc>::begin() QLIBC_NOEXCEPT {
        return iterator (this->_M_start);
    }
    template<typename _Tp, typename _Alloc>
    typename vector<_Tp, _Alloc>::const_iterator vector<_Tp, _Alloc>::end() const QLIBC_NOEXCEPT {
        return const_iterator(this->_M_finish);
    }
    template<typename _Tp, typename _Alloc>
    typename vector<_Tp, _Alloc>:: const_iterator vector<_Tp, _Alloc>::begin() const QLIBC_NOEXCEPT {
        return const_iterator (this->_M_start);
    }
    template<typename _Tp, typename _Alloc>
    typename vector<_Tp, _Alloc>::const_iterator vector<_Tp, _Alloc>::cend() const QLIBC_NOEXCEPT {
        return const_iterator(this->_M_finish);
    }
    template<typename _Tp, typename _Alloc>
    typename vector<_Tp, _Alloc>:: const_iterator vector<_Tp, _Alloc>::cbegin() const QLIBC_NOEXCEPT {
        return const_iterator (this->_M_start);
    }
    template<typename _Tp, typename _Alloc>
    QLIBC_CONSTEXPR typename vector<_Tp, _Alloc>:: size_type vector<_Tp, _Alloc>::size() const QLIBC_NOEXCEPT {
        return static_cast<size_type>(this->_M_finish - this->_M_start);
    }
    template<typename _Tp, typename _Alloc>
    QLIBC_CONSTEXPR typename vector<_Tp, _Alloc>:: size_type vector<_Tp, _Alloc>::capacity()const QLIBC_NOEXCEPT {
        return static_cast<size_type>(this->_M_end_of_storage - this->_M_start);
    }
    template<typename _Tp, typename _Alloc>
    QLIBC_CONSTEXPR bool vector<_Tp, _Alloc>::empty() const noexcept {
        return (this->_M_start == this->_M_finish);
    }
    template<typename _Tp, typename _Alloc>
    typename vector<_Tp, _Alloc>:: reference vector<_Tp, _Alloc>::operator[](difference_type n) const QLIBC_NOEXCEPT {
        return this->_M_start[n];
    }
    /// Operator Overload For Vector !
    template<typename _Tp, typename _Alloc>
    OSTREAM& operator<<(OSTREAM & OS, const vector<_Tp, _Alloc>& buffer){
        STD_COUT << "[";
        for (auto _Iter = buffer.begin(); _Iter != buffer.end(); ){
            STD_COUT << *_Iter;
            ++_Iter;
            if (_Iter != buffer.end())
                STD_COUT<< ", ";
        }
        STD_COUT << "]";
    }
}
#endif //QLIBC___0_0_1_QLIBC_VECTOR_H
