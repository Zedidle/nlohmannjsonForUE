// Copyright Epic Games, Inc. All Rights Reserved.

#include "nlohmannjsonBPLibrary.h"
#include "nlohmannjson.h"



const FJSON FJSON::SetField(const FString& key, const FJSON& field)
{
	string k = TCHAR_TO_UTF8(*key);
	if (data->is_object())
	{
		//(*data)[k] = json::parse(TCHAR_TO_UTF8(*field));
		(*data)[k] = *(field.data);
	}
	else if (data->is_null())
	{
		//(*data) = {
		//	{ k , TCHAR_TO_UTF8(*field) }
		//};
		(*data) = { k, *(field.data) };
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("It's not a valid type can set a key-field"));
	}
	return *this;
}



UnlohmannjsonBPLibrary::UnlohmannjsonBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

FJSON& UnlohmannjsonBPLibrary::Loadjsonfile(const FString& file)
{
	std::ifstream f(TCHAR_TO_UTF8(*file));
	if (!f) {
		UE_LOG(LogTemp, Error, TEXT("UnlohmannjsonBPLibrary::loadjsonfile load error: %s"), *file);
		return *(new FJSON());
	}

	static json j = json::parse(f);
	FJSON* J = new FJSON(j);
	f.close();
	return *J;
}

FJSON UnlohmannjsonBPLibrary::Parse(const FString& content)
{
	json j = json::parse(TCHAR_TO_UTF8(*content));
	return FJSON(j);
}

const FJSON& UnlohmannjsonBPLibrary::PrintJSON(const FJSON& J)
{
	if (J.data)
	{
		string s = (*J.data).dump();
		UE_LOG(LogTemp, Log, TEXT("Print J : %s"), UTF8_TO_TCHAR(s.c_str()));

		const FString Message = FString::Printf(TEXT("Print J : %s"), UTF8_TO_TCHAR(s.c_str()));
		if (GEngine != nullptr) {
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Turquoise, *Message);
		}
	}
	return J;
}

void UnlohmannjsonBPLibrary::PrintJSONType(const FJSON& J)
{
	string s = J.data->type_name();
	UE_LOG(LogTemp, Log, TEXT("Print J Type: %s"), UTF8_TO_TCHAR(s.c_str()));

	const FString Message = FString::Printf(TEXT("Print J Type: %s"), UTF8_TO_TCHAR(s.c_str()));
	if (GEngine != nullptr) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Emerald, *Message);
	}
}

FString UnlohmannjsonBPLibrary::JSONToString(const FJSON& J)
{
	string s = J.data->dump();
	const FString Message = FString::Printf(TEXT("%s"), UTF8_TO_TCHAR(s.c_str()));
	return Message;
}

FString UnlohmannjsonBPLibrary::GetString(const FJSON& J, const FString& key)
{
	string k = TCHAR_TO_UTF8(*key);
	if (J.data->contains(k))
	{
		json b = (*J.data)[k];

		check(b.is_string());
		if (b.is_string()) {
			string result = b.template get<string>();
			return result.c_str();
		}
		else {
			UE_LOG(LogTemp, Log, TEXT("J GetString :  No String Type ."));
			return "JSONGetString-NoStringType";
		}
	}
	else
	{
		return "Key-Absent";
	}
}

float UnlohmannjsonBPLibrary::GetFloat(const FJSON& J, const FString& key)
{
	string k = TCHAR_TO_UTF8(*key);
	json b = (*J.data)[k];
	check(b.is_number_float());
	if (b.is_number_float()) {
		float result = b.template get<float>();
		return result;
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("J GetFloat :  No Float Type ."));
		return 0.0f;
	}
}

int32 UnlohmannjsonBPLibrary::GetInteger(const FJSON& J, const FString& key)
{
	string k = TCHAR_TO_UTF8(*key);
	json b = (*J.data)[k];
	check(b.is_number_integer());
	if (b.is_number_integer()) {
		int32 result = b.template get<int32>();
		return result;
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("J GetFloat :  No Integer Type ."));
		return 0;
	}

}

bool UnlohmannjsonBPLibrary::GetBoolean(const FJSON& J, const FString& key)
{
	string k = TCHAR_TO_UTF8(*key);
	json b = (*J.data)[k];
	check(b.is_boolean());
	if (b.is_boolean()) {
		bool result = b.template get<bool>();
		return result;
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("J GetFloat :  No Boolean Type ."));
		return false;
	}

}

bool UnlohmannjsonBPLibrary::IsObjectSelf(const FJSON& J)
{
	return J.data->is_object();
}

bool UnlohmannjsonBPLibrary::IsObject(const FJSON& J, const FString& key)
{
	string k = TCHAR_TO_UTF8(*key);
	json b = (*J.data)[k];
	return b.is_object();
}

FJSON UnlohmannjsonBPLibrary::GetObject(const FJSON& J, const FString& key)
{
	string k = TCHAR_TO_UTF8(*key);
	if (J.data->contains(k))
	{
		json b = (*J.data)[k];
		check(b.is_object());
		if (b.is_object()) {
			static json result = b.template get<json>();
			return FJSON(result);
		}
		else {
			UE_LOG(LogTemp, Log, TEXT("J GetObject :  No Object Type ."));
			return FJSON();
		}
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("J GetObject :  Key-Absent."));
		return FJSON();
	}
}

bool UnlohmannjsonBPLibrary::IsArraySelf(const FJSON& J)
{
	return J.data->is_array();
}

bool UnlohmannjsonBPLibrary::IsArray(const FJSON& J, const FString& key)
{
	string k = TCHAR_TO_UTF8(*key);
	json b = (*J.data)[k];
	return b.is_array();
}

FJSON UnlohmannjsonBPLibrary::GetArray(const FJSON& J, const FString& key)
{
	string k = TCHAR_TO_UTF8(*key);
	json b = (*J.data)[k];
	check(b.is_array());
	if (b.is_array()) {
		json result = b.template get<json>();
		return FJSON(result);
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("J GetFloat :  No Array Type ."));
		return FJSON();
	}
}

FJSON UnlohmannjsonBPLibrary::GetArrayElement(const FJSON& J, int32 Index)
{
	check(J.data->is_array());
	if (J.data->is_array())
	{
		json b = (*J.data)[Index];
		return FJSON(b);
	}
	else {
		return FJSON();
	}
}

int UnlohmannjsonBPLibrary::GetArraySize(const FJSON& J)
{
	check(J.data->is_array());
	if (J.data->is_array())
	{
		return J.data->size();
	}
	else
	{
		return 0;
	}
}

FString UnlohmannjsonBPLibrary::ToString(const FJSON& J)
{
	check(J.data->is_string());
	if (J.data->is_string()) {
		string result = J.data->template get<string>();
		return result.c_str();
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("J ToString :  No String Type ."));
		return "";
	}
}

float UnlohmannjsonBPLibrary::ToFloat(const FJSON& J)
{
	check(J.data->is_number_float());
	if (J.data->is_number_float()) {
		float result = J.data->template get<float>();
		return result;
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("J ToFloat :  No Float Type ."));
		return 0.0f;
	}
}

int UnlohmannjsonBPLibrary::ToInteger(const FJSON& J)
{
	check(J.data->is_number_integer());
	if (J.data->is_number_integer()) {
		float result = J.data->template get<int>();
		return result;
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("J ToInteger :  No Integer Type ."));
		return 0;
	}
}

bool UnlohmannjsonBPLibrary::ToBoolean(const FJSON& J)
{
	check(J.data->is_boolean());
	if (J.data->is_boolean()) {
		bool result = J.data->template get<bool>();
		return result;
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("J ToBoolean :  No Boolean Type ."));
		return false;
	}
}

FJSON UnlohmannjsonBPLibrary::SetJSONField(const FJSON& J, const FString& key, const FJSON& field)
{

	string k = TCHAR_TO_UTF8(*key);
	if(J.data->is_null())
	{
		(*J.data)[k] =  *(field.data);
	}
	else
	{
		if (J.data->is_object())
		{
			(*J.data)[k] = *(field.data);
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("It's not a valid type can set a key-field"));
		}
	}
	
	return J;
}

FString UnlohmannjsonBPLibrary::BinaryDecode(const FString& Message)
{
		FString DecodedMessage = FString(UTF8_TO_TCHAR(TCHAR_TO_UTF8(*Message)));
		return DecodedMessage;
}
