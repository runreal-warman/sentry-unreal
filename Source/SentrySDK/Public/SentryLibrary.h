// Copyright (c) 2022 Sentry. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"

#include "SentryDataTypes.h"

#include "SentryLibrary.generated.h"

class USentryEvent;
class USentryUser;
class USentryUserFeedback;
class USentryId;

UCLASS()
class SENTRYSDK_API USentryLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	 * Creates the event.
	 *
	 * @param Message Message to sent.
	 * @param Level Level of the event.
	 */
	UFUNCTION(BlueprintCallable, Category = "Sentry")
	static USentryEvent* CreateSentryEvent(const FString& Message, ESentryLevel Level);

	/**
	 * Creates user.
	 *
	 * @param Email Email address of the user.
	 * @param Id Id of the user.
	 * @param Username Username of the user.
	 * @param IpAddress IP address of the user.
	 * @param Data Additional arbitrary fields related to the user.
	 */
	UFUNCTION(BlueprintCallable, Category = "Sentry", meta = (AutoCreateRefTerm = "Data"))
	static USentryUser* CreateSentryUser(const FString& Email, const FString& Id, const FString& Username, const FString& IpAddress,
		const TMap<FString, FString>& Data);

	/**
	 * Creates user feedback for the event.
	 *
	 * @param EventId Id of the event to which user feedback is associated.
	 * @param Name Name of the user.
	 * @param Email Email of the user.
	 * @param Comments Comments of the user about what happened.
	 */
	UFUNCTION(BlueprintCallable, Category = "Sentry")
	static USentryUserFeedback* CreateSentryUserFeedback(USentryId* EventId, const FString& Name, const FString& Email, const FString& Comments);

	/** Crashes the application. */
	UFUNCTION(BlueprintCallable, Category = "Sentry")
	static void Crash();

	/** Generates assert. */
	UFUNCTION(BlueprintCallable, Category = "Sentry")
	static void Assert();
};
