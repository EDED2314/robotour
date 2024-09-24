// /* This code is meant to read RPM of motors to allow control feedback to incorporate differential turns.
//  * Depending on the number of Interupt pins on the 3DoT, we may only monitor 2 motors and link the rest.
//  */

// // ticks of the right and left encoder. This is volatile so that it doesn't interfere with the rest of the code.
// volatile unsigned long ticksM1 = 0;
// volatile unsigned long ticksM1_old = 0;
// volatile unsigned long RPM_M1 = 0;

// volatile unsigned long ticksM2 = 0;
// volatile unsigned long ticksM2_old = 0;
// volatile unsigned long RPM_M2 = 0;

// volatile unsigned long ticksM3 = 0;
// volatile unsigned long ticksM3_old = 0;
// volatile unsigned long RPM_M3 = 0;

// volatile unsigned long ticksM4 = 0;
// volatile unsigned long ticksM4_old = 0;
// volatile unsigned long RPM_M4 = 0;

// volatile unsigned long ticksM5 = 0;
// volatile unsigned long ticksM5_old = 0;
// volatile unsigned long RPM_M5 = 0;

// volatile unsigned long ticksM6 = 0;
// volatile unsigned long ticksM6_old = 0;
// volatile unsigned long RPM_M6 = 0;

// void setup()
// {
//     Serial.begin(9600);
//     delay(2000);
//     Serial.println("Start reading RPM");

//     attachInterrupt(digitalPinToInterrupt(3), ISR_CountTicksM1, CHANGE); // attachings pins to interrupts
//     attachInterrupt(digitalPinToInterrupt(2), ISR_CountTicksM2, CHANGE); // attachings pins to interrupts
//     attachInterrupt(digitalPinToInterrupt(1), ISR_CountTicksM3, CHANGE);
//     attachInterrupt(digitalPinToInterrupt(4), ISR_CountTicksM4, CHANGE);
//     attachInterrupt(digitalPinToInterrupt(5), ISR_CountTicksM5, CHANGE);
//     attachInterrupt(digitalPinToInterrupt(6), ISR_CountTicksM6, CHANGE);
// }
// void loop()
// {
//     RPM_M1 = (ticksM1 - ticksM1_old) * 60;
//     RPM_M2 = (ticksM2 - ticksM2_old) * 60;

//     Serial.println("Ticks1: \t RPM1: \t \t Ticks2: \t RPM2:");
//     Serial.print("\t");
//     Serial.print(ticksM1 / 1000);
//     Serial.print("\t \t");
//     Serial.print(RPM_M1 / 1000);
//     Serial.print("\t \t");
//     Serial.print(ticksM2 / 1000);
//     Serial.print("\t \t");
//     Serial.println(RPM_M2 / 1000);

//     ticksM1_old = ticksM1;
//     ticksM2_old = ticksM2;
//     delay(500);
// }

// void ISR_CountTicksM1()
// { // interrupt service routine to count the right encoder ticks
//     ticksM1++;
// }

// void ISR_CountTicksM2()
// { // interrupt service routine to count the left encoder ticks
//     ticksM2++;
// }

// void ISR_CountTicksM3()
// { // interrupt service routine to count the left encoder ticks
//     ticksM3++;
// }

// void ISR_CountTicksM4()
// { // interrupt service routine to count the left encoder ticks
//     ticksM4++;
// }

// void ISR_CountTicksM5()
// { // interrupt service routine to count the left encoder ticks
//     ticksM5++;
// }

// void ISR_CountTicksM6()
// { // interrupt service routine to count the left encoder ticks
//     ticksM6++;
// }