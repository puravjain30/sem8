#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

// Class to perform parallel reduction operations
class ParallelReduction {
public:
    // Function to compute minimum value using parallel reduction
    int Min(const vector<int> &arr) {
        int result = arr[0];
#pragma omp parallel for reduction(min : result)
        for (int i = 0; i < arr.size(); ++i) {
            result = min(result, arr[i]);
        }
        return result;
    }

    // Function to compute maximum value using parallel reduction
    int Max(const vector<int> &arr) {
        int result = arr[0];
#pragma omp parallel for reduction(max : result)
        for (int i = 0; i < arr.size(); ++i) {
            result = max(result, arr[i]);
        }
        return result;
    }

    // Function to compute sum using parallel reduction
    int Sum(const vector<int> &arr) {
        int result = arr[0];
#pragma omp parallel for reduction(+ : result)
        for (int i = 0; i < arr.size(); ++i) {
            result += arr[i];
        }
        return result;
    }

    // Function to compute average using parallel reduction
    double Average(const vector<int> &arr) {
        int sum = Sum(arr);
        return static_cast<double>(sum) / arr.size();
    }
};

int main() {
    const int size = 10;
    vector<int> arr(size);

    // Initialize the array with random values
    for (int i = 0; i < size; ++i) {
        arr[i] = rand() % 1000;
        cout << arr[i] << " ";
    }
    cout << endl;

    // Create an instance of the ParallelReduction class
    ParallelReduction parallelReduction;

    // Compute min, max, sum, and average using parallel reduction
    int minVal = parallelReduction.Min(arr);
    int maxVal = parallelReduction.Max(arr);
    int sum = parallelReduction.Sum(arr);
    double average = parallelReduction.Average(arr);

    cout << "Minimum value: " << minVal << endl;
    cout << "Maximum value: " << maxVal << endl;
    cout << "Sum: " << sum << endl;
    cout << "Average: " << average << endl;

    return 0;
}
