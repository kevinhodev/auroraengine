#include "QVizualizacaoDeMiniatura.h"

#include <QSize>
#include <QBoxLayout>
#include <QStyledItemDelegate>
#include <QToolButton>
#include <QModelIndex>
#include <QAbstractItemView>

namespace Privado_QVisualizacaoDeMiniatura
{
	class CVisualizacaoDeLista : public QListView
	{
		public:
			CVisualizacaoDeLista(QWidget* pPai = nullptr)
				: QListView(pPai)
			{}
	};
}

class QVisualizacaoEmMiniatura::Delegado : public QStyledItemDelegate
{
	public:
		Delegado(QVisualizacaoEmMiniatura* pVisualizacao)
			: m_pVisualizacao(pVisualizacao)
			, m_iconeDeCarregamento(":/icones/IconeDeCarregamneto")
		{}

	private:
		QVisualizacaoEmMiniatura* m_pVisualizacao;
		QIcon m_iconeDeCarregamento;
};

QVisualizacaoEmMiniatura::QVisualizacaoEmMiniatura(QListView* pVisualizacaoInterna, bool mostrarBotoesDeTamanho /*true*/, QWidget* pPai /*nullptr*/)
	: QWidget(pPai)
	, m_tamanhoMinimoDoItem(16, 16)
	, m_tamanhoMaximoDoItem(256, 256)
	, m_tamanhoPadrao(64, 64)
	, m_bTemporizadorIniciou(false)
	, m_bRestaurarSelecao(true)
	, m_pBotoesDeTamanhoDeVisualizacao(nullptr)
{
	m_pVisualizacaoDeLista = pVisualizacaoInterna ? pVisualizacaoInterna : new Privado_QVisualizacaoDeMiniatura::CVisualizacaoDeLista();
	m_pVisualizacaoDeLista->setContextMenuPolicy(Qt::CustomContextMenu);
	m_pVisualizacaoDeLista->viewport()->installEventFilter(this);

	m_pDelegado = new Delegado(this);
	m_pVisualizacaoDeLista->setItemDelegate(m_pDelegado);

	m_pVisualizacaoDeLista->setUniformItemSizes(true);
	m_pVisualizacaoDeLista->setSpacing(4);
	m_pVisualizacaoDeLista->setViewMode(QListView::IconMode);
	m_pVisualizacaoDeLista->setFlow(QListView::LeftToRight);
	m_pVisualizacaoDeLista->setWrapping(true);
	m_pVisualizacaoDeLista->setResizeMode(QListView::Adjust);
	m_pVisualizacaoDeLista->setSelectionRectVisible(true);
	m_pVisualizacaoDeLista->setMovement(QListView::Snap);
	m_pVisualizacaoDeLista->setWordWrap(true);
	m_pVisualizacaoDeLista->setLayoutMode(QListView::Batched);
	m_pVisualizacaoDeLista->setBatchSize(500);

	auto layout = new QVBoxLayout();
	layout->setSpacing(0);
	layout->setMargin(0);
	layout->addWidget(m_pVisualizacaoDeLista);

	if (mostrarBotoesDeTamanho)
	{
		m_pBotoesDeTamanhoDeVisualizacao = new QButtonGroup(this);

		for (int i = 0; i < m_numeroDeTamanhosDeVisualização; i++)
		{
			AdicionarBotãoDeDimensionamento(16 << i, i);
		}

		auto caixaInferior = new QHBoxLayout();
		caixaInferior->setMargin(0);
		caixaInferior->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
		QList<QAbstractButton*> botoes = m_pBotoesDeTamanhoDeVisualizacao->buttons();

		for each (QAbstractButton * botao in botoes)
		{
			caixaInferior->addWidget(botao);
		}

		layout->addLayout(caixaInferior);
	}

	DefinirTamanhoDoItem(m_tamanhoPadrao);
	setLayout(layout);
}

QVisualizacaoEmMiniatura::~QVisualizacaoEmMiniatura()
{

}

bool QVisualizacaoEmMiniatura::DefinirTamanhoDoItem(const QSize& tamanho)
{
	if (tamanho.width() >= m_tamanhoMinimoDoItem.width() && tamanho.width() <= m_tamanhoMaximoDoItem.width()
		&& tamanho.height() >= m_tamanhoMinimoDoItem.height() && tamanho.height() <= m_tamanhoMaximoDoItem.height())
	{
		m_tamanhoDoItem = tamanho;
		m_pVisualizacaoDeLista->setIconSize(tamanho);

		if (m_pBotoesDeTamanhoDeVisualizacao)
		{
			QAbstractButton* pBotao = m_pBotoesDeTamanhoDeVisualizacao->button(tamanho.height());

			if (tamanho.height() == tamanho.width() && pBotao)
			{
				pBotao->setChecked(true);
			}
			else
			{
				pBotao = m_pBotoesDeTamanhoDeVisualizacao->checkedButton();

				if (pBotao)
				{
					pBotao->setChecked(false);
				}
			}
		}

		if (m_pVisualizacaoDeLista->selectionModel() && m_pVisualizacaoDeLista->selectionModel()->currentIndex().isValid())
		{
			RolarParaLinha(m_pVisualizacaoDeLista->selectionModel()->currentIndex(), QAbstractItemView::PositionAtCenter);
		}

		return true;
	}

	return false;
}

