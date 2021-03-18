#pragma once

#include <QString>

namespace UtilidadesDePasta
{
	namespace detalhes
	{
		template<typename>
		struct SConstantesDeString
		{
			static constexpr const char* BarraParaFrente = "/";
		};

		template<typename>
		struct StringValida : std::false_type {};

		template<>
		struct StringValida<QString> : std::true_type {};
	}

	template<typename TString>
	typename std::enable_if<detalhes::StringValida<TString>::value, TString>::type
	inline AdicionarBarra(const TString& caminho)
	{
		if (caminho.isEmpty() || caminho[caminho.length() - 1] == '/')
		{
			return caminho;
		}

		if (caminho[caminho.length() - 1] == '\\')
		{
			QStringRef substr(&caminho, 0, caminho.length() - 1);
			return substr + detalhes::SConstantesDeString<TString>::BarraParaFrente;
		}

		return caminho + detalhes::SConstantesDeString<TString>::BarraParaFrente;
	}

	inline QString AdicionarBarra(const char* szCaminho)
	{
		return AdicionarBarra(QString(szCaminho));
	}

	template<typename TString>
	typename std::enable_if<detalhes::StringValida<TString>::value, TString>::type
	inline FazerCaminho(const TString& diretorio, const TString& nomeDoArquivo)
	{
		return AdicionarBarra(diretorio) + nomeDoArquivo;
	}

	inline QString FazerCaminho(const char* szCaminho, const char* szNomeDoArquivo)
	{
		return FazerCaminho(QString(szCaminho), QString(szNomeDoArquivo));
	}
};

