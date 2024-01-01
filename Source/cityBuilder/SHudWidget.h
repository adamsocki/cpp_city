// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SlateBasics.h"
#include "Slate.h"

/**
 * 
 */
class  SHudWidget : public SCompoundWidget
{
public:
	
	SLATE_BEGIN_ARGS(SHudWidget) {}

	SLATE_ARGUMENT(TWeakObjectPtr<class AMyHUD>, OwningHUD)

	SLATE_END_ARGS()


	void Construct(const FArguments& InArgs);

	//class AMyHUD

	TWeakObjectPtr<class AMyHUD> OwningHUD;

	virtual bool SupportsKeyboardFocus() const override { return true; };
};
