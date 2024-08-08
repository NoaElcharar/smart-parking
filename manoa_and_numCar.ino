#include <ESP32Servo.h>
#include <Keypad.h>

#define ROW_NUM 4     // ארבע שורות
#define COLUMN_NUM 4  // ארבעה עמודות

//יציאה
#define Trigpin1 18   //מרחק
#define echopin1 21   //מרחק
#define servoPin1 33  //מנוע
//כניסה
#define Trigpin 4    //מרחק
#define echopin 19   //מרחק
#define servoPin 26  //מנוע
// הגדרת מקשי המטריצה 
char keys[ROW_NUM][COLUMN_NUM] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};
// רכבים המורשים להכנס לחניון
char* arrCar[] = { "12345678", "14785236", "11111111", "44444444" };

// חיבורים של מקלדת 
byte pin_rows[ROW_NUM] = { 15, 12, 14, 27 };      //  מחוברים לפינים של השורות
byte pin_column[COLUMN_NUM] = { 5, 23, 22, 13 };  //  מחוברים לפינים של העמודות
// יצירת אוביקט שמתקשר עם המקלדת מטריצה 

// -שיהיה אפשר לשעת איזה לחצן לחץ המרת מערך לוח המקשים למבנה שהספריה יכולה לעבוד עליו 
Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM);


// פונקציה הקולטת מהמשתמש מספר רכב מלוח המקשים
char* numberCar() {
  static char number[9];  //שמירת המספר שהזין המשתמש
  bool flag = false;      // משתנה לצורך בדיקה אם הוכנס מספר תקין

  //קולט ממנו  כל עוד לא הזמין המשתשמש מספר נכון
  while (!flag) {
    // קליטה 8 ספרות מהמשתמש
    for (int i = 0; i < 8; i++) {
      char key;
      do {
        //  קליטה מהמשתמש מחזירה את הקלט  לבקר 
        key = keypad.getKey(); 
      } while (!key);  // המתנה ללחיצה על מקש
      number[i] = key;
      Serial.println(key);
    }
    number[8] = '\0';  // סיום המחרוזת

    flag = true;
    // בדיקה אם המספר שנקלט מכיל רק מספרים
    for (int j = 0; j < 8; j++) {
      if (number[j] < '0' || number[j] > '9') {
        flag = false;
        break;
      }
    }
  }
  return number;
}


// פונקציה שמודדת מרחק-חיישן2
int Distance_check1() {
  //פונקציה שבודקת מרחק
  //long duration, distance; // משתנים המאחסנים את מדידת הזמן והמרחק המחושב
  // איתחול השידור על ידי איפוס חיבור ה TRIG
  digitalWrite(Trigpin1, LOW);
  delayMicroseconds(2);
  // שליחת פולס מעורר
  digitalWrite(Trigpin1, HIGH);
  delayMicroseconds(10);
  // סיום פולס מעורר
  digitalWrite(Trigpin1, LOW);
  // המתנה והד מוחזר ומדידת זמן
  int duration1 = pulseIn(echopin1, HIGH);
  //חישוב המרחק
  int distance1 = duration1 / 58.82;
  Serial.print("distance1[cm]=");
  Serial.println(distance1);
  return distance1;
}


//  פונקציה שמודדת מרחק
int Distance_check() {
  //פונקציה שבודקת מרחק
  //long duration, distance; // משתנים המאחסנים את מדידת הזמן והמרחק המחושב
  // איתחול השידור על ידי איפוס חיבור ה TRIG
  digitalWrite(Trigpin, LOW);
  delayMicroseconds(2);
  // שליחת פולס מעורר
  digitalWrite(Trigpin, HIGH);
  delayMicroseconds(10);
  // סיום פולס מעורר
  digitalWrite(Trigpin, LOW);
  // המתנה והד מוחזר ומדידת זמן
  int duration = pulseIn(echopin, HIGH);
  //חישוב המרחק
  int distance = duration / 58.82;
  Serial.print("distance[cm]=");
  Serial.println(distance);
  return distance;
}

//משתנים  למנוע
Servo myservo;   // create servo object to control a servo
Servo myservo1;  // create servo object to control a servo
int pos = 0;     // variable to store the servo position



// פונקציה שמזיזה את השער של החניה
void Moving_the_parking_gate() {
  //  לפתיחת השער עוברת מ0עד 180 מעלות
  for (pos = 0; pos <= 180; pos += 1) {
    myservo.write(pos);
    // ממתינה
    delay(15);
  }
  // לסגירת השער עוברת מ0 180עד 0 מעלות

  for (pos = 180; pos >= 0; pos -= 1) {
    myservo.write(pos);
    delay(15);
  }
}


//  יציאה פונקציה שמזיזה את השער של החניה
void Moving_the_parking_gate1() {

  for (pos = 0; pos <= 180; pos += 1) {  // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo1.write(pos);  // tell servo to go to position in variable 'pos'
    delay(15);            // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) {  // goes from 180 degrees to 0 degrees
    myservo1.write(pos);                 // tell servo to go to position in variable 'pos'
    delay(15);                           // waits 15ms for the servo to reach the position
  }
}
bool is_number_can(char* number_car) {
  int i;
  for ( i =0; i < 4; i++) {
    if (strcmp(number_car, arrCar[i]) == 0) {
      Serial.print(number_car);
      Serial.println(" car can");
      return true;
    } 
  }
  if(i==4)
   {
      Serial.print(number_car);
      Serial.println(" car cant to enter");
      return false;
    }
}
// --------------------------------------
void setup() {
  //יציאה
  myservo1.attach(servoPin1, 1000, 2000);  //מנוע
  pinMode(Trigpin1, OUTPUT);               //מרחק
  pinMode(echopin1, INPUT);                //מרחק
  Serial.begin(9600);
  //כניסה
  myservo.attach(servoPin, 1000, 2000);  //מנוע
  pinMode(Trigpin, OUTPUT);              //מרחק
  pinMode(echopin, INPUT);               //מרחק
  Serial.begin(9600);
}


void loop() {

  // int move = 0;
  // int move1 = 0;
  float distance = Distance_check();    //מרחק
  float distance1 = Distance_check1();  //מרחק
  // move = distance;
  Serial.println(distance);  //מרחק
  // move1 = distance1;
  Serial.println(distance1);  //מרחק
  if (distance < 7)          //יש תנועה תפתח את השער
  {
    Serial.print("distance[cm]=");
    Serial.println(distance);  //מרחק
    char* carnum = numberCar();
    if (is_number_can(carnum)==true) {
      Serial.println(carnum); // הדפסת מספר הרכב
      Serial.println("open gate");  
      Moving_the_parking_gate();
    }
  }
  // // delay(500);
  if (distance1 < 7)  //1יש תנועה תפתח את השער
  {
    // char* carnum1 = numberCar();
    Serial.print("distance: "); // הדפסת מספר הרכב
    Serial.println(distance); // הדפסת מספר הרכב
    Moving_the_parking_gate1();
  }
  delay(500);
}
