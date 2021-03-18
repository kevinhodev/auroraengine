#pragma once

#include <QString>

#include "functor.h"
#include "AtalhoDeTeclado.h"

class CComando;

class CDescricaoDoComando
{
	friend class CComando;

	public:
		CDescricaoDoComando(const QString& descricao)
			: m_pComando(nullptr)
			, m_descricao(descricao)
		{
		}

		CDescricaoDoComando(const CDescricaoDoComando& descricao)
			: m_pComando(descricao.m_pComando)
			, m_descricao(descricao.m_descricao)
		{
		}

		inline const QString& ObterDescricao() const { return m_descricao; }
		virtual bool PodeSerUmComandoDaIU() const { return false; }

	private:
		inline void DefinirComando(CComando* const pPai)
		{
			m_pComando = pPai;
		}

		CComando* m_pComando;
		QString m_descricao;
};

class CComando
{
	public:
		CComando(const QString& modulo, const QString& nome, const CDescricaoDoComando& descricao)
			: m_modulo(modulo)
			, m_nome(nome)
			, m_descricaoDoComando(descricao)
		{
			m_descricaoDoComando.DefinirComando(this);
		}

		virtual ~CComando() {}

		inline const QString& ObterModulo() const { return m_modulo; }
		inline const QString& ObterNome() const { return m_nome; }
		inline const QString& ObterDescricao() const { return m_descricaoDoComando.ObterDescricao(); }
		virtual QString ObterStringDoComando() const { return m_modulo + "." + m_nome; }

		virtual QString Executar() = 0;

		virtual bool PodeSerUmComandoDaIU() const { return false; }

	protected:
		QString m_modulo;
		QString m_nome;
		CDescricaoDoComando m_descricaoDoComando;
};

class CComandoDaIU : public CComando
{
	public:
		CComandoDaIU(const QString& modulo, const QString& nome, const CDescricaoDoComando& descricao)
			: CComando(modulo, nome, descricao)
			, m_informacoesDaIU(nullptr)
		{
		}

		~CComandoDaIU()
		{
			delete m_informacoesDaIU;
		}

		struct InformacoesDaIU
		{
			QString textoDoBotao;
			QString icone;
			CAtalhoDeTeclado tecla;
			bool eChecavel;

			InformacoesDaIU()
				: textoDoBotao("")
				, icone("")
				, eChecavel(false)
			{
			}

			InformacoesDaIU(const QString& texto, const QString& nomeDoIcone, const CAtalhoDeTeclado& atalho, bool checavel)
				: textoDoBotao(texto)
				, icone(nomeDoIcone)
				, tecla(atalho)
				, eChecavel(checavel)
			{
			}

			virtual ~InformacoesDaIU()
			{
			}

			virtual void operator=(const InformacoesDaIU& informacoes)
			{
				textoDoBotao = informacoes.textoDoBotao;
				icone = informacoes.icone;
				tecla = informacoes.tecla;
				eChecavel = informacoes.eChecavel;
			}
		};

		inline InformacoesDaIU* ObterInformacoesDaIU() { return m_informacoesDaIU; }
		void DefinirInformacoesDaIU(InformacoesDaIU* informacoes)
		{
			if (m_informacoesDaIU != informacoes)
			{
				delete m_informacoesDaIU;
				m_informacoesDaIU = informacoes;
			}
		}

		virtual bool PodeSerUmComandoDaIU() const override { return true; }

	private:
		InformacoesDaIU* m_informacoesDaIU;
};

class CComando0 : public CComandoDaIU
{
	public:
		CComando0(const QString& modulo, const QString& nome, const CDescricaoDoComando& descricao, const Functor0& functor)
			: CComandoDaIU(modulo, nome, descricao)
			, m_functor(functor)
		{
		}

		inline QString Executar()
		{
			m_functor();
			return "";
		}

	private:
		Functor0 m_functor;
};