#include <iostream>

int part_sort(int arr[], int low, int high)
{
    int middle = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j] <= middle)
        {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

void quick_sort(int arr[], int low, int high)
{
    if (low < high)
    {
        int middle = part_sort(arr, low, high);

        quick_sort(arr, low, middle - 1);
        quick_sort(arr, middle + 1, high);
    }
}

int main()
{

}