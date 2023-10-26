#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 24
#define nRows 8
#define nCols 3

// Function to print an array
void print_array(int array[], int length) {
    for (int i = 0; i < length; i++) {
        printf("array[%d] = %d\n", i, array[i]);
    }
}

// Function to print a matrix
void print_matrix(int mat[][nCols], int rows) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < nCols; j++) {
            printf("mat[%d][%d] = %d\n", i, j, mat[i][j]);
        }
        puts("");
    }
}

// Function to print a transposed matrix with 3 rows in each column side by side
void print_trans_matrix(int arr2d[nRows][nCols]) {
    for (int i = 0; i < nCols; i++) {
        for (int j = 0; j < nRows; j++) {
            printf("mat[%d][%d] = %d\t", j, i, arr2d[j][i]);
        }
        puts("");
    }
}

// Function to initialize an array with values equal to their indices
void set_array(int arr[], int length) {
    for (int i = 0; i < length; i++) {
        arr[i] = i;
    }
}

// Function to remove an element from an array at the specified position
void rem_align(int arr[], int length, int pos) {
    if (pos < 0 || pos >= length) {
        printf("Invalid index for removal: %d\n", pos);
        return;
    }

    for (int i = pos; i < length - 1; i++) {
        arr[i] = arr[i + 1];
    }
}

// Function to insert a value at a specific position in an array
void insert_align(int arr[], int length, int pos, int value) {
    if (pos < 0 || pos > length) {
        printf("Invalid index for insertion: %d\n", pos);
        return;
    }

    for (int i = length; i > pos; i--) {
        arr[i] = arr[i - 1];
    }
    arr[pos] = value;
}

// Function to reshape a 1D array into a 2D array
void reshape(int arr[], int length, int arr2d[nRows][nCols]) {
    if (length != nRows * nCols) {
        printf("Error: Array length does not match nRows x nCols\n");
        return;
    }

    int k = 0;
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nCols; j++) {
            arr2d[i][j] = arr[k++];
        }
    }
}

// Function to check if an array contains duplicate values
bool found_duplicate(int arr[], int length) {
    for (int i = 0; i < length - 1; i++) {
        for (int j = i + 1; j < length; j++) {
            if (arr[i] == arr[j]) {
                return true;
            }
        }
    }
    return false;
}

// Function to create a new array with reversed content
int* flip_array(int arr[], int length) {
    int* reversedArray = (int*)malloc(length * sizeof(int));

    for (int i = 0; i < length; i++) {
        reversedArray[i] = arr[length - 1 - i];
    }

    return reversedArray;
}

int main() {
    int arr[SIZE];
    int arr2d[nRows][nCols];

    // Call to different functions
    set_array(arr, SIZE);

    printf("Original Array:\n");
    print_array(arr, SIZE);

    rem_align(arr, SIZE, 2);

    printf("\nArray after removing element at position 2:\n");
    print_array(arr, SIZE - 1);

    insert_align(arr, SIZE - 1, 2, 80);

    printf("\nArray after inserting 80 at position 2:\n");
    print_array(arr, SIZE);

    reshape(arr, SIZE, arr2d);

    printf("\n2D Array after reshaping:\n");
    print_matrix(arr2d, nRows);

    bool hasDuplicate = found_duplicate(arr, SIZE);
    if (hasDuplicate) {
        printf("\nArray contains duplicates.\n");
    } else {
        printf("\nArray does not contain duplicates.\n");
    }

    int* reversedArr = flip_array(arr, SIZE);

    printf("\nReversed Array:\n");
    print_array(reversedArr, SIZE);

    printf("\nTransposed Matrix with 3 Rows in Each Column Side by Side:\n");
    print_trans_matrix(arr2d);

    free(reversedArr); // Free dynamically allocated memory for the reversed array

    return 0;
}
