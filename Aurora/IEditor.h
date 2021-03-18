#pragma once
#include <QString>

class CServicoDaBarraDeFerramentas;

struct IGerenciadorDeComandos;

struct IEditor
{
	virtual ~IEditor() {}

	virtual IGerenciadorDeComandos* ObterIGerenciadorDeComandos() = 0;
	virtual CServicoDaBarraDeFerramentas* ObterServicoDaBarraDeFerramentas() = 0;
};