#pragma once
#include <string.h>
class Debug
{
public:
	static void print(double info, bool isFlash = true)
	{
		{
			if (isFlash)
			{
#ifdef Debug_M0
				SerialUSB.print(F(info));
#endif // Debug_M0

#ifdef DEBUG_MEAG2560
				Serial.print(F(info));
#endif // DEBUG_MEAG2560
			}
			else
			{
#ifdef DEBUG_M0
				SerialUSB.print(info);
#endif // DEBUG_M0

#ifdef DEBUG_MEAG2560
				Serial.print(info);
#endif // DEBUG_MEAG2560
			}
		}
	}

	static void print(String info, bool isFlash = true)
	{
		if (isFlash)
		{
#ifdef DEBUG_M0
			SerialUSB.print(F(info));
#endif // DEBUG_M0

#ifdef DEBUG_MEAG2560
			Serial.print(F(info));
#endif // DEBUG_MEAG2560
		}
		else
		{
#ifdef DEBUG_M0
			SerialUSB.print(info);
#endif // DEBUG_M0

#ifdef DEBUG_MEAG2560
			Serial.print(info);
#endif // DEBUG_MEAG2560
		}
	}
	
	static void println(String info, bool isFlash = true)
	{
		if (isFlash)
		{
#ifdef DEBUG_M0
			SerialUSB.println(F(info));
#endif // DEBUG_M0

#ifdef DEBUG_MEAG2560
			Serial.println(F(info));
#endif // DEBUG_MEAG2560
		}
		else
		{
#ifdef DEBUG_M0
			SerialUSB.println(info);
#endif // DEBUG_M0

#ifdef DEBUG_MEAG2560
			Serial.println(info);
#endif // DEBUG_MEAG2560
		}
	}

};
