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
 *    Stephen Costigan, Alexander Dohms, Jonathan Colwell, Shaun Crook
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
        // Constructors
        //
        // Jon
        priority_queue() {container.resize(0); }
        priority_queue(const priority_queue& rhs) { *this = rhs;  }                                      // throw (const char*); Copy Constructor
        priority_queue(priority_queue&& rhs) { this->container = std::move(rhs.container); }                                 // throw (const char*); Move Constructor
        template <class Iterator>
        priority_queue(Iterator first, Iterator last)                                                    // Range Constructor
        {
            container.reserve(last - first);
            for (auto element = first; element != last; ++element)
                push(*element);
        }
        explicit priority_queue(custom::vector<T>&& rhs) { container = rhs; }                 // Explicit Move Constructor
        explicit priority_queue(custom::vector<T>& rhs) {this->container = rhs;}//container = std::move(rhs); }                             // Explicit Copy Constructor
        ~priority_queue() { container.clear(); }                                                         // Deconstructor

        //
        // Overloads for  our copy constructor | Alexander
        // Copy Overload
        priority_queue& operator = (const priority_queue& rhs)
        {
           container = std::move(rhs.container);
           return *this;
        }
        // Move Overload
        priority_queue& operator = (priority_queue&& rhs)
        {
           container = std::move(rhs.container);
           return *this;
        }

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
        void swap(T posOne, T posTwo)
        {
            auto temp = posOne;
            posOne = posTwo;
            posTwo = temp;
        }
        //
        // Status
        //
        size_t size()  const
        {
            return container.size();
        }
        bool empty() const
        {
            return (size() == size_t(0));//container.empty();
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
        
        if (size() > 0)
            r = container[0];
        else throw "std:out_of_range";
        return r;
    }

    /**********************************************
     * P QUEUE :: POP
     * Delete the top item from the heap.
     **********************************************/
    template <class T>
    void priority_queue <T> ::pop()
    {
        if (container.size() != 0) {
            std::swap(container.front(), container.back());
            container.pop_back();
            percolateDown(1);
        }
        else
            return;
    }

    /*****************************************
     * P QUEUE :: PUSH
     * Add a new element to the heap, reallocating as necessary
     ****************************************/
    template <class T>
    void priority_queue <T> ::push(const T& t)
    {
        container.push_back(t);
        size_t i = container.size() / 2;
        while (i /*= container.size()/2*/ && percolateDown(i))
            i /= 2;
    }
    template <class T>
    void priority_queue <T> ::push(T&& t)
    {
        container.push_back(t);
        size_t i = container.size() / 2;
        while (i /*= container.size() / 2*/ && percolateDown(i))
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
        auto indexLeft = ((indexHeap-1) * 2)+1;
        auto indexRight = indexLeft + 1;
        bool change = 0;

        if (indexRight <= container.numElements - 1 &&      
            container[indexRight] > container[indexLeft] &&
            container[indexRight] > container[indexHeap-1])            
        {
            std::swap(container[indexHeap-1], container[indexRight]);
            percolateDown(indexRight + 1);
            change = 1;
        }
        else if(indexLeft <= container.numElements - 1 && 
            container[indexLeft] > container[indexHeap-1])
        {
            std::swap(container[indexHeap-1], container[indexLeft]);
            percolateDown(indexLeft + 1);
            change = 1;
        }
        return change;
    }


};

template <class T>
inline void swap(custom::priority_queue <T>& lhs,
   custom::priority_queue <T>& rhs)
{
   lhs.container.swap(rhs.container);
}
