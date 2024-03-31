/**
 *  @brief A data container with linear time access to elements,
 *  and fixed time insertion/deletion at any point in the sequence.
 *
 *  @tparam _Tp  Type of element.
 *
 *  This is a @e singly @e linked %list.  Traversal up the
 *  %list requires linear time, but adding and removing elements (or
 *  @e nodes) is done in constant time, regardless of where the
 *  change takes place.  Unlike std::vector and std::deque,
 *  random-access iterators are not provided, so subscripting ( @c
 *  [] ) access is not allowed.  For algorithms which only need
 *  sequential access, this lack makes no difference.
 *
 *  Similarly to std::forward_list, mfpkg::forward_list provides
 *  specialized algorithms %unique to linked lists, such as splicing, 
 *  sorting, in-place reversal and also provides extra operations 
 *  such as push_back(), back() and size().
 * 
 *  @file forward_list.h
 *  @author Mohamed fareed
 */

#ifndef FORWARD_LIST_H
#define FORWARD_LIST_H

template <typename _Tp>
class mfpkg::forward_list : public basic_mfpkg::basic_forward_list
{
private:

    typedef forward_list<_Tp> _Self;
    typedef iterator<_Tp> Iterator;
    typedef const_iterator<_Tp> const_Iterator;
    typedef _Tp& reference;
    typedef const _Tp& const_reference;
    typedef basic_forward_list::forward_list<_Tp> basic_object;

    basic_object object;

public:

    forward_list() = default;

    forward_list(std::initializer_list<_Tp> __list)
    {
        for (auto& __x : __list)
        {
            object.insert_after(object.rbegin(), __x);
        }
    }

    forward_list(const _Self& __list)
    {
        for (auto& __x : __list)
        {
            object.insert_after(object.rbegin(), __x);
        }
    }

    ~forward_list() noexcept { }

    _Self& operator=(std::initializer_list<_Tp> __list)
    {
        object.assign(__list);
        return *this;
    }

    _Self& operator=(const _Self& __list)
    {
        object.assign(__list.object);
        return *this;
    }

    _Self& operator=(_Self&& __list)
    {
        object.assign(std::move(__list.object));
        return *this;
    }

    /**
     * @brief  Assigns an initializer_list to a %forward_list.
     * @param  __list  An initializer_list.
     *
     * Replace the contents of the %forward_list with copies 
     * of the elements in the initializer_list @a __list. This is 
     * linear in __list.size().
     */
    void assign(std::initializer_list<_Tp> __list)
    {
        object.assign(__list);
    }

    /**
     *  Returns an iterator that points before the first element
     *  in the %forward_list.  Iteration is done in ordinary element order.
     */
    Iterator before_begin(void) noexcept
    {
        return object.before_begin();
    }

    /**
     *  Returns a const iterator that points before the first element
     *  in the %forward_list.  Iteration is done in ordinary element order.
     */
    const_Iterator before_begin(void) const noexcept
    {
        return object.before_begin();
    }

    /**
     * Returns a read/write iterator that points to the first element
     * in the %forward_list. Iteration is done in ordinary element order.
     */
    Iterator begin(void) noexcept
    {
        return object.begin();
    }

    /**
     * Returns a read-only (constant) iterator that points to the first element
     * in the %forward_list. Iteration is done in ordinary element order.
     */
    const_Iterator begin(void) const noexcept
    {
        return object.begin();
    }

    /**
     * Returns a read/write reversed iterator that points to the last element
     * in the %forward_list. Iteration is not possible due to the nature of
     * the %forward_list.
     */
    Iterator rbegin(void) noexcept
    {
        return object.rbegin();
    }

    /**
     * Returns a read-only (constant) reversed iterator that points to the last 
     * element in the %forward_list. Iteration is not possible due to the nature
     * of the %forward_list.
     */
    const_Iterator rbegin(void) const noexcept
    {
        return object.rbegin();
    }

    /**
     * Returns a read/write iterator that points one past the last element
     * in the %forward_list. Iteration is not possible.
     */
    Iterator end(void) noexcept
    {
        return object.end();
    }

