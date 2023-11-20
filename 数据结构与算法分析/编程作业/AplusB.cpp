# include <iostream>
using namespace std;

int main() {
    int n = 0;
    cin >> n;
    int a, b;
    int arr[n];
    for (int i = 0; i < n; i++) {
        cin >> a >>b;
        arr[i] = a + b;
    }
    for (int i = 0; i < n; i++) {
        cout << arr[i] << endl;
    }
    return 0;
}