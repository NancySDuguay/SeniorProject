// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameViewportClient.h"
#include "MultiplayerViewportClient.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJECT_API UMultiplayerViewportClient : public UGameViewportClient
{
	GENERATED_BODY()
	
		virtual bool InputKey(FViewport* Viewport, int32 ControllerId, FKey Key, EInputEvent EventType, float AmountDepressed = 1.f, bool bGamepad = false) override;
	
	
};
