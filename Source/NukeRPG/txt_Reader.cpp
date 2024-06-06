// Fill out your copyright notice in the Description page of Project Settings.
#include "txt_Reader.h"
#include "HAL/FileManager.h"
#include <fstream>
txt_Reader::txt_Reader()
{
}

txt_Reader::~txt_Reader()
{
}

TArray<FString> txt_Reader::LargeStringReadIn(FString FileToReadPath)
{
	TArray<FString> TempList;
	const char wordSpace = ' ';
	const char newLine = '\n';
	char characters;
	FString tempText;
	

	if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*(FPaths::ProjectContentDir() + "/" + FileToReadPath))) return TempList;//checks if file exists if it doesnt then it will reurn null

	std::ifstream inputFile(*(FPaths::ProjectContentDir() + "/" + FileToReadPath));

	inputFile >> std::noskipws;//doesnt skip end of lines and spaces 
	if (inputFile.is_open())
	{
		while (inputFile)
		{
			inputFile >> characters;
			if (characters == newLine || inputFile.eof())
			{
				TempList.Add(tempText);
				tempText = {};
			}
			else
			{
				tempText += characters;
			}
		}
	}
	return TempList;//returns finished array
}
