/*
 *   12.11.10.9.8
 *  _______________
 * |               |
 * |      LED      |
 * |_______________|
 *    1.2.3.4.5.6
 *    
 * PIN LED      PIN BOARD   
 *   1              6
 *   2              5
 *   3              4
 *   4              3
 *   5              7
 *   6             13
 *   7              2
 *   8             12
 *   9             11 
 *   10             8
 *   11             9
 *   12            10
 */

//ABCDEFG,dp
const int numeral[10]= { 
  B11111100, //0
  B01100000, //1
  B11011010, //2
  B11110010, //3
  B01100110, //4
  B10110110, //5
  B10111110, //6
  B11100000, //7
  B11111110, //8
  B11110110, //9
};

//pins for decimal point and each segment
//dp, G, F, E, D, C, B, A
const int segmentPins[]= { 4, 7, 8, 6, 5, 3, 2, 9}; 

const int numberofDigits=4;

const int digitPins[numberofDigits] = { 10,11,12, 13}; //digits 1, 2, 3, 4

int realtime = 0;

void setup() 
{ 
  for (int i=0; i < 8; i++)
    pinMode(segmentPins[i], OUTPUT); //set segment and DP pins to output
  
  //sets the digit pins as outputs
  for (int i=0; i < numberofDigits; i++)
    pinMode(digitPins[i], OUTPUT);
}

void loop()
{
  int timeAtm = millis()/1000%(60*24), time0, time1, time2, time3;
  
  time0 = timeAtm%60%10;
  time1 = int((timeAtm%60)/10)*10;
  time3 = int(timeAtm/600)*1000;
  if(time3 >= 2000)
    time2 = (int(timeAtm/60%10)%4)*100;
  else
    time2 = int(timeAtm/60%10)*100;
    
  showNumber(time0+time1+time2+time3);
}

void showNumber (int number)
{
  if (number == 0)
    showDigit (0, numberofDigits-1); //display 0 in the rightmost digit
  else
  {
    for (int digit= numberofDigits-1; digit >=0; digit--)
    {
      if (number > 0)
      {
        showDigit(number % 10, digit);
        number= number/10;
      }else{
        showDigit(0, digit);
      }
    }
  }
}

//Displays given number on a 7-segment display at the given digit position 
void showDigit (int number, int digit)
{
  digitalWrite(digitPins[digit], HIGH);
  for (int segment= 1; segment < 8; segment++)
  {
    boolean isBitSet= bitRead(numeral[number], segment);
    
    isBitSet= ! isBitSet; //remove this line if common cathode display
    digitalWrite(segmentPins[segment], isBitSet);
  }
  delay(5);
  digitalWrite(digitPins[digit], LOW);
}



