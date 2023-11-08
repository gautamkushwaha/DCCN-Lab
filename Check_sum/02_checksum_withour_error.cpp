#include <iostream>

using namespace std;

unsigned short checksum(const char* data, int length) {
  unsigned short sum = 0;
  for (int i = 0; i < length; i++) {
    sum += data[i];
  }
  return sum;
}

bool checkDataIntegrity(const char* data, int length) {
  unsigned short calculatedChecksum = checksum(data, length - 1); // Subtract 1 to exclude the checksum byte
  unsigned short receivedChecksum = data[length - 1]; // Assuming checksum is the last byte

  if (calculatedChecksum == receivedChecksum) {
    return true; // Data received without errors
  } else {
    return false; // Error detected during data transmission
  }
}

int main() {
  const char data[] = "Hello, World!"; // Data without error

  cout << "Data received: " << data << endl;

  bool dataIntegrity = checkDataIntegrity(data, sizeof(data) - 1); // Check data without error

  if (dataIntegrity) {
    cout << "Data received without errors." << endl;
  } else {
    cout << "Error detected during data transmission." << endl;
  }

  return 0;
}