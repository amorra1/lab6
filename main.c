#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct heap_element {
    int priority; // Lower priority means higher priority in the heap.
    const char *data; // This is just an example; the heap doesn't care what the data is.
};

struct heap {
    struct heap_element *data; // Array of heap elements.
    size_t capacity, length; // Capacity is the number of elements allocated; length is the number of elements in use.
};

// Computes the index of the left child, given the parent index.
size_t left_child_of(size_t index) {
    return 3 * index + 1; //changed to 3
}

size_t middle_child_of(size_t index) {
    return 3 * index + 2; //changed to 3
}

// Computes the index of the right child, given the parent index.
size_t right_child_of(size_t index) {
    return 3 * index + 3; //changed to 3
}

// Computes the index of the parent, given a child index.
size_t parent_of(size_t index) {
    return (index - 1) / 3; //changed to 3
}

// Swap two heap elements.
void heap_swap(struct heap_element *a, struct heap_element *b) {
    struct heap_element temp = *a;
    *a = *b;
    *b = temp;
}

// Move the element at the given index up the heap until it is in the correct position.
// All ancestors of the given element must be correctly ordered; descendants of the element are ignored.
void heap_up(struct heap *h, size_t index) {
    // Loop until we reach the root element.
    while (index > 0) {
        size_t parent = parent_of(index);

        // If the element is correctly ordered with respect to its parent, then it is in the correct position.
        if (h->data[parent].priority <= h->data[index].priority) //YOUC HANGES THIS TO <= NOT =>
            break;

        // If it is incorrectly ordered, swap with its parent then continue.
        heap_swap(&h->data[index], &h->data[parent]);
        index = parent;
    }
}

// Move the element at the given index down the heap until it is in the correct position.
// All descendants of the given element must be correctly ordered; ancestors of the element are ignored.
void heap_down(struct heap *h, size_t index) {
    while (true) {
        // If the left child does not exist, then neither does the right, so exit.
        size_t left_child = left_child_of(index);
        if (left_child >= h->length)
            break;

        // If the middle child doesn't exist, or if the left child is lower priority, then only look at the left child.
        size_t middle_child = middle_child_of(index);
        size_t right_child = right_child_of(index);
       
         size_t min_child = left_child; // Assume left is the minimum.

        // Check if middle child exists and has lower priority.
        if (middle_child < h->length && h->data[middle_child].priority < h->data[min_child].priority) {
            min_child = middle_child;
        }

        // Check if right child exists and has lower priority.
        if (right_child < h->length && h->data[right_child].priority < h->data[min_child].priority) {
            min_child = right_child;
        }

        // If the element is incorrectly ordered with respect to the minimum child, then swap and continue.
        if (h->data[index].priority > h->data[min_child].priority) {
            heap_swap(&h->data[index], &h->data[min_child]);
            index = min_child;
        } else
            break;
    }
}

void heap_insert(struct heap *h, int priority, const char *data) {
    // Allocate or re-allocate as needed.
    if (h->capacity == 0) {
        h->capacity = 1;
        h->data = malloc(sizeof(struct heap_element));
    } else if (h->length == h->capacity) {
        h->capacity *= 2;
        h->data = realloc(h->data, h->capacity * sizeof(struct heap_element));
    }

    // Set up new element.
    struct heap_element el = {
            .priority = priority,
            .data = data, //changed data to .data
    };

    // Insert new element at bottom of heap, then heap-up to correctly place it.
    size_t index = h->length++;
    h->data[index] = el;
    heap_up(h, index);
}

bool heap_remove(struct heap *h, int *priority_out, const char **data_out) {
    // Check if the heap is empty.
    if (h->length == 0)
        return false;

    // Extract root element.
    *priority_out = h->data[0].priority;
    *data_out = h->data[0].data;

    // Move last element to root, then heap-down to correctly place it.
    h->data[0] = h->data[--h->length];
    heap_down(h, 0);

    // Shrink allocation if applicable.
    if (h->length == 0) {
        h->capacity = 0;
        free(h->data);
        h->data = NULL;
    } else if (h->length * 2 < h->capacity) {
        h->capacity /= 2;
        h->data = realloc(h->data, h->capacity * sizeof(struct heap_element));
    }

    return true;
}

int main() {
    struct heap h = {
            .data = NULL,
            .capacity = 0,
            .length = 0, //
    };

    heap_insert(&h, 7, "this");
    heap_insert(&h, 3, "is");
    heap_insert(&h, 0, "an");
    heap_insert(&h, 9, "example");
    heap_insert(&h, 3, "piece");
    heap_insert(&h, 4, "of");
    heap_insert(&h, 8, "text");
    heap_insert(&h, 8, "to");
    heap_insert(&h, 2, "make");
    heap_insert(&h, 1, "sure");
    heap_insert(&h, 7, "your");
    heap_insert(&h, 5, "code");
    heap_insert(&h, 3, "works");

    for (size_t i = 0; i < h.length; i++) //for loop that prints the priority and data
        printf("%d: %d %s\n", (int) i, h.data[i].priority, h.data[i].data); //prints the priority and data at index i

    puts("Processing all elements according to priority:"); //tertiary heap prints all elements according to priority

    int priority; //priority is
    const char *data;//this points to the data
    while (heap_remove(&h, &priority, &data)) //while heap_remove is
        printf("%d %s\n", priority, data); //prints priority and data

    return 0;
}


