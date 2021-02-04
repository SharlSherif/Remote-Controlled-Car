/*
 Name:		Remote_Controlled_Car.ino
 Created:	1/23/2021 7:19:11 PM
 Author:	Sharl
*/

#include <IRremote.h>

const int RECV_PIN = 13;
IRrecv irrecv(RECV_PIN);
decode_results results;

//L293D
//Motor A
const int motorPin1 = 9;  // Pin 14 of L293
const int motorPin2 = 10;  // Pin 10 of L293
//Motor B
const int motorPin3 = 6; // Pin  7 of L293
const int motorPin4 = 5;  // Pin  2 of L293

const int motorSpeed = 240;
String previousCode = "";
//This will run only one time.
void setup() {
	Serial.begin(9600);
	irrecv.enableIRIn();
	//  irrecv.blink13(true);
		//Set pins as outputs
	pinMode(motorPin1, OUTPUT);
	pinMode(motorPin2, OUTPUT);
	pinMode(motorPin3, OUTPUT);
	pinMode(motorPin4, OUTPUT);
}


void loop() {
	//Motor Control - Motor A: motorPin1,motorpin2 & Motor B: motorpin3,motorpin4
	if (irrecv.decode(&results)) {
		String code = translateIR();
		if (code == "REPEAT") {
			code = previousCode;
		}

		if (code == "LEFT")
		{
			MoveLeft();
		}

		if (code == "RIGHT") {
			MoveRight();
		}

		if (code == "FORWARD") {
			MoveForward();
		}

		if (code == "REVERSE") {
			MoveBackwards();
		}
		RecordCodeValue(code);
		Serial.println(code);
		irrecv.resume();
	}
	else {
		delay(150);
		Stop();
	}

}

void RecordCodeValue(String code) {
	if (code != "REPEAT") {
		previousCode = code;
	}
}
void Stop() {
	analogWrite(motorPin1, 0);
	analogWrite(motorPin2, 0);
	analogWrite(motorPin3, 0);
	analogWrite(motorPin4, 0);
}

void MoveRight() {
	analogWrite(motorPin1, motorSpeed);
	analogWrite(motorPin2, 0);

	analogWrite(motorPin3, 0);
	analogWrite(motorPin4, motorSpeed);
}

void MoveForward() {
	analogWrite(motorPin1, motorSpeed);
	analogWrite(motorPin2, 0);
	analogWrite(motorPin3, motorSpeed);
	analogWrite(motorPin4, 0);
}

void MoveLeft() {
	analogWrite(motorPin1, 0);
	analogWrite(motorPin2, motorSpeed);

	analogWrite(motorPin3, motorSpeed);
	analogWrite(motorPin4, 0);
}

void MoveBackwards() {
	analogWrite(motorPin1, 0);
	analogWrite(motorPin2, motorSpeed);
	analogWrite(motorPin3, 0);
	analogWrite(motorPin4, motorSpeed);
}

String translateIR()
{
	switch (results.value)
	{
	case 0xFF18E7:
		return("FORWARD");
		break;
	case 0xFF10EF:
		return("LEFT");
		break;
	case 0xFF38C7:
		return("-OK-");
		break;
	case 0xFF5AA5:
		return("RIGHT");
		break;
	case 0xFF4AB5:
		return ("REVERSE");
		break;
	case 0xFFA25D:
		return ("1");
		break;
	case 0xFF629D:
		return ("2");
		break;
	case 0xFFE21D:
		return ("3");
		break;
	case 0xFF22DD:
		return ("4");
		break;
	case 0xFF02FD:
		return ("5");
		break;
	case 0xFFC23D:
		return ("6");
		break;
	case 0xFFE01F:
		return ("7");
		break;
	case 0xFFA857:
		return ("8");
		break;
	case 0xFF906F:
		return ("9");
		break;
	case 0xFF6897:
		return ("*");
		break;
	case 0xFF9867:
		return ("0");
		break;
	case 0xFFB04F:
		return ("#");
		break;
	case 0xFFFFFFFF:
		return ("REPEAT");
		break;

	default:
		return ("Unidentified button");
	}
}