#include <iostream>

using namespace std;

unsigned short checksum(const char* data, int length) {
  unsigned short sum = 0;
  for (int i = 0; i < length; i++) {
    sum += data[i];
  }
  return sum;
}

int main() {
  const char data[] = "Hello";
  int length = sizeof(data) - 1; // Subtract 1 to exclude the null terminator

  unsigned short calculatedChecksum = checksum(data, length);
  cout << "Calculated checksum: " << calculatedChecksum << endl;

  cout << "Sending data: " << data << endl;

  // Assuming the checksum is transmitted along with the data
  // Extract the received checksum from the data block
  unsigned short receivedChecksum = 500;
  
  cout << "recievedchecksum: " << receivedChecksum << endl;

  bool dataIntegrity = calculatedChecksum == receivedChecksum;

  if (dataIntegrity) {
    cout << "Data received without errors." << endl;
  } else {
    cout << "Error detected during data transmission." << endl;
  }

  return 0;
}