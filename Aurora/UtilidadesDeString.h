#pragma once

#include <cstdio>   
#include <cstdarg>  

namespace Privado_UtilidadesDeString
{
	inline int ComputarComprimentoFormatadoVA(const char* const formato, va_list argumentos)
	{
		if (!formato || !formato[0])
		{
			return 0;
		}

		//#pragma(4996);
		return vsnprintf(nullptr, 0, formato, argumentos);
	}
}