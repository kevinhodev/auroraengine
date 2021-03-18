#include "GerenciadorDeProjeto.h"

#include "CQuadroPrincipal.h"
#include "GerenciadorDeComando.h"
#include "DialogoSelecionarProjeto.h"

namespace Comandos
{
    void CriarProjeto()
    {
        CDialogoSelecionarProjeto* dialogo = new CDialogoSelecionarProjeto(CQuadroPrincipal::ObterInstancia(), CDialogoSelecionarProjeto::Tab::Criar);
        dialogo->resize(586, 408);
        dialogo->exec();
    }
}

CGerenciadorDeProjeto::CGerenciadorDeProjeto()
{
    // Novo -> Projeto.
    AuxiliarDoGerenciadorDeComando::RegistrarComando(ObterEditor()->ObterGerenciadorDeComandos(), "Projeto", "Novo", CDescricaoDoComando("Criar Novo Projeto..."), functor(Comandos::CriarProjeto));
    ObterEditor()->ObterGerenciadorDeComandos()->RegistrarDescricaoDaIU("Projeto", "Novo", "Projeto...", CAtalhoDeTeclado("Ctrl+Shift+N"), "", false);
}

