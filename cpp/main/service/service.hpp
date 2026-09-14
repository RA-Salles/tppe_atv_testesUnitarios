#include "../common/imports.hpp"
#include "../model/TipoCliente.hpp"

namespace fga0242::service{
    //take a look at the calc test example! We're using that as a base...
    class EstoqueInsuficienteException : public std::exception {

        std::string produtoId;
        int         solicitado;
        int         disponivel;
        
        
        public:

            //this will initialize with default values.
            EstoqueInsuficienteException(): produtoId{"null"}, solicitado{0}, disponivel{0}{};
        
            //and this will initialize it with specified values...
            EstoqueInsuficienteException(std::string &produtoId, int solicitado, int disponivel):
            produtoId{produtoId}, solicitado{solicitado}, disponivel{disponivel}{
            }
            //spits out textual explanation of error.
            const char* what();
            

            int getValue() {return -1;};
    };
}