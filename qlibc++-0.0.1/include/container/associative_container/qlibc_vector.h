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
        QLIBC_CONSTEXPR _Vector_Imp(_Tp* start, _Tp * _finish, _Tp* end_of_storage) :
        _M_start(start), _M_finish(_finish), _M_end_of_storage(end_of_storage) { }
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
        template<typename _InputIterator>
        _Vector_Imp(_InputIterator __first, _InputIterator __last)
        : _Vector_Imp(qlibc::distance(__first, __last)){
                qlibc::copy(__first, __last, this->_M_start);
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
        template<typename _Up>
        QLIBC_CONSTEXPR _vector_iterator(const _vector_iterator<_Up>& _other)
            QLIBC_NOEXCEPT : M_base(const_cast<_element_type*>(_other.base())) { }

        _vector_iterator(const _vector_iterator& _other) : M_base(_other.M_base) { }
        _vector_iterator& operator=(const _vector_iterator& _other);
         operator _vector_iterator<const _Tp>(){
             return _vector_iterator<const _Tp>(this->M_base);
         }
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
            this->M_base = _other.base();
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
        template<typename _InputIterator>
        vector(_InputIterator __first, _InputIterator __last) : _Base_Vector(__first, __last) { }

        vector(const vector& _other) : _Base_Vector(_other.size()) {
            qlibc::uninitialized_copy(_other.begin(), _other.end(), this->_M_start);
        }
        vector(vector&& _other) QLIBC_NOEXCEPT
            : _Base_Vector(_other->_M_start, _other->_M_finish, _other->_M_end_of_storage) {
            _other->_M_start = nullptr;
            _other->_M_finish = nullptr;
            _other->_M_end_of_storage = nullptr;
        }
        vector& operator=(vector && _other) QLIBC_NOEXCEPT;
        ~vector() = default;
    private:
        enum {EXPAND_SIZE_FACTOR = 2};
        void _require_non_empty() QLIBC_NOEXCEPT;
        QLIBC_CONSTEXPR size_type _storage_can_be_used() const QLIBC_NOEXCEPT;
        template<typename... _Args>
        void _emplace_back_auxiliary(_Args&&... _args);
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

        reference back()  QLIBC_NOEXCEPT;
        reference front()  QLIBC_NOEXCEPT;

        void clear();
        void pop_back();
        void push_back(const value_type& value);
        void push_back(value_type&& value);

        template<typename... _Args>
        void emplace_back(_Args&&... __args);
        template<typename... _Args>
        iterator emplace(const_iterator __position, _Args&&... __args);

        iterator erase(const_iterator __position);
        iterator erase(const_iterator __first, const_iterator __last);

        iterator insert(const_iterator __position, const value_type& __value);
        iterator insert(const_iterator __position, value_type&& __value);
        iterator insert(const_iterator __position, size_type __count, const _Tp& __value);
        template<typename _InputIterator>
        iterator insert(iterator __position, _InputIterator __first, _InputIterator __last);
        iterator insert(const_iterator __position, const std::initializer_list<value_type>& li);
    };

    template<typename _Tp, typename _Alloc>
    vector<_Tp, _Alloc>&vector<_Tp, _Alloc>::operator=(vector &&_other) QLIBC_NOEXCEPT {
        if (this != &_other){
            this->clear();
            this->_M_start = _other._M_start;
            this->_M_finish = _other._M_finish;
            this->_M_end_of_storage = _other._M_end_of_storage;
            _other->_M_start = nullptr;
            _other->_M_finish = nullptr;
            _other->_M_end_of_storage = nullptr;
        }
        return *this;
    }
    template<typename _Tp, typename _Alloc>
    template<typename... _Args>
    typename vector<_Tp, _Alloc>::iterator vector<_Tp, _Alloc>
            ::emplace(const_iterator __position, _Args &&... __args) {
        if (this->empty()){
            this->_emplace_back_auxiliary(qlibc::forward<decltype(__args)>(__args)...);
            return iterator(this->_M_start);
        }
        if (this->_storage_can_be_used()){
            qlibc::copy_backward(__position, const_iterator(this->_M_finish), this->_M_finish + 1);
            typedef typename qlibc::iterator_traits<iterator>::value_type Val_Type;
            /// According To C++ ISO/ANSI Standard
            /// The emplace function needs to construct an object in-place and move this object to the existing position
            Val_Type __temp_value(qlibc::forward<decltype(__args)>(__args)...);
            *const_cast<pointer>(__position.base()) = qlibc::move(__temp_value);
            ++this->_M_finish;
            return iterator(__position);
        } else{
            const size_t _old_size = this->size();
            const size_t _new_size = (_old_size == 0) ? 1 : _old_size * EXPAND_SIZE_FACTOR;
            pointer _new_start = this->_M_get_allocator().allocate(_new_size);
            auto _new_finish = _new_start;
            pointer _insert_position;
            try {
                _new_finish = qlibc::uninitialized_copy
                        (const_iterator(this->_M_start), __position, _new_finish);
                __qlibc__::_Construct(_new_finish, qlibc::forward<decltype(__args)>(__args)...);
                _insert_position = _new_finish;
                _new_finish++;
                _new_finish = qlibc::uninitialized_copy(__position,
                                                        const_iterator(this->_M_finish),_new_finish);
            } catch (QLIBC_ALL_EXCEPTION) {
                __qlibc__::_Destroy(_new_start, _new_finish);
                this->_M_get_allocator().deallocate(_new_start);
                QLIBC_THROW_EXCEPTION_AGAIN;
            }
            __qlibc__::_Destroy(this->_M_start, this->_M_finish);
            this->_M_get_allocator().deallocate(this->_M_start);
            this->_M_start = _new_start;
            this->_M_finish = _new_finish;
            this->_M_end_of_storage = this->_M_start + _new_size;
            return iterator (_insert_position);
        }
    }
    /// Insert
    template<typename _Tp, typename _Alloc>
    typename vector<_Tp, _Alloc>::iterator vector<_Tp, _Alloc>
            ::insert(vector::const_iterator __position, const vector::value_type &__value) {
        return this->emplace(__position, __value);
    }
    template<typename _Tp, typename _Alloc>
    typename vector<_Tp, _Alloc>::iterator vector<_Tp, _Alloc>
    ::insert(vector::const_iterator __position, value_type&& __value) {
        return this->emplace(__position, qlibc::move(__value));
    }
    /// TODO : Finish These Function
    template<typename _Tp, typename _Alloc>
    typename vector<_Tp, _Alloc>::iterator vector<_Tp, _Alloc>
    ::insert(vector::const_iterator __position, size_type __count, const _Tp& __value) {

    }
    template<typename _Tp, typename _Alloc>
    typename vector<_Tp, _Alloc>::iterator vector<_Tp, _Alloc>
    ::insert(vector::const_iterator __position, const std::initializer_list<value_type>& li) {

    }
    template<typename _Tp, typename _Alloc>
    template<typename _InputIterator>
    typename vector<_Tp, _Alloc>::iterator vector<_Tp, _Alloc>
    ::insert(iterator __position, _InputIterator __first, _InputIterator __last) {

    }
    template<typename _Tp, typename _Alloc>
    typename vector<_Tp, _Alloc>::iterator vector<_Tp, _Alloc>
            ::erase(vector::const_iterator __first, vector::const_iterator __last) {

    }
    template<typename _Tp, typename _Alloc>
    typename vector<_Tp, _Alloc>::iterator vector<_Tp, _Alloc>::erase(const_iterator __position) {

    }
    /// TODO End
    template<typename _Tp, typename _Alloc>
    void vector<_Tp, _Alloc>::pop_back() {
        if (!this->empty()){
            --this->_M_finish;
            __qlibc__::_Destroy(this->_M_finish);
        }
    }
    template<typename _Tp, typename _Alloc>
    template<typename... _Args>
    void vector<_Tp, _Alloc>::_emplace_back_auxiliary(_Args &&... _args) {
        const size_type _old_size = this->size();
        const size_type _new_size = (_old_size == 0) ? 1 : this->size() * EXPAND_SIZE_FACTOR;
        pointer _new_start = this->_M_get_allocator().allocate(_new_size);
        auto _new_finish = _new_start;
        try {
            _new_finish = qlibc::uninitialized_copy(this->_M_start, this->_M_finish, _new_start);
            __qlibc__::_Construct(_new_finish, qlibc::forward<decltype(_args)>(_args)...);
            ++_new_finish;
        } catch (QLIBC_ALL_EXCEPTION) {
            __qlibc__::_Destroy(_new_start, _new_finish);
            this->_M_get_allocator().deallocate(_new_start);
            QLIBC_THROW_EXCEPTION_AGAIN;
        }
        __qlibc__::_Destroy(this->_M_start, this->_M_finish);
        this->_M_get_allocator().deallocate(this->_M_start);
        this->_M_start = _new_start;
        this->_M_finish = _new_finish;
        this->_M_end_of_storage = this->_M_start + _new_size;
    }
    template<typename _Tp, typename _Alloc>
    template<typename... _Args>
    void vector<_Tp, _Alloc>::emplace_back(_Args&&... __args) {
        if (this->_storage_can_be_used()){
            __qlibc__::_Construct(this->_M_finish, qlibc::forward<decltype(__args)>(__args)...);
            ++this->_M_finish;
        }else
            this->_emplace_back_auxiliary(qlibc::forward<decltype(__args)>(__args)...);
    }
    template<typename _Tp, typename _Alloc>
    void vector<_Tp, _Alloc>::push_back(vector::value_type &&value) {
        this->emplace_back(qlibc::move(value));
    }
    template<typename _Tp, typename _Alloc>
    void vector<_Tp, _Alloc>::push_back(const vector::value_type &value) {
        this->emplace_back(value);
    }
    template<typename _Tp, typename _Alloc>
    void vector<_Tp, _Alloc>::clear() {
        if (!this->empty()){
            __qlibc__::_Destroy(this->_M_start, this->_M_finish);
            this->_M_get_allocator().deallocate(this->_M_start);
        }
        this->_M_start = nullptr;
        this->_M_finish = nullptr;
        this->_M_end_of_storage = nullptr;
    }
    template<typename _Tp, typename _Alloc>
    QLIBC_CONSTEXPR typename vector<_Tp, _Alloc>::size_type vector<_Tp, _Alloc>::
            _storage_can_be_used() const QLIBC_NOEXCEPT {
        return this->capacity() - this->size();
    }

    template<typename _Tp, typename _Alloc>
    typename vector<_Tp, _Alloc>::reference vector<_Tp, _Alloc>::front() QLIBC_NOEXCEPT {
        this->_require_non_empty();
        return *(this->_M_start);
    }
    template<typename _Tp, typename _Alloc>
    typename vector<_Tp, _Alloc>::reference vector<_Tp, _Alloc>::back() QLIBC_NOEXCEPT {
        this->_require_non_empty();
        return *(this->_M_finish - 1);
    }
    template<typename _Tp, typename _Alloc>
    void vector<_Tp, _Alloc>::_require_non_empty() QLIBC_NOEXCEPT{
        if (this->_M_start == this->_M_finish){
            STD_CERROR << "Try To Access The Element of Empty Container\n";
            exit(-1);
        }
    }
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
        OS << "[";
        for (auto _Iter = buffer.begin(); _Iter != buffer.end(); ){
            OS << *_Iter;
            ++_Iter;
            if (_Iter != buffer.end())
                OS<< ", ";
        }
        OS << "]";
        return OS;
    }
    template<typename _Tp, typename _Alloc>
    inline bool operator==(const vector<_Tp, _Alloc>& _lhs, const vector<_Tp, _Alloc>& _rhs){
        return _lhs.size() == _rhs.size() && qlibc::equal(_lhs.begin(), _lhs.end(), _rhs.begin());
    }
    template<typename _Tp, typename _Alloc>
    inline bool operator!=(const vector<_Tp, _Alloc>& _lhs, const vector<_Tp, _Alloc>& _rhs){
        return !(_lhs == _rhs);
    }
}
#endif //QLIBC___0_0_1_QLIBC_VECTOR_H
