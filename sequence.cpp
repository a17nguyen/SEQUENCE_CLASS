// file: sequence.cpp
// Andrew Nguyen
// COEN 79 Friday Lab

// This file contains the implementation of the sequence functions 
// which include insert, attach, and remove

#include <math.h>
#include <cassert>
#include <iostream>
#include <cstdlib>
#include "sequence1.h"

using namespace std;
using namespace coen79_lab3;

namespace coen79_lab3{

    sequence::sequence ( )
    {
        current_index = 0;
        used = 0;
    }
    
    // start sequence
    void sequence::start()
    {
        current_index = 0;
    }
    
    void sequence::last()
    {
        current_index = CAPACITY - 1;
    }
    
    void sequence::retreat()
    {
        current_index--;
    }

    
    // advance sequence
    void sequence::advance()
    {
        assert (is_item());
        ++current_index;
    }
    
    // return size of sequence
    sequence::size_type sequence::size() const {
        return used;
    }
    
    // return current item of sequence
    sequence::value_type sequence::current() const {
        assert(is_item());
        return data[current_index];
    }
    
    // check if current item exists
    bool sequence::is_item() const {
        return current_index < used;
    }
    
    // insert entry before current item
    void sequence::insert (const value_type& entry) {
        assert(size() < CAPACITY);
        size_type i;
        if (current_index < used) {
            for (i = used; i > current_index; i--) {
                data[i] = data[i-1];
            }
        }
        data[current_index] = entry;
        ++used;
    }
    
    // insert at front of sequence
    void sequence::insert_front (const value_type& entry) {
        assert(size() < CAPACITY);
        size_type i;
        if (current_index < used) {
            for (i = used; i > 0; --i){
                data[i] = data[i-1];
            }
        }
        data[0] = entry;
        current_index = 0;
        ++used;
    }
    
    // remove first entry
    void sequence::remove_front() {
        size_type i;
        assert(is_item());
        if (used == 1) {
            used--;
        }
        else {
            for (i = 0; i < used; i++) {
                data[i] = data[i+1];
            }
            --used;
        }
    }
    
    // insert at end of sequence
    void sequence::attach_back (const value_type& entry) {
        size_type i;
        assert(size() < CAPACITY);
        if (is_item() == 1)
            current_index = used - 1;
        for (i = used; i > current_index + 1; --i)
            data[i] = data[i-1];
        ++current_index;
        data[current_index] = entry;
        ++used;
    }
    
    // make last item the current item
    void sequence::end() {
        current_index = used-1;
    }
    
    // remove current entry
    void sequence::remove_current() {
        size_type i;
        assert(is_item());
        for (i = current_index; i < used; i++) {
            data[i] = data[i+1];
        }
        --used;
    }
    
    // insert after current entry
    void sequence::attach (const value_type& entry) {
        assert(size() < CAPACITY);
        size_type i;
        if (current_index < used) {
            for (i = used; i > current_index + 1; i--) {
                data[i] = data[i-1];
            }
        }
        current_index = current_index + 1;
        data[current_index] = entry;
        ++used;
    }
    sequence::value_type sequence::mean() const
    {
        double x;
        double avg;
        for(size_type i = 0; i < used; i++){
            x += data[i];
        }
        avg = x / used;
        return avg;
    }
    sequence::value_type sequence::standardDeviation() const{
        double std;
        double x=0;
        for(size_type i = 0; i < used; i++){
            x+= pow((data[i] - mean()), 2);
        }
        x= sqrt(x/(used-1));
        return x;
    }
    // overload + operator
    sequence operator +(const sequence& lhs, const sequence& rhs)
    {
        sequence total;
	total.start();
	sequence left = lhs;
	sequence right = rhs;
	for(sequence::size_type i = 0; i < left.size(); left.advance())
		total.insert(left.current());
        for(sequence::size_type i = 0; i < right.size(); right.advance())
		total.attach_back(right.current());
	return total;
    }
    
    // overload += operator
    sequence operator +=(sequence& lhs, const sequence& rhs)
    {
	sequence left = lhs;
	sequence right = rhs;
	for(sequence::size_type i = 0; i < right.size(); right.advance())
		left.attach_back(right.current());
	return left;
    }
    
    sequence::value_type summation(const sequence &s){
        sequence::value_type sum;
        for(sequence::size_type index = 0; index < s.size(); index++){
            sum += s.current();
        }
        return sum;
    }
    sequence::value_type sequence::operator [] (size_type index) const
    {
        assert(index < size());
        return data[index];
    }

}
