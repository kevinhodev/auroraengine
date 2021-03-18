#include "PainelAbrirProjeto.h"

#include "DialogoSelecionarProjeto.h"
#include "QVisualizacaoDeArvoreAvancada.h"
#include "QVizualizacaoDeMiniatura.h"

#include <QlineEdit>
#include <QBoxLayout>
#include <QSortFilterProxyModel>
#include <QButtonGroup>
#include <QPushButton>
#include <QToolButton>

CPainelAbrirProjeto::CPainelAbrirProjeto(CDialogoSelecionarProjeto* pPai)
	: QWidget(pPai)
	, m_pPai(pPai)
	, m_pModeloClassificado(new QSortFilterProxyModel(this))
	, m_pLayoutPrincipal(new QVBoxLayout(this))
	, m_pVisualizacaoEmArvore(new QVisualizacaoEmArvoreAvancada())
	, m_pVisualizacaoEmMiniatura(new QVisualizacaoEmMiniatura(nullptr, false, this))
{
	m_pLayoutPrincipal->setMargin(0);
	m_pLayoutPrincipal->setSpacing(0);
	setLayout(m_pLayoutPrincipal);

	CriarPainelDePesquisa();
	CriarVizualizacoes();
	CriarBotoesDoDialogo();

	DefinirModoDeVisualizacao(ModoDeVisualizacao::Arvore);
}

CPainelAbrirProjeto::~CPainelAbrirProjeto()
{
}

void CPainelAbrirProjeto::CriarPainelDePesquisa()
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

void CPainelAbrirProjeto::CriarVizualizacoes()
{
	m_pVisualizacaoEmArvore->setModel(m_pModeloClassificado);
	m_pVisualizacaoEmArvore->setRootIsDecorated(false);

	m_pVisualizacaoEmArvore->setContextMenuPolicy(Qt::CustomContextMenu);

	m_pVisualizacaoEmMiniatura->DefinirModelo(m_pModeloClassificado);
	m_pVisualizacaoEmMiniatura->DefinirLimitesDeTamanhoDeItem({ 96, 96 }, { 96, 96 });
	m_pVisualizacaoEmMiniatura->DefinirIndiceRaiz(QModelIndex());

	m_pVisualizacaoEmMiniatura->setContextMenuPolicy(Qt::CustomContextMenu);

	QAbstractItemView* const pView = m_pVisualizacaoEmMiniatura->ObterVisualizacaoInterna();
	pView->setSelectionMode(QAbstractItemView::SingleSelection);
	pView->setSelectionBehavior(QAbstractItemView::SelectRows);
	pView->setSelectionModel(m_pVisualizacaoEmArvore->selectionModel());
	pView->update();

	QHBoxLayout* pLayout = new QHBoxLayout;
	pLayout->setMargin(0);
	pLayout->setSpacing(0);
	pLayout->addWidget(m_pVisualizacaoEmArvore);
	pLayout->addWidget(m_pVisualizacaoEmMiniatura);

	QVBoxLayout* pLayoutDosBotoes = new QVBoxLayout;
	pLayoutDosBotoes->setMargin(0);
	pLayoutDosBotoes->setSpacing(0);
	pLayoutDosBotoes->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding));

	QButtonGroup* pBotoesModoDeVisualizacao = new QButtonGroup(this);
	CriarBotaoVisualizacaoEmLista(pBotoesModoDeVisualizacao);
	CriarBotaoVisualizacaoEmMiniatura(pBotoesModoDeVisualizacao);

	const QList<QAbstractButton*> botoes = pBotoesModoDeVisualizacao->buttons();
	for (QAbstractButton* pBotao : botoes)
	{
		pLayoutDosBotoes->addWidget(pBotao);
	}

	pLayout->addLayout(pLayoutDosBotoes);
	m_pLayoutPrincipal->addLayout(pLayout);
}

void CPainelAbrirProjeto::CriarBotaoVisualizacaoEmLista(QButtonGroup* pGrupo)
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

void CPainelAbrirProjeto::CriarBotaoVisualizacaoEmMiniatura(QButtonGroup* pGrupo)
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

void CPainelAbrirProjeto::CriarBotoesDoDialogo()
{
	m_pBotaoAdicionarProjeto = new QPushButton("Adicionar Existente...");

	m_pBotaoAbrirProjeto = new QPushButton("Abrir", this);
	m_pBotaoAbrirProjeto->setDefault(true);
	m_pBotaoAbrirProjeto->setDisabled(m_pVisualizacaoEmArvore->selectionModel()->selection().count() == 0);

	QPushButton* pBotaoCancelar = new QPushButton("Cancelar", this);
	connect(pBotaoCancelar, SIGNAL(clicked()), m_pPai, SLOT(reject()));

	QHBoxLayout* pLayoutDosBotoes = new QHBoxLayout;
	pLayoutDosBotoes->setMargin(0);
	pLayoutDosBotoes->setSpacing(0);
	pLayoutDosBotoes->addWidget(m_pBotaoAdicionarProjeto);
	pLayoutDosBotoes->addStretch();
	pLayoutDosBotoes->addWidget(m_pBotaoAbrirProjeto, 0, Qt::AlignRight);
	pLayoutDosBotoes->addWidget(pBotaoCancelar, 0, Qt::AlignRight);

	m_pLayoutPrincipal->addLayout(pLayoutDosBotoes);
}

void CPainelAbrirProjeto::DefinirModoDeVisualizacao(ModoDeVisualizacao modo)
{
	if (modo == ModoDeVisualizacao::Miniatura)
	{
		m_pVisualizacaoEmArvore->setVisible(false);
		m_pVisualizacaoEmMiniatura->setVisible(true);
	}
	else
	{
		m_pVisualizacaoEmArvore->setVisible(true);
		m_pVisualizacaoEmMiniatura->setVisible(false);
	}
}
