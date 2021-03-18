#include "ServicoDaBarraDeFerramentas.h"

#include "IEditor.h"
#include "UtilidadesDePasta.h"

#include <QToolBar>
#include <QString>
#include <QDir>
#include <QFileInfo>
#include <QJSONDocument>
#include <QVariant>

CServicoDaBarraDeFerramentas::CServicoDaBarraDeFerramentas()
{}

CServicoDaBarraDeFerramentas::~CServicoDaBarraDeFerramentas()
{}

void CServicoDaBarraDeFerramentas::EncontreABarraDeFerramentasNoDiretorioEExecute(const QString & caminhoDoDiretorio, std::function<void(const QFileInfo&)> callback) const
{
	QDir diretorio(caminhoDoDiretorio);

	if (!diretorio.exists())
	{
		return;
	}

	QFileInfoList listaDeInformacoes = diretorio.entryInfoList(QDir::AllDirs | QDir::Files | QDir::NoDotAndDotDot);
	for (QFileInfo& informacoesDoArquivo : listaDeInformacoes)
	{

		if (informacoesDoArquivo.isDir())
		{
			continue;
		}

		callback(informacoesDoArquivo);
	}
}

void CServicoDaBarraDeFerramentas::CarregarBarraDeFerramentasDoDiretorio(const QString& caminhoDoDiretorio, std::map<QString, std::shared_ptr<QDescricaoDaBarraDeFerramentas>>&descritoresDaBarraDeFerramentaDeSaida) const
{
	EncontreABarraDeFerramentasNoDiretorioEExecute(caminhoDoDiretorio, [this, &descritoresDaBarraDeFerramentaDeSaida](const QFileInfo& informacoesDoArquivo)
	{
		QString nomeDaBarraDeFerramentas = QDescricaoDaBarraDeFerramentas::ObterNomeDaInformacaoDoArquivo(informacoesDoArquivo);
		auto iterador = descritoresDaBarraDeFerramentaDeSaida.find(nomeDaBarraDeFerramentas);

		if (iterador != descritoresDaBarraDeFerramentaDeSaida.end())
		{
			return;
		}

		std::shared_ptr<QDescricaoDaBarraDeFerramentas> pDescricaoDaBarraDeFerramentas = CarregarBarraDeFerramentas(informacoesDoArquivo.absoluteFilePath());

		//descritoresDaBarraDeFerramentaDeSaida.insert({nomeDaBarraDeFerramentas, })
	});
}

std::shared_ptr<CServicoDaBarraDeFerramentas::QDescricaoDaBarraDeFerramentas> CServicoDaBarraDeFerramentas::CarregarBarraDeFerramentas(const QString& caminhoAbsoluto) const
{
	QFileInfo informacoesDoArquivo(caminhoAbsoluto);
	QFile arquivo(caminhoAbsoluto);

	if (!arquivo.open(QIODevice::ReadOnly))
	{
		return nullptr;
	}

	QJsonDocument documento(QJsonDocument::fromJson(arquivo.readAll()));
	QVariantMap mapaVariante = documento.toVariant().toMap();
	
	const QString nomeDoDiretorio = informacoesDoArquivo.absoluteDir().dirName();
	const QString nomeDoArquivo = informacoesDoArquivo.fileName();
	const QString caminhoRelativoDaBarraDeFerramentas = nomeDoDiretorio + "/" + nomeDoArquivo;
	 
	QVariantList barraDeFerramentasVariante = mapaVariante["barraDeFerramentas"].toList();
	std::shared_ptr<QDescricaoDaBarraDeFerramentas> pDescricaoDaBarraDeFerramentas = std::make_shared<QDescricaoDaBarraDeFerramentas>();

	return pDescricaoDaBarraDeFerramentas;
}

std::vector<QToolBar*> CServicoDaBarraDeFerramentas::CarregarBarrasDeFerramentas(const char* szCaminhoRelativo, const CEditor * pEditor) const
{
	std::map<QString, std::shared_ptr<QDescricaoDaBarraDeFerramentas>> descritoresDaBarraDeFerramenta;
	std::vector<QString> diretoriosDaBarraDeFerramentas = ObterDiretoriosDaBarraDeFerramentas(szCaminhoRelativo);

	for (const QString& diretorioDaBarraDeFerramenta : diretoriosDaBarraDeFerramentas)
	{
		CarregarBarraDeFerramentasDoDiretorio(diretorioDaBarraDeFerramenta, descritoresDaBarraDeFerramenta);
	}

	//return CreateEditorToolBars(toolBarDescriptors, pEditor);
    return std::vector<QToolBar*>();
}

std::vector<QString> CServicoDaBarraDeFerramentas::ObterDiretoriosDaBarraDeFerramentas(const char* szCaminhoRelativo) const
{
	std::vector<QString> resultado;
	QString caminhoDaBarraDeFerramentasDoEditor = "C:/Users/Kevin/source/repos/Aquom/Editor/BarraDeFerramentas/QuadroPrincipal";

	resultado.push_back(caminhoDaBarraDeFerramentasDoEditor);

	return resultado;
}

CServicoDaBarraDeFerramentas::QDescricaoDaBarraDeFerramentas::QDescricaoDaBarraDeFerramentas()
{}

CServicoDaBarraDeFerramentas::QDescricaoDaBarraDeFerramentas::~QDescricaoDaBarraDeFerramentas()
{}

QString CServicoDaBarraDeFerramentas::QDescricaoDaBarraDeFerramentas::ObterNomeDaInformacaoDoArquivo(const QFileInfo & informacaoDoArquivo)
{
	return informacaoDoArquivo.baseName();
}
