#pragma once

#include "IEditor.h"
#include "GerenciadorDeComando.h"
#include "Evento.h"

class CGerenciadorDeProjeto;

class CEditor : public IEditor
{
	public:
		CEditor();
		~CEditor();

		CGerenciadorDeComandosDoEditor* ObterGerenciadorDeComandos() { return m_pGerenciadorDeComandos; }
		IGerenciadorDeComandos* ObterIGerenciadorDeComandos() { return m_pGerenciadorDeComandos; }
		virtual CServicoDaBarraDeFerramentas* ObterServicoDaBarraDeFerramentas() override { return m_pServicoDaBarraDeFerramentas; }

	protected:
		CGerenciadorDeComandosDoEditor* m_pGerenciadorDeComandos;
		CGerenciadorDeProjeto* m_pGerenciadorDeProjeto;
		CServicoDaBarraDeFerramentas* m_pServicoDaBarraDeFerramentas;
};

CEditor* ObterEditor();

