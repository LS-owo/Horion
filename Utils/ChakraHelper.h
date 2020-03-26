#pragma once
#include "DllHelper.h"
#include "../include/chakra/ChakraCore.h"

#define DECL_API(f) decltype(f)* f##_ = _dll[#f]

class ChakraApi {
	DllHelper _dll{"Chakra.dll"};

public:
	DECL_API(JsCreateRuntime);
	DECL_API(JsCreateContext);
	DECL_API(JsSetCurrentContext);
	DECL_API(JsDisposeRuntime);
	DECL_API(JsRunScript);
	DECL_API(JsConvertValueToString);
	DECL_API(JsStringToPointer);
	DECL_API(JsSetRuntimeMemoryLimit);
	DECL_API(JsCreateObject);
	DECL_API(JsGetGlobalObject);
	DECL_API(JsGetPropertyIdFromName);
	DECL_API(JsPointerToString);
	DECL_API(JsSetProperty);
	DECL_API(JsCreateFunction);

	void defineFunction(JsValueRef object, const wchar_t* callbackName, JsNativeFunction function, void* callbackState = nullptr) {
		JsPropertyIdRef propertyId;
		this->JsGetPropertyIdFromName_(callbackName, &propertyId);

		JsValueRef functionRef;
		this->JsCreateFunction_(function, callbackState, &functionRef);

		this->JsSetProperty_(object, propertyId, functionRef, true);
	}
};