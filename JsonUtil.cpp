#include "JsonUtil.h"

#include "skse/PluginAPI.h"
#include "skse/GameAPI.h"
#include "skse/GameTypes.h"
#include "skse/PapyrusNativeFunctions.h"
#include "skse/PapyrusArgs.h"

#include "External.h"

namespace JsonUtil {
	using namespace External;

	bool SaveJson(StaticFunctionTag* base, BSFixedString name, bool styled){
		ExternalFile* file = GetFile(name.data);
		if (!file)
			return false;
		return file->SaveFile(styled);
	}
	bool LoadJson(StaticFunctionTag* base, BSFixedString name){
		ExternalFile* file = GetFile(name.data);
		if (!file)
			return false;
		return file->LoadFile();
	}

	void ClearAll(StaticFunctionTag* base, BSFixedString name){
		ExternalFile* file = GetFile(name.data);
		return file->ClearAll();
	}

	template <typename T>
	T SetValue(StaticFunctionTag* base, BSFixedString name, BSFixedString key, T value) {
		ExternalFile* file = GetFile(name.data);
		return file->SetValue<T>(key.data, value);
	}

	template <typename T>
	T GetValue(StaticFunctionTag* base, BSFixedString name, BSFixedString key, T missing) {
		ExternalFile* file = GetFile(name.data);
		return file->GetValue<T>(key.data, missing);
	}

	template <typename T>
	T AdjustValue(StaticFunctionTag* base, BSFixedString name, BSFixedString key, T value) {
		ExternalFile* file = GetFile(name.data);
		return file->AdjustValue<T>(key.data, value);
	}

	template <typename T>
	bool UnsetValue(StaticFunctionTag* base, BSFixedString name, BSFixedString key) {
		ExternalFile* file = GetFile(name.data);
		return file->UnsetValue<T>(key.data);
	}

	template <typename T>
	bool HasValue(StaticFunctionTag* base, BSFixedString name, BSFixedString key) {
		ExternalFile* file = GetFile(name.data);
		return file->HasValue<T>(key.data);
	}

	template <typename T>
	UInt32 ListAdd(StaticFunctionTag* base, BSFixedString name, BSFixedString key, T value, bool allowDuplicate) {
		ExternalFile* file = GetFile(name.data);
		return file->ListAdd<T>(key.data, value, allowDuplicate);
	}

	template <typename T>
	T ListGet(StaticFunctionTag* base, BSFixedString name, BSFixedString key, UInt32 index) {
		ExternalFile* file = GetFile(name.data);
		return file->ListGet<T>(key.data, index);
	}

	template <typename T>
	T ListSet(StaticFunctionTag* base, BSFixedString name, BSFixedString key, UInt32 index, T value) {
		ExternalFile* file = GetFile(name.data);
		return file->ListSet<T>(key.data, index, value);
	}

	template <typename T>
	T ListAdjust(StaticFunctionTag* base, BSFixedString name, BSFixedString key, UInt32 index, T value) {
		ExternalFile* file = GetFile(name.data);
		return file->ListAdjust<T>(key.data, index, value);
	}

	template <typename T>
	UInt32 ListRemove(StaticFunctionTag* base, BSFixedString name, BSFixedString key, T value, bool allInstances) {
		ExternalFile* file = GetFile(name.data);
		return file->ListRemove<T>(key.data, value, allInstances);
	}

	template <typename T>
	bool ListRemoveAt(StaticFunctionTag* base, BSFixedString name, BSFixedString key, UInt32 index) {
		ExternalFile* file = GetFile(name.data);
		return file->ListRemoveAt<T>(key.data, index);
	}

	template <typename T>
	bool ListInsertAt(StaticFunctionTag* base, BSFixedString name, BSFixedString key, UInt32 index, T value) {
		ExternalFile* file = GetFile(name.data);
		return file->ListInsertAt<T>(key.data, index, value);
	}

	template <typename T>
	UInt32 ListClear(StaticFunctionTag* base, BSFixedString name, BSFixedString key) {
		ExternalFile* file = GetFile(name.data);
		return file->ListClear<T>(key.data);
	}

	template <typename T>
	UInt32 ListCount(StaticFunctionTag* base, BSFixedString name, BSFixedString key) {
		ExternalFile* file = GetFile(name.data);
		return file->ListCount<T>(key.data);
	}

	template <typename T>
	SInt32 ListFind(StaticFunctionTag* base, BSFixedString name, BSFixedString key, T value) {
		ExternalFile* file = GetFile(name.data);
		return file->ListFind<T>(key.data, value);
	}

	template <typename T>
	bool ListHas(StaticFunctionTag* base, BSFixedString name, BSFixedString key, T value) {
		ExternalFile* file = GetFile(name.data);
		return file->ListHas<T>(key.data, value);
	}

	template <typename T>
	void ListSlice(StaticFunctionTag* base, BSFixedString name, BSFixedString key, VMArray<T> Output, UInt32 startIndex){
		if (!Output.arr || Output.Length() < 1)
			return;
		ExternalFile* file = GetFile(name.data);
		file->ListSlice<T>(key.data, Output, startIndex);
	}

	template <typename T>
	SInt32 ListResize(StaticFunctionTag* base, BSFixedString name, BSFixedString key, UInt32 length, T filler) {
		if (length > 500)
			return 0;
		ExternalFile* file = GetFile(name.data);
		return file->ListResize(key.data, length, filler);
	}

	template <typename T>
	bool ListCopy(StaticFunctionTag* base, BSFixedString name, BSFixedString key, VMArray<T> Input) {
		if (!Input.arr || Input.Length() < 1)
			return false;
		ExternalFile* file = GetFile(name.data);
		return file->ListCopy(key.data, Input);
	}


