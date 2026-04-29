#include <stdio.h> // Using C-style I/O (scanf/printf) for speed
#include <new>     // To use 'new' and 'delete' operators

// A structure to hold the student's id and mark together
struct Student {
    int id;
    int mark;
};

/**
 * @brief Merges two sorted subarrays into one sorted array.
 *
 * This function is the core of the Merge Sort algorithm.
 * It merges two halves: arr[left...mid] and arr[mid+1...right].
 */
void merge(Student arr[], int left, int mid, int right) {
    int n1 = mid - left + 1; // Size of the left subarray
    int n2 = right - mid;    // Size of the right subarray

    // Create temporary arrays to hold the data of the two halves
    // We use dynamic allocation (new[]) to avoid stack overflow for large inputs
    Student* L = new Student[n1];
    Student* R = new Student[n2];

    // --- 1. Copy data to temporary arrays L[] and R[] ---
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // --- 2. Merge the temp arrays back into arr[left...right] ---
    int i = 0; // Initial index of first subarray (L)
    int j = 0; // Initial index of second subarray (R)
    int k = left; // Initial index of the merged main array (arr)

    while (i < n1 && j < n2) {
        // --- This is the custom comparison logic ---
        
        // Primary Sort Key: marks in ascending order
        if (L[i].mark < R[j].mark) {
            arr[k] = L[i];
            i++;
        }
        else if (L[i].mark > R[j].mark) {
            arr[k] = R[j];
            j++;
        }
        else {
            // Secondary Sort Key: IDs in ascending order (if marks are equal)
            if (L[i].id < R[j].id) {
                arr[k] = L[i];
                i++;
            }
            else {
                arr[k] = R[j];
                j++;
            }
        }
        k++;
    }

    // --- 3. Copy any remaining elements ---
    // If we ran out of elements in R[], copy the rest of L[]
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // If we ran out of elements in L[], copy the rest of R[]
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    
    // --- 4. Clean up the temporary dynamic arrays ---
    delete[] L;
    delete[] R;
}

/**
 * @brief The main Merge Sort function (recursive).
 *
 * @param arr The array of Students to be sorted.
 * @param left The starting index of the segment to sort.
 * @param right The ending index of the segment to sort.
 */
void mergeSort(Student arr[], int left, int right) {
    if (left < right) {
        // Find the middle point to divide the array
        // Using (left + (right - left) / 2) to avoid overflow for large l, r
        int mid = left + (right - left) / 2;

        // Recursively sort the two halves
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Merge the two sorted halves
        merge(arr, left, mid, right);
    }
}

int main() {
    int n;
    scanf("%d", &n);

    // Dynamically allocate memory for n students on the heap
    // This is necessary because n=100005 would overflow the stack
    Student* students = new Student[n];

    // Read all student data
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &students[i].id, &students[i].mark);
    }

    // Call our custom mergeSort function to sort the entire array
    mergeSort(students, 0, n - 1);

    // Print the sorted IDs
    for (int i = 0; i < n; i++) {
        printf("%d\n", students[i].id);
    }
    
    // Free the dynamically allocated memory
    delete[] students;

    return 0;
}