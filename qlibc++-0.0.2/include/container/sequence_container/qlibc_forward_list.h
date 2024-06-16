#ifndef QLIBC___0_0_2_QLIBC_FORWARD_LIST_H
#define QLIBC___0_0_2_QLIBC_FORWARD_LIST_H

#include "../dep.h"
namespace __qlibc__{
    /// Forward List Node
    template<typename _Tp>
    struct _forward_list_node{
    public:
        _Tp M_data;
        _forward_list_node<_Tp> * M_next;

        QLIBC_CONSTEXPR _forward_list_node() QLIBC_NOTHROW : M_data(), M_next(nullptr) { }
        _forward_list_node(const _Tp& __data) : M_data(__data), M_next(nullptr) { }
        _forward_list_node(_Tp&& __data) : M_data(qlibc::move(__data)), M_next(nullptr) { }
        ~_forward_list_node() = default;
    };
    /// Forward List Iterator
    template<typename _Tp, bool IS_CONSTANT>
    class forward_list_iterator{
    private:
        using element_type = typename qlibc::conditional<IS_CONSTANT, const _Tp, _Tp>::type;
        using node_type = _forward_list_node<element_type>;

        node_type * _M_base;
    public:
        typedef qlibc::forward_iterator_tag iterator_category;
        typedef _Tp                     value_type;
        typedef _Tp*                    pointer;
        typedef const _Tp*              const_pointer;
        typedef _Tp&                    reference;
        typedef const _Tp&              const_reference;
        typedef qlibc::size_t           size_type;
        typedef qlibc::ptrdiff_t        difference_type;
    public:
        /// Constructor
        QLIBC_CONSTEXPR forward_list_iterator() QLIBC_NOTHROW : _M_base(nullptr) { }
        QLIBC_CONSTEXPR forward_list_iterator(node_type * __ptr) QLIBC_NOTHROW : _M_base(__ptr) { }
        /// Copy Constructor
        forward_list_iterator(const forward_list_iterator& _Other);
        forward_list_iterator& operator=(const forward_list_iterator& _Other);
        operator forward_list_iterator<_Tp, false>() const;
        ~forward_list_iterator() = default;

        QLIBC_CONSTEXPR node_type * base() const QLIBC_NOTHROW;
    public:
        /// Public Member Function
        forward_list_iterator& operator++();
        forward_list_iterator operator++(int);
        reference operator*() const;
        pointer operator->() const;
    };
    template<typename _Tp, bool IS_CONSTANT>
    typename forward_list_iterator<_Tp, IS_CONSTANT>::pointer
    forward_list_iterator<_Tp, IS_CONSTANT>::operator->() const {
        return &(this->_M_base->M_data);
    }
    template<typename _Tp, bool IS_CONSTANT>
    typename forward_list_iterator<_Tp, IS_CONSTANT>::reference
    forward_list_iterator<_Tp, IS_CONSTANT>::operator*() const {
        return *(this->_M_base->M_data);
    }
    template<typename _Tp, bool IS_CONSTANT>
    forward_list_iterator<_Tp, IS_CONSTANT> forward_list_iterator<_Tp, IS_CONSTANT>::operator++(int) {
        auto __temp = *this;
        ++(*this);
        return __temp;
    }
    template<typename _Tp, bool IS_CONSTANT>
    forward_list_iterator<_Tp, IS_CONSTANT> &forward_list_iterator<_Tp, IS_CONSTANT>::operator++() {
        this->_M_base = this->_M_base->M_next;
        return *this;
    }
    template<typename _Tp, bool IS_CONSTANT>
    forward_list_iterator<_Tp, IS_CONSTANT>::operator forward_list_iterator<_Tp, false>() const {
        return forward_list_iterator<_Tp, false>(this->base());
    }
    template<typename _Tp, bool IS_CONSTANT>
    forward_list_iterator<_Tp, IS_CONSTANT> &forward_list_iterator<_Tp, IS_CONSTANT>::
            operator=(const forward_list_iterator &_Other) {
        if (this != qlibc::address_of(_Other)){
            this->_M_base = _Other.base();
        }
        return *this;
    }
    template<typename _Tp, bool IS_CONSTANT>
    QLIBC_CONSTEXPR typename forward_list_iterator<_Tp, IS_CONSTANT>::node_type
    *forward_list_iterator<_Tp, IS_CONSTANT>::base() const QLIBC_NOTHROW {
        return this->_M_base;
    }
    template<typename _Tp, bool IS_CONSTANT>
    forward_list_iterator<_Tp, IS_CONSTANT>::
        forward_list_iterator(const forward_list_iterator &_Other) : _M_base(_Other.base()){}

