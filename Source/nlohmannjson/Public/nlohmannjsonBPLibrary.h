// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include <nlohmann/json.hpp>
#include "Kismet/BlueprintFunctionLibrary.h"
#include "fstream"
#include <iostream>
#include <iomanip>
#include <sstream>
#include "nlohmannjsonBPLibrary.generated.h"

using namespace std;
using json = nlohmann::json;

USTRUCT(BlueprintType)
struct FJSON
{
	GENERATED_BODY()
	FJSON(){};
	FJSON(json d):data(d){};

	json data;
	operator bool() const {
		return bool(data);
	}
};



UCLASS()
class NLOHMANNJSON_API UnlohmannjsonBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	/* Load file to Make JSON */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Load JSON", Keywords = "njson"), Category = "njson")
	static FJSON Loadjsonfile(const FString& file);

	/* Parse a string to json, it's should be vliad json string. */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Prase JSON", Keywords = "njson"), Category = "njson")
	static FJSON Parse(const FString& content);

	/* Handle  UTF8 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "BinaryDecode", Keywords = "njson"), Category = "njson")
	static FString BinaryDecode(const FString& Message);

	/* Print JSON as string on Screen */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Print JSON", Keywords = "njson"), Category = "njson")
	static const FJSON& PrintJSON(const FJSON& JSON);

	/* Print JSON's datatype */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Print JSON Type", Keywords = "njson"), Category = "njson")
	static void PrintJSONType(const FJSON& JSON);

	/* Convert JSON as string */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "ToString", Keywords = "njson"), Category = "njson")
	static FString JSONToString(const FJSON& JSON);

	/* Get JSON string field with a key */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Get JSON String", Keywords = "njson"), Category = "njson")
	static FString GetString(const FJSON& JSON, const FString& str);

	/* Get JSON float field with a key */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Get JSON Float", Keywords = "njson"), Category = "njson")
	static float GetFloat(const FJSON& JSON, const FString& str);

	/* Get JSON integer field with a key */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Get JSON Integer", Keywords = "njson"), Category = "njson")
	static int32 GetInteger(const FJSON& JSON, const FString& str);

	/* Get JSON bool field with a key */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Get JSON Boolean", Keywords = "njson"), Category = "njson")
	static bool GetBoolean(const FJSON& JSON, const FString& str);
	
	/* Judge if a JSON is object type */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Is JSON Object Self", Keywords = "njson"), Category = "njson")
	static bool IsObjectSelf(const FJSON& JSON);
	/* Judge if a JSON's field with the key is object type */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Is JSON Object", Keywords = "njson"), Category = "njson")
	static bool IsObject(const FJSON& JSON, const FString& str);
	/* Get JSON's object field with a key */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Get JSON Object", Keywords = "njson"), Category = "njson")
	static FJSON GetObject(const FJSON& JSON, const FString& str);

	/* Judge if a JSON is array type */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Is JSON Array Self", Keywords = "njson"), Category = "njson")
	static bool IsArraySelf(const FJSON& JSON);
	/* Judge if a JSON's field with the key is array type */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Is JSON Array", Keywords = "njson"), Category = "njson")
	static bool IsArray(const FJSON& JSON, const FString& str);
	/* Get JSON's array field with a key */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Get JSON Array", Keywords = "njson"), Category = "njson")
	static FJSON GetArray(const FJSON& JSON, const FString& str);

	/* Get JSON array's length */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Get JSON Array Size", Keywords = "njson"), Category = "njson")
	static int GetArraySize(const FJSON& JSON);

	/* Get JSON array's element with index */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Get JSON Array Element", Keywords = "njson"), Category = "njson")
	static FJSON GetArrayElement(const FJSON& JSON, int32 Index);


	/* Convert JSON to string type data */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "JSON To Value String", Keywords = "njson"), Category = "njson")
	static FString ToString(const FJSON& JSON);

	/* Convert JSON to float type data */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "JSON To Value Float", Keywords = "njson"), Category = "njson")
	static float ToFloat(const FJSON& JSON);

	/* Convert JSON to integer type data */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "JSON To Value Integer", Keywords = "njson"), Category = "njson")
	static int ToInteger(const FJSON& JSON);

	/* Convert JSON to bool type data */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "JSON To Value Boolean", Keywords = "njson"), Category = "njson")
	static bool ToBoolean(const FJSON& JSON);
	


};
