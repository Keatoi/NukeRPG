// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class NUKERPG_API txt_Reader
{
public:
	txt_Reader();
	~txt_Reader();


	TArray<FString> LargeStringReadIn(FString FileToReadPath);
};