    template<typename _Tp, bool IS_CONSTANT>
    inline QLIBC_CONSTEXPR bool operator==(const forward_list_iterator<_Tp, IS_CONSTANT>& __lhs,
            const forward_list_iterator<_Tp, IS_CONSTANT>& __rhs){
        return __lhs.base() == __rhs.base();
    }
    template<typename _Tp, bool IS_CONSTANT>
    inline QLIBC_CONSTEXPR bool operator!=(const forward_list_iterator<_Tp, IS_CONSTANT>& __lhs,
                                           const forward_list_iterator<_Tp, IS_CONSTANT>& __rhs){
        return !(__lhs == __rhs);
    }
}
namespace qlibc{

    /// forward list
    template<typename _Tp, typename _Alloc = qlibc::allocator<_Tp>>
    class forward_list{
    private:
        using Node_type = __qlibc__::_forward_list_node<_Tp>;
        using allocator_traits = qlibc::allocator_traits<_Alloc>;
    public:
        typedef _Tp                     value_type;
        typedef _Tp*                    pointer;
        typedef const _Tp*              const_pointer;
        typedef _Tp&                    reference;
        typedef const _Tp&              const_reference;
        typedef qlibc::size_t           size_type;
        typedef qlibc::ptrdiff_t        difference_type;
        using allocator_type = typename allocator_traits::template rebind_allocator_type<Node_type>;

        using iterator = __qlibc__::forward_list_iterator<_Tp, false>;
        using const_iterator = __qlibc__::forward_list_iterator<_Tp, true>;
    private:
        /// Private Member Variables
        Node_type M_Base_Node;
        /// Private Member Function
        QLIBC_CONSTEXPR allocator_type _M_get_allocator() const QLIBC_NOTHROW;
        Node_type * _M_Create_Node(const _Tp& __value);
        Node_type * _M_Create_Node(_Tp&& __value);
        void _M_Destroy_Node(Node_type* __ptr);
    public:
        QLIBC_CONSTEXPR forward_list() QLIBC_NOTHROW;
        ~forward_list();
    };

    template<typename _Tp, typename _Alloc>
    void forward_list<_Tp, _Alloc>::_M_Destroy_Node(forward_list::Node_type *__ptr) {
        qlibc::Destroy(qlibc::address_of(__ptr->M_data));
        __ptr->M_next = nullptr;
        this->_M_get_allocator().deallocate(__ptr);
    }
    template<typename _Tp, typename _Alloc>
    typename forward_list<_Tp, _Alloc>::Node_type *forward_list<_Tp, _Alloc>::_M_Create_Node(_Tp &&__value) {
        Node_type * _Result_Node = this->_M_get_allocator().allocate(1);
        _Result_Node->M_next = nullptr;
        qlibc::Construct(qlibc::address_of(_Result_Node->M_data), qlibc::move(__value));
        return _Result_Node;
    }
    template<typename _Tp, typename _Alloc>
    constexpr typename forward_list<_Tp, _Alloc>::allocator_type
    forward_list<_Tp, _Alloc>::_M_get_allocator() const QLIBC_NOTHROW {
        return allocator_type();
    }
    template<typename _Tp, typename _Alloc>
    typename forward_list<_Tp, _Alloc>::Node_type *forward_list<_Tp, _Alloc>::_M_Create_Node(const _Tp &__value) {
        Node_type * _Result_Node = this->_M_get_allocator().allocate(1);
        _Result_Node->M_next = nullptr;
        qlibc::Construct(qlibc::address_of(_Result_Node->M_data), __value);
        return _Result_Node;
    }
    template<typename _Tp, typename _Alloc>
    QLIBC_CONSTEXPR forward_list<_Tp, _Alloc>::
            forward_list() QLIBC_NOTHROW : M_Base_Node() { }
}

#endif //QLIBC___0_0_2_QLIBC_FORWARD_LIST_H
