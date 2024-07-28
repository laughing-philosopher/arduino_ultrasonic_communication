#define TX_pin 3 // Connect transducer at pin no. 3
String stringVariable1;
int count = 0;
int NoOfTimesToSend = 5;

void setup()
{
  Serial.begin(9600); // set serial monitor baud rate at 15200
  pinMode(TX_pin, OUTPUT); 
}
void loop()
{
  String stringVariable = Serial.readString();
  if(stringVariable !=""){
    count = 0;
  stringVariable1 = stringVariable;
  }
if(stringVariable1 !="" && count < NoOfTimesToSend){
  count++;
  Serial.println(stringVariable1);
  send(stringVariable1 + "\n");
}else{
  count=0;
    while (Serial.available() == 0) {
  }
}

  // send("AC project ho gya kaam khtm!!!\n"); // Write the message to send in the function argument as string
}

void send(String msg)
{
  byte ch;
  unsigned int pos = 0; // to store position of byte in string
  unsigned int sz = msg.length(); // size of string
  while (pos < sz) // untill the string is fully tavarsed
  {
    ch = msg.charAt(pos); // Access the character at pos in msg string
    Serial.print((char)ch);
    tone(TX_pin, 40000); // Generate a 40k Hz sound wave for 10 milliseconds 
    delay(10);
    noTone(TX_pin); // Stop generating the sound
    for (int i = 0; i < 8; i++) // Traverse each bit of a character
    {
      bool b; // Variable to store bit 
      b = bitRead(ch, 7 - i); // Returns if the bit at ith position is HIGH (1) or LOW (0)
      if (b) // IF the bit is ONE send 2 millisecond sound of 4k Hz
      {
        tone(TX_pin, 40000);
        delay(2);
      }
      else // If the bit is ZERO send 4 millisecond sound of 4k Hz
      {
        tone(TX_pin, 40000);
        delay(4);
      }
      noTone(TX_pin);// After sending a character, send nothing for 11 milliseconds
      delay(11);
    }
    pos++; // Go to next character in the string
  }
}
