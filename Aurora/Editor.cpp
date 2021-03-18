#include "Editor.h"

#include "GerenciadorDeProjeto.h"
#include "ServicoDaBarraDeFerramentas.h"
#include "DialogoSobre.h"

namespace ComandoDeFocoDoEditor
{
	void Salvar()
	{
		CEventoDeComando("Geral.Salvar").EnvieParaOFocoDoTeclado();
	}

	void SalvarComo()
	{
		CEventoDeComando("Geral.SalvarComo").EnvieParaOFocoDoTeclado();
	}

	void IrParaDocumentacao()
	{
		CEventoDeComando("Geral.Ajuda").EnvieParaOFocoDoTeclado();
	}

	void AbrirDialogSobre()
	{
		CDialogoSobre* m_pDialogoSobre = new CDialogoSobre(CQuadroPrincipal::ObterInstancia());
		m_pDialogoSobre->setWindowTitle("Sobre o Aurora...");
		m_pDialogoSobre->exec();
	}
}

static CEditor* s_pEditor = nullptr;

CEditor* ObterEditor() { return s_pEditor; }

CEditor::CEditor()
{
	s_pEditor = this;
	m_pGerenciadorDeComandos = new CGerenciadorDeComandosDoEditor();
	m_pGerenciadorDeProjeto = new CGerenciadorDeProjeto();
	m_pServicoDaBarraDeFerramentas = new CServicoDaBarraDeFerramentas();

	/* Menu Arquivo */
	AuxiliarDoGerenciadorDeComando::RegistrarComando(ObterGerenciadorDeComandos(), "Geral", "Salvar", CDescricaoDoComando("Comando 'Salvar' baseado em contexto"), functor(ComandoDeFocoDoEditor::Salvar));
	ObterGerenciadorDeComandos()->RegistrarDescricaoDaIU("Geral", "Salvar", "Salvar", CAtalhoDeTeclado::TeclaPadrao::Salvar, ":/icones/IconeSalvar", false);

	AuxiliarDoGerenciadorDeComando::RegistrarComando(ObterGerenciadorDeComandos(), "Geral", "SalvarComo", CDescricaoDoComando("Comando 'Salvar Como' baseado em contexto"), functor(ComandoDeFocoDoEditor::SalvarComo));
	ObterGerenciadorDeComandos()->RegistrarDescricaoDaIU("Geral", "SalvarComo", "Salvar Como...", CAtalhoDeTeclado::TeclaPadrao::SalvarComo, ":/icones/IconeSalvarComo", false);
	/*--------------*/

	/* Menu Ajuda */
	AuxiliarDoGerenciadorDeComando::RegistrarComando(ObterGerenciadorDeComandos(), "Geral", "Ajuda", CDescricaoDoComando("Ir Para Documentação..."), functor(ComandoDeFocoDoEditor::IrParaDocumentacao));
	ObterGerenciadorDeComandos()->RegistrarDescricaoDaIU("Geral", "Ajuda", QStringLiteral("Ir Para Documentação..."), CAtalhoDeTeclado::TeclaPadrao::WikiDeAjuda, ":/icones/IconeIrParaDocumentacao", false);

	AuxiliarDoGerenciadorDeComando::RegistrarComando(ObterGerenciadorDeComandos(), "Geral", "Sobre", CDescricaoDoComando("Sobre o Aurora..."), functor(ComandoDeFocoDoEditor::AbrirDialogSobre));
	ObterGerenciadorDeComandos()->RegistrarDescricaoDaIU("Geral", "Sobre", QStringLiteral("Sobre o Aurora..."), "", "", false);
	/*------------*/
}

CEditor::~CEditor()
{
	delete m_pGerenciadorDeComandos;
}