#include "model.hpp"

using namespace fga0242::model;

        
Pedido::Pedido(Cliente &cliente, std::list<ItemPedido> &itens, std::string &regiaoEntrega) {
    this->cliente       = cliente;
    this->itens         = itens; //why are we trying to keep this as a pointer, wtf?
    this->regiaoEntrega = regiaoEntrega;
}

Cliente                     Pedido::getCliente()       { return cliente; }
const std::list<ItemPedido> Pedido::getItens()         { return std::list<ItemPedido>(this->itens); }
std::string                 Pedido::getRegiaoEntrega() { return regiaoEntrega; }

double Pedido::getValorTotalProdutos() {
    double total = 0.0;
    for (ItemPedido item : itens) {
        total += item.getSubtotal();
    } 
    return total;
}

double Pedido::getPesoTotal() {
    double peso = 0.0;
    for (auto item : itens){
        peso += item.getPesoTotal();
    } 
    return peso;
}
