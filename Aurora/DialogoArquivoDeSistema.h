#pragma once

#include <QString>
#include <QWidget>
#include <QFileDialog>

class CDialogoArquivoDeSistema
{
	public:
		enum Modo
		{
			SelecionarDiretorio,

			Quantidade
		};

		struct ParametrosDeAbertura
		{
			Modo modo;
			QString titulo;
			QString diretorioInicial;

			ParametrosDeAbertura(Modo md) : modo(md) {}
		};

		CDialogoArquivoDeSistema(const ParametrosDeAbertura& parametrosDeAbertura, QWidget* pPai = nullptr);

		inline int Executar() { return m_dialogo.exec(); }
		std::vector<QString> ObterArquivosSelecionados() const;

	protected:
		QFileDialog m_dialogo;
};

