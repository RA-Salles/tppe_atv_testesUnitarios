#include "service.hpp"

using namespace fga0242::service;
/**
 * Orquestra o processamento de um pedido: validação, reserva de
 * estoque, cálculo de frete e aplicação de desconto.
 */
 
double PedidoService::processar(Pedido &pedido) {
    validar(pedido);
    // we do this so the compiler doesn't get very angry... 
    // actual work order won't get altered by reserving stuff!
    for(auto item : pedido.getItens()){
        auto prod = item.getProduto() ;  //
        auto qt = item.getQuantidade(); //
        estoque.reservar(prod, qt); 
    }

    double valorProdutos = pedido.getValorTotalProdutos();
    double frete = calculadoraFrete.calcularFrete(pedido.getPesoTotal(), pedido.getRegiaoEntrega());

    // Simplificação didática: usa a categoria do primeiro item como
    // categoria de referência para o cálculo de desconto.

    // estranhamente, usa apenas o primeiro item da lista pra cálculo do desconto. 
    // solução correta seria aplicar desconto por item?

    //std::string categoriaReferencia = pedido.getItens().get(0).getProduto().getCategoria(); //original line. Somewhat hard, will require some copies...
    ItemPedido item = *(pedido.getItens().begin()); //will complain if not done with this copy...

    double valorComDesconto = aplicadorDesconto.calcularValorComDesconto(
        pedido.getCliente()->getTipo(), valorProdutos, item.getProduto().getCategoria()
    );
    
    return valorComDesconto + frete;
}