void QVisualizacaoEmMiniatura::DefinirLimitesDeTamanhoDeItem(const QSize& minimo, const QSize& maximo)
{
	m_tamanhoMinimoDoItem = minimo;
	m_tamanhoMaximoDoItem = maximo;

	if (!DefinirTamanhoDoItem(ObterTamanhoDoItem()))
	{
		DefinirTamanhoDoItem(m_tamanhoMinimoDoItem);
	}
}

void QVisualizacaoEmMiniatura::DefinirIndiceRaiz(const QModelIndex& indice)
{
	m_pVisualizacaoDeLista->setRootIndex(indice);
}

QModelIndex QVisualizacaoEmMiniatura::ObterIndiceRaiz() const
{
	return m_pVisualizacaoDeLista->rootIndex();
}

void QVisualizacaoEmMiniatura::DefinirColunaDeDados(int coluna)
{
	m_pVisualizacaoDeLista->setModelColumn(coluna);
}

/*bool QVisualizacaoEmMiniatura::DefinirAtributoDeDados(const CAtributoDeModeloDeItem* atributo, int funcaoDeAtributo)
{
	assert(atributo);

	auto pModelo = m_pVisualizacaoDeLista->model();
	assert(pModelo);

	const int contagemDeColuna = pModelo->columnCount(ObterIndiceRaiz());

	for (int i = 0; i < contagemDeColuna; i++)
	{
		QVariant valor = pModelo->headerData(i, Qt::Horizontal, funcaoDeAtributo);
		CAtributoDeModeloDeItem* pAtributo = valor.value<CAtributoDeModeloDeItem*>();

		if (pAtributo == atributo)
		{
			DefinirColunaDeDados(i);
			return true;
		}
	}

	return false;
}*/

void QVisualizacaoEmMiniatura::DefinirModelo(QAbstractItemModel* pModelo)
{
	QAbstractItemModel* pAntigo = m_pVisualizacaoDeLista->model();

	if (pAntigo != pModelo)
	{
		if (pAntigo)
		{
			disconnect(pAntigo, &QAbstractItemModel::modelAboutToBeReset, this, &QVisualizacaoEmMiniatura::AoModeloPrestesASerReiniciado);
			disconnect(pAntigo, &QAbstractItemModel::modelReset, this, &QVisualizacaoEmMiniatura::AoReiniciarOModelo);
		}

		m_pVisualizacaoDeLista->setModel(pModelo);
		//DefinirAtributoDeDados();
		
		if (pModelo)
		{
			connect(pModelo, &QAbstractItemModel::modelAboutToBeReset, this, &QVisualizacaoEmMiniatura::AoModeloPrestesASerReiniciado);
			connect(pModelo, &QAbstractItemModel::modelReset, this, &QVisualizacaoEmMiniatura::AoReiniciarOModelo);
		}
	}
}

void QVisualizacaoEmMiniatura::RolarParaLinha(const QModelIndex& indiceNaLinha, QAbstractItemView::ScrollHint dicaDeRolagem)
{
	if (indiceNaLinha.isValid())
	{
		assert(indiceNaLinha.model() == m_pVisualizacaoDeLista->model());
		m_pVisualizacaoDeLista->scrollTo(indiceNaLinha.sibling(indiceNaLinha.row(), m_pVisualizacaoDeLista->modelColumn()), dicaDeRolagem);
	}
}

void QVisualizacaoEmMiniatura::AoModeloPrestesASerReiniciado()
{
	if (!m_bRestaurarSelecao)
	{
		return;
	}

	QVisualizacaoEmArvoreAvancada::SalvarSelecao(m_backupSelecionado, m_pVisualizacaoDeLista->model(), m_pVisualizacaoDeLista->selectionModel());
}

void QVisualizacaoEmMiniatura::AoReiniciarOModelo()
{
	if (!m_bRestaurarSelecao)
	{
		return;
	}

	QVisualizacaoEmArvoreAvancada::RestaurarSelecao(m_backupSelecionado, m_pVisualizacaoDeLista->model(), m_pVisualizacaoDeLista->selectionModel());
}

void QVisualizacaoEmMiniatura::AdicionarBotãoDeDimensionamento(int tamanho, int numeroDoIcone)
{
	QToolButton* pBotao = new QToolButton();
	QString icone = QString(":/icones/VisualizaçãoTamanho1").arg(numeroDoIcone);
	// Falta connect
	pBotao->setIcon(QIcon(icone));
	pBotao->setCheckable(true);
	pBotao->setAutoRaise(true);
	m_pBotoesDeTamanhoDeVisualizacao->addButton(pBotao, tamanho);
}
