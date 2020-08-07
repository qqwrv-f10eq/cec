/*
# natives.cpp

This source file contains the bridge between natives and implementations. I
prefer to keep the actual implementation separate. The implementation contains
no instances of `cell` or `AMX*` and is purely C++ and external library code.
The code here acts as the translation between AMX data types and native types.
*/

#include "natives.hpp"

unsigned char igor_spaces[] = { ' ', '\n', '\t' };

// this is vowel from Thai language, They will merge to character then embed color will not work
// Need encoding to "Thai (Windows 874)" for this.

// char vowel[] = { 'ั', 'ิ', 'ี', 'ึ', 'ื', 'ุ', 'ู', 'ฺ', '็', '่', '้', '๊', '๋', '์', 'ํ', '๎', 'ำ' };
unsigned char vowel[] = { 0xd1, 0xd4, 0xd5, 0xd6, 0xd7, 0xd8, 0xd9, 0xda, 0xe7, 0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, 0xd3 };

char* subc(const char* input, int offset, int len, char* dest)
{
	int input_len = strlen(input);

	if (offset + len > input_len)
	{
		return NULL;
	}
	strncpy(dest, input + offset, len);
	return dest;
}

int shiftLeft(char text[], char color[], int Pos, int shiftBy)
{
	int count = 0;
	while (shiftBy > 0) 
	{
		text[Pos + 7 - count] = text[Pos - 1 - count];
		if (!memchr(igor_spaces, text[Pos - 1 - count], sizeof(igor_spaces)))
		{
			shiftBy--;
		}
		count++;
	}
	int tempIndex = Pos - count;

	text[tempIndex] = '{';
	text[tempIndex + 1] = color[0];
	text[tempIndex + 2] = color[1];
	text[tempIndex + 3] = color[2];
	text[tempIndex + 4] = color[3];
	text[tempIndex + 5] = color[4];
	text[tempIndex + 6] = color[5];
	text[tempIndex + 7] = '}';
	return Pos - count + 7;
}

int shiftRight(char text[], char color[], int Pos, int shiftBy)
{
	int count = 0;
	while (shiftBy > 0) 
	{
		text[Pos - 7 + count] = text[Pos + 1 + count];
		if (!memchr(igor_spaces, text[Pos + 1 + count], sizeof(igor_spaces)))
		{
			shiftBy--;
		}
		count++;
	}
	int tempIndex = Pos + count;

	text[tempIndex - 7] = '{';
	text[tempIndex - 6] = color[0];
	text[tempIndex - 5] = color[1];
	text[tempIndex - 4] = color[2];
	text[tempIndex - 3] = color[3];
	text[tempIndex - 2] = color[4];
	text[tempIndex - 1] = color[5];
	text[tempIndex] = '}';

	return Pos + count;
}

int Natives::CE_Convert(AMX *amx, cell *params)
{
	int
		len = 0;

	cell *addr = NULL;
	cell *output = NULL;

	amx_GetAddr(amx, params[1], &addr);
	amx_GetAddr(amx, params[2], &output);
	amx_StrLen(addr, &len);

	if (len)
	{
		len++;
		char* text = new char[len];
		amx_GetString(text, addr, 0, len);

		int 
			next_space = -1,
			last_check = 0,
			vowel_count = 0
		;

		for (int i = 0, j = len; i < j; ++i) 
		{
			next_space = i + 7;
			if (text[i] == '{' && next_space < j && text[next_space] == '}') 
			{
				char EmbledColor[6]; 
				int local_vowel = 0;
				subc(text, i+1, 6, EmbledColor);
				for (int x = last_check + 1; x < i; x++) 
				{
					// find vowel - หาวรรณยุกต์
					if (memchr(vowel, text[x], sizeof(vowel)))
					{
						// Left Shift Color Tag - ขยับไปทางซ้าย
						vowel_count++;

						// after vowel (white space, \n, \t) - หลังวรรณยุกต์เป็นที่ว่าง
						if  (memchr(igor_spaces, text[x - 1], sizeof(igor_spaces)))
						{
							// except some vowel - ยกเว้นพวก สมบัติ, ปฏิบัติ
							if ((text[x] == 'ิ' && text[x+2] == 'ั'))
							{
								// Right Shift Color Tag - ขยับไปทางขวา
								vowel_count--;
							}
						}

					}
				}
				if (vowel_count > 0) shiftLeft(text, EmbledColor, i, vowel_count);
				else if (vowel_count < 0) shiftRight(text, EmbledColor, next_space, abs(vowel_count));
				last_check = next_space;
				i = next_space;
			}
		}
		amx_SetString(output, text, 0, 0, len);
		delete[] text;	
	}
	return 1;
}

