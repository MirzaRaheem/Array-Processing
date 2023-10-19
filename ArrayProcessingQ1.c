#include <stdio.h>

void set_array(int arr[], int length) {
    for (int i = 0; i < length; i++) {
        arr[i] = i;
    }
}

int main() {
    int arr[] = {0, 0, 0, 0, 0};    // Initializing the array with zeros
    int length = sizeof(arr) / sizeof(arr[0]);

    set_array(arr, length);

    printf("Array after setting values to its index:\n");
    for (int i = 0; i < length; i++) {
        printf("arr[%d] = %d\n", i, arr[i]);
    }

    return 0;
}