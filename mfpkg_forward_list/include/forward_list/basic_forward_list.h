/** 
 * @file basic_forward_list.h
 *  This is an internal header file, included by forward_list.h
 *  Do not attempt to use it directly.
 */

#ifndef BASIC_FORWARD_LIST_H
#define BASIC_FORWARD_LIST_H

class basic_mfpkg::basic_forward_list
{
protected:

    struct node_base
    {
        struct node_base *link;
    };

    template <typename _Tp>
    struct node : node_base
    {
        _Tp storage;
    };

public:

    template <typename _Tp>
    struct iterator
    {
        typedef iterator<_Tp> _Self;
        typedef _Tp& reference;
        typedef node<_Tp>* pointer;

        public:

        node_base* _M_node;

        iterator() noexcept : _M_node(nullptr) {}

        iterator(node_base* __n) noexcept : _M_node(__n) {}

        iterator(_Self& __it) noexcept : _M_node(__it._M_node) {}

        iterator(const _Self& __it) noexcept : _M_node(__it._M_node) {}

        ~iterator() {}

        reference operator*() const noexcept
        {
            return static_cast<node<_Tp>*>(_M_node)->storage;
        }

        pointer operator->() const noexcept
        {
            return static_cast<node<_Tp>*>(_M_node);
        }

        _Self& operator++() noexcept
        {
            if(_M_node)
            {
                _M_node = _M_node->link;
            }
            return *this;
        }

        _Self operator++(int) noexcept
        {
            _Self __tmp(*this);
            if(_M_node)
            {
                _M_node = _M_node->link;
            }
            return __tmp;
        }

        _Self& operator+= (std::size_t __n) noexcept
        {
            for(; __n; --__n)
            {
                if(_M_node)
                {
                    _M_node = _M_node->link;
                }
                else
                {
                    break;
                }
            }
            return *this;
        }

        _Self& operator= (const _Self& __it) noexcept
        {
            _M_node = __it._M_node;
            return *this;
        }

        private:

        friend bool operator==(const _Self& __x, const _Self& __y) noexcept
        {
            return __x._M_node == __y._M_node;
        }
        
        friend bool operator!=(const _Self& __x, const _Self& __y) noexcept
        {
            return __x._M_node != __y._M_node;
        }

        public:

        _Self next(void) noexcept
        {
            if(_M_node)
            {
                return _M_node->link;
            }
            else
            {
                return _M_node;
            }
        }
    };

    template <typename _Tp>
    struct const_iterator
    {
        typedef const_iterator<_Tp> _Self;
        typedef iterator<_Tp> Iterator;
        typedef const _Tp& reference;
        typedef const node<_Tp>* pointer;

        public:

        const node_base* _M_node;

        const_iterator() noexcept : _M_node(nullptr) {}

        const_iterator(const node_base* __n) noexcept : _M_node(__n) {}

        const_iterator(const Iterator& __it) noexcept : _M_node(__it._M_node) {}

        const_iterator(const _Self& __it) noexcept : _M_node(__it._M_node) {}

        ~const_iterator() {}

        reference operator*() const noexcept
        {
            return static_cast<const node<_Tp>*>(_M_node)->storage;
        }

        pointer operator->() const noexcept
        {
            return static_cast<const node<_Tp>*>(_M_node);
        }

        _Self& operator++() noexcept
        {
            if(_M_node)
            {
                _M_node = _M_node->link;
            }
            return *this;
        }

        _Self operator++(int) noexcept
        {
            _Self __tmp(*this);
            if(_M_node)
            {
                _M_node = _M_node->link;
            }
            return __tmp;
        }

        _Self& operator+= (std::size_t __n) noexcept
        {
            for(; __n; --__n)
            {
                if(_M_node)
                {
                    _M_node = _M_node->link;
                }
                else
                {
                    break;
                }
            }
            return *this;
        }

        _Self& operator= (const _Self& __it) noexcept
        {
            _M_node = __it._M_node;
            return *this;
        }

