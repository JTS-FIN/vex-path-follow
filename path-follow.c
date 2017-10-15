#pragma config(Sensor, port2,  distanceMM,     sensorVexIQ_Distance)
#pragma config(Sensor, port3,  colorDetector,  sensorVexIQ_ColorHue)
#pragma config(Sensor, port4,  gyroSensor,     sensorNone)
#pragma config(Sensor, port5,  touchLED,       sensorNone)
#pragma config(Sensor, port8,  bumpSwitchLeft, sensorVexIQ_Touch)
#pragma config(Sensor, port9,  bumpSwitchRight, sensorVexIQ_Touch)
#pragma config(Motor,  motor1,          leftMotor,     tmotorVexIQ, openLoop, driveLeft, encoder)
#pragma config(Motor,  motor6,          rightMotor,    tmotorVexIQ, openLoop, reversed, driveRight, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#define MOVEMENT_SPEED 35


task main()
{
	int i = 0;
	setColorMode(port3, colorTypeGrayscale_Reflected);
	bool onTape = false;
	int onTapeGrayThreshold = 100;
	int notSeenTapeCount = 0;
	while (1) {
		if (i > 255) {
			i = 0;
		}
		else {
			i++;
		}
		if (getBumperValue(bumpSwitchLeft) == 1) {
			if (i % 10 == 0) { onTapeGrayThreshold--; }
		}
		else if (getBumperValue(bumpSwitchRight) == 1) {
			if (i % 10 == 0) { onTapeGrayThreshold++; }
		}
		int grayValue = getColorGrayscale(port3);
		displayTextLine(0, "Grayvalue: %d", grayValue);
		displayTextLine(1, "Threshold: %d", onTapeGrayThreshold);
		//displayTextLine(2, "i: %d", i);
		if (grayValue < onTapeGrayThreshold) {
			onTape = true;
		}
		else {
			onTape = false;
		}
		if (onTape == true) {
			// Teipill�, tiukka k��nt� oikealle
			setMotorSpeed(leftMotor, MOVEMENT_SPEED);
			setMotorSpeed(rightMotor, MOVEMENT_SPEED * -1);
			notSeenTapeCount = 0;
		}
		else {
			// Ei n�hd� teippi�, eteenp�in loivasti vasemmalle
			int leftMotorSpeed = 0;
			if (notSeenTapeCount > 200) {
				// Jyrkent�� k��ntymist� jos teippi� ei n�hty pitk��n aikaan
				leftMotorSpeed = MOVEMENT_SPEED / 4 - MOVEMENT_SPEED * notSeenTapeCount / 400;
				if (leftMotorSpeed < -100) {
					leftMotorSpeed = -100;
				}
			}
			else {
				leftMotorSpeed = MOVEMENT_SPEED / 4;
			}
			setMotorSpeed(leftMotor, leftMotorSpeed);
			setMotorSpeed(rightMotor, MOVEMENT_SPEED);
			notSeenTapeCount++;
		}
	}
}
