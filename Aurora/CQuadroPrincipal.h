#pragma once

#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QWidget>

class CDialogoSobre;

#include "Menu.h"
#include "Editor.h"

/*
 * - Essa Classe representa a Interface Principal do Usuário.
 * - Manipula a Barra de Menus, de Ferramentas e Status.  
 * - Como só deve ter uma instância dessa classe, ela deve ser implementada usando o padrão singleton.
 */

class CQuadroPrincipal : public QMainWindow
{
    Q_OBJECT

    public:
        CQuadroPrincipal(QWidget* pai = nullptr);
        ~CQuadroPrincipal();
        void ConfigurarIU(QMainWindow* janelaPrincipal);
        void PosCarregamento();
        void InicializarMenus();

        static CQuadroPrincipal* ObterInstancia();
        static CQuadroPrincipal* s_pIntancia;

    private:
        QMenuBar* m_pBarraDeMenus = nullptr;

        CMenu* m_pMenuArquivo = nullptr;
        CMenu* m_pMenuNovoArquivo = nullptr;
        CMenu* m_pMenuAbrirArquivo = nullptr;
        QMenu* m_pMenuArquivosRecentes = nullptr;

        QMenu* m_pMenuEditar = nullptr;
        QMenu* m_pMenuAlinharSnap = nullptr;
        QMenu* m_pMenuModoDeEdicao = nullptr;
        QMenu* m_pMenuConstranger = nullptr;
        QMenu* m_pMenuRotacaoRapida = nullptr;
        QMenu* m_pMenuCoordenadas = nullptr;

        CMenu* m_pMenuNivel = nullptr;
        CMenu* m_pMenuFisicas = nullptr;
        CMenu* m_pMenuGrupo = nullptr;
        CMenu* m_pMenuVincular = nullptr;
        CMenu* m_pMenuPrefabricados = nullptr;
        CMenu* m_pMenuSelecao = nullptr;
        CMenu* m_pMenuMascaraDeSelecao = nullptr;
        CMenu* m_pMenuIluminacao = nullptr;
        CMenu* m_pMenuMaterial = nullptr;

        CMenu* m_pMenuExibicao = nullptr;
        CMenu* m_pMenuGraficos = nullptr;
        CMenu* m_pMenuInformacoesDeExibicao = nullptr;
        CMenu* m_pMenuLocalizacao = nullptr;
        CMenu* m_pMenuLembrarLocalizacao = nullptr;
        CMenu* m_pMenuIrParaLocalizacao = nullptr;
        CMenu* m_pMenuAlterarCamera = nullptr;

        CMenu* m_pMenuJogo = nullptr;
        CMenu* m_pMenuAudio = nullptr;
        QAction* m_pAcaoMutarAudio = nullptr;
        QAction* m_pAcaoPararTodosOsSons = nullptr;
        QAction* m_pAcaoAtualizarAudio = nullptr;
        CMenu* m_pMenuIA = nullptr;

        CMenu* m_pMenuDepurar = nullptr;
        CMenu* m_pMenuRecarregarScripts = nullptr;
        CMenu* m_pMenuAvancado = nullptr;
        QAction* m_pAcaoReduzirConjuntoDeTrabalho = nullptr;
        QAction* m_pAcaoMostrarArquivoDeLog = nullptr;

        CMenu* m_pMenuFerramentas = nullptr;

        CMenu* m_pMenuLayout = nullptr;

        CMenu* m_pMenuAjuda = nullptr;

        CEditor* m_pEditor = nullptr;
        CDialogoSobre* m_pDialogoSobre = nullptr;
};
