#include<bits/stdc++.h>
using namespace std;

void merge(vector<int> &arr, int left, int mid, int right) {
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

    // Copy back to original array
    for (int k = 0; k < temp.size(); k++)
        arr[left + k] = temp[k];
}

// Parallel merge sort
void parallelMergeSort(vector<int> &arr, int left, int right) {
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

int main(){
    vector<int> arr = {9, 7, 3, 8, 1, 2, 5, 4, 6};

    cout << "Original array: ";
    for (int x : arr) cout << x << " ";
        cout << endl;
    auto start=std::chrono::high_resolution_clock::now();
    parallelMergeSort(arr, 0, arr.size() - 1);
    auto end=std::chrono::high_resolution_clock::now();
    cout << "Sorted array: ";
    for (int x : arr) cout << x << " ";
    cout << endl;
    std::chrono::duration<double> duration=end-start;
    cout<<"Time taken: "<<duration.count()<<"s"<<endl;
    return 0;
}