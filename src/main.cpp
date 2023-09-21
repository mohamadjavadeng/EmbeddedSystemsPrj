#include <Arduino.h>
#include <SD.h>
#include <SPI.h>

// put function declarations here:
int baudrate = 9600; //set the baud rate.
String filename; //Store file name.
boolean isDirectory = false; //Set for directory flag
boolean isRemoveDirectory = false; //Set delete (file/director) flag.
boolean isRemoveFile = false;
boolean isChangeDirectory = false; //Set change directory flag.
boolean isReadFromFile = false;
boolean isWriteToFile = false;
String root = "/";
String tvRemoteOption;
String dataInput;
int CSpin = 10; //Chip Select pin.
void ListDirectory(void);
void ErrorHandler(int errorCode);
void PrintDirectory(File dir, int numTabs);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(baudrate); // Start serial communication.
  // pinMode(10,OUTPUT);//Required by the SD library?
  pinMode(CSpin,OUTPUT);//Required by the SD library?
  Serial.println(F("************************************************************"));
  Serial.println(F("************************************************************"));
  Serial.println();
  Serial.println(F("Initialize the SD card..."));
  delay(2000);
  //Initialized SD card
  if (!SD.begin(CSpin)){  //Test for initialized.
    ErrorHandler(9);
  }//End if.
  Serial.println(F("Initialization Complete."));
  ListDirectory();

}// End Setup

void loop() {
  // put your main code here, to run repeatedly:
  //ListDirectory();
}



//ErrorHandler ***************************************************
//Use this function to trap and display error messages. If an error
//occurs stop all processing.
void ErrorHandler(int errorCode){

 
switch(errorCode){

case 1:  
  Serial.print(F("ERROR[1]: "));
  Serial.print(filename);
  Serial.println(F(" file not found."));
  //tone(buzzerPin, 494, 100);  //Debug.
  delay(200); //Debug.
  //noTone(buzzerPin);//Debug. Turn off tone function.
  while(true); //Stop running.
break;

case 2:
    Serial.print(F("ERROR[2]: directory "));
    Serial.print(filename);
    Serial.println(F(" does not exist.")); //Error message.
    //tone(buzzerPin, 494, 100);  //Debug.
    delay(200); //Debug.
    //noTone(buzzerPin);//Debug. Turn off tone function.
    while(true); //Stop running. 
break;

case 3:
    Serial.print(F("ERROR[3]: Can not create file "));
    Serial.print(filename);
    Serial.println("."); //Error message.
    //tone(buzzerPin, 494, 100);  //Debug.
    delay(200); //Debug.
    //noTone(buzzerPin);//Debug. Turn off tone function.
    while(true); //Stop running.
break;


case 4:  
  Serial.print(F("ERROR[4]: Could not OPEN file "));
  Serial.print(filename);
  Serial.println(".");
  //tone(buzzerPin, 494, 100);  //Debug.
  delay(200); //Debug.
  //noTone(buzzerPin);//Debug. Turn off tone function.
  while(true); //Stop running.
break;


case 9:
    Serial.println(F("ERROR[9]: SD card initialization failed!"));
    Serial.println(F("Program execution is halted."));
    //tone(buzzerPin, 494, 100);  //Debug.
    delay(200); //Debug.
    //noTone(buzzerPin);//Debug. Turn off tone function.
    while(true); //Stop running.
break;


  } //End case statement.

}//End ErrorHandler.


//ListDirectory **************************************************
void ListDirectory(){
    File myFile = SD.open(root); //Root directory.
    delay(200);//Wait for myFile to open.
    PrintDirectory(myFile, 0);
    myFile.close();//Close the myFile.

}//end ListDirectory function.

void PrintDirectory(File dir, int numTabs) {
  dir.seek(0); // Add seek!!!

  while (true) {

    File entry =  dir.openNextFile();
     if (! entry) {
      dir.rewindDirectory();
      break; 
    } //End if. 
    
    for (uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');
    } //End for.
   
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
      PrintDirectory(entry, numTabs + 1);
    } //End if. 
    
    else 
    {
      // files have sizes, directories do not
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    } //End else
    
    entry.close(); //Write the file to the disk.
    
  }
  } //End while.