        private:

        friend bool operator==(const _Self& __x, const _Self& __y) noexcept
        {
            return __x._M_node == __y._M_node;
        }
        
        friend bool operator!=(const _Self& __x, const _Self& __y) noexcept
        {
            return __x._M_node != __y._M_node;
        }

        public:

        _Self next(void) noexcept
        {
            if(_M_node)
            {
                return _M_node->link;
            }
            else
            {
                return _M_node;
            }
        }
    };

protected:

    template <typename _Tp>
    class forward_list
    {
        private:
        typedef forward_list<_Tp> _Self;
        
        node_base start;
        node_base finish;
        std::size_t count;

        node<_Tp>* get_node(const _Tp& __data)
        {
            node<_Tp>* __node = nullptr;
            try 
            {
                __node = new node<_Tp>({nullptr, __data});
            }
            catch (const std::bad_alloc& __a) 
            {
                this->~forward_list();
                std::cout << __a.what() << '\n';
            }
            return __node;
        }

        node<_Tp>* get_node(void)
        {
            node<_Tp>* __node = nullptr;
            try 
            {
                __node = new node<_Tp>();
            }
            catch (const std::bad_alloc& __a) 
            {
                this->~forward_list();
                std::cout << __a.what() << '\n';
            }
            return __node;
        }

        void init_list(node_base* __node)
        {
            __node->link = nullptr;
            start.link = __node;
            finish.link = __node;
        }
        
        void insert_before_begin(node_base* __node)
        {
            __node->link = start.link;
            start.link = __node;
        }

        void insert_after(node_base* __pos, node_base* __node)
        {
            __node->link = __pos->link;
            if(__node->link == nullptr)
            {
                finish.link = __node;
            }
            __pos->link = __node;
        }

        node_base* erase_first_element(void)
        {
            node_base* __temp = start.link;
            start.link = start.link->link;
            if(!start.link)
            {
                finish.link = start.link;
            }
            delete __temp;
            return start.link;
        }

        void erase_last_element(node_base* __pos)
        {
            delete finish.link;
            finish.link = __pos;
            __pos->link = nullptr;
        }

        node_base* erase_next_element(node_base* __pos)
        {
            node_base* __temp = __pos->link;
            __pos->link = __pos->link->link;
            delete __temp;
            return __pos;
        }

        node_base* unlink_node(_Self& __list, node_base* __i)
        {
            node_base* __node = nullptr;
            if(__i->link)
            {
                __node = __i->link;
            }
            else
            {
                return nullptr;
            }
            if(__i == __list.before_begin())
            {
                __list.start.link = __list.start.link->link;
                if(__list.start.link == __list.end())
                {
                    __list.finish.link = __list.start.link;
                }
            }
            else if(__i->link == __list.rbegin())
            {
                __list.finish.link = __i;
                __list.finish.link->link = nullptr;
            }
            else
            {
                if(__i->link)
                {
                    __i->link = __i->link->link;
                }
            }
            --__list.count;
            return __node;
        }

        void splice_node(node_base* __pos, node_base* __node)
        {
            if(!__node)
            {
                return;
            }
            if(start.link == nullptr)
            {
                init_list(__node);
            }
            else if(__pos == before_begin())
            {
                insert_before_begin(__node);
            }
            else
            {
                insert_after(__pos, __node);
            }
            ++count;
        }

        void truncate(node_base* __curr, node_base* __prev)
        {
            node_base* __temp = nullptr;
            for (; __curr != nullptr; --count)
            {
                __temp = __curr;
                __curr = __curr->link;
                delete __temp;
            }
            finish.link = __prev;
            finish.link->link = nullptr;
        }

        void shrink_list(std::size_t __n)
        {
            std::size_t __i = 0;
            node_base* __prev = nullptr;
            for (node_base* __it = begin(); __it != nullptr; 
                            __it = __it->link, ++__i)
            {
                if(__i == __n)
                {
                    truncate(__it, __prev);
                    break;
                }
                __prev = __it;
            }
        }

