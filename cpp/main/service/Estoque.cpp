#include "service.hpp"

using namespace fga0242::model;
using namespace fga0242::service;


void Estoque::repor(Produto &produto, int quantidade) {
    //if product not found, register
    if(quantidadesPorProduto.find(produto.getId()) == quantidadesPorProduto.end()){
        quantidadesPorProduto[produto.getId()] = quantidade;
    }else{ // go ahead and add it to what we got...
        quantidadesPorProduto[produto.getId()] += quantidade;
    }
}

//other code was the dirtiest nastiest object oriented slop I've ever seen.
// ACCESS IT WITH OPERATOR[] AND BE DONE! BE... GONE!!

/*
    interface of access to internal map. 
    Accesses product's registered id.
*/
int Estoque::consultarQuantidade(Produto &produto) {
    return quantidadesPorProduto[produto.getId()];
}

/** 
Reserva a quantidade solicitada de um produto para um pedido.

    @throws EstoqueInsuficienteException caso a quantidade disponível
        seja menor que a solicitada.


    @related test this documentation style
*/
void Estoque::reservar(Produto &produto, int quantidadeSolicitada) {
    int disponivel = consultarQuantidade(produto);
    if (quantidadeSolicitada > disponivel) {
        // EstoqueInsuficienteException( std::string &produtoId, int solicitado, int disponivel)
        auto err = EstoqueInsuficienteException(produto.getId(), 1, 2);
        throw err;
        //throw fga0242::service::EstoqueInsuficienteException(produto.getId(), quantidadeSolicitada, disponivel);
    }
    
    quantidadesPorProduto[produto.getId()] = disponivel - quantidadeSolicitada;
}
