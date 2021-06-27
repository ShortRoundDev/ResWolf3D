#pragma once

#include <windows.h>
#include <stdint.h>

namespace ResWolf
{
	class PngTextureLoader
	{
		static HRESULT loadTextureDataFromFile(
			_In_z_ LPWSTR fileName,
			_Out_ uint8_t* bitData,
			_Out_ int* imgWidth,
			_Out_ int* imgHeight
		);
	};
}