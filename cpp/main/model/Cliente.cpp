#include "model.hpp"

using namespace fga0242::model;

Cliente::Cliente(std::string &nome, TipoCliente tipo) {
    this->nome = nome;
    this->tipo = tipo;
};

//now we can do cliente1 = cliente2. Very good!
Cliente& Cliente::operator=(Cliente &outro){
    if(this == &outro)
        return *this;
    this->nome = outro.nome;
    this->tipo = outro.tipo;
    return *this;
}
std::string Cliente::getNome()      { return this->nome; };
enum TipoCliente Cliente::getTipo() { return this->tipo; };
