// This is a reference voltage determined with a multimeter
#define aref_voltage 4.20 //(change it according to the reference voltage captured with multimeter between =ve and -ve terminal of arduino)

// Pin connections
// S - 18
// + - 19
// - - -

// Setting up the pins

//pin to get sensor reading
int tempPin = 16;


//pin for positive output to the sensor
int positivePin = 18;
//pin for color output.
int redPin = 5;
int bluePin = 06;
int greenPin = 10;
int redValue = 0;   // Variables to store the values to send to the pins
int grnValue = 0;
int bluValue = 0;                                                         


// Voltage of sensor

int voltage;
// Raw temperature read from pin S / 18
int tempReading;
// Temperature in degrees Celcius
float temperatureC;
// Temperature in degrees Fahrenheit
float temperatureF;

void setup(void) {
  // To send debugging information via the serial monitor
  Serial.begin(9600);
  // Initialization of the pins
  pinMode(tempPin,INPUT);
  pinMode(positivePin, OUTPUT);
  // The value that is read is positive - LOW = minus , HIGH = positive
  digitalWrite(positivePin, HIGH);
  pinMode(redPin, OUTPUT);   // sets the pins as output
  pinMode(greenPin, OUTPUT);   
  pinMode(bluePin, OUTPUT);
}

void loop(void) {
  // Get the temperature reading from the temperature sensor
  tempReading = analogRead(tempPin);

  // Debugging raw analog information available in the Serial monitor
  Serial.print("Temp reading = ");
  Serial.print(tempReading);
  //Serial.println(“”);

  // Converting that reading to voltage, which is based on the reference voltage
  float voltage = tempReading * aref_voltage;
  voltage /= 1024.0;

  Serial.print(" - ");
  Serial.print(voltage);
  Serial.println(" volts");

  // Converting from 10 mv per degree with 500 mV offset to degrees Celsius ((voltage - 500mV) times 100)
  temperatureC = (voltage - 0.5) * 100 ;
  Serial.print(temperatureC);
  Serial.println(" degrees Celsius");

  // To degrees Fahrenheit
  temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;
  Serial.print(temperatureF);
  Serial.println(" degrees Fahrenheit");
  if(temperatureC < 8){

    redValue = 255;  // off
    grnValue = 255;        // off
    bluValue = 1;             // full on
  
  }else  if(temperatureC >8 && temperatureC <15){

    redValue = 235;  // off
    grnValue = 66;        // Green from full to off
    bluValue = 244;             // Blue from off to full
  
  }else  if(temperatureC >15){

    redValue = 255;  // on
    grnValue = 1;        // Green from full to off
    bluValue = 255;             // Blue from off to full
  
  }
  analogWrite(redPin, redValue);   // Write values to LED pins
  analogWrite(greenPin, grnValue); 
  analogWrite(bluePin, bluValue);
  delay(1000);
}
