#pragma once

#include <assert.h>

template<typename D>
struct VerificacaoDeConversao
{
	VerificacaoDeConversao(D& d)
		: destino(&d)
	{}

	template<typename S>
	D& operator=(S const& s)
	{
		return VerificarConversao(*destino, s);
	}

protected:
	D* destino;
};

template<typename D, typename S>
inline D ConversaoComChecagem(S const& s)
{
	D d = D(s);
	assert(S(d) == s);
	return d;
}

template<typename D, typename S>
inline D& VerificarConversao(D& d, S const& s)
{
	d = D(s);
	assert(S(d) == s);
	return d;
}

template<typename D>
inline VerificacaoDeConversao<D> VerificarConversao(D& d)
{
	return d;
}