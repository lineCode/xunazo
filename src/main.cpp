////////////////////////////////////////////////////////////////////////////////////////////////////
/// 
/// xunazo
/// 
/// @author   parkkh
/// @date     Wed Jul 25 18:02:40 2018
/// 
/// Copyright(C) 2018 Bandisoft, All rights reserved.
/// 
////////////////////////////////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "XStream.h"
#include "Global.h"
#include "XAzo.h"


#pragma warning(disable: 26429)


bool ExtractAzo(XReadStream* in, XWriteStream* out, uint32_t& crc32)
{
	XAzo azo;

	if (azo.Open(in, out) == false)
	{
		wprintf(L"can't open azo file\n");
		return false;
	}

	if (azo.Extract() == false)
	{
		wprintf(L"error occurred during extraction\n");
		return false;
	}

	crc32 = azo.GetCRC();

	return true;
}


bool ExtractAzo(LPCWSTR compFile, LPCWSTR extFile, uint32_t& crc32)
{
	XFileReadStream in;
	XFileWriteStream out;

	if (in.Open(compFile) == FALSE)
	{
		wprintf(L"can't open azo file:%s\n", compFile);
		return false;
	}

	if (out.Open(extFile) == FALSE)
	{
		wprintf(L"can't open out file:%s\n", extFile);
		return false;
	}

	wprintf(L"Extracting %ls -> %ls .. ", compFile, extFile);

	const ULONGLONG tick = ::GetTickCount64();

	const bool ret = ExtractAzo(&in, &out, crc32);

	wprintf(L"done(%I64dms), crc:0x%x\n", (INT64)(GetTickCount64() - tick), crc32);

	return ret;
}


int wmain(const int argc, const wchar_t * const argv[])
{
	_wsetlocale(LC_ALL, L"korean");
	
	if (argc != 3)
	{
		printf("xunazo.exe [infile.azo] [outfile.ext] \n");
		return 1;
	}

	uint32_t crc;
	ExtractAzo(argv[1], argv[2], crc);

    return 0;
}


