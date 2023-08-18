// Copyright Epic Games, Inc. All Rights Reserved.

#include "nlohmannjsonBPLibrary.h"
#include "nlohmannjson.h"

UnlohmannjsonBPLibrary::UnlohmannjsonBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

FJSON UnlohmannjsonBPLibrary::loadjsonfile(const FString& file)
{
	std::ifstream f(TCHAR_TO_UTF8(*file));
	if (!f) {
		// Å×³öÒì³£
		return nullptr;
	}

	json data = json::parse(f);
	FJSON j(data);
	f.close();
	return  j;
}

const FJSON& UnlohmannjsonBPLibrary::PrintJSON(const FJSON& JSON)
{
	string s = JSON.data.dump();
	UE_LOG(LogTemp, Log, TEXT("Print JSON : %s"), UTF8_TO_TCHAR(s.c_str()));
	
	const FString Message = FString::Printf(TEXT("Print JSON : %s"), UTF8_TO_TCHAR(s.c_str()));
	if (GEngine != nullptr) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Turquoise, *Message);
	}
	return JSON;
}

void UnlohmannjsonBPLibrary::PrintJSONType(const FJSON& JSON)
{
	string s = JSON.data.type_name();
	UE_LOG(LogTemp, Log, TEXT("Print JSON Type: %s"), UTF8_TO_TCHAR(s.c_str()));

	const FString Message = FString::Printf(TEXT("Print JSON Type: %s"), UTF8_TO_TCHAR(s.c_str()));
	if (GEngine != nullptr) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Emerald, *Message);
	}
}

FString UnlohmannjsonBPLibrary::GetString(const FJSON& JSON, const FString& str)
{
	string key = TCHAR_TO_UTF8(*str);
	json b = JSON.data[key];
	check(b.is_string());
	if (b.is_string()) {
		string result = b.template get<string>();
		return result.c_str();
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("JSON GetString :  No String Type ."));
		return "JSONGetString-NoStringType";
	}
}

float UnlohmannjsonBPLibrary::GetFloat(const FJSON& JSON, const FString& str)
{
	string key = TCHAR_TO_UTF8(*str);
	json b = JSON.data[key];
	check(b.is_number_float());
	if (b.is_number_float()) {
		float result = b.template get<float>();
		return result;
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("JSON GetFloat :  No Float Type ."));
		return 0.0f;
	}
}

int32 UnlohmannjsonBPLibrary::GetInteger(const FJSON& JSON, const FString& str)
{
	string key = TCHAR_TO_UTF8(*str);
	json b = JSON.data[key];
	check(b.is_number_integer());
	if (b.is_number_integer()) {
		int32 result = b.template get<int32>();
		return result;
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("JSON GetFloat :  No Integer Type ."));
		return 0;
	}
}

bool UnlohmannjsonBPLibrary::GetBoolean(const FJSON& JSON, const FString& str)
{
	string key = TCHAR_TO_UTF8(*str);
	json b = JSON.data[key];
	check(b.is_boolean());
	if (b.is_boolean()) {
		bool result = b.template get<bool>();
		return result;
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("JSON GetFloat :  No Boolean Type ."));
		return false;
	}
}

FJSON UnlohmannjsonBPLibrary::GetObject(const FJSON& JSON, const FString& str)
{
	string key = TCHAR_TO_UTF8(*str);
	json b = JSON.data[key];
	check(b.is_object());
	if (b.is_object()) {
		json result = b.template get<json>();
		return FJSON(result);
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("JSON GetFloat :  No Object Type ."));
		return nullptr;
	}
}

FJSON UnlohmannjsonBPLibrary::GetArray(const FJSON& JSON, const FString& str)
{
	string key = TCHAR_TO_UTF8(*str);
	json b = JSON.data[key];
	check(b.is_array());
	if (b.is_array()) {
		json result = b.template get<json>();
		return FJSON(result);
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("JSON GetFloat :  No Array Type ."));
		return nullptr;
	}
}

FJSON UnlohmannjsonBPLibrary::GetArrayElement(const FJSON& JSON, int32 Index)
{
	check(JSON.data.is_array());
	if (JSON.data.is_array())
	{
		json b = JSON.data[Index];
		return FJSON(b);
	}
	else {
		return nullptr;
	}
}

FString UnlohmannjsonBPLibrary::ToString(const FJSON& JSON)
{
	check(JSON.data.is_string());
	if (JSON.data.is_string()) {
		string result = JSON.data.template get<string>();
		return result.c_str();
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("JSON ToString :  No String Type ."));
		return "";
	}
}

float UnlohmannjsonBPLibrary::ToFloat(const FJSON& JSON)
{
	check(JSON.data.is_number_float());
	if (JSON.data.is_number_float()) {
		float result = JSON.data.template get<float>();
		return result;
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("JSON ToFloat :  No Float Type ."));
		return 0.0f;
	}
}

int UnlohmannjsonBPLibrary::ToInteger(const FJSON& JSON)
{
	check(JSON.data.is_number_integer());
	if (JSON.data.is_number_integer()) {
		float result = JSON.data.template get<int>();
		return result;
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("JSON ToInteger :  No Integer Type ."));
		return 0;
	}
}

bool UnlohmannjsonBPLibrary::ToBoolean(const FJSON& JSON)
{
	check(JSON.data.is_boolean());
	if (JSON.data.is_boolean()) {
		bool result = JSON.data.template get<bool>();
		return result;
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("JSON ToBoolean :  No Boolean Type ."));
		return false;
	}
}

