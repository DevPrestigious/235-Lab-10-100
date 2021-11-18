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
        // construct
        //

        // Jon
        priority_queue() {container.resize(0); }
       
        priority_queue(const priority_queue& rhs) { *this = rhs;  }  //throw (const char*);
        
        priority_queue(priority_queue&& rhs) { *this = std::move(rhs); }      //throw (const char*);

        //Our range constructor. Needs work.
        /*priority_queue(priority_queue first, priority_queue last)
        priority_queue() //: numCapacity(0), numElements(0), data(NULL)
        {
           container.reserve(first - last);
           for (siz i = 0; i < length; i++)
           {

           }
        }*/
        
        //Overloads for  our copy constructor | Alexander
        priority_queue& operator = (const priority_queue& rhs)
        {
           container = std::move(rhs.container);
           return *this;
        }

        //Overloads for our move constructor | Alexander
        priority_queue& operator = (priority_queue&& rhs)
        {
           container = std::move(rhs.container);
           return *this;
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

        inline void swap(custom::priority_queue <T>& lhs,
           custom::priority_queue <T>& rhs);

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
        //priority_queue.pop()
        //    swap(array[1], array[size()])
        //    array.pop_back()
        //    percolateDown(1)
        //swap(container[1], container[size()]); //if in include this it breaks
        container.pop_back();
        percolateDown(1);

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
        //priority_queue.percolateDown(index)
        //    Find the left childand the right child of index
        //    indexLeft = index x 2
        //    indexRight = indexLeft + 1
        //    If the right child is greater than the parent, then swapand go from there
        //    IF(indexRight =< num and
        //        container[indexRight] > container[indexLeft] and
        //        container[indexRight] > container[index]
        //      swap(index, indexRight)
        //      percolateDown(indexRight)
        //    If the left child is greater than the parent, then swap it
        //    ELSE IF array[indexLeft] > container[index]
        //        swap(index, indexLeft)
        //        percolateDown(indexLeft)
        auto indexLeft = indexHeap * 2;
        auto indexRight = indexLeft + 1;
        auto index = 1; //not sure what this is suppose to be
        
        if (indexRight <= container.numElements &&      
            container[indexRight] > container[indexLeft] &&
            container[indexRight] > container[indexHeap])            
        {
            //swap(index, indexRight); //if in include this it breaks
            percolateDown(indexRight);
        }
        else if (container[indexLeft] > container[indexHeap])
        {
            swap(index, indexLeft);//if in include this it breaks
            percolateDown(indexLeft);
        }
        return false;
    }




};

template <class T>
inline void swap(custom::priority_queue <T>& lhs,
   custom::priority_queue <T>& rhs)
{
   //I'm pretty sure we need a swap function similar to this. | Alexander
   auto tempdata = std::move(rhs.container);
   rhs.container = std::move(lhs.container);
   lhs.container = std::move(tempdata);

}
