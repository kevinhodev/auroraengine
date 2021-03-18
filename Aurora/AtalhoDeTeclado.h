#pragma once

#include <QList>
#include <QKeySequence>

class QString;

class CAtalhoDeTeclado
{
	public:
		enum class TeclaPadrao
		{
			WikiDeAjuda,  // F1, abre a página wiki relevante
			Salvar, // Ctrl + S
			SalvarComo, // Sem Atalho no Windows

			Contagem
		};

		CAtalhoDeTeclado();
		CAtalhoDeTeclado(TeclaPadrao tecla);
		CAtalhoDeTeclado(const char* string);
		inline bool EUmaTeclaPadrao() const { return m_tecla != TeclaPadrao::Contagem; }
		inline TeclaPadrao ObterTecla() const { return m_tecla; }
		const QString& ObterSring() const { return m_string;  }
		QList<QKeySequence> ConverterParaSequenciaDeTecla() const;

	private:
		TeclaPadrao m_tecla;
		QString m_string;
};

