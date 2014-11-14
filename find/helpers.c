/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // test for positve, non-zero integer
    while (n <= 0)
    {   
        // return false if input not positive, non-zero integer
        return false;
    }   
    
    // set bound variables   
    int begin = 0;
    int end = n - 1;
    
    // while length of list > 0
    while (end >= begin)
    {
        // look at middle of list
        int middle = (begin + end) / 2;
        if (values[middle] == value)
        {   
            // if number found, return true
            return true;
        }
        // else if number in middle is greater, search to the left
        else if (values[middle] > value)
        {
            end = middle - 1;
        }
        // else if number in middle is less, search to the right
        else
        {
            begin = middle + 1;
        }
    }
    // return false
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // while the list is out of order
    for (int i = 0; i < n; i++)
    {   
    	// declare and initialize variables for smallest value and location
        int smallest = values[i];
        int smallest_location = i;
                
        // loop through the entire list
        for (int j = i + 1; j < n; j++)
        {    
            // search for smallest number and smallest number location   
            if (smallest > values[j])
            {
                smallest = values[j];
                smallest_location = j;
            }
        }
        
        // reset beginning of the list to where the smallest number was
        values[smallest_location] = values[i];
        
        // place smallest number in the beginning of the list
        values[i] = smallest;
    }
    return;
}
