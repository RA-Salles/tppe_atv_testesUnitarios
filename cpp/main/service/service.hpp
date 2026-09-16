#pragma once

#include "../common/imports.hpp"
#include "../model/model.hpp"

using namespace fga0242::model;

namespace fga0242::service{
    

    //take a look at the calc test example! We're using that as a base...
    class EstoqueInsuficienteException : public std::exception {

        std::string produtoId;
        int         solicitado;
        int         disponivel;
        
        
        public:

            //this will initialize with default values.
            EstoqueInsuficienteException() = default; // produtoId{"null"}, solicitado{0}, disponivel{0}{};
        
            /*
                this error happens when you try to get more than you have inside the stock.

                inputs: 
                    std::string &produtoId : a guven product id
                    int         solicitado : the qt you wanted
                    int         disponível : the quantity it haves
            */
            EstoqueInsuficienteException(const std::string &produtoId, int solicitado, int disponivel):
                solicitado{solicitado}, disponivel{disponivel} {
                this->produtoId = produtoId;
            }
            //spits out textual explanation of error.
            const char* what();
            

            std::string getId() { return produtoId;  };
            int getSolicitado() { return solicitado; };
            int getDisponivel() { return disponivel; };

    };

    class PedidoInvalidoException : std::exception {
        std::string motivo;

        public:
            PedidoInvalidoException(std::string motivo): motivo{motivo}{};
            const char *what(){
                return motivo.c_str();
            };
    };

    class UnsupportedOperationException: std::exception {
        std::string motivo;

        public:
            UnsupportedOperationException(std::string motivo): motivo{motivo}{};
            const char *what(){
                return motivo.c_str();
            };
    };

    class CalculadoraFrete {
        private:

            static constexpr double BASE_DF        = 8.0;
            static constexpr double BASE_GO        = 12.0;
            static constexpr double BASE_OUTROS    = 25.0;
            
            static constexpr double TAXA_KG_DF     = 0.50;
            static constexpr double TAXA_KG_GO     = 0.80;
            static constexpr double TAXA_KG_OUTROS = 1.50;
            
            double menorDistancia(int origem, std::list<int> &restantes, std::vector<std::vector<double>> &distancias);
        
        public:
            

            double calcularFrete(double pesoTotalKg, const std::string &regiao);
            double calcularRotaMaisEconomica(std::list<std::string> pontosDeEntrega, std::vector<std::vector<double>> distancias);

    };

    class AplicadorDesconto {
        private:
            std::string CATEGORIA_INSUMOS    = "INSUMOS";
            std::string CATEGORIA_HORTIFRUTI = "HORTIFRUTI";

        /**
         * Calcula o percentual de desconto (ex.: 0.10 = 10%) aplicável a um
         * pedido, de acordo com o tipo de cliente, o valor total do pedido
         * e a categoria predominante dos produtos.
         */

        public:
            double calcularPercentualDesconto(const fga0242::model::TipoCliente tipoCliente, double valorTotalPedido, const std::string &categoriaProduto);

            bool isElegivelParaDesconto(fga0242::model::TipoCliente tipoCliente, double valorTotalPedido, std::string &categoriaProduto);

            double calcularValorComDesconto(const fga0242::model::TipoCliente tipoCliente, double valorTotalPedido, const std::string &categoriaProduto);
    };

    class Estoque {
    private:
        std::map<std::string, int> quantidadesPorProduto; //qtProd would make it so much EASIER to type code faster... stronger...
    
    public:

        Estoque() = default;

        /*
         * Controla a quantidade disponível de cada produto no armazém
         * da cooperativa.
        */
        void repor(Produto &produto, int quantidade);
        
        int consultarQuantidade(Produto &produto) {
            return quantidadesPorProduto[produto.getId()];
        }

        /**
         * Reserva a quantidade solicitada de um produto para um pedido.
         *
         * @throws EstoqueInsuficienteException caso a quantidade disponível
         *         seja menor que a solicitada.
         */
        void reservar(Produto &produto, int quantidadeSolicitada) ;
    };

    class PedidoService {
        private:
            Estoque           estoque;
            CalculadoraFrete  calculadoraFrete;
            AplicadorDesconto aplicadorDesconto;

            void validar(Pedido &pedido){
                if (pedido.getCliente() == nullptr) {
                    throw new PedidoInvalidoException("Pedido sem cliente associado");
                }
                if (pedido.getItens().empty()){
                    throw new PedidoInvalidoException("Pedido sem itens");
                }
            }

        public:
            PedidoService() = default;

            PedidoService(Estoque estoque, CalculadoraFrete calculadoraFrete, AplicadorDesconto aplicadorDesconto) {
                this->estoque           = estoque           ;
                this->calculadoraFrete  = calculadoraFrete  ;
                this->aplicadorDesconto = aplicadorDesconto ;
            } 

            /**
                Valida o pedido, reserva os itens no estoque e retorna o valor
                final (produtos + frete - desconto).

                @throws PedidoInvalidoException se o pedido não tiver itens ou
                        não possuir cliente associado.
                @throws EstoqueInsuficienteException se algum item não tiver
                        quantidade suficiente em estoque.
            */
            double processar(Pedido &pedido);

            /**
             * TODO (funcionalidade futura - Sprint 5): implementar frete
             * grátis para clientes ATACADO cujo valor total do pedido
             * ultrapasse R$ 1000,00. Ainda não implementado.
             */
            double processarComFreteGratisAtacado(Pedido pedido) {
                throw UnsupportedOperationException("Frete grátis para atacado ainda não implementado");
            }

    };

}