    /**
     * Returns a read-only (constant) iterator that points one past the last element
     * in the %forward_list. Iteration is not possible.
     */
    const_Iterator end(void) const noexcept
    {
        return object.end();
    }

    /**
     * Returns a read/write reference to the first element in non-empty %forward_list.
     */
    reference front(void) noexcept
    {
        return *begin();
    }

    /**
     * Returns a read-only (constant) reference to the first element in non-empty %forward_list.
     */
    const_reference front(void) const noexcept
    {
        return *begin();
    }

    /**
     * Returns a read/write reference to the last element in non-empty %forward_list.
     */
    reference back(void) noexcept
    {
        return *rbegin();
    }

    /**
     * Returns a read-only (constant) reference to the last element in non-empty %forward_list.
     */
    const_reference back(void) const noexcept
    {
        return *rbegin();
    }

    /**
     * @brief  Add data to the end of the %forward_list.
     * @param  __val  Data to be added.
     *
     * This is a typical stack operation.  The function creates an
     * element at the end of the %forward_list. and assigns the given 
     * data to it. Due to the nature of a %forward_list. this operation
     * can be done in constant time, and does not invalidate iterators
     * and references.
     */
    void push_back(const _Tp& __val)
    {
        object.insert_after(object.rbegin(), __val);
    }

    /**
     *
     */
    void push_back(_Tp&& __val)
    {
        object.insert_after(object.rbegin(), __val);
    }

    /**
     * @brief  Add data to the front of the %forward_list.
     * @param  __val  Data to be added.
     *
     * This is a typical stack operation.  The function creates an
     * element at the front of the %forward_list and assigns the given 
     * data to it.  Due to the nature of a %forward_list this operation 
     * can be done in constant time, and does not invalidate iterators 
     * and references.
     */
    void push_front(const _Tp& __val)
    {
        object.insert_after(object.before_begin(), __val);
    }

    /**
     *
     */
    void push_front(_Tp&& __val)
    {
        object.insert_after(object.before_begin(), __val);
    }

    /**
     * @brief  Removes first element.
     *
     * This is a typical stack operation.  It shrinks the %forward_list
     * by one.  Due to the nature of a %forward_list this operation can 
     * be done in constant time, and only invalidates iterators/references
     * to the element being removed.
     *
     * Note that no data is returned, and if the first element's data
     * is needed, it should be retrieved before pop_front() is
     * called.
     */ 
    void pop_front(void) noexcept
    {
        object.pop_front();
    }

    /**
     * @brief  Removes last element.
     *
     * This is a typical stack operation.  It shrinks the %forward_list
     * by one.  Due to the nature of a %forward_list this kind of operation
     * could be expensive and if it is frequently used the user should consider
     * using std::list. this operation only invalidates iterators/references to 
     * the element being removed.
     *
     * Note that no data is returned, and if the last element's data
     * is needed, it should be retrieved before pop_back() is
     * called.
     */ 
    void pop_back(void) noexcept
    {
        erase_after(before_begin()+=size()-1);
    }

    /**
     * @brief Inserts given value into %forward_list after specified iterator.
     * @param __position Iterator into the %forward_list.
     * @param __val      Data to be inserted.
     * @return Iterator that points to the inserted data.
     * 
     * This function will insert a copy of the given value after the specified location.
     * Due to the nature of a %forward_list this operation can be done in constant time,
     * and does not invalidate iterators and references.
     */
    Iterator insert_after(const Iterator& __position, const _Tp& __val)
    {
        return object.insert_after(__position._M_node, __val);
    }

    /**
     *
     */
    Iterator insert_after(const Iterator& __position, _Tp&& __val)
    {
        return object.insert_after(__position._M_node, __val);
    }

    /**
     *  @brief  Inserts the contents of an initializer_list into
     *          %forward_list after the specified iterator.
     *  @param  __position  Iterator into the %forward_list.
     *  @param  __list      An initializer_list.
     *  @return  Iterator pointing to the last inserted element
     *           or @a __position if @a __list is empty.
     *
     *  This function will insert copies of the data in the
     *  initializer_list @a __list into the %forward_list after 
     *  the location specified by @a __position.
     *
     *  This operation is linear in the number of elements inserted and
     *  does not invalidate iterators and references.
     */
    Iterator insert_after(const Iterator& __position, std::initializer_list<_Tp> __list)
    {
        auto __pos = __position;
        for (auto& __x : __list)
        {
            __pos = insert_after(__pos, __x);
        }
        return __pos;
    }

    /**
     * @brief Removes the element pointed to by the iterator following position.
     * @param __position Iterator pointing before the element to be erased.
     * @return Iterator pointing to the element following the one that was 
     *         erased, or end() if no such element exists.
     * 
     * This function will erase the element pointed to by the iterator following
     * position and thus shorten the %forward_list by one. 
     *  
     * This function only erases the element, and that if the element is itself
     * a pointer, the pointed-to memory is not touched in any way. Managing the 
     * pointer is the user's responsibility.
     */
    Iterator erase_after(const Iterator& __position) noexcept
    {
        return object.erase_after(__position._M_node);
    }

    /**
     * @brief Removes a range of elements.
     * @param __first Iterator pointing before the first element to be erased.
     * @param __last  Iterator pointing to one past the last element to be erased.
     * @return Iterator pointing to the element pointed to by @a last
     *         prior to erasing (or end()).
     * 
     * This function will erase the elements in the range @a [first,last) and 
     * shorten the %forward_list accordingly.
     * Note if the elements themselves are pointers, the pointed-to memory is not
     * touched in any way. Managing the pointer is the user's responsibility.
     */
    Iterator erase_after(const Iterator& __before, const Iterator& __last) noexcept
    {
        return object.erase_after(__before._M_node, __last._M_node);
    }

    /**
     *  @brief  Insert contents of another %forward_list.
     *  @param  __position  Iterator referencing the element to insert after.
     *  @param  __list      Source list.
     *
     *  The elements of @a list are inserted in constant time after
     *  the element referenced by @a position.  @a list becomes an empty
     *  list.
     */
    void splice_after(const Iterator& __position, _Self&& __list) noexcept
    {
        object.splice_after(__position._M_node, __list.object);
    }

    void splice_after(const Iterator& __position, _Self& __list) noexcept
    {
        splice_after(__position, std::move(__list));
    }

    /**
     *  @brief  Insert element from another %forward_list.
     *  @param  __position  Iterator referencing the element to insert after.
     *  @param  __list      Source list.
     *  @param  __i         Iterator referencing the element before the element
     *                      to move.
     *
     *  Removes the element after the element referenced by @a i in @a list 
     *  and inserts it into the current list after @a position.
     */
    void splice_after(const Iterator& __position, _Self&& __list, const Iterator& __i) noexcept
    {
        object.splice_after(__position._M_node, __list.object, __i._M_node);
    }

    void splice_after(const Iterator& __position, _Self& __list, const Iterator& __i) noexcept
    {
        splice_after(__position._M_node, std::move(__list), __i._M_node);
    }

    /**
     *  @brief  Insert range from another %forward_list.
     *  @param  __position  Iterator referencing the element to insert after.
     *  @param  __list      Source list.
     *  @param  __before    Iterator referencing before the start of range
     *                      in list.
     *  @param  __last      Iterator referencing the end of range in list.
     *
     *  Removes elements in the range (__before,__last) in @a list and inserts
     *  them after @a __position in constant time.
     */
    void splice_after(const Iterator& __position, _Self&& __list, const Iterator& __before,
                                                                 const Iterator& __last) noexcept
    {
        object.splice_after(__position._M_node, __list.object, __before._M_node, __last._M_node);
    }

    void splice_after(const Iterator& __position, _Self& __list, const Iterator& __before,
                                                                 const Iterator& __last) noexcept
    {
        splice_after(__position._M_node, std::move(__list), __before._M_node, __last._M_node);
    }

    /**
     * @brief  Returns true if the %forward_list is empty.
     */ 
    bool empty(void) noexcept
    {
        return object.empty();
    }

    /**
     * @brief  Returns true if the %forward_list is empty.
     */ 
    bool empty(void) const noexcept
    {
        return object.empty();
    }

    /**
     * @brief  Returns the number of elements in the %forward_list.
     */ 
    std::size_t size(void) noexcept
    {
        return object.size();
    }

    /**
     * @brief  Returns the number of elements in the %forward_list.
     */ 
    std::size_t size(void) const noexcept
    {
        return object.size();
    }

    /**
     * @brief Sorts the %forward_list.
     * 
     * This function sorts the %forward_list. Equivalent elements
     * remain in list order. 
    */
    void sort(void) noexcept
    {
        object.sort();
    }

    /**
     * @brief Removes all elements equal to value.
     * @param __val The value to remove.
     * 
     * Removes every element in the list equal to value. Remaining 
     * elements stay in list order. 
     * 
     * Note that this function only erases the elements, and that if
     * the elements themselves are pointers, the pointed-to memory is
     * not touched in any way.
     */
    void remove(const _Tp& __val) noexcept
    {
        object.remove(__val);
    }

    /**
     *  @brief  Remove all elements satisfying a predicate.
     *  @param  __pred  Unary predicate function.
     *
     *  Removes every element in the %forward_list for which the 
     *  predicate returns true.  Remaining elements stay in list order.
     *  Note that this function only erases the elements, and that if 
     *  the elements themselves are pointers, the pointed-to memory is
     *  not touched in any way.  Managing the pointer is the user's
     *  responsibility.
     */
    void remove_if(bool (*__pred)(const _Tp& __val)) noexcept
    {
        object.remove_if(__pred);
    }

    /**
     * @brief Removes consecutive duplicate elements.
     * 
     * Removes consecutive duplicate elements. For each consecutive set
     * of elements with the same value, removes all but one element.
     * Remaining elements stay in list order.
     * 
     * Note that this function only erases the elements, and that if the 
     * elements themselves are pointers, the pointed-to memory is not 
     * touched in any way. Managing the pointer is the user's responsibility.
    */
    void unique(void) noexcept
    {
        object.unique();
    }

    /**
     * @brief  Reverse the elements in %forward_list.
     * 
     * This function Reverses the order of elements in the %forward_list.
     * in linear time.
     */
    void reverse(void) noexcept
    {
        object.reverse();
    }

    /**
     * @brief Resizes the %forward_list to the specified number of elements.
     * @param __n Number of elements the %forward_list should contain.
     * 
     * This function will %resize the %forward_list to the specified number
     * of elements.  If the number is smaller than the %forward_list's current
     * number of elements the %forward_list is truncated, otherwise the %forward_list
     * is extended and the new elements are default constructed.
     */
    void resize(std::size_t __n)
    {
        object.resize(__n);
    }

    /**
     * @brief Resizes the %forward_list to the specified number of elements.
     * @param __n   Number of elements the %forward_list should contain.
     * @param __val Data with which new elements should be populated.
     * 
     * This function will %resize the %forward_list to the specified number of 
     * elements. If the number is smaller than the %forward_list's current number
     * of elements the %forward_list is truncated, otherwise the %forward_list is
     * extended and new elements are populated with given data.
     */
    void resize(std::size_t __n, const _Tp& __val)
    {
        object.resize(__n, __val);
    }

    /**
     * @brief Erases all elements.
     * 
     * This function Only erases the %forward_list elements, Note
     * that if the elements themselves are pointers, the pointed-to 
     * memory is not touched in any way. Managing the pointer is the 
     * user's responsibility.
     */
    void clear(void) noexcept
    {
        object.clear();
    }

    /**
     * @brief Swaps data with another %forward_list.
     * @param  __list  A %forward_list of the same element type.
     * 
     * This exchanges the elements between two lists in constant
     * time.
     */ 
    void swap(forward_list<_Tp>& __list) noexcept
    {
        object.swap(__list.object);
    }
};

#endif
