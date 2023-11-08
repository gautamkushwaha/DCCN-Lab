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
    cout << "Data received without errors." << endl;
    return true;
  } else {
    cout << "Error detected during data transmission." << endl;
    return false;
  }
}

int main() {
  const char data[] = "Hello, World!";
  int length = sizeof(data) - 1; // Subtract 1 to exclude the null terminator

  unsigned short calculatedChecksum = checksum(data, length);
  cout << "Calculated checksum: " << calculatedChecksum << endl;

  cout << "Sending data: " << data << endl;

  const char corruptedData[] = "Hello, World!"; // Intentional error introduced

  bool dataIntegrity = checkDataIntegrity(corruptedData, sizeof(corruptedData) - 1);

  return 0;
}

