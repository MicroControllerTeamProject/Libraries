#include <MyBlueTooth.h>
#include <Arduino.h>


MyBlueTooth::MyBlueTooth(uint8_t blueToothKeyPin,
	uint8_t baseTransistorPin,
	long baudRateProgramMode,
	long baudRateReceveMode,
	uint8_t rx, uint8_t tx)
{
	_hardwareSerial = nullptr;
	_blueToothKeyPin = blueToothKeyPin;
	_baseTransistorPin = baseTransistorPin;
	_softwareSerial = new SoftwareSerial(rx, tx);

	_baudRateProgramMode = baudRateProgramMode;
	_baudRateReceveMode = baudRateReceveMode;

	pinMode(_blueToothKeyPin, OUTPUT);

	pinMode(_baseTransistorPin, OUTPUT);
}

MyBlueTooth::MyBlueTooth(HardwareSerial* hardwareSerial,
	uint8_t blueToothKeyPin,
	uint8_t baseTransistorPin,
	long baudRateProgramMode,
	long baudRateReceveMode)
{
	_softwareSerial = nullptr;
	_blueToothKeyPin = blueToothKeyPin;
	_baseTransistorPin = baseTransistorPin;
	_hardwareSerial = hardwareSerial;


	_baudRateProgramMode = baudRateProgramMode;
	_baudRateReceveMode = baudRateReceveMode;

	pinMode(_blueToothKeyPin, OUTPUT);
	pinMode(_baseTransistorPin, OUTPUT);
}

MyBlueTooth::~MyBlueTooth()
{
	delete(_softwareSerial);
	delete(_hardwareSerial);
}

void MyBlueTooth::println(String message)
{
	if (_softwareSerial != NULL)
	{
		_softwareSerial->println(message);
	}
	else
	{
		//_hardwareSerial->println(message);
		_hardwareSerial->println(message);
	}
}

void MyBlueTooth::Reset_To_Master_Mode()
{
	ProgramMode();
	if (_softwareSerial != NULL)
	{
		_softwareSerial->println(F("AT+ROLE=1"));
		_softwareSerial->readString();
		delay(500);
		/*	_softwareSerial->println("AT+RESET");
			_softwareSerial->readString();
			delay(3500);*/
		_softwareSerial->println(F("AT+CMODE=0"));
		_softwareSerial->readString();
		// AT+INQM=p1,p2,p3
		// p1 - 0 inquire_mode_standad, 1 inquire_mode_rssi
		// p2 - maximum number of bluetooth devices response
		// p3 - the maximum of limited inquiring time. 1~48 (1.28s ~ 61.44s)
		// 15*1.28 = 19sec 
		//delay(3500);
		///*_softwareSerial->println("AT+RMAAD");
		//_softwareSerial->readString();
		//delay(3500);*/
		//_softwareSerial->println(F("AT+INIT"));
		//_softwareSerial->readString();
		//delay(3500);
	}
	else
	{
		_hardwareSerial->println(F("AT+ROLE=1"));
		_hardwareSerial->readString();
		delay(500);
		/*	_hardwareSerial->println("AT+RESET");
			_hardwareSerial->readString();
			delay(3500);*/
		_hardwareSerial->println(F("AT+CMODE=0"));
		_hardwareSerial->readString();
		// AT+INQM=p1,p2,p3
		// p1 - 0 inquire_mode_standad, 1 inquire_mode_rssi
		// p2 - maximum number of bluetooth devices response
		// p3 - the maximum of limited inquiring time. 1~48 (1.28s ~ 61.44s)
		// 15*1.28 = 19sec 
		//delay(3500);
		///*_softwareSerial->println("AT+RMAAD");
		//_softwareSerial->readString();
		//delay(3500);*/
		//_hardwareSerial->println(F("AT+INIT"));
		//_hardwareSerial->readString();
		//delay(3500);
	}

}

