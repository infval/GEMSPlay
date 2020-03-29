#include <iostream>
#include "GEMSPlayLibrary.h"

uint32_t PatLength;
uint8_t* PatData;
uint32_t EnvLength;
uint8_t* EnvData;
uint32_t SeqLength;
uint8_t* SeqData;
uint32_t SmpLength;
uint8_t* SmpData;

uint8_t LoadDataFile(const char* FileName, uint32_t* RetLength, uint8_t** RetData)
{
	FILE* hFile;

	*RetLength = 0x00;
	*RetData = NULL;

	fopen_s(&hFile, FileName, "rb");
	if (hFile == NULL)
	{
		printf("Error opening %s!\n", FileName);
		return 0xFF;
	}

	fseek(hFile, 0, SEEK_END);
	*RetLength = ftell(hFile);
	if (!*RetLength)
	{
		fclose(hFile);
		return 0x01;
	}

	fseek(hFile, 0, SEEK_SET);
	*RetData = (uint8_t*)malloc(*RetLength);
	fread(*RetData, 0x01, *RetLength, hFile);

	fclose(hFile);

	return 0x00;
}

int main(int argc, char* argv[])
{
	if (argc != 5)
	{
		return 0;
	}

	PatLength = 0x00;	PatData = NULL;
	EnvLength = 0x00;	EnvData = NULL;
	SeqLength = 0x00;	SeqData = NULL;
	SmpLength = 0x00;	SmpData = NULL;

	LoadDataFile(argv[1], &PatLength, &PatData); // Patch
	LoadDataFile(argv[2], &EnvLength, &EnvData); // Envelope
	LoadDataFile(argv[3], &SeqLength, &SeqData); // Sequence
	LoadDataFile(argv[4], &SmpLength, &SmpData); // Sample File

	for (int i = 0; i < 4; i++)
	{
		bool isOK = gemsplay_init(PatData, EnvData, SeqData, SmpData);

		if (isOK)
		{
			gemsplay_play();
			getchar();
			gemsplay_pause();
			getchar();
			gemsplay_pause();
			getchar();
			gemsplay_stop();

			gemsplay_cleanup();
		}
	}

	if (PatLength && PatData != NULL)
		free(PatData);
	if (EnvLength && EnvData != NULL)
		free(EnvData);
	if (SeqLength && SeqData != NULL)
		free(SeqData);
	if (SmpLength && SmpData != NULL)
		free(SmpData);

	return 0;
}
