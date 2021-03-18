#include "PainelCriarProjeto.h"

#include "DialogoSelecionarProjeto.h"
#include "DialogoArquivoDeSistema.h"
#include "QVizualizacaoDeMiniatura.h"

#include <QBoxLayout>
#include <QTreeView>
#include <QLineEdit>
#include <QButtonGroup>
#include <QToolButton>
#include <QLabel>
#include <QPushButton>
#include <QFileSystemModel>
#include <QSortFilterProxyModel>

CPainelCriarProjeto::CPainelCriarProjeto(CDialogoSelecionarProjeto* pPai)
	: QWidget(pPai)
	, m_pPai(pPai)
	, m_pModeloClassificado(new QSortFilterProxyModel(this))
	, m_pLayoutPrincipal(new QVBoxLayout(this))
	, m_pVisualizacaoDeArvore(new QTreeView())
	, m_pVisualizacaoDeMiniatura(new QVisualizacaoEmMiniatura(nullptr, false, this))
	, m_pLinhaDeEdicaoDiretorioDeSaida(new QLineEdit)
{
	m_pLayoutPrincipal->setMargin(0);
	m_pLayoutPrincipal->setSpacing(0);
	setLayout(m_pLayoutPrincipal);

	CriarPainelDePesquisa();
	CriarVizualizacoes();
	CriarCaixaDeEdicaoPastaRaizDeSaida();
	CriarCaixaDeEdicaoNomeDoProjeto();
	CriarBotoesDoDialogo();

	DefinirModoDeVisualizacao(ModoDeVisualizacao::Arvore);
}

CPainelCriarProjeto::~CPainelCriarProjeto()
{
}

void CPainelCriarProjeto::CriarPainelDePesquisa()
{
	QWidget* pContainerDaCaixaDePesquisa = new QWidget();
	pContainerDaCaixaDePesquisa->setObjectName("ContainerDaCaixaDePesquisa");

	QLineEdit* pCaixaDePesquisa = new QLineEdit(this);

	QHBoxLayout* pLayoutDaCaixaDePesquisa = new QHBoxLayout();
	pLayoutDaCaixaDePesquisa->setAlignment(Qt::AlignTop);
	pLayoutDaCaixaDePesquisa->setMargin(0);
	pLayoutDaCaixaDePesquisa->setSpacing(0);
	pLayoutDaCaixaDePesquisa->addWidget(pCaixaDePesquisa);

	pContainerDaCaixaDePesquisa->setLayout(pLayoutDaCaixaDePesquisa);

	m_pLayoutPrincipal->addWidget(pContainerDaCaixaDePesquisa);
}

void CPainelCriarProjeto::CriarVizualizacoes()
{
	m_pVisualizacaoDeArvore->setModel(m_pModeloClassificado);
	m_pVisualizacaoDeArvore->setRootIsDecorated(false);
	m_pVisualizacaoDeArvore->selectionModel()->select(m_pVisualizacaoDeArvore->model()->index(0, 0), QItemSelectionModel::Select | QItemSelectionModel::Rows);

	m_pVisualizacaoDeMiniatura->DefinirModelo(m_pModeloClassificado);
	m_pVisualizacaoDeMiniatura->DefinirLimitesDeTamanhoDeItem({ 96, 96 }, { 96, 96 });
	m_pVisualizacaoDeMiniatura->DefinirIndiceRaiz(QModelIndex());

	QAbstractItemView* const pVisualizacao = m_pVisualizacaoDeMiniatura->ObterVisualizacaoInterna();
	pVisualizacao->setSelectionMode(QAbstractItemView::SingleSelection);
	pVisualizacao->setSelectionBehavior(QAbstractItemView::SelectRows);
	pVisualizacao->setSelectionModel(m_pVisualizacaoDeArvore->selectionModel());
	pVisualizacao->update();

	QHBoxLayout* pLayout = new QHBoxLayout;
	pLayout->setMargin(0);
	pLayout->setSpacing(0);
	pLayout->addWidget(m_pVisualizacaoDeArvore);
	pLayout->addWidget(m_pVisualizacaoDeMiniatura);

	QVBoxLayout* pLayoutDosBotoes = new QVBoxLayout;
	pLayoutDosBotoes->setMargin(0);
	pLayoutDosBotoes->setSpacing(0);
	pLayoutDosBotoes->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding));

	QButtonGroup* pGrupo = new QButtonGroup(this);
	CriarBotaoVizualizacaoDeLista(pGrupo);
	CriarBotaoMiniatura(pGrupo);

	const QList<QAbstractButton*> botoes = pGrupo->buttons();
	for (QAbstractButton* botao : botoes)
	{
		pLayoutDosBotoes->addWidget(botao);
	}
	
	pLayout->addLayout(pLayoutDosBotoes);
	
	m_pLayoutPrincipal->addLayout(pLayout);
}

void CPainelCriarProjeto::CriarBotaoVizualizacaoDeLista(QButtonGroup* pGrupo)
{
	QToolButton* pBotao = new QToolButton();
	connect(pBotao, &QToolButton::clicked, this, [this]() { DefinirModoDeVisualizacao(ModoDeVisualizacao::Arvore); });
	pBotao->setIcon(QIcon(":/icones/VizualizacaoDeLista.ico"));
	pBotao->setCheckable(true);
	pBotao->setAutoRaise(true);
	pBotao->setToolTip("Mostrar Detalhes");
	pBotao->setChecked(true);
	pGrupo->addButton(pBotao);
}

