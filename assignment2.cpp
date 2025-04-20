#include <bits/stdc++.h>
using namespace std;

vector<int> generateRandomArray(int size) {
    vector<int> array(size); 
    for (int i = 0; i < size; i++) {
        array[i] = rand() % 1000; 
    }
    return array;
}

void merge(vector<int>& arr, int left, int mid, int right) {
    vector<int> temp;
    int i = left, j = mid + 1;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j])
            temp.push_back(arr[i++]);
        else
            temp.push_back(arr[j++]);
    }

    while (i <= mid) temp.push_back(arr[i++]);
    while (j <= right) temp.push_back(arr[j++]);

    for (int k = 0; k < temp.size(); k++)
        arr[left + k] = temp[k];
}

void parallelMergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            parallelMergeSort(arr, left, mid);

            #pragma omp section
            parallelMergeSort(arr, mid + 1, right);
        }

        merge(arr, left, mid, right);
    }
}

void seqMergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        seqMergeSort(arr, left, mid); 
        seqMergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int main() {
    int size;
    cout << "Enter the size of the array: ";
    cin >> size;

    vector<int> arr = generateRandomArray(size); 

    
    auto start = std::chrono::high_resolution_clock::now();
    parallelMergeSort(arr, 0, arr.size() - 1);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    cout << "Time taken (Parallelly): " << duration.count() << "s" << endl;


    cout << "Sequential merge sort: ";
    vector<int> arrSeq = generateRandomArray(size); 
    auto startSeq = std::chrono::high_resolution_clock::now();
    seqMergeSort(arrSeq, 0, arrSeq.size() - 1);
    auto endSeq = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> durationSeq = endSeq - startSeq;
    cout << "Time taken (Sequentially): " << durationSeq.count() << "s" << endl;

    return 0;
}
