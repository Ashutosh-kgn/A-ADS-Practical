#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int partition(int arr[], int low, int high){
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++){
        if (arr[j] <= pivot){
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

int randomizedPartition(int arr[], int low, int high){
    int randomIndex = low + rand() % (high - low + 1);
    swap(arr[randomIndex], arr[high]);
    return partition(arr, low, high);
}

int randomizedSelect(int arr[], int low, int high, int i){
    if (low == high)
        return arr[low];
    int q = randomizedPartition(arr, low, high);
    int k = q - low + 1;
    if (i == k)
        return arr[q];
    else if (i < k)
        return randomizedSelect(arr, low, q - 1, i);
    else
        return randomizedSelect(arr, q + 1, high, i - k);
}

int main(){
    srand(time(0));
    int n, i;
    cout << "Enter the number of elements: ";
    cin >> n;
    int arr[n];
    cout << "Enter array elements: ";
    for (int j = 0; j < n; j++)
        cin >> arr[j];
    cout << "Enter i S: ";
    cin >> i;
    if (i < 1 || i > n){
        cout << "Invalid value of i!";
        return 0;
    }
    int result = randomizedSelect(arr, 0, n - 1, i);
    cout << i << "-th smallest element is: " << result << endl;
    return 0;
}