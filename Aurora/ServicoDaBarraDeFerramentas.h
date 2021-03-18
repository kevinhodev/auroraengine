#pragma once

#include <vector>
#include <memory>
#include <map>
#include <functional>

class QToolBar;
class QString;
class CEditor;
class QFileInfo;

namespace Privado_GerenciadorDaBarraDeFerramentas
{
	static const char* szCaminhoDasBarrasDeFerramentasDoUsuario = "BarrasDeFerramentas";
	static const char* s_caminhoPadrao = "Editor/BarrasDeFerramentas";
	static const int s_versao = 2;
}

class CServicoDaBarraDeFerramentas
{
	public:
		class QDescricaoDaBarraDeFerramentas
		{
			public:
				QDescricaoDaBarraDeFerramentas();
				~QDescricaoDaBarraDeFerramentas();
				static QString ObterNomeDaInformacaoDoArquivo(const QFileInfo& informacaoDoArquivo);
		};


		CServicoDaBarraDeFerramentas();
		~CServicoDaBarraDeFerramentas();
		void EncontreABarraDeFerramentasNoDiretorioEExecute(const QString& caminhoDoDiretorio, std::function<void(const QFileInfo&)> callback) const;
		void CarregarBarraDeFerramentasDoDiretorio(const QString& caminhoDoDiretorio, std::map<QString, std::shared_ptr<QDescricaoDaBarraDeFerramentas>>& descritoresDaBarraDeFerramentaDeSaida) const;
		std::shared_ptr<QDescricaoDaBarraDeFerramentas> CarregarBarraDeFerramentas(const QString& caminhoAbsoluto) const;

	private:
		friend class CQuadroPrincipal;

		std::vector<QToolBar*> CarregarBarrasDeFerramentas(const char* szCaminhoRelativo, const CEditor* pEditor = nullptr) const;
		std::vector<QString> ObterDiretoriosDaBarraDeFerramentas(const char* szCaminhoRelativo) const;
};

