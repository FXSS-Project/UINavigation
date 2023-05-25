﻿// Copyright (C) 2019 Gonçalo Marques - All Rights Reserved

#include "UINavPromptWidget.h"
#include "UINavBlueprintFunctionLibrary.h"
#include "Components/TextBlock.h"
#include "Data/PromptData.h"

void UUINavPromptWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (IsValid(TitleText) && !Title.IsEmpty())
	{
		TitleText->SetText(Title);
	}

	if (IsValid(MessageText) && !Message.IsEmpty())
	{
		MessageText->SetText(Message);
	}
}

void UUINavPromptWidget::OnSelect_Implementation(UUINavComponent* Component)
{
	ProcessPromptWidgetSelected(UUINavBlueprintFunctionLibrary::CreateBinaryPromptData(IsAcceptComponent(Component)));
}

void UUINavPromptWidget::OnReturn_Implementation()
{
	ProcessPromptWidgetSelected(UUINavBlueprintFunctionLibrary::CreateBinaryPromptData(false));
}

void UUINavPromptWidget::ProcessPromptWidgetSelected(UPromptDataBase* InPromptData)
{
	if (!IsValid(InPromptData))
	{
		return;
	}

	ReturnToParent();

	Callback.Execute(InPromptData);
}

bool UUINavPromptWidget::IsAcceptComponent(UUINavComponent* Component) const
{
	return (Component == FirstComponent) == FirstComponentIsAccept;
}