        void extend_list(std::size_t __n)
        {
            node<_Tp>* __node = nullptr;
            if(empty())
            {
                __node = get_node();
                init_list(__node);
                ++count;
            }
            for (; count < __n; ++count)
            {
                __node = get_node();
                insert_after(rbegin(), __node);
            }
        }

        void swap(node_base& __p1, node_base& __p2)
        {
            auto __tmp = __p1;
            __p1 = __p2;
            __p2 = __tmp;
        }

        void swap(std::size_t& __c)
        {
            auto __tmp = __c;
            __c = this->count;
            this->count = __tmp;
        }

        void reset(void) noexcept
        {
            start.link = nullptr;
            finish.link = nullptr;
            count = 0;
        }

        public:

        explicit forward_list() : start({nullptr}), finish({nullptr}), count(0) {}

        explicit forward_list(node_base* __s, node_base* __f, std::size_t __c) 
        : start({__s}), finish({__f}), count(__c) {}
        
        ~forward_list() noexcept
        {
            clear();
        }

        void assign(std::initializer_list<_Tp> __list)
        {
            if(!__list.size())
            {
                clear();
                return;
            }
            resize(__list.size());
            auto* __curr = begin();
            for (auto* __it = __list.begin(); __it != __list.end(); ++__it)
            {
                static_cast<node<_Tp>*>(__curr)->storage = *__it;
                __curr = __curr->link;
            }
        }

        void assign(const _Self& __list)
        {
            if(!__list.empty())
            {
                clear();
                return;
            }
            resize(__list.size());
            auto* __curr = begin();
            for (auto* __it = __list.begin(); __it != nullptr; )
            {
                static_cast<node<_Tp>*>(__curr)->storage = 
                static_cast<node<_Tp>*>(__it)->storage;
                __curr = __curr->link;
                __it = __it->link;
            }            
        }

        void assign(_Self&& __list)
        {
            swap(__list);
        }

        node_base* before_begin(void) noexcept
        {
            return &start;
        }

        node_base* before_begin(void) const noexcept
        {
            return &start;
        }

        node_base* begin(void) noexcept
        {
            return start.link;
        }

        node_base* begin(void) const noexcept
        {
            return start.link;
        }

        node_base* rbegin(void) noexcept
        {
            return finish.link;
        }

        node_base* rbegin(void) const noexcept
        {
            return finish.link;
        }

        node_base* end(void) noexcept
        {
            return nullptr;
        }

        node_base* end(void) const noexcept
        {
            return nullptr;
        }

        node_base* insert_after(node_base* __pos, const _Tp& __data)
        {
            node<_Tp>* __node = get_node(__data);
            if(empty())
            {
                init_list(__node);
            }
            else
            {
                if(__pos == before_begin())
                {
                    insert_before_begin(__node);
                }
                else
                {
                    insert_after(__pos, __node);
                }
            }
            ++count;
            return __node;
        }

        void pop_front(void) noexcept
        {
            if(start.link)
            {
                erase_first_element();
                --count;
            }
        }

        node_base* erase_after(node_base* __pos) noexcept
        {
            if(!__pos || !__pos->link)
            {
                return nullptr;
            }
            node_base* __ret = nullptr;
            if(__pos == before_begin())
            {
                __ret = erase_first_element();
            }
            else if(__pos->link == rbegin())
            {
                erase_last_element(__pos);
            }
            else if(__pos->link->link)
            {
                __ret = erase_next_element(__pos);
            }
            else { }
            --count;
            return __ret;
        }

        node_base* erase_after(node_base* __before, node_base* __last) noexcept
        {
            if(__before == __last)
            {
                return __before;
            }
            if(empty())
            {
                return nullptr;
            }
            auto* __it = __before;
            if(__it == before_begin())
            {
                while (start.link != __last)
                {
                    erase_after(__it);
                }
            }
            else
            {
                while (__it->link != __last)
                {
                    erase_after(__it);
                }
            }
            return __last;
        }

