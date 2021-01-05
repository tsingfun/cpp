/************************************
 * 快速排序
 * 不稳定排序，O{nlogn} ~ O{n^2}
 * 适合排序大量数据
 * 设最左边为基准数
 * 右边往左找一个比基准数小的
 * 左边往右找一个比基准数大的，和上一步交换
 * 碰头后和基准数交换
 *
 * https://www.tsingfun.com
 ************************************/
#include <iostream>

void printArray(int *array, int n)
{
    for (int i = 0; i < n; ++i)
        std::cout << array[i] << std::endl;
}

void quickSort(int *array, int low, int high)
{
    int i = low;
    int j = high;
    int pivot = array[(i + j) / 2];
    int temp;

    while (i <= j)
    {
        while (array[i] < pivot)
            i++;
        while (array[j] > pivot)
            j--;
        if (i <= j)
        {
            temp = array[i];
            array[i] = array[j];
            array[j] = temp;
            i++;
            j--;
        }
    }
    if (j > low)
        quickSort(array, low, j);
    if (i < high)
        quickSort(array, i, high);
}

int main()
{
    int array[] = {95, 45, 48, 98, 1, 485, 65, 478, 1, 2325};
    int n = sizeof(array)/sizeof(array[0]);

    std::cout << "Before Quick Sort :" << std::endl;
    printArray(array, n);

    quickSort(array, 0, n-1);

    std::cout << "After Quick Sort :" << std::endl;
    printArray(array, n);
    return (0);
}