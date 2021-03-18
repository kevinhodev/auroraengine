#include "QAcaoDeComando.h"
#include "Editor.h"

QAcaoDeComando::QAcaoDeComando(const QString& nomeDaAcao, const QString& textoDaAcao, QObject* pai, const char* comando /*=0*/)
	: QAction(nomeDaAcao, pai)
{
	setShortcutContext(Qt::WidgetWithChildrenShortcut);
	setShortcutVisibleInContextMenu(true);
	setText(textoDaAcao);

	if (comando)
	{
		setProperty("QAcaoDeComando", QVariant(QString(comando)));
	}

	connect(this, &QAcaoDeComando::triggered, this, &QAcaoDeComando::AoAcionar);
}

QAcaoDeComando::QAcaoDeComando(const QString& nomeDaAcao, QObject* pai, const char* comando /*=0*/)
	: QAction(nomeDaAcao, pai)
{
	setShortcutContext(Qt::WidgetWithChildrenShortcut);
	setShortcutVisibleInContextMenu(true);
	setObjectName(nomeDaAcao);

	if (comando)
	{
		setProperty("QAcaoDeComando", QVariant(QString(comando)));
	}

	connect(this, &QAcaoDeComando::triggered, this, &QAcaoDeComando::AoAcionar);
}

QAcaoDeComando::QAcaoDeComando(const QAcaoDeComando& acao)
	: QAction(acao.text(), nullptr)
	, InformacoesDaIU(acao.InformacoesDaIU::textoDoBotao, acao.InformacoesDaIU::icone, acao.InformacoesDaIU::tecla, acao.InformacoesDaIU::eChecavel)
{
	setShortcutContext(Qt::WidgetWithChildrenShortcut);
	setShortcutVisibleInContextMenu(true);
	setIcon(acao.QAction::icon());
	setCheckable(acao.QAction::isCheckable());
	setObjectName(acao.objectName());
	setProperty("QAcaoDeComando", acao.property("QAcaoDeComando"));
	setShortcuts(acao.QAction::shortcuts());

	connect(this, &QAcaoDeComando::triggered, this, &QAcaoDeComando::AoAcionar);
}

QAcaoDeComando::QAcaoDeComando(const CComandoDaIU& comando)
	: QAction(comando.ObterDescricao().toStdString().c_str(), nullptr)
{
	setShortcutContext(Qt::WidgetWithChildrenShortcut);
	setShortcutVisibleInContextMenu(true);
	setObjectName(comando.ObterNome().toStdString().c_str());
	setProperty("QAcaoDeComando", QVariant(QString(comando.ObterStringDoComando())));
	connect(this, &QAcaoDeComando::triggered, this, &QAcaoDeComando::AoAcionar);
}

void QAcaoDeComando::AoAcionar()
{
	QVariant propriedadeDoComando = property("QAcaoDeComando");
	QString qstr;

	if (propriedadeDoComando.isValid())
	{
		QString qstr = propriedadeDoComando.toString();
		ObterEditor()->ObterGerenciadorDeComandos()->ExecutarComando(qstr);
	}
}

void QAcaoDeComando::operator=(const InformacoesDaIU& informacoes)
{
	InformacoesDaIU::operator=(informacoes);

	QList<QKeySequence> atalhos = informacoes.tecla.ConverterParaSequenciaDeTecla();
	setCheckable(informacoes.eChecavel);

	if (!atalhos.empty())
	{
		setShortcuts(atalhos);
		DefinirAtalhosPadroes(atalhos);
	}

	if (!informacoes.textoDoBotao.toStdString().c_str() || *informacoes.textoDoBotao.toStdString().c_str())
	{
		setText(informacoes.textoDoBotao);
	}

	if (!informacoes.icone.toStdString().c_str() || *informacoes.icone.toStdString().c_str())
	{
		setIcon(QIcon(informacoes.icone));
	}
}

