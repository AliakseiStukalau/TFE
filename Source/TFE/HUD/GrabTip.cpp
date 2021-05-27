// Fill out your copyright notice in the Description page of Project Settings.


#include "GrabTip.h"

UGrabTip::UGrabTip()
{
    Id = TipId::Grab;
    TipText = FText::FromString(FString("Press F to grab it"));
}

