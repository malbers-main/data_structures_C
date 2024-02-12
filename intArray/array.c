#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ARRAY_ERROR -9999

// Array structure definition
typedef struct {
    int *array;
    size_t size;
    size_t capacity;
} Array;

// Function to initialize array with specific capacity
Array *createArray(size_t capacity) {
    Array *arr = malloc(sizeof(Array));
    if (arr == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for Array structure.\n");
        return NULL;
    }
    arr->array = malloc(capacity * sizeof(int));
    if (arr->array == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for array data.\n");
        free(arr);
        return NULL;
    }
    arr->size = 0;
    arr->capacity = capacity;
    return arr;
}

// Function to double the capacity of the array
void resize(Array *arr, size_t newCapacity) {
    if (arr == NULL) {
        fprintf(stderr, "Error: Cannot resize array because it is not allocated.\n");
        return;
    }
    int *newArray = realloc(arr->array, newCapacity * sizeof(int));
    if (newArray == NULL) {
        fprintf(stderr, "Error: Memory reallocation failed for array data during resize.\n");
        return;
    }
    arr->array = newArray;
    arr->capacity = newCapacity;
}

// Return current sizeo f array
size_t getSize(const Array *arr) {
    return (arr != NULL) ? arr->size : 0;
}

// Return current capacity of array
size_t getCapacity(const Array *arr) {
    return (arr != NULL) ? arr->capacity : 0;
}

// True if empty, false if not
bool isEmpty(const Array *arr) {
    return (arr == NULL || arr->size == 0);
}

// Returns element at specified index
int itemAt(const Array *arr, int index) {
    if (arr == NULL || index < 0 || index >= arr->size) {
        fprintf(stderr, "Error: Index out of bounds or array is not allocated.\n");
        return ARRAY_ERROR;
    }
    return arr->array[index];
}

// Pushes element to the tail of the array
bool push(Array *arr, int element) {
    if (arr == NULL) {
        fprintf(stderr, "Error: Cannot push element because the array is not allocated.\n");
        return false;
    }
    // Check if the array is full and resize if necessary
    if (arr->size == arr->capacity) {
        size_t newCapacity = (arr->capacity == 0) ? 1 : arr->capacity * 2; // Double the capacity
        resize(arr, newCapacity);
    }
    arr->array[arr->size++] = element;
    return true;
}

// Inserts element at specified index, filling in leading indices with 0's if not occupied
bool insert(Array *arr, int element, int index) {
    if (arr == NULL) {
        fprintf(stderr, "Error: Cannot insert element because the array is not allocated.\n");
        return false;
    }
    if (index < 0) {
        fprintf(stderr, "Error: Cannot insert element because the index is out of bounds.\n");
        return false;
    }
    // Check if the array is full and resize if necessary
    if (arr->size == arr->capacity) {
        size_t newCapacity = (arr->capacity == 0) ? 1 : arr->capacity * 2; // Double the capacity
        resize(arr, newCapacity);
    }
    if (index >= arr->size) {
        // If index is greater than or equal to current size, fill empty slots with default value
        for (int i = arr->size; i < index; i++) {
            arr->array[i] = 0; // Fill with default value (0)
        }
        arr->array[index] = element;
        arr->size = index + 1; // Update size
    } else {
        // Shift elements to the right to make space for the new element
        for (int i = arr->size; i > index; i--) {
            arr->array[i] = arr->array[i - 1];
        }
        arr->array[index] = element;
        arr->size++;
    }
    return true;
}

// Adds element to the head of the array
bool prepend(Array *arr, int element) {
    return insert(arr, element, 0);
}

// Removes and returns element at the tail of the array
int pop(Array *arr) {
    if (arr == NULL || arr->size == 0) {
        fprintf(stderr, "Error: Cannot pop element because the array is empty or not allocated.\n");
        return ARRAY_ERROR;
    }
    return arr->array[--arr->size];
}

// Removes element at specified index and shifts trailing elements to the left
bool delete(Array *arr, int index) {
    if (arr == NULL || index < 0 || index >= arr->size) {
        fprintf(stderr, "Error: Cannot delete element because the index is out of bounds or array is not allocated.\n");
        return false;
    }
    for (int i = index; i < arr->size - 1; i++) {
        arr->array[i] = arr->array[i + 1];
    }
    arr->size--;
    return true;
}

// Returns index of the first occurence of the specified element
int find(Array *arr, int element) {
    // If the array is uninitialized or the size is zero return error code
    if (arr == NULL) {
        fprintf(stderr, "Error: Cannot find element index because the array is unitialized.\n");
        return ARRAY_ERROR;
    }
    if (arr->size == 0) {
        fprintf(stderr, "Error: Cannot find element index because the array is empty.\n");
        return ARRAY_ERROR;
    }
    // Linear search through elements to find specified value, return index
    for (int i = 0; i < arr->size; i++) {
        if (arr->array[i] == element) {
            return i;
        }
    }
    // Element not found, return -1
    fprintf(stderr, "Error: Cannot find element in array.\n");
    return -1;
}