int Natives::CE_Convert_Dialog(AMX *amx, cell *params)
{
	int
		len = 0;

	cell *addr = NULL;
	cell *output = NULL;

	amx_GetAddr(amx, params[1], &addr);
	amx_GetAddr(amx, params[2], &output);
	amx_StrLen(addr, &len);

	if (len)
	{
		len++;
		char* text = new char[len];
		amx_GetString(text, addr, 0, len);

		int 
			next_space = -1,
			last_check = 0,
			vowel_count = 0
		;

		for (int i = 0, j = len; i < j; ++i) 
		{

			next_space = i + 7;
			switch(params[3]) // Dialog Style
			{
				case 2:
					// Reset shifting for this style
					if (text[i] == '\n') 
					{
						vowel_count = 0;
						last_check = i;
					}
					break;
				case 4:
				case 5:
					// Reset shifting for this style
					if (text[i] == '\t' || text[i] == '\n')
					{
						vowel_count = 0;
						last_check = i;
					}
					break;
			}

			if (text[i] == '{' && next_space < j && text[next_space] == '}') 
			{

				char EmbledColor[6];
				subc(text, i + 1, 6, EmbledColor);
				for (int x = last_check + 1; x < i; x++) 
				{
					// find vowel - หาวรรณยุกต์
					if (memchr(vowel, text[x], sizeof(vowel)))
					{
						// Left Shift Color Tag - ขยับไปทางซ้าย
						vowel_count++;

						// after vowel (white space, \n, \t) - หลังวรรณยุกต์เป็นที่ว่าง
						if  (memchr(igor_spaces, text[x - 1], sizeof(igor_spaces)))
						{
							// except some vowel - ยกเว้นพวก สมบัติ, ปฏิบัติ
							if ((text[x] == 'ิ' && text[x+2] == 'ั'))
							{
								// Right Shift Color Tag - ขยับไปทางขวา
								vowel_count--;
							}
						}

					}
				}
				if (vowel_count > 0) 
				{
					shiftLeft(text, EmbledColor, i, vowel_count);
				}
				else if (vowel_count < 0) 
				{
					shiftRight(text, EmbledColor, next_space, vowel_count * -1);
				}
				last_check = next_space;
				i = next_space;
			}

		}
		amx_SetString(output, text, 0, 0, len);
		delete[] text;

	}
	return 1;
}

int Natives::CE_CountTag(AMX *amx, cell *params)
{
	int
		len = 0,
		tag_found = 0;

	cell *addr = NULL;

	amx_GetAddr(amx, params[1], &addr);
	amx_StrLen(addr, &len);

	if (len)
	{
		len++; // for \0
		char* text = new char[len];
		amx_GetString(text, addr, 0, len);

		int next_space = -1;
		for (int i = 0, j = len; i < j; ++i) 
		{
			next_space = i + 7;
			if (text[i] == '{' && next_space < j && text[next_space] == '}') 
			{
				tag_found++;
				i = next_space;
			}
		}
		delete[] text;
	}
	return tag_found;
}

int Natives::CE_CountVowel(AMX *amx, cell *params)
{
	int
		len = 0,
		tag_found = 0;

	cell *addr = NULL;

	amx_GetAddr(amx, params[1], &addr);
	amx_StrLen(addr, &len);

	if (len)
	{
		len++; // for \0
		char* text = new char[len];
		amx_GetString(text, addr, 0, len);

		for (int i = 0, j = len; i < j; ++i) 
		{
			if (memchr(vowel, text[i], sizeof(vowel)))
			{
				tag_found++;
			}
		}
		delete[] text;
	}
	return tag_found;
}