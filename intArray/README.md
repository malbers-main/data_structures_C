# intArray
Implementation of an integer array in C which fulfills the following requirements:

 - [X] Implement a vector (mutable array with automatic resizing):
    - [X] New raw data array with allocated memory
            - can allocate int array under the hood, just not use its features
            - start with 16, or if the starting number is greater, use power of 2 - 16, 32, 64, 128
        - [X] size() - number of items
        - [X] capacity() - number of items it can hold
        - [X] is_empty()
        - [X] at(index) - returns the item at a given index, blows up if index out of bounds
        - [X] push(item)
        - [X] insert(index, item) - inserts item at index, shifts that index's value and trailing elements to the right
        - [X] prepend(item) - can use insert above at index 0
        - [X] pop() - remove from end, return value
        - [X] delete(index) - delete item at index, shifting all trailing elements left
        - [X] remove(item) - looks for value and removes index holding it (even if in multiple places)
        - [X] find(item) - looks for value and returns first index with that value, -1 if not found
        - [X] resize(new_capacity) // private function
            - when you reach capacity, resize to double the size
            - when popping an item, if the size is 1/4 of capacity, resize to half
    - [X] Time
        - O(1) to add/remove at end (amortized for allocations for more space), index, or update
        - O(n) to insert/remove elsewhere
    - [X] Space
        - contiguous in memory, so proximity helps performance
        - space needed = (array capacity, which is >= n) * size of item, but even if 2n, still O(n)
