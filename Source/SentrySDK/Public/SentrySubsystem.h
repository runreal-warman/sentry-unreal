// Copyright (c) 2022 Sentry. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "SentryDataTypes.h"
#include "SentryScope.h"

#include "SentrySubsystem.generated.h"

class USentrySettings;
class USentryEvent;

UCLASS()
class SENTRYSDK_API USentrySubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	/** Initializes Sentry SDK with values specified in ProjectSettings > Plugins > SentrySDK. */
	UFUNCTION(BlueprintCallable, Category = "Sentry")
	void Initialize();

	/**
	 * Adds a breadcrumb to the current Scope.
	 *
	 * @param Message If a message is provided it’s rendered as text and the whitespace is preserved.
	 * Very long text might be abbreviated in the UI.
	 * 
	 * @param Category Categories are dotted strings that indicate what the crumb is or where it comes from.
	 * Typically it’s a module name or a descriptive string. For instance ui.click could be used to indicate that a click
	 * happened in the UI or flask could be used to indicate that the event originated in the Flask framework.
	 * 
	 * @param Type The type of breadcrumb.
	 * The default type is default which indicates no specific handling.
	 * Other types are currently http for HTTP requests and navigation for navigation events.
	 * 
	 * @param Data Data associated with this breadcrumb.
	 * Contains a sub-object whose contents depend on the breadcrumb type.
	 * Additional parameters that are unsupported by the type are rendered as a key/value table.
	 * 
	 * @param Level Breadcrumb level.
	 */
	UFUNCTION(BlueprintCallable, Category = "Sentry", meta = (AutoCreateRefTerm = "Data"))
	void AddBreadcrumb(const FString& Message, const FString& Category, const FString& Type, const TMap<FString, FString>& Data,
		ESentryLevel Level = ESentryLevel::Info);

	/**
	 * Captures the message.
	 *
	 * @param Message The message to send.
	 * @param Level The message level.
	 */
	UFUNCTION(BlueprintCallable, Category = "Sentry")
	FString CaptureMessage(const FString& Message, ESentryLevel Level = ESentryLevel::Info);

	/**
	 * Captures the message with a configurable scope.
	 * This allows modifying a scope without affecting other events.
	 * Changing message level during scope configuration will override Level parameter value.
	 *
	 * @param Message The message to send.
	 * @param OnConfigureScope The callback to configure the scope.
	 * @param Level The message level.
	 */
	UFUNCTION(BlueprintCallable, Category = "Sentry", meta = (AutoCreateRefTerm = "OnCofigureScope"))
	FString CaptureMessageWithScope(const FString& Message, const FConfigureScopeDelegate& OnConfigureScope, ESentryLevel Level = ESentryLevel::Info);

	/**
	 * Captures a manually created event and sends it to Sentry.
	 *
	 * @param Event The event to send to Sentry.
	 */
	UFUNCTION(BlueprintCallable, Category = "Sentry")
	FString CaptureEvent(USentryEvent* Event);

	/**
	 * Captures a manually created event and sends it to Sentry.
	 *
	 * @param Event The event to send to Sentry.
	 * @param Scope The scope containing event metadata.
	 */
	UFUNCTION(BlueprintCallable, Category = "Sentry")
	FString CaptureEventWithScope(USentryEvent* Event, const FConfigureScopeDelegate& OnConfigureScope);

	UFUNCTION(BlueprintCallable, Category = "Sentry")
	FString CaptureError();
};
