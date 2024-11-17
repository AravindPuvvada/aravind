#include <SoftwareSerial.h>
String inputString="";
String fromGSM="";
SoftwareSerial mySerial(8,9);//Tx of GSM to arduino pin 3, Rx of GSM to arduino pin 2//
char sim800l[255],SMS[255];
int sim800lIndex=0,SMS_Index=0;
bool NewSMSArrived=0;

void setup() 
{
Serial.begin(9600);
mySerial.begin(9600);
Serial.println(" Command --> AT ");
mySerial.print("AT");
mySerial.print("\r");
delay(100);
Serial.print(" Response --> ");
while(mySerial.available())
{ 
sim800l[sim800lIndex] = mySerial.read();
sim800lIndex++;
Serial.print( sim800l[sim800lIndex-1]);
}
sim800lIndex=0;
Serial.println("");
Serial.println(" Command --> ATEO ");
mySerial.print("ATE0");
mySerial.print("\r");
delay(100);
Serial.print(" Response --> ");
while(mySerial.available())
{ 
sim800l[sim800lIndex] = mySerial.read();
sim800lIndex++;
Serial.print( sim800l[sim800lIndex-1]);
}
sim800lIndex=0;
Serial.println("");

Serial.println(" Command --> AT+CFUN=1 ");
mySerial.print("AT+CFUN =1");
mySerial.print("\r");
delay(100);
Serial.print(" Response --> ");
// while( ! (mySerial.available()) );
while(mySerial.available())
{ 
sim800l[sim800lIndex] = mySerial.read();
sim800lIndex++;
Serial.print( sim800l[sim800lIndex-1]);
}
sim800lIndex=0;
Serial.println("");

Serial.println(" Command --> AT+CMGF=1 ");
Serial.print(" Response --> ");
mySerial.print("AT+CMGF =1");
mySerial.print("\r");
delay(100);
// while( ! (mySerial.available()) );
while(mySerial.available())
{ 
sim800l[sim800lIndex] = mySerial.read();
sim800lIndex++;
Serial.print( sim800l[sim800lIndex-1]);
}

Serial.println(" Command --> AT+CSCS=\"GSM\"");
Serial.print(" Response --> ");
mySerial.print("AT+CSCS =\"GSM\"");
mySerial.print("\r");
delay(100);
// while( ! (mySerial.available()) );
while(mySerial.available())
{ 
sim800l[sim800lIndex] = mySerial.read();
sim800lIndex++;
Serial.print( sim800l[sim800lIndex-1]);
}

Serial.println(" Command --> AT+CPMS=\"SM\"");
Serial.print(" Response --> ");
mySerial.print("AT+CPMS =\"SM\"");
mySerial.print("\r");
delay(100);
// while( ! (mySerial.available()) );
while(mySerial.available())
{ 
sim800l[sim800lIndex] = mySerial.read();
sim800lIndex++;
Serial.print( sim800l[sim800lIndex-1]);
}

Serial.println(" Command --> AT+CMGS=\"7013984982\"");
Serial.print(" Response --> ");
mySerial.print("AT+CMGS=\"7013984982\"");
mySerial.print("\n");
delay(100);

// while( ! (mySerial.available()) );
while(mySerial.available())
{ 
sim800l[sim800lIndex] = mySerial.read();
sim800lIndex++;
Serial.print( sim800l[sim800lIndex-1]);
}
mySerial.print(" SILICON TOUCH TECHNOLOGIES "); // txt msg
mySerial.write(0x1A);

Serial.print(" CHECK THE DESTINATION DEVICE ");

}

void loop() 
{ 
while(1)
{
while(Serial.available())
{ 
sim800l[sim800lIndex] = Serial.read();
sim800lIndex++;
mySerial.print( sim800l[sim800lIndex-1]);
}
while(mySerial.available())
{ 
sim800l[sim800lIndex] = mySerial.read();
sim800lIndex++;
/* if(sim800l[sim800lIndex-5]=='+'&&sim800l[sim800lIndex-4]=='C'&&sim800l[sim800lIndex-3]=='M'&&sim800l[sim800lIndex-2]=='T'&&sim800l[sim800lIndex-1]=='I')
{
NewSMSArrived=1; 
} */
Serial.print( sim800l[sim800lIndex-1]);
}

/* if(NewSMSArrived == 1)
{
for(int i=0;i= (sim800lIndex-1);i++)
{
SMS[i] = sim800l[i];
}
NewSMSArrived=0;
Serial.print(SMS);
} */
} 
} 
