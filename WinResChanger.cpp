/*           DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
                    Version 2, December 2004

 Copyright (C) 2012 Ijon Tichy <gztichy@lavabit.com>

 Everyone is permitted to copy and distribute verbatim or modified
 copies of this license document, and changing it is allowed as long
 as the name is changed.

            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION

  0. You just DO WHAT THE FUCK YOU WANT TO. */
// Cacodemon345's Windows Resolution Changer: Source Code.

#include <iostream>
#include "WinResChanger.h"
#include "windows.h"
#include <sstream>
#include <string>
int setScreenRes(int width, int height, int bpp, int refreshrate)
{
	auto verstruct = new OSVERSIONINFO;
	verstruct->dwOSVersionInfoSize = sizeof(verstruct);
	GetVersionEx(verstruct);
	if ((verstruct->dwMajorVersion >= 6 && verstruct->dwMinorVersion >= 2) || bpp == NULL)
	{
		if (verstruct->dwMajorVersion >= 6 && verstruct->dwMinorVersion >= 2) std::cout << "Windows 8 and later only support 32-bit color mode, ignoring bpp setting...\n";
		else printf("Bits-per-pixel not specified, defaulting to 32-bit...");
		bpp = 32;
	}
	if (height == NULL || width == NULL)
	{
		if (height == NULL)
		{
			printf("Height Not Specified!");
			return 1;
		}
		if (width == NULL)
		{
			printf("Width Not Specified!");
			return 1;
		}
	}
	auto displayStruct = new DEVMODE;
	displayStruct->dmSize = sizeof(displayStruct);
	EnumDisplaySettings(NULL, 0, displayStruct);
	displayStruct->dmBitsPerPel = bpp;
	displayStruct->dmPelsWidth = width;
	displayStruct->dmPelsHeight = height;
	displayStruct->dmDisplayFrequency = refreshrate;
	displayStruct->dmFields |= DM_BITSPERPEL;
	displayStruct->dmFields |= DM_PELSHEIGHT;
	displayStruct->dmFields |= DM_PELSWIDTH;
	displayStruct->dmFields |= DM_DISPLAYFREQUENCY;
	auto returnedvalue = ChangeDisplaySettings(displayStruct, CDS_RESET | CDS_UPDATEREGISTRY);
	if (returnedvalue == DISP_CHANGE_SUCCESSFUL)
	{
		printf("Resolution/Color Depth/Refresh Rate successfully set.");
		return 0;
	}
	else
	{
		printf("Resolution and/or Color Depth set failed.\n");
		printf("Reason: ");
		switch (returnedvalue)
		{
		case DISP_CHANGE_BADDUALVIEW:
			printf("This program does not work on DualView systems.\n");
			break;
		case DISP_CHANGE_BADMODE:
			printf("Wrong Width/Height/Color Depth/Refresh Rate specified, check again.\n");
			break;
		}
		return 1;
	}
}

int main(int argc, char* argv[])
{
	if (argc > 1 && argc < 6)
	{
		std::cout << "Setting...\nHeight: " << argv[1] << "\n";
		std::cout << "Width: " << argv[2] << "\n";
		std::cout << "Color Depth: " << argv[3] << "\n";
		std::cout << "Refresh Rate:" << argv[4] << "\n";
		int arg1, arg2, arg3, arg4;
		std::istringstream iss(argv[1]);
		iss >> arg1;
		std::istringstream iss2(argv[2]);
		iss2 >> arg2;
		std::istringstream iss3(argv[3]);
		iss3 >> arg3;
		std::istringstream iss4(argv[4]);
		iss4 >> arg4;
		return setScreenRes(arg1,arg2,arg3,arg4);
	}
	int height = GetSystemMetrics(SM_CYSCREEN);
	DISPLAY_DEVICEA *currentdisplay;
	currentdisplay = new DISPLAY_DEVICEA;
	currentdisplay->cb = sizeof(currentdisplay);
	auto hdccontext = GetDC(NULL);
	int bpp = GetDeviceCaps(hdccontext,BITSPIXEL);
	int vrefrate = GetDeviceCaps(hdccontext, VREFRESH);
	std::cout << "Screen Width: " << GetSystemMetrics(SM_CXSCREEN) << "\n";
	std::cout << "Screen Height: " << GetSystemMetrics(SM_CYSCREEN) << "\n";
	std::cout << "Color depth: " << bpp << "\n";
	std::cout << "Refresh Rate: " << vrefrate << "\n";
}