void CPainelCriarProjeto::CriarBotaoMiniatura(QButtonGroup* pGrupo)
{
	QToolButton* pBotao = new QToolButton();
	connect(pBotao, &QToolButton::clicked, this, [this]() { DefinirModoDeVisualizacao(ModoDeVisualizacao::Miniatura); });
	pBotao->setIcon(QIcon(":/icones/VisualizacaoEmMiniatura"));
	pBotao->setCheckable(true);
	pBotao->setAutoRaise(true);
	pBotao->setToolTip("Mostrar Miniaturas");
	pBotao->setChecked(false);
	pGrupo->addButton(pBotao);
}

void CPainelCriarProjeto::CriarCaixaDeEdicaoPastaRaizDeSaida()
{
	QLabel* pRotulo = new QLabel("Local:", this);
	pRotulo->setFixedWidth(100);

	m_pLinhaDeEdicaoDiretorioDeSaida->setText("C:/");
	m_pLinhaDeEdicaoDiretorioDeSaida->setReadOnly(true);

	QPushButton* pBotaoSelecionarPasta = new QPushButton(this);
	pBotaoSelecionarPasta->setIcon(QIcon(":/icones/SelecionarPasta"));
	pBotaoSelecionarPasta->setToolTip("Selecionar Pasta de Saida");
	pBotaoSelecionarPasta->setFixedWidth(24);
	pBotaoSelecionarPasta->setCheckable(false);
	connect(pBotaoSelecionarPasta, &QPushButton::clicked, this, &CPainelCriarProjeto::AoAlterarAPastaDeSaida);

	QHBoxLayout* pLayout = new QHBoxLayout();
	pLayout->setMargin(0);
	pLayout->setSpacing(0);
	pLayout->addWidget(pRotulo);
	pLayout->addWidget(m_pLinhaDeEdicaoDiretorioDeSaida);
	pLayout->addWidget(pBotaoSelecionarPasta);

	m_pLayoutPrincipal->addLayout(pLayout);
}

void CPainelCriarProjeto::CriarCaixaDeEdicaoNomeDoProjeto()
{
	QLabel* pRotulo = new QLabel("Nome:", this);
	pRotulo->setFixedWidth(100);	

	QLineEdit* pLinhaDeEdicaoNomeDoNovoProjeto = new QLineEdit(this);
	pLinhaDeEdicaoNomeDoNovoProjeto->setText("Meu Projeto");
	pLinhaDeEdicaoNomeDoNovoProjeto->setReadOnly(false);

	QHBoxLayout* pLayout = new QHBoxLayout;
	pLayout->setMargin(0);
	pLayout->setSpacing(0);
	pLayout->addWidget(pRotulo);
	pLayout->addWidget(pLinhaDeEdicaoNomeDoNovoProjeto);

	m_pLayoutPrincipal->addLayout(pLayout);
}

void CPainelCriarProjeto::CriarBotoesDoDialogo()
{
	QPushButton* pBotaoCancelar = new QPushButton("Cancelar", this);
	QPushButton* pBotaoCriarProjeto = new QPushButton("Criar Projeto", this);
	pBotaoCriarProjeto->setDefault(true);

	connect(pBotaoCancelar, SIGNAL(clicked()), m_pPai, SLOT(reject()));

	QHBoxLayout* pLayoutDosBotoes = new QHBoxLayout;
	pLayoutDosBotoes->setAlignment(Qt::AlignRight | Qt::AlignBottom);
	pLayoutDosBotoes->setMargin(0);
	pLayoutDosBotoes->setSpacing(0);
	pLayoutDosBotoes->addWidget(pBotaoCriarProjeto);
	pLayoutDosBotoes->addWidget(pBotaoCancelar);

	m_pLayoutPrincipal->addLayout(pLayoutDosBotoes);
}

void CPainelCriarProjeto::DefinirModoDeVisualizacao(ModoDeVisualizacao modo)
{
	if (modo == ModoDeVisualizacao::Miniatura)
	{
		m_pVisualizacaoDeArvore->setVisible(false);
		m_pVisualizacaoDeMiniatura->setVisible(true);
	}
	else
	{
		m_pVisualizacaoDeArvore->setVisible(true);
		m_pVisualizacaoDeMiniatura->setVisible(false);
	}
}

void CPainelCriarProjeto::AoAlterarAPastaDeSaida()
{
	CDialogoArquivoDeSistema::ParametrosDeAbertura parametrosDeAbertura(CDialogoArquivoDeSistema::SelecionarDiretorio);
	parametrosDeAbertura.titulo = "Selecione a Pasta";
	parametrosDeAbertura.diretorioInicial = m_pLinhaDeEdicaoDiretorioDeSaida->text();

	CDialogoArquivoDeSistema dialogo(parametrosDeAbertura, this);

	if (dialogo.Executar())
	{
		auto arquivos = dialogo.ObterArquivosSelecionados();
		assert(arquivos.size() == 1);
		m_pLinhaDeEdicaoDiretorioDeSaida->setText(arquivos.front());
	}
}
