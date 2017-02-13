#include <Arduino.h>

void setup() {
  float e, n;
  int b, bands, bins, count=0, d;

  while (!Serial && (millis() <= 6000));  // Wait for Serial interface

  bands = 15;                             // Frequency bands; (Adjust to desired value)
  bins = 512;                             // FFT bins; (Adjust to desired value)
  
  e = FindE(bands, bins);                 // Find calculated E value
  if (e) {                                // If a value was returned continue
    Serial.printf("E = %4.4f\n", e);      // Print calculated E value
    for (b = 0; b < bands; b++) {         // Test and print the bins from the calculated E
      n = pow(e, b);
      d = int(n + 0.5);

      Serial.printf( "%4d ", count);      // Print low bin
      count += d - 1;
      Serial.printf( "%4d\n", count);     // Print high bin
      ++count;
    }
  }
  else
    Serial.println("Error\n");            // Error, something happened
}

void loop() {
  // put your main code here, to run repeatedly:

}

float FindE(int bands, int bins) {
  float increment=0.1, eTest, n;
  int b, count, d;

  for (eTest = 1; eTest < bins; eTest += increment) {     // Find E through brute force calculations
    count = 0;
    for (b = 0; b < bands; b++) {                         // Calculate full log values
      n = pow(eTest, b);
      d = int(n + 0.5);
      count += d;
    }
    if (count > bins) {     // We calculated over our last bin
      eTest -= increment;   // Revert back to previous calculation increment
      increment /= 10.0;    // Get a finer detailed calculation & increment a decimal point lower
    }
    else
      if (count == bins)    // We found the correct E
        return eTest;       // Return calculated E
    if (increment < 0.0000001)        // Ran out of calculations. Return previous E. Last bin will be lower than (bins-1)
      return (eTest - increment);
  }
  return 0;                 // Return error 0
}
