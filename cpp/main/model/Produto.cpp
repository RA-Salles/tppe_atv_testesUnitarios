#include "../common/imports.hpp"
#include "model.hpp"
using namespace fga0242::model;

//inicialização é mais complicadinha...

Produto::Produto(std::string &id       , std::string &nome   ,
                 std::string &categoria, double precoUnitario,
                 double pesoKg):
                 id           {id           },
                 nome         {nome         },
                 categoria    {categoria    },
                 precoUnitario{precoUnitario},
                 pesoKg       {pesoKg       } {

}

//WHY IS THE ID A STRING!? 
Produto::Produto(): 
    id           {""},
    nome         {""},
    categoria    {""},
    precoUnitario{0} ,
    pesoKg       {0}{
}

//exemplo graciosamente encontrado na referência do cpp, cppreference
Produto& Produto::operator=(const Produto &outro){
    // Guard self assignment
    if (this == &outro)
        return *this;
    
    //copia valores;
    this->categoria     = outro.categoria     ;
    this->id            = outro.id            ;
    this->nome          = outro.nome          ;
    this->pesoKg        = outro.pesoKg        ;
    this->precoUnitario = outro.precoUnitario ;

    return *this;
}


std::string Produto::getId()            {return id;           }
std::string Produto::getNome()          {return nome;         }
std::string Produto::getCategoria()     {return categoria;    }
double      Produto::getPrecoUnitario() {return precoUnitario;}
double      Produto::getPesoKg()        {return pesoKg;       }
