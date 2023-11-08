#include <iostream>

using namespace std;

bool checkParity(int data, bool parityType) {
  int count = 0;
  while (data > 0) {
    if (data % 2 == 1) {
      count++;
    }
    data /= 2;
  }

  bool expectedParity;
  if (count % 2 == 0) {
    expectedParity = true; // Even parity
  } else {
    expectedParity = false; // Odd parity
  }

  return expectedParity == parityType; // Check if calculated parity matches expected parity
}

int main() {
  int data = 10; // Binary representation: 1010
  bool parityType = true; // Even parity

  bool parityCheckResult = checkParity(data, parityType);

  if (parityCheckResult) {
    cout << "Data received without errors." << endl;
  } else {
    cout << "Error detected in data transmission." << endl;
  }

  return 0;
}