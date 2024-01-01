// Fill out your copyright notice in the Description page of Project Settings.


#include "SHudWidget.h"

#define LOCTEXT_NAMESPACE "Main Menu"

void SHudWidget::Construct(const FArguments& InArgs)
{

	const FMargin ContentPadding = FMargin(500.f, 300.f);

	const FText TitleText = LOCTEXT("GameTitle", "My GreatGame");

	ChildSlot
		[
			SNew(SOverlay)
				+ SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
					SNew(SImage)
						.ColorAndOpacity(FColor::Black)
				]

			
				+ SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
					SNew(SVerticalBox)
						+SVerticalBox::Slot()
						[
							SNew(STextBlock)
								.Text(TitleText)
						]
				]
		];

}


#undef LOCTEXT_NAMESPACE
