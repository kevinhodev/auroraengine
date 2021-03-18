#pragma once

#include <intsafe.h>
#include <intrin.h>

inline LONG IncrementoIntertravado(volatile int* pDestino)
{
	static_assert(sizeof(int) == sizeof(LONG), "Convers�o insegura. int n�o � do mesmo tamanho que LONG.");
	return _InterlockedIncrement((volatile LONG*)pDestino);
}