void  MyBlueTooth::Clear2()
{
	if (_softwareSerial != NULL)
	{
		//_softwareSerial->clearWriteError();
		//_hardwareSerial->flush();
		//_softwareSerial->end();
	}
	else
	{
		//_hardwareSerial->clearWriteError();
		//_hardwareSerial->flush();
		//_hardwareSerial->end();
	}
}

void  MyBlueTooth::Flush()
{
	if (_softwareSerial != NULL)
	{
		_softwareSerial->flush();
	}
	else
	{
		_hardwareSerial->flush();
	}
	
}

bool  MyBlueTooth::IsDeviceDetected(String deviceAddress, String deviceName)
{
	if (_softwareSerial != NULL)
	{
		return;
		_softwareSerial->readString();
		_softwareSerial->println(F("AT+INQM=0,5,65"));
		_softwareSerial->readString();
		//delay(2500);
		_softwareSerial->println(F("AT+INQ"));
		//delay(2500);
		if (available() > 0)
		{
			_softwareSerial->readString();
			/*String command = "AT+RNAME?" + deviceAddress + "\r\n";*/
			_softwareSerial->print("AT+RNAME?" + deviceAddress + "\r\n");
			//delay(2500);
			String phoneName = _softwareSerial->readString();
			//delay(1500);
			String command = "+RNAME:" + deviceName;
			if (phoneName.indexOf(command) > -1)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	else {
		clearBuffer();
	/*	_hardwareSerial->println(F("AT+INQM=1,5,48"));
		delay(500);*/
		//_hardwareSerial->readString();
		///*delay(500);
		//_hardwareSerial->println("AT+INQ");
		///*if (available() > 0)
		//{*/
		//	//_hardwareSerial->readString();
		//	/*String command = "AT+RNAME?" + deviceAddress + "\r\n";*/
		_hardwareSerial->print("AT+RNAME?" + deviceAddress + "\r\n");
		//todo:
		//ATTENTION:Increase time with BT version 3 or 4 can find device also when it's turned off.don't know way
		//I need to urderstand with BT version 2
		delay(500);
		String phoneName = _hardwareSerial->readString();
	
		String command = "+RNAME:" + deviceName;
		
		if (phoneName.indexOf(command) > -1)
		{
			//Serial.println("trovato");
			return true;
		}
		else
		{
			return false;
		}
		
	}
	return false;
}

void  MyBlueTooth::Reset_To_Slave_Mode()
{
	ProgramMode();
	if (_softwareSerial != NULL)
	{
		//_softwareSerial->println("AT+ORGL");
		//_softwareSerial->readString();
		delay(1500);
		//_softwareSerial->println("AT+RMAAD");
		//_softwareSerial->readString();
		//delay(1500);
		_softwareSerial->println(F("AT+ROLE=0"));
		_softwareSerial->readString();
		delay(1500);
		_softwareSerial->println("AT+UART=" + String(_baudRateReceveMode) + ",0,0");
		_softwareSerial->readString();

		delay(1500);
		ReceveMode();
		//Clear2();
	}
	else
	{
		//_hardwareSerial->println("AT+ORGL");
		//_hardwareSerial->readString();
		delay(1500);
		/*Serial.println("AT+RMAAD");
		Serial.readString();
		delay(1500);*/
		_hardwareSerial->println(F("AT+ROLE=0"));
		_hardwareSerial->readString();
		delay(1500);
		_hardwareSerial->println("AT+UART=" + String(_baudRateReceveMode) + ",0,0");
		_hardwareSerial->readString();

		delay(1500);
		ReceveMode();
		//Clear2();
	}

}

void MyBlueTooth::print(String message)
{
	if (_softwareSerial != NULL)
	{
		_softwareSerial->print(message);
	}
	else
	{
		//_hardwareSerial->print(message);
		_hardwareSerial->print(message);
	}
}

void MyBlueTooth::begin(long baudrate)
{
	if (_softwareSerial != NULL)
	{
		_softwareSerial->begin(baudrate);
	}
	else
	{
		_hardwareSerial->begin(baudrate);
	}
}

int MyBlueTooth::available()
{
	if (_softwareSerial != NULL)
	{
		//Serial.println("Leggo");
		return _softwareSerial->available();
	}
	else
	{
		//return _hardwareSerial->available();
		return _hardwareSerial->available();
	}
}

String MyBlueTooth::readString()
{
	if (_softwareSerial != NULL)
	{
		return _softwareSerial->readString();
	}
	else
	{
		//return _hardwareSerial->readString();
		return _hardwareSerial->readString();
	}
}

void MyBlueTooth::clearBuffer()
{
	if (_softwareSerial != NULL)
	{
		for (int i = 0; i < 2; i++)
		{
			String c = _softwareSerial->readString();
		}
	}
	else
	{
		for (int i = 0; i < 2; i++)
		{
			String c = _hardwareSerial->readString();
		}
	}
}

void  MyBlueTooth::ProgramMode()
{
	delay(100);
	digitalWrite(_blueToothKeyPin, HIGH);
	delay(100);
	digitalWrite(_baseTransistorPin, LOW);
	delay(100);
	digitalWrite(_baseTransistorPin, HIGH);
	delay(2000);

	this->begin(_baudRateProgramMode);
}

void MyBlueTooth::ReceveMode()
{
	digitalWrite(_blueToothKeyPin, LOW);
	digitalWrite(_baseTransistorPin, LOW);
	delay(300);
	digitalWrite(_baseTransistorPin, HIGH);
	delay(3000);
	this->begin(_baudRateReceveMode);
}

void MyBlueTooth::turnOnBlueTooth()
{
	digitalWrite(_baseTransistorPin, HIGH);
	blueToothOff = false;
	blueToothOn = true;
}

void MyBlueTooth::turnOffBlueTooth()
{
	digitalWrite(_baseTransistorPin, LOW);
	blueToothOff = true;
	blueToothOn = false;
}

bool MyBlueTooth::isBlueToothOff()
{
	return blueToothOff;
}

bool MyBlueTooth::isBlueToothOn()
{
	return blueToothOn;
}

void MyBlueTooth::SetPassword(String password)
{
	ProgramMode();
	println("AT+PSWD=" + password);
	delay(1000);
	print(readString());
	println("AT+UART=38400,0,0");
	delay(1000);
	print(readString());
	ReceveMode();
}

void MyBlueTooth::SetBlueToothName(String name)
{
	ProgramMode();
	print("AT+NAME=" + name + "\r\n");
	delay(2000);
	readString();
	ReceveMode();
}

String MyBlueTooth::GetPassword()
{
	_oldPassword.trim();
	if (_oldPassword == "")
	{
		ProgramMode();
		GetOldPassword();
		ReceveMode();
	}
	return _oldPassword;
}

String MyBlueTooth::GetOldPassword()
{
	_oldPassword = "";
	clearBuffer();
	print("AT+PSWD?\r\n");
	delay(2000);
	if (available())
	{
		String getData = readString();
		if (getData.startsWith(F("+PSWD:")))
		{
			_oldPassword = getData.substring(6);
			_oldPassword = SplitStringIndex(_oldPassword, '\r', 0);
		}
		return _oldPassword;
	}
	return _oldPassword;
}

String MyBlueTooth::SplitStringIndex(String data, char separator, int index)
{
	int found = 0;
	int strIndex[] = { 0, -1 };
	int maxIndex = data.length() - 1;

	for (int i = 0; i <= maxIndex && found <= index; i++) {
		if (data.charAt(i) == separator || i == maxIndex) {
			found++;
			strIndex[0] = strIndex[1] + 1;
			strIndex[1] = (i == maxIndex) ? i + 1 : i;
		}
	}
	return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

String MyBlueTooth::getVersion()
{
	ProgramMode();
		this->println(F("AT+VERSION?"));
		delay(1000);
		if (this->available() > 0)
		{
			ReceveMode();
			return this->readString();
		}
		ReceveMode();
}






