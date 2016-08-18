#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    armPot,         sensorPotentiometer)
#pragma config(Sensor, in6,    rightLine,      sensorLineFollower)
#pragma config(Sensor, in7,    centerLine,     sensorLineFollower)
#pragma config(Sensor, in8,    leftLine,       sensorLineFollower)
#pragma config(Sensor, dgtl8,  sonarCM,        sensorSONAR_cm)
#pragma config(Sensor, I2C_1,  leftEncoder,    sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_2,  rightEncoder,   sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Motor,  port1,           leftMotor,     tmotorVex393_HBridge, openLoop, encoderPort, I2C_1)
#pragma config(Motor,  port2,           clawMotor,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           armMotor,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          rightMotor,    tmotorVex393_HBridge, openLoop, reversed, encoderPort, I2C_2)

//+++++++++++++++++++++++++++++++++++++++| Global Variables |+++++++++++++++++++++++++++++++++++++++++
int threshold = 10;					// Deadzone control of JoySticks
int lowerLimit = 4085;			// Arm POT upper and lower limit
int upperLimit = 2500;

//+++++++++++++++++++++++++++++++++++++++++++++| MAIN |+++++++++++++++++++++++++++++++++++++++++++++++

task main()
{
	while(1 == 1)
	{
		//Driving Motor Control System - we use Theshold to deal with 'dead stick'
		if(abs(vexRT[Ch2]) > threshold ) {
			motor[leftMotor] = vexRT[Ch2] / 2;
			} else {
			motor[leftMotor]  = 0;                // Stop the left motor (cancel noise)
		}
		if(abs(vexRT[Ch3]) > threshold ){
			motor[rightMotor] = vexRT[Ch3] / 2;
			} else {
			motor[rightMotor] = 0;
		}

		//Arm Control
		if(vexRT[Btn6D] == 1 && SensorValue(armPot) < lowerLimit){
			motor[armMotor] = 40;
			} else if(vexRT[Btn6U] == 1 && SensorValue(armPot) > upperLimit) {
			motor[armMotor] = -40;
			} else {
			motor[armMotor] = 0;
		}

		// Claw Control
		if(vexRT[Btn5U] == 1){
			motor[clawMotor] = 40;
			} else if(vexRT[Btn5D] == 1) {
			motor[clawMotor] = -40;
			} else {
			motor[clawMotor] = 0;
		}

	}	// END control WHILE
} // END main TASK

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
