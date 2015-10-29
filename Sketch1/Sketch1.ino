#include <Timer.h>
#include <Event.h>
#include <LCD5110_Basic.h>

LCD5110 myGLCD(8, 9, 10, 11, 12);
extern uint8_t SmallFont[];
Timer t;
int loc1;
int loc2;
int b1pin = 3;
int b2pin = 4;

int button1State = 0;
int lastButton1State = 0;

int button2State = 0;
int lastButton2State = 0;

int win1=0;
int win2=0;

void setup()
{
	pinMode(b1pin, INPUT);
	pinMode(b2pin, INPUT);
	pinMode(2, OUTPUT);
	myGLCD.InitLCD();
	myGLCD.setFont(SmallFont);
	myGLCD.print("|DOT RACING|", CENTER, 16);
	delay(3000);
	digitalWrite(2, HIGH);
	t.after(300, kapa);
	myGLCD.clrRow(2);
}
void kapa() {
	digitalWrite(2, LOW);
}
void printDot(int loc,int satir) {
	String a;
	for (int i = 0; i < loc; i++) {
		a = a + " ";
	}
	a = a + ".";
		myGLCD.print(a, LEFT, satir);
}

void loop()
{
	t.update();
	myGLCD.printNumI(win1, LEFT, 0);
	myGLCD.printNumI(win2, RIGHT, 0);
	printDot(loc1, 8);
	printDot(loc2, 24);
	// read the pushbutton input pin:
	button1State = digitalRead(b1pin);

	// compare the buttonState to its previous state
	if (button1State != lastButton1State) {
		// if the state has changed, increment the counter
		if (button1State == HIGH) {
			// if the current state is HIGH then the button
			// wend from off to on:
			loc1++;
		}
		else {
		}
		// Delay a little bit to avoid bouncing
		delay(10);
	}
	// save the current state as the last state,
	//for next time through the loop
	lastButton1State = button1State;


	button2State = digitalRead(b2pin);

	// compare the buttonState to its previous state
	if (button2State != lastButton2State) {
		// if the state has changed, increment the counter
		if (button2State == HIGH) {
			// if the current state is HIGH then the button
			// wend from off to on:
			loc2++;
		}
		else {
		}
		// Delay a little bit to avoid bouncing
		delay(10);
	}
	// save the current state as the last state,
	//for next time through the loop
	lastButton2State = button2State;

	if (loc1 == 14) {

		win1++;
		myGLCD.clrScr();
		myGLCD.print("Player 1 Won", CENTER, 16);
		delay(3000);
		myGLCD.print("|DOT RACING|", CENTER, 16);
		myGLCD.print("P1: " + String(win1) + "  P2: " + String(win2), CENTER, 24);
		delay(3000);
		digitalWrite(2, HIGH);
		t.after(300, kapa);
		myGLCD.clrScr();
		loc1 = 0;
		loc2 = 0;
	}
	if (loc2 == 14) {

		win2++;
		myGLCD.clrScr();
		myGLCD.print("Player 2 Won", CENTER, 16);
		delay(3000);
		myGLCD.print("|DOT RACING|", CENTER, 16);
		myGLCD.print("P1: " + String(win1) +"  P2: " + String(win2), CENTER, 24);
		delay(3000);
		digitalWrite(2, HIGH);
		t.after(300, kapa);
		myGLCD.clrScr();
		loc1 = 0;
		loc2 = 0;
	}
}