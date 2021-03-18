#include "DialogoSobre.h"

#include <QLabel>
#include <QBoxLayout>
#include <QPushButton>

CDialogoSobre::CDialogoSobre(CQuadroPrincipal* pPai)
	: QDialog(pPai)
{
	setModal(true);
	QVBoxLayout* layout = new QVBoxLayout();
	setLayout(layout);

	m_pRotuloVersao = new QLabel();
	m_pRotuloVersao->setText("0.1");

	m_pRotuloInformacoesMista = new QLabel();
	m_pRotuloInformacoesMista->setText(QStringLiteral("Aurora(R) Caixa de Areia(TM) Editor\nDireito Autoral 2019, Kevin Brabo\n\Aquom, o Logo do Aquom, Aurora, Caixa de Areia são marcas registradas do Kevin Brabo.\n"));

	QPixmap* logo = new QPixmap(":/icones/ImagemSobre");
	QLabel* imagemDoLogo = new QLabel();
	imagemDoLogo->setPixmap(*logo);

	QPushButton* botaoFechar = new QPushButton(tr("&Fechar"));
	connect(botaoFechar, SIGNAL(clicked()), pPai, SLOT(reject()));
	/*connect(botaoFechar, &QPushButton::clicked, [this]()
	{
		close();
	});*/

	QHBoxLayout* layoutDoBotao = new QHBoxLayout();
	layoutDoBotao->addStretch(1);
	layoutDoBotao->addWidget(botaoFechar);

	layout->addWidget(imagemDoLogo, 0, Qt::AlignCenter);
	layout->addWidget(m_pRotuloInformacoesMista);
	layout->addWidget(m_pRotuloVersao);
	layout->addLayout(layoutDoBotao);

	setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
}

CDialogoSobre::~CDialogoSobre()
{
	close();
}
