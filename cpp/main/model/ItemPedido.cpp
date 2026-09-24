#include "model.hpp"

using namespace fga0242::model;

ItemPedido::ItemPedido(Produto &produto, int quantidade){
    this->produto    = produto; // todo! -> check if we're copying or referencing passed product...
    this->quantidade = quantidade;
}

//this class would benefit from not giving access to the registered product
Produto  ItemPedido::getProduto()    { return produto;                                 }
int      ItemPedido::getQuantidade() { return quantidade;                              }
double   ItemPedido::getSubtotal()   { return produto.getPrecoUnitario() * quantidade; }
double   ItemPedido::getPesoTotal()  { return produto.getPesoKg() * quantidade;        }
