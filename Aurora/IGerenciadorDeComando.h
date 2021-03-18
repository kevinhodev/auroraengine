#pragma once

#include "Comando.h"

typedef void (*TPfnDeletador)(void*);

class QAcaoDeComando;

struct IGerenciadorDeComandos
{
	virtual ~IGerenciadorDeComandos() {}
	virtual bool AdicionarComando(CComando* pComando, TPfnDeletador deletador = nullptr) = 0;
	virtual QAction* ObterAcao(const char* nomeCompletoDoComando, const char* texto = nullptr) const = 0;
	virtual void RegistrarDescricaoDaIU(const QString& modulo, const QString& nome, const QString& textoDoBotao, const CAtalhoDeTeclado& atalho, QString icone, bool checavel) = 0;
	virtual void DefinirDescricaoDaIU(const QString& modulo, const QString& nome, const CComandoDaIU::InformacoesDaIU& informacoes) = 0;
	virtual QAcaoDeComando* ObterAcaoDeComando(const char* comando, const char* texto = nullptr) const = 0;
	virtual bool EstaRegistrado(const QString& modulo, const QString& nome) const = 0;
	virtual void ExecutarComando(const QString& sComando, ...) = 0;
};

namespace AuxiliarDoGerenciadorDeComando
{
	inline bool RegistrarComando(IGerenciadorDeComandos* pGrnCmd, QString szModulo, QString szNome, CDescricaoDoComando& descricao, Functor0& functor);

	namespace Privado
	{
		template<typename TipoDeFunctor, typename TipoDeComando>
		bool RegistrarComando(IGerenciadorDeComandos* pGrnCmd, QString szModulo, QString szNome, CDescricaoDoComando& descricao, TipoDeFunctor& functor);

		inline void DeletadorPadrao(void* p)
		{
			delete p;
		}
	}
}

template<typename TipoDeFunctor, typename TipoDeComando>
bool AuxiliarDoGerenciadorDeComando::Privado::RegistrarComando(IGerenciadorDeComandos* pGrnCmd, QString szModulo, QString szNome, CDescricaoDoComando& descricao, TipoDeFunctor& functor)
{
	if (!functor)
	{
		return false;
	}

	TipoDeComando* const pComando = new TipoDeComando(szModulo, szNome, descricao, functor);

	if (pGrnCmd->AdicionarComando(pComando, DeletadorPadrao) == false)
	{
		DeletadorPadrao(pComando);
		return false;
	}
}

inline bool AuxiliarDoGerenciadorDeComando::RegistrarComando(IGerenciadorDeComandos* pGrnCmd, QString szModulo, QString szNome, CDescricaoDoComando& descricao, Functor0& functor)
{
	return Privado::RegistrarComando<Functor0, CComando0>(pGrnCmd, szModulo, szNome, descricao, functor);
}