        void splice_after(node_base* __pos, _Self& __list) noexcept
        {
            if(!__pos)
            {
                return;
            }
            if(empty())
            {
                start.link = __list.start.link;
                finish.link = __list.finish.link;
            }
            else if(__pos == before_begin())
            {
                __list.finish.link->link = start.link;
                start.link = __list.start.link;
            }
            else if(__pos == rbegin())
            {
                finish.link->link = __list.start.link;
                finish.link = __list.finish.link;
            }
            else
            {
                __list.finish.link->link = __pos->link;
                __pos->link = __list.start.link;
            }
            count += __list.count;
            __list.reset();
        }

        void splice_after(node_base* __pos, _Self& __list, node_base* __i) noexcept
        {
            if(!__pos || !__i)
            {
                return;
            }
            splice_node(__pos, unlink_node(__list, __i));
        }

        void splice_after(node_base* __pos, _Self& __list, node_base* __before, node_base* __last) noexcept
        {
            if(__list.empty() || !__before || __before == __last || __before->link == __last)
            {
                return;
            }
            node_base* __start = __before->link;
            node_base* __end = __last;
            node_base* __it = __before->link;
            __before->link = __last;
            if(__before->link == nullptr)
            {
                if(__before == __list.before_begin())
                {
                    __list.start.link = __before->link;
                    __list.finish.link = __before->link;
                }
                else
                {
                    __list.finish.link = __before;
                }
            }
            std::size_t __i = 0;
            for (; __it->link != __end; __it = __it->link, ++__i);
            __it->link = nullptr;
            __list.count -= __i+1;
            _Self __temp(__start, __it, 1+__i);
            splice_after(__pos, __temp);
        }

        bool empty(void) noexcept
        {
            return start.link == nullptr;
        }

        bool empty(void) const noexcept
        {
            return start.link == nullptr;
        }

        std::size_t size(void) noexcept
        {
            return count;
        }

        std::size_t size(void) const noexcept
        {
            return count;
        }

        /**
         * I don't own the sort algorithm, You can check it via this link
         * https://www.geeksforgeeks.org/iterative-merge-sort-for-linked-list/
         */
        void sort(void) noexcept
        {
            if (!start.link || !start.link->link)
            {
                return;
            }

            node_base** head = &start.link;
            node_base* start1 = NULL;
            node_base* end1 = NULL;
            node_base* start2 = NULL;
            node_base* end2 = NULL; 
            node_base* prevend = NULL;
            node_base* Temp = NULL;

            node_base* temp = NULL;
            node_base* astart = NULL;
            node_base* aend = NULL;
            node_base* bstart = NULL;
            node_base* bendnext = NULL;

            std::size_t counter = 0;
            int isFirstIter = 0;

            for (std::size_t gap = 1; gap < count; gap = gap * 2) 
            {
                start1 = *head;
                for (; start1;) 
                {
        
                    /* If this is first iteration */
                    isFirstIter = 0;
                    if (start1 == *head)
                    {
                        isFirstIter = 1;
                    }
        
                    /* First part for merging */
                    counter = gap;
                    end1 = start1;
                    for (; --counter && end1->link;)
                    {
                        end1 = end1->link;
                    }
        
                    /* Second part for merging */
                    start2 = end1->link;
                    if (!start2)
                    {
                        break;
                    }
                    
                    counter = gap;
                    end2 = start2;
                    for (; --counter && end2->link;)
                    {
                        end2 = end2->link;
                    }
        
                    /* To store for next iteration. */
                    Temp = end2->link;

                    /* begin merge */

                    if (static_cast<node<_Tp>*>(start1)->storage > 
                        static_cast<node<_Tp>*>(start2)->storage) 
                    {
                        temp = start1;
                        start1 = start2;
                        start2 = temp;

                        temp = end1;
                        end1 = end2;
                        end2 = temp;
                    }

                    astart = start1;
                    aend = end1;
                    bstart = start2;
                    bendnext = end2->link;
                    for (; astart != aend && bstart != bendnext;)
                    {
                        if (static_cast<node<_Tp>*>(astart->link)->storage > 
                            static_cast<node<_Tp>*>(bstart)->storage) 
                        {
                            temp = bstart->link;
                            bstart->link = astart->link;
                            astart->link = bstart;
                            bstart = temp;
                        }
                        astart = astart->link; 
                    }

                    if(astart == aend)
                    {
                        astart->link = bstart;
                    }
                    else
                    {
                        end2 = end1;
                    }

                    /* end merge */
                    
                    /* Update head for first iteration, else append after previous list */
                    if (isFirstIter)
                    {
                        *head = start1;
                    }
                    else
                    {
                        prevend->link = start1;
                    }
        
                    prevend = end2;
                    start1 = Temp;
                }
                prevend->link = start1;
            }
            finish.link = end2;
        }

        void remove(const _Tp& __val) noexcept
        {
            if(!empty())
            {
                for (auto* __it = begin(); __it && __it->link != nullptr; )
                {
                    if(__val == static_cast<node<_Tp>*>(__it->link)->storage)
                    {
                        __it = erase_after(__it);
                    }
                    else
                    {
                        __it = __it->link;
                    }
                }
                if(__val == static_cast<node<_Tp>*>(start.link)->storage)
                {
                    pop_front();
                }
            }
        }

        void remove_if(bool (*__pred)(const _Tp& __val)) noexcept
        {
            if(!empty())
            {
                for (auto* __it = begin(); __it && __it->link != nullptr; )
                {
                    if(__pred(static_cast<node<_Tp>*>(__it->link)->storage))
                    {
                        __it = erase_after(__it);
                    }
                    else
                    {
                        __it = __it->link;
                    }
                }
                if(__pred(static_cast<node<_Tp>*>(start.link)->storage))
                {
                    pop_front();
                }
            }
        }

        void unique(void) noexcept
        {
            if(!start.link || !start.link->link)
            {
                return;
            }
            for (auto* __it = begin(); __it && __it->link != nullptr; )
            {
                if(static_cast<node<_Tp>*>(__it)->storage ==
                   static_cast<node<_Tp>*>(__it->link)->storage)
                {
                    __it = erase_after(__it);
                }
                else
                {
                    __it = __it->link;
                }
            }
        }

        void reverse(void) noexcept
        {
            if(!start.link || !start.link->link)
            {
                return;
            }
            node_base* __current = start.link;
            node_base* __start = start.link;
            node_base* __prev = nullptr;
            node_base* __next = nullptr;
            while (__current)
            {
                __next = __current->link;
                __current->link = __prev;
                __prev = __current;
                __current = __next;
            }
            start.link = __prev;
            finish.link = __start;
        }

        void resize(std::size_t __n)
        {
            if(!__n)
            {
                clear();
                return;
            }
            if(size() == __n)
            {
                return;
            }
            else if(size() > __n)
            {
                shrink_list(__n);
            }
            else
            {
                extend_list(__n);
            }
        }

        void resize(std::size_t __n, const _Tp& __val)
        {
            std::size_t old_size = size();
            auto* old_finish = finish.link;
            resize(__n);
            if(size() <= old_size)
            {
                return;
            }
            for (auto* __it = old_finish ? old_finish->link : begin(); 
                       __it != nullptr; __it = __it->link)
            {
                static_cast<node<_Tp>*>(__it)->storage = __val;
            }   
        }

        void clear(void) noexcept
        {
            if(!empty())
            {
                node_base* __temp = nullptr;
                for (auto* __it = begin(); __it != nullptr; )
                {
                    __temp = __it;
                    __it = __it->link;
                    delete __temp;
                }
                reset();
            }
        }

        void swap(_Self& __list) noexcept
        {
            swap(__list.start, this->start);
            swap(__list.finish, this->finish);
            swap(__list.count);
        }
        
    };
};

#endif