// Deletes all occurences of specified element 
bool removeElement(Array *arr, int element) {
    bool elementRemoved = false;
    int removeIndex;

    if (arr == NULL) {
        fprintf(stderr, "Error: Cannot remove element because the array is not allocated.\n");
        return false;
    }
    if (arr->size == 0) {
        fprintf(stderr, "Error: Cannot remove element because array is empty.\n");
        return false;
    }
    while (find(arr, element) != -1) {
        removeIndex = find(arr, element);
        delete(arr, removeIndex);
        elementRemoved = true;
    }
    if (elementRemoved == true) {
        return true;
    } else {
        fprintf(stderr, "Error: No elements of specified value were found.\n");
        return false;
    }
}

int main() {
    // Define variables for user input
    int choice;
    int element, index, foundIndex;
    size_t capacity;
    Array *arr = NULL; // Initialize array pointer

    while (1) {
        // Print menu options
        printf("\nArray Operations Menu:\n");
        printf("1. Create a new array\n");
        printf("2. Push element\n");
        printf("3. Insert element at index\n");
        printf("4. Prepend element\n");
        printf("5. Pop element\n");
        printf("6. Delete element at index\n");
        printf("7. Find element\n");
        printf("8. Display array information\n");
        printf("9. Remove element\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        printf("\n");

        // Perform operation based on user choice
        switch (choice) {
            case 1:
                printf("Enter the capacity of the array: ");
                scanf("%zu", &capacity);
                arr = createArray(capacity);
                if (arr == NULL) {
                    printf("Failed to create array.\n");
                } else {
                    printf("Array created successfully with capacity %zu.\n", getCapacity(arr));
                }
                break;
            case 2:
                printf("Enter the element to push: ");
                scanf("%d", &element);
                if (!push(arr, element)) {
                    printf("Failed to push element to array.\n");
                } else {
                    printf("Element %d pushed to array.\n", element);
                }
                break;
            case 3:
                printf("Enter the element to insert: ");
                scanf("%d", &element);
                printf("Enter the index to insert at: ");
                scanf("%d", &index);
                if (!insert(arr, element, index)) {
                    printf("Failed to insert element at index %d.\n", index);
                } else {
                    printf("Element %d inserted at index %d.\n", element, index);
                }
                break;
            case 4:
                printf("Enter the element to prepend: ");
                scanf("%d", &element);
                if (!prepend(arr, element)) {
                    printf("Failed to prepend element to array.\n");
                } else {
                    printf("Element %d prepended to array.\n", element);
                }
                break;
            case 5:
                element = pop(arr);
                if (element != ARRAY_ERROR) {
                    printf("Popped element: %d\n", element);
                } else {
                    printf("Failed to pop element.\n");
                }
                break;
            case 6:
                printf("Enter the index to delete: ");
                scanf("%d", &index);
                if (!delete(arr, index)) {
                    printf("Failed to delete element at index %d.\n", index);
                } else {
                    printf("Element at index %d deleted.\n", index);
                }
                break;
            case 7:
                printf("Enter the element to find: ");
                scanf("%d", &element);
                foundIndex = find(arr, element);
                if (foundIndex != ARRAY_ERROR) {
                    printf("Element %d found at index %d.\n", element, foundIndex);
                } else {
                    printf("Element %d not found in array.\n", element);
                }
                break;
            case 8:
                if (arr != NULL) {
                    printf("Array Information:\n");
                    printf("Size: %zu\n", getSize(arr));
                    printf("Capacity: %zu\n", getCapacity(arr));
                    printf("Contents: ");
                    printf("[");
                    for (size_t i = 0; i < getSize(arr) - 1; i++) {
                        printf("%d ", *(arr->array + i));
                        printf(",");
                    }
                    printf("%d", *(arr->array + getSize(arr) - 1));
                    printf("]");
                    printf("\n");
                } else {
                    printf("Array is not initialized.\n");
                }
                break;
            case 9:
                printf("Enter the element to remove: ");
                scanf("%d", &element);
                if (removeElement(arr, element) == true) {
                    printf("Element %d was removed from the array.\n", element);
                } else {
                    printf("Element %d not found in array.\n", element);
                }
                break;
            case 0:
                printf("Exiting program.\n");
                // Free allocated memory before exiting
                if (arr != NULL) {
                    free(arr->array);
                    free(arr);
                }
                return 0;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
                break;
        }
    }

    return 0;
}

