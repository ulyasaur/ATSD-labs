#include <iostream>
#include <chrono>

void insertion_sort(int arr[], int low, int high)
{
    int i, key, j;
    for (i = low + 1; i <= high; i++)
    {
        key = arr[i];
        j = i - 1;

        while (j >= low && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

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

void quick_sort(int arr[], int low, int high, bool flag)
{
    if (flag && high - low < 10)
    {
        insertion_sort(arr, low, high);
    }
    else if (low < high)
    {
        int middle = part_sort(arr, low, high);

        quick_sort(arr, low, middle - 1, flag);
        quick_sort(arr, middle + 1, high, flag);
    }
}

int main()
{
    int n;
    std::cout << "Enter size of array: ";
    std::cin >> n;

    srand(time(NULL));
    int* L = new int[n];
    int* L1 = new int[n];

    std::cout << "Your array:\n";
    for (int i = 0; i < n; i++)
    {
        int temp = rand() % 1000;
        L[i] = temp;
        L1[i] = temp;
        std::cout << temp << " ";
    }
    std::cout << "\n\n";

    std::cout << "Your array after mixed Quick sort:\n";
    auto start = std::chrono::system_clock::now();
    quick_sort(L, 0, n - 1, true);
    for (int i = 0; i < n; i++)
    {
        std::cout << L[i] << " ";
    }
    std::cout << "\n";
    auto end = std::chrono::system_clock::now();
    std::cout << "Time: " 
        << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / 1000000.0 
        << " ms\n\n";
   

    std::cout << "Your array after ordinary Quick sort:\n";
    start = std::chrono::system_clock::now();
    quick_sort(L1, 0, n - 1, false);
    for (int i = 0; i < n; i++)
    {
        std::cout << L1[i] << " ";
    }
    std::cout << "\n";
    end = std::chrono::system_clock::now();
    std::cout << "Time: " 
        << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / 1000000.0 
        << " ms\n";
}