	void RegisterFuncs(VMClassRegistry* registry){

		// File manipulation
		registry->RegisterFunction(new NativeFunction2<StaticFunctionTag, bool, BSFixedString, bool>("Save", "JsonUtil", SaveJson, registry));
		registry->SetFunctionFlags("JsonUtil", "Save", VMClassRegistry::kFunctionFlag_NoWait);

		registry->RegisterFunction(new NativeFunction1<StaticFunctionTag, bool, BSFixedString>("Load", "JsonUtil", LoadJson, registry));
		registry->SetFunctionFlags("JsonUtil", "Load", VMClassRegistry::kFunctionFlag_NoWait);

		registry->RegisterFunction(new NativeFunction1<StaticFunctionTag, void, BSFixedString>("ClearAll", "JsonUtil", ClearAll, registry));
		registry->SetFunctionFlags("JsonUtil", "ClearAll", VMClassRegistry::kFunctionFlag_NoWait);

		// Global  values
		registry->RegisterFunction(new NativeFunction3<StaticFunctionTag, SInt32, BSFixedString, BSFixedString, SInt32>("SetIntValue", "JsonUtil", SetValue<SInt32>, registry));
		registry->RegisterFunction(new NativeFunction3<StaticFunctionTag, float, BSFixedString, BSFixedString, float>("SetFloatValue", "JsonUtil", SetValue<float>, registry));
		registry->RegisterFunction(new NativeFunction3<StaticFunctionTag, BSFixedString, BSFixedString, BSFixedString, BSFixedString>("SetStringValue", "JsonUtil", SetValue<BSFixedString>, registry));
		registry->RegisterFunction(new NativeFunction3<StaticFunctionTag, TESForm*, BSFixedString, BSFixedString, TESForm*>("SetFormValue", "JsonUtil", SetValue<TESForm*>, registry));
		registry->SetFunctionFlags("JsonUtil", "SetIntValue", VMClassRegistry::kFunctionFlag_NoWait);
		registry->SetFunctionFlags("JsonUtil", "SetFloatValue", VMClassRegistry::kFunctionFlag_NoWait);
		registry->SetFunctionFlags("JsonUtil", "SetStringValue", VMClassRegistry::kFunctionFlag_NoWait);
		registry->SetFunctionFlags("JsonUtil", "SetFormValue", VMClassRegistry::kFunctionFlag_NoWait);

		registry->RegisterFunction(new NativeFunction3<StaticFunctionTag, SInt32, BSFixedString, BSFixedString, SInt32>("GetIntValue", "JsonUtil", GetValue<SInt32>, registry));
		registry->RegisterFunction(new NativeFunction3<StaticFunctionTag, float, BSFixedString, BSFixedString, float>("GetFloatValue", "JsonUtil", GetValue<float>, registry));
		registry->RegisterFunction(new NativeFunction3<StaticFunctionTag, BSFixedString, BSFixedString, BSFixedString, BSFixedString>("GetStringValue", "JsonUtil", GetValue<BSFixedString>, registry));
		registry->RegisterFunction(new NativeFunction3<StaticFunctionTag, TESForm*, BSFixedString, BSFixedString, TESForm*>("GetFormValue", "JsonUtil", GetValue<TESForm*>, registry));
		registry->SetFunctionFlags("JsonUtil", "GetIntValue", VMClassRegistry::kFunctionFlag_NoWait);
		registry->SetFunctionFlags("JsonUtil", "GetFloatValue", VMClassRegistry::kFunctionFlag_NoWait);
		registry->SetFunctionFlags("JsonUtil", "GetStringValue", VMClassRegistry::kFunctionFlag_NoWait);
		registry->SetFunctionFlags("JsonUtil", "GetFormValue", VMClassRegistry::kFunctionFlag_NoWait);

		registry->RegisterFunction(new NativeFunction3<StaticFunctionTag, SInt32, BSFixedString, BSFixedString, SInt32>("AdjustIntValue", "JsonUtil", AdjustValue<SInt32>, registry));
		registry->RegisterFunction(new NativeFunction3<StaticFunctionTag, float, BSFixedString, BSFixedString, float>("AdjustFloatValue", "JsonUtil", AdjustValue<float>, registry));
		registry->SetFunctionFlags("JsonUtil", "AdjustIntValue", VMClassRegistry::kFunctionFlag_NoWait);
		registry->SetFunctionFlags("JsonUtil", "AdjustFloatValue", VMClassRegistry::kFunctionFlag_NoWait);

		registry->RegisterFunction(new NativeFunction2<StaticFunctionTag, bool, BSFixedString, BSFixedString>("UnsetIntValue", "JsonUtil", UnsetValue<SInt32>, registry));
		registry->RegisterFunction(new NativeFunction2<StaticFunctionTag, bool, BSFixedString, BSFixedString>("UnsetFloatValue", "JsonUtil", UnsetValue<float>, registry));
		registry->RegisterFunction(new NativeFunction2<StaticFunctionTag, bool, BSFixedString, BSFixedString>("UnsetStringValue", "JsonUtil", UnsetValue<BSFixedString>, registry));
		registry->RegisterFunction(new NativeFunction2<StaticFunctionTag, bool, BSFixedString, BSFixedString>("UnsetFormValue", "JsonUtil", UnsetValue<TESForm*>, registry));
		registry->SetFunctionFlags("JsonUtil", "UnsetIntValue", VMClassRegistry::kFunctionFlag_NoWait);
		registry->SetFunctionFlags("JsonUtil", "UnsetFloatValue", VMClassRegistry::kFunctionFlag_NoWait);
		registry->SetFunctionFlags("JsonUtil", "UnsetStringValue", VMClassRegistry::kFunctionFlag_NoWait);
		registry->SetFunctionFlags("JsonUtil", "UnsetFormValue", VMClassRegistry::kFunctionFlag_NoWait);

		registry->RegisterFunction(new NativeFunction2<StaticFunctionTag, bool, BSFixedString, BSFixedString>("HasIntValue", "JsonUtil", HasValue<SInt32>, registry));
		registry->RegisterFunction(new NativeFunction2<StaticFunctionTag, bool, BSFixedString, BSFixedString>("HasFloatValue", "JsonUtil", HasValue<float>, registry));
		registry->RegisterFunction(new NativeFunction2<StaticFunctionTag, bool, BSFixedString, BSFixedString>("HasStringValue", "JsonUtil", HasValue<BSFixedString>, registry));
		registry->RegisterFunction(new NativeFunction2<StaticFunctionTag, bool, BSFixedString, BSFixedString>("HasFormValue", "JsonUtil", HasValue<TESForm*>, registry));
		registry->SetFunctionFlags("JsonUtil", "HasIntValue", VMClassRegistry::kFunctionFlag_NoWait);
		registry->SetFunctionFlags("JsonUtil", "HasFloatValue", VMClassRegistry::kFunctionFlag_NoWait);
		registry->SetFunctionFlags("JsonUtil", "HasStringValue", VMClassRegistry::kFunctionFlag_NoWait);
		registry->SetFunctionFlags("JsonUtil", "HasFormValue", VMClassRegistry::kFunctionFlag_NoWait);

		// Global  lists
		registry->RegisterFunction(new NativeFunction4<StaticFunctionTag, UInt32, BSFixedString, BSFixedString, SInt32, bool>("IntListAdd", "JsonUtil", ListAdd<SInt32>, registry));
		registry->RegisterFunction(new NativeFunction4<StaticFunctionTag, UInt32, BSFixedString, BSFixedString, float, bool>("FloatListAdd", "JsonUtil", ListAdd<float>, registry));
		registry->RegisterFunction(new NativeFunction4<StaticFunctionTag, UInt32, BSFixedString, BSFixedString, BSFixedString, bool>("StringListAdd", "JsonUtil", ListAdd<BSFixedString>, registry));
		registry->RegisterFunction(new NativeFunction4<StaticFunctionTag, UInt32, BSFixedString, BSFixedString, TESForm*, bool>("FormListAdd", "JsonUtil", ListAdd<TESForm*>, registry));
		registry->SetFunctionFlags("JsonUtil", "IntListAdd", VMClassRegistry::kFunctionFlag_NoWait);
		registry->SetFunctionFlags("JsonUtil", "FloatListAdd", VMClassRegistry::kFunctionFlag_NoWait);
		registry->SetFunctionFlags("JsonUtil", "StringListAdd", VMClassRegistry::kFunctionFlag_NoWait);
		registry->SetFunctionFlags("JsonUtil", "FormListAdd", VMClassRegistry::kFunctionFlag_NoWait);

		registry->RegisterFunction(new NativeFunction3<StaticFunctionTag, SInt32, BSFixedString, BSFixedString, UInt32>("IntListGet", "JsonUtil", ListGet<SInt32>, registry));
		registry->RegisterFunction(new NativeFunction3<StaticFunctionTag, float, BSFixedString, BSFixedString, UInt32>("FloatListGet", "JsonUtil", ListGet<float>, registry));
		registry->RegisterFunction(new NativeFunction3<StaticFunctionTag, BSFixedString, BSFixedString, BSFixedString, UInt32>("StringListGet", "JsonUtil", ListGet<BSFixedString>, registry));
		registry->RegisterFunction(new NativeFunction3<StaticFunctionTag, TESForm*, BSFixedString, BSFixedString, UInt32>("FormListGet", "JsonUtil", ListGet<TESForm*>, registry));
		registry->SetFunctionFlags("JsonUtil", "IntListGet", VMClassRegistry::kFunctionFlag_NoWait);
		registry->SetFunctionFlags("JsonUtil", "FloatListGet", VMClassRegistry::kFunctionFlag_NoWait);
		registry->SetFunctionFlags("JsonUtil", "StringListGet", VMClassRegistry::kFunctionFlag_NoWait);
		registry->SetFunctionFlags("JsonUtil", "FormListGet", VMClassRegistry::kFunctionFlag_NoWait);

		registry->RegisterFunction(new NativeFunction4<StaticFunctionTag, SInt32, BSFixedString, BSFixedString, UInt32, SInt32>("IntListAdjust", "JsonUtil", ListAdjust<SInt32>, registry));
		registry->RegisterFunction(new NativeFunction4<StaticFunctionTag, float, BSFixedString, BSFixedString, UInt32, float>("FloatListAdjust", "JsonUtil", ListAdjust<float>, registry));
		registry->SetFunctionFlags("JsonUtil", "IntListAdjust", VMClassRegistry::kFunctionFlag_NoWait);
		registry->SetFunctionFlags("JsonUtil", "FloatListAdjust", VMClassRegistry::kFunctionFlag_NoWait);

		registry->RegisterFunction(new NativeFunction4<StaticFunctionTag, SInt32, BSFixedString, BSFixedString, UInt32, SInt32>("IntListSet", "JsonUtil", ListSet<SInt32>, registry));
		registry->RegisterFunction(new NativeFunction4<StaticFunctionTag, float, BSFixedString, BSFixedString, UInt32, float>("FloatListSet", "JsonUtil", ListSet<float>, registry));
		registry->RegisterFunction(new NativeFunction4<StaticFunctionTag, BSFixedString, BSFixedString, BSFixedString, UInt32, BSFixedString>("StringListSet", "JsonUtil", ListSet<BSFixedString>, registry));
		registry->RegisterFunction(new NativeFunction4<StaticFunctionTag, TESForm*, BSFixedString, BSFixedString, UInt32, TESForm*>("FormListSet", "JsonUtil", ListSet<TESForm*>, registry));
		registry->SetFunctionFlags("JsonUtil", "IntListSet", VMClassRegistry::kFunctionFlag_NoWait);
		registry->SetFunctionFlags("JsonUtil", "FloatListSet", VMClassRegistry::kFunctionFlag_NoWait);
		registry->SetFunctionFlags("JsonUtil", "StringListSet", VMClassRegistry::kFunctionFlag_NoWait);
		registry->SetFunctionFlags("JsonUtil", "FormListSet", VMClassRegistry::kFunctionFlag_NoWait);

		registry->RegisterFunction(new NativeFunction4<StaticFunctionTag, UInt32, BSFixedString, BSFixedString, SInt32, bool>("IntListRemove", "JsonUtil", ListRemove<SInt32>, registry));
		registry->RegisterFunction(new NativeFunction4<StaticFunctionTag, UInt32, BSFixedString, BSFixedString, float, bool>("FloatListRemove", "JsonUtil", ListRemove<float>, registry));
		registry->RegisterFunction(new NativeFunction4<StaticFunctionTag, UInt32, BSFixedString, BSFixedString, BSFixedString, bool>("StringListRemove", "JsonUtil", ListRemove<BSFixedString>, registry));
		registry->RegisterFunction(new NativeFunction4<StaticFunctionTag, UInt32, BSFixedString, BSFixedString, TESForm*, bool>("FormListRemove", "JsonUtil", ListRemove<TESForm*>, registry));
		registry->SetFunctionFlags("JsonUtil", "IntListRemove", VMClassRegistry::kFunctionFlag_NoWait);
		registry->SetFunctionFlags("JsonUtil", "FloatListRemove", VMClassRegistry::kFunctionFlag_NoWait);
		registry->SetFunctionFlags("JsonUtil", "StringListRemove", VMClassRegistry::kFunctionFlag_NoWait);
		registry->SetFunctionFlags("JsonUtil", "FormListRemove", VMClassRegistry::kFunctionFlag_NoWait);

		registry->RegisterFunction(new NativeFunction3<StaticFunctionTag, bool, BSFixedString, BSFixedString, UInt32>("IntListRemoveAt", "JsonUtil", ListRemoveAt<SInt32>, registry));
		registry->RegisterFunction(new NativeFunction3<StaticFunctionTag, bool, BSFixedString, BSFixedString, UInt32>("FloatListRemoveAt", "JsonUtil", ListRemoveAt<float>, registry));
		registry->RegisterFunction(new NativeFunction3<StaticFunctionTag, bool, BSFixedString, BSFixedString, UInt32>("StringListRemoveAt", "JsonUtil", ListRemoveAt<BSFixedString>, registry));
		registry->RegisterFunction(new NativeFunction3<StaticFunctionTag, bool, BSFixedString, BSFixedString, UInt32>("FormListRemoveAt", "JsonUtil", ListRemoveAt<TESForm*>, registry));
		registry->SetFunctionFlags("JsonUtil", "IntListRemoveAt", VMClassRegistry::kFunctionFlag_NoWait);
		registry->SetFunctionFlags("JsonUtil", "FloatListRemoveAt", VMClassRegistry::kFunctionFlag_NoWait);
		registry->SetFunctionFlags("JsonUtil", "StringListRemoveAt", VMClassRegistry::kFunctionFlag_NoWait);
		registry->SetFunctionFlags("JsonUtil", "FormListRemoveAt", VMClassRegistry::kFunctionFlag_NoWait);

		registry->RegisterFunction(new NativeFunction4<StaticFunctionTag, bool, BSFixedString, BSFixedString, UInt32, SInt32>("IntListInsertAt", "JsonUtil", ListInsertAt<SInt32>, registry));
		registry->RegisterFunction(new NativeFunction4<StaticFunctionTag, bool, BSFixedString, BSFixedString, UInt32, float>("FloatListInsertAt", "JsonUtil", ListInsertAt<float>, registry));
		registry->RegisterFunction(new NativeFunction4<StaticFunctionTag, bool, BSFixedString, BSFixedString, UInt32, BSFixedString>("StringListInsertAt", "JsonUtil", ListInsertAt<BSFixedString>, registry));
		registry->RegisterFunction(new NativeFunction4<StaticFunctionTag, bool, BSFixedString, BSFixedString, UInt32, TESForm*>("FormListInsertAt", "JsonUtil", ListInsertAt<TESForm*>, registry));
		registry->SetFunctionFlags("JsonUtil", "IntListInsertAt", VMClassRegistry::kFunctionFlag_NoWait);
		registry->SetFunctionFlags("JsonUtil", "FloatListInsertAt", VMClassRegistry::kFunctionFlag_NoWait);
		registry->SetFunctionFlags("JsonUtil", "StringListInsertAt", VMClassRegistry::kFunctionFlag_NoWait);
		registry->SetFunctionFlags("JsonUtil", "FormListInsertAt", VMClassRegistry::kFunctionFlag_NoWait);

		registry->RegisterFunction(new NativeFunction2<StaticFunctionTag, UInt32, BSFixedString, BSFixedString>("IntListClear", "JsonUtil", ListClear<SInt32>, registry));
		registry->RegisterFunction(new NativeFunction2<StaticFunctionTag, UInt32, BSFixedString, BSFixedString>("FloatListClear", "JsonUtil", ListClear<float>, registry));
		registry->RegisterFunction(new NativeFunction2<StaticFunctionTag, UInt32, BSFixedString, BSFixedString>("StringListClear", "JsonUtil", ListClear<BSFixedString>, registry));
		registry->RegisterFunction(new NativeFunction2<StaticFunctionTag, UInt32, BSFixedString, BSFixedString>("FormListClear", "JsonUtil", ListClear<TESForm*>, registry));
		registry->SetFunctionFlags("JsonUtil", "IntListClear", VMClassRegistry::kFunctionFlag_NoWait);
		registry->SetFunctionFlags("JsonUtil", "FloatListClear", VMClassRegistry::kFunctionFlag_NoWait);
		registry->SetFunctionFlags("JsonUtil", "StringListClear", VMClassRegistry::kFunctionFlag_NoWait);
		registry->SetFunctionFlags("JsonUtil", "FormListClear", VMClassRegistry::kFunctionFlag_NoWait);

		registry->RegisterFunction(new NativeFunction2<StaticFunctionTag, UInt32, BSFixedString, BSFixedString>("IntListCount", "JsonUtil", ListCount<SInt32>, registry));
		registry->RegisterFunction(new NativeFunction2<StaticFunctionTag, UInt32, BSFixedString, BSFixedString>("FloatListCount", "JsonUtil", ListCount<float>, registry));
		registry->RegisterFunction(new NativeFunction2<StaticFunctionTag, UInt32, BSFixedString, BSFixedString>("StringListCount", "JsonUtil", ListCount<BSFixedString>, registry));
		registry->RegisterFunction(new NativeFunction2<StaticFunctionTag, UInt32, BSFixedString, BSFixedString>("FormListCount", "JsonUtil", ListCount<TESForm*>, registry));
		registry->SetFunctionFlags("JsonUtil", "IntListCount", VMClassRegistry::kFunctionFlag_NoWait);
		registry->SetFunctionFlags("JsonUtil", "FloatListCount", VMClassRegistry::kFunctionFlag_NoWait);
		registry->SetFunctionFlags("JsonUtil", "StringListCount", VMClassRegistry::kFunctionFlag_NoWait);
		registry->SetFunctionFlags("JsonUtil", "FormListCount", VMClassRegistry::kFunctionFlag_NoWait);

		registry->RegisterFunction(new NativeFunction3<StaticFunctionTag, SInt32, BSFixedString, BSFixedString, SInt32>("IntListFind", "JsonUtil", ListFind<SInt32>, registry));
		registry->RegisterFunction(new NativeFunction3<StaticFunctionTag, SInt32, BSFixedString, BSFixedString, float>("FloatListFind", "JsonUtil", ListFind<float>, registry));
		registry->RegisterFunction(new NativeFunction3<StaticFunctionTag, SInt32, BSFixedString, BSFixedString, BSFixedString>("StringListFind", "JsonUtil", ListFind<BSFixedString>, registry));
		registry->RegisterFunction(new NativeFunction3<StaticFunctionTag, SInt32, BSFixedString, BSFixedString, TESForm*>("FormListFind", "JsonUtil", ListFind<TESForm*>, registry));
		registry->SetFunctionFlags("JsonUtil", "IntListFind", VMClassRegistry::kFunctionFlag_NoWait);
		registry->SetFunctionFlags("JsonUtil", "FloatListFind", VMClassRegistry::kFunctionFlag_NoWait);
		registry->SetFunctionFlags("JsonUtil", "StringListFind", VMClassRegistry::kFunctionFlag_NoWait);
		registry->SetFunctionFlags("JsonUtil", "FormListFind", VMClassRegistry::kFunctionFlag_NoWait);

		registry->RegisterFunction(new NativeFunction3<StaticFunctionTag, bool, BSFixedString, BSFixedString, SInt32>("IntListHas", "JsonUtil", ListHas<SInt32>, registry));
		registry->RegisterFunction(new NativeFunction3<StaticFunctionTag, bool, BSFixedString, BSFixedString, float>("FloatListHas", "JsonUtil", ListHas<float>, registry));
		registry->RegisterFunction(new NativeFunction3<StaticFunctionTag, bool, BSFixedString, BSFixedString, BSFixedString>("StringListHas", "JsonUtil", ListHas<BSFixedString>, registry));
		registry->RegisterFunction(new NativeFunction3<StaticFunctionTag, bool, BSFixedString, BSFixedString, TESForm*>("FormListHas", "JsonUtil", ListHas<TESForm*>, registry));
		registry->SetFunctionFlags("JsonUtil", "IntListHas", VMClassRegistry::kFunctionFlag_NoWait);
		registry->SetFunctionFlags("JsonUtil", "FloatListHas", VMClassRegistry::kFunctionFlag_NoWait);
		registry->SetFunctionFlags("JsonUtil", "StringListHas", VMClassRegistry::kFunctionFlag_NoWait);
		registry->SetFunctionFlags("JsonUtil", "FormListHas", VMClassRegistry::kFunctionFlag_NoWait);

		registry->RegisterFunction(new NativeFunction4<StaticFunctionTag, void, BSFixedString, BSFixedString, VMArray<SInt32>, UInt32>("IntListSlice", "JsonUtil", ListSlice<SInt32>, registry));
		registry->RegisterFunction(new NativeFunction4<StaticFunctionTag, void, BSFixedString, BSFixedString, VMArray<float>, UInt32>("FloatListSlice", "JsonUtil", ListSlice<float>, registry));
		registry->RegisterFunction(new NativeFunction4<StaticFunctionTag, void, BSFixedString, BSFixedString, VMArray<BSFixedString>, UInt32>("StringListSlice", "JsonUtil", ListSlice<BSFixedString>, registry));
		registry->RegisterFunction(new NativeFunction4<StaticFunctionTag, void, BSFixedString, BSFixedString, VMArray<TESForm*>, UInt32>("FormListSlice", "JsonUtil", ListSlice<TESForm*>, registry));
		registry->SetFunctionFlags("JsonUtil", "IntListSlice", VMClassRegistry::kFunctionFlag_NoWait);
		registry->SetFunctionFlags("JsonUtil", "FloatListSlice", VMClassRegistry::kFunctionFlag_NoWait);
		registry->SetFunctionFlags("JsonUtil", "StringListSlice", VMClassRegistry::kFunctionFlag_NoWait);
		registry->SetFunctionFlags("JsonUtil", "FormListSlice", VMClassRegistry::kFunctionFlag_NoWait);

		registry->RegisterFunction(new NativeFunction4 <StaticFunctionTag, SInt32, BSFixedString, BSFixedString, UInt32, SInt32>("IntListResize", "JsonUtil", ListResize<SInt32>, registry));
		registry->RegisterFunction(new NativeFunction4 <StaticFunctionTag, SInt32, BSFixedString, BSFixedString, UInt32, float>("FloatListResize", "JsonUtil", ListResize<float>, registry));
		registry->RegisterFunction(new NativeFunction4 <StaticFunctionTag, SInt32, BSFixedString, BSFixedString, UInt32, BSFixedString>("StringListResize", "JsonUtil", ListResize<BSFixedString>, registry));
		registry->RegisterFunction(new NativeFunction4 <StaticFunctionTag, SInt32, BSFixedString, BSFixedString, UInt32, TESForm*>("FormListResize", "JsonUtil", ListResize<TESForm*>, registry));
		registry->SetFunctionFlags("JsonUtil", "IntListResize", VMClassRegistry::kFunctionFlag_NoWait);
		registry->SetFunctionFlags("JsonUtil", "FloatListResize", VMClassRegistry::kFunctionFlag_NoWait);
		registry->SetFunctionFlags("JsonUtil", "StringListResize", VMClassRegistry::kFunctionFlag_NoWait);
		registry->SetFunctionFlags("JsonUtil", "FormListResize", VMClassRegistry::kFunctionFlag_NoWait);

		registry->RegisterFunction(new NativeFunction3 <StaticFunctionTag, bool, BSFixedString, BSFixedString, VMArray<SInt32>>("IntListCopy", "JsonUtil", ListCopy<SInt32>, registry));
		registry->RegisterFunction(new NativeFunction3 <StaticFunctionTag, bool, BSFixedString, BSFixedString, VMArray<float>>("FloatListCopy", "JsonUtil", ListCopy<float>, registry));
		registry->RegisterFunction(new NativeFunction3 <StaticFunctionTag, bool, BSFixedString, BSFixedString, VMArray<BSFixedString>>("StringListCopy", "JsonUtil", ListCopy<BSFixedString>, registry));
		registry->RegisterFunction(new NativeFunction3 <StaticFunctionTag, bool, BSFixedString, BSFixedString, VMArray<TESForm*>>("FormListCopy", "JsonUtil", ListCopy<TESForm*>, registry));
		registry->SetFunctionFlags("JsonUtil", "IntListCopy", VMClassRegistry::kFunctionFlag_NoWait);
		registry->SetFunctionFlags("JsonUtil", "FloatListCopy", VMClassRegistry::kFunctionFlag_NoWait);
		registry->SetFunctionFlags("JsonUtil", "StringListCopy", VMClassRegistry::kFunctionFlag_NoWait);
		registry->SetFunctionFlags("JsonUtil", "FormListCopy", VMClassRegistry::kFunctionFlag_NoWait);
	}

}