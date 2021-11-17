/***********************************************************************
 * Header:
 *    PRIORITY QUEUE
 * Summary:
 *    Our custom implementation of std::priority_queue
 *      __       ____       ____         __
 *     /  |    .'    '.   .'    '.   _  / /
 *     `| |   |  .--.  | |  .--.  | (_)/ /
 *      | |   | |    | | | |    | |   / / _
 *     _| |_  |  `--'  | |  `--'  |  / / (_)
 *    |_____|  '.____.'   '.____.'  /_/
 *
 *    This will contain the class definition of:
 *        priority_queue          : A class that represents a Priority Queue
 * Author
 *    Stephen Costigan, Alexander Dohms
 ************************************************************************/

#pragma once

#include <cassert>
#include "vector.h"

namespace custom
{

    /*************************************************
     * P QUEUE
     * Create a priority queue.
     *************************************************/
    template<class T>
    class priority_queue
    {
    public:

        //
        // construct
        //

        // Jon
        priority_queue()
        {
        }
        priority_queue(const priority_queue& rhs)
        {
        }
        priority_queue(priority_queue&& rhs)
        {
        }

        // Steve
        template <class Iterator>
        priority_queue(Iterator first, Iterator last)
        {
            for (auto c = first; c != last; c++)
                push(*c);
        }
        explicit priority_queue(custom::vector<T>&& rhs) { container = std::move(rhs); }
        explicit priority_queue(custom::vector<T>& rhs) { container = rhs; }
        ~priority_queue() { container.clear(); }

        //
        // Access
        //
        const T& top() const;

        //
        // Insert
        //
        void  push(const T& t);
        void  push(T&& t);

        //
        // Remove -- Shaun
        //
        void  pop();

        //
        // Status
        //
        size_t size()  const
        {
            return container.size();
        }
        bool empty() const
        {
            return container.empty();
        }

#ifdef DEBUG // make this visible to the unit tests
    public:
#else
    private:
#endif

        bool percolateDown(size_t indexHeap);      // fix heap from index down. This is a heap index!

        custom::vector<T> container;

    };

    /************************************************
     * P QUEUE :: TOP
     * Get the maximum item from the heap: the top item.
     ***********************************************/
    template <class T>
    const T& priority_queue <T> ::top() const
    {
        T r;
        try {
            r = container.front();
        }
        catch (std::out_of_range& e) {
            std::cout << e.what();
        }
        return r;
    }

    /**********************************************
     * P QUEUE :: POP
     * Delete the top item from the heap.
     **********************************************/
    template <class T>
    void priority_queue <T> ::pop()
    {
    }

    /*****************************************
     * P QUEUE :: PUSH
     * Add a new element to the heap, reallocating as necessary
     ****************************************/
    template <class T>
    void priority_queue <T> ::push(const T& t)
    {
        container.push_back(t);
        size_t i = size() / 2;
        while (i = size()/2 && percolateDown(i))
            i /= 2;
    }
    template <class T>
    void priority_queue <T> ::push(T&& t)
    {
        container.push_back(t);
        size_t i = size() / 2;
        while (i = size() / 2 && percolateDown(i))
            i /= 2;
    }

    /************************************************
     * P QUEUE :: PERCOLATE DOWN
     * The item at the passed index may be out of heap
     * order. Take care of that little detail!
     * Return TRUE if anything changed.
     ************************************************/
    template <class T>
    bool priority_queue <T> ::percolateDown(size_t indexHeap)
    {
        return false;
    }

};

template <class T>
inline void swap(custom::priority_queue <T>& lhs,
    custom::priority_queue <T>& rhs)
{
}
