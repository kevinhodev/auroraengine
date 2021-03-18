#pragma once

#include <intsafe.h>
#include <intrin.h>

inline LONG IncrementoIntertravado(volatile int* pDestino)
{
	static_assert(sizeof(int) == sizeof(LONG), "Conversão insegura. int não é do mesmo tamanho que LONG.");
	return _InterlockedIncrement((volatile LONG*)pDestino);
}