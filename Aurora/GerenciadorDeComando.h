#pragma once

#include "IGerenciadorDeComando.h"
#include "AtalhoDeTeclado.h"

#include <map>

class CGerenciadorDeComandosDoEditor : public IGerenciadorDeComandos
{
	public:
		CGerenciadorDeComandosDoEditor();
		~CGerenciadorDeComandosDoEditor();

		bool AdicionarComando(CComando* pComando, TPfnDeletador deletador = nullptr) override;
		void RegistrarDescricaoDaIU(const QString& modulo, const QString& nome, const QString& textoDoBotao, const CAtalhoDeTeclado& atalho, QString icone, bool checavel) override;
		bool EstaRegistrado(const QString& modulo, const QString& nome) const override;
		virtual QAction* ObterAcao(const char* nomeCompletoDoComando, const char* texto = nullptr) const override;
		virtual QAcaoDeComando* ObterAcaoDeComando(const char* comando, const char* texto = nullptr) const override;
		void DefinirDescricaoDaIU(const QString& modulo, const QString& nome, const CComandoDaIU::InformacoesDaIU& informacoes) override;
		void ExecutarComando(const QString& sComando, ...) override;

	protected:
		struct SEntradaDaTabelaDeComandos
		{
			CComando* pComando;
			TPfnDeletador deletador;
		};

		typedef std::map<QString, SEntradaDaTabelaDeComandos> TabelaDeComandos;
		TabelaDeComandos m_comandos;

		static QString ObterNomeCompletoDoComando(const QString& modulo, const QString& nome);
};