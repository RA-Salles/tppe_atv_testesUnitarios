//done!
#include "service.hpp"

using namespace fga0242::service;
//ah yeah, this will, most probably, get all mangled up. fixme!
const char* EstoqueInsuficienteException::what(){
    std::string ret;
    ret += "Estoque insuficiente para o produto ";
    ret += this->produtoId; 
    ret +=": solicitado=";
    ret+=this->solicitado; 
    ret+=",disponivel="; 
    ret+=this->disponivel;
    return ret.c_str();
};
