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

    class CalculadoraFrete {
    private:

        static const double BASE_DF        = 8.0;
        static const double BASE_GO        = 12.0;
        static const double BASE_OUTROS    = 25.0;
        
        static const double TAXA_KG_DF     = 0.50;
        static const double TAXA_KG_GO     = 0.80;
        static const double TAXA_KG_OUTROS = 1.50;
        //cool functions! but they'll not solve our problem...
        //std::function<bool (std::string&, std::string&)> compare = [](std::string &a, std::string &b){ return std::strcmp(a.c_str(), b.c_str()) < 0;};
        //const std::map<std::string, int, decltype(compare) > converter { {"DF", 1} , {"GO", 2} };
;
    /**
     * Calcula o valor do frete a partir do peso total do pedido e da
     * região de entrega.
     */
        double menorDistancia(int origem, std::list<int> restantes, std::vector<std::vector<double>> &distancias) {
            if (restantes.empty()) {
                return 0.0;
            }
            double menor = std::numeric_limits<double>::max();
            int proximo;
            std::list<int>::iterator it;
            for (int i = 0; i < restantes.size(); i++) {
                
                //this is kind of complicated in cpp for a list type
                //int proximo = restantes.get(i);
                it = restantes.begin();
                std::advance(it, i-1);
                proximo = *it; //all that to get whatever is in i... 
                
                std::list<int> semProximo{restantes};
                semProximo.remove(i);
                double distancia = distancias[origem][proximo] + menorDistancia(proximo, semProximo, distancias);
                menor = std::min(menor, distancia);
            }
            return menor;
        }
    public:

        /*
            This is  hard in cpp. The easiest way is an if else ladder 
            using strcmp.

            in a beautiful world, switch would work with std::string thingy.
            It does not...
        */
        

        double calcularFrete(double pesoTotalKg, std::string &regiao) {
            if(!std::strcmp(regiao.c_str(), "DF")){
                return BASE_DF + pesoTotalKg * TAXA_KG_DF;
            } else if(!std::strcmp(regiao.c_str(), "DF")){
                return BASE_GO + pesoTotalKg * TAXA_KG_GO;
            } 
            return BASE_OUTROS + pesoTotalKg * TAXA_KG_OUTROS;
        }
        
        /* 
        double calcularFrete(double pesoTotalKg, std::string &regiao) {
            auto res = converter[regiao]; //fixme

            switch (res) {
                case "DF":
                    return BASE_DF + pesoTotalKg * TAXA_KG_DF;
                case "GO":
                    return BASE_GO + pesoTotalKg * TAXA_KG_GO;
                default:
                    return BASE_OUTROS + pesoTotalKg * TAXA_KG_OUTROS;
            }
        }
        */
        /**
         * Calcula a rota de entrega de menor distância total testando TODAS
         * as permutações possíveis dos pontos de entrega (força bruta).
         *
         * ATENÇÃO PEDAGÓGICA: a complexidade deste método é O(n!). Ele é
         * adequado apenas para pedidos com poucos pontos de entrega (na
         * prática, cooperativas pequenas raramente entregam mais que 7-8
         * pontos numa mesma rota). É exatamente esse tipo de método —
         * correto, porém sensível ao tamanho da entrada — que justifica a
         * existência de testes com timeout: eles funcionam como uma rede de
         * segurança contra regressões de desempenho.
         */
        double calcularRotaMaisEconomica(std::list<std::string> pontosDeEntrega, std::vector<std::vector<double>> distancias) {
            std::list<int> indices;
            for (int i = 1; i < pontosDeEntrega.size(); i++) {
                indices.emplace_back(i);
            }
            return menorDistancia(0, indices, distancias);
        }

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
            double calcularPercentualDesconto(fga0242::model::TipoCliente tipoCliente, double valorTotalPedido, std::string &categoriaProduto);

            bool isElegivelParaDesconto(fga0242::model::TipoCliente tipoCliente, double valorTotalPedido, std::string &categoriaProduto);

            double calcularValorComDesconto(fga0242::model::TipoCliente tipoCliente, double valorTotalPedido, std::string categoriaProduto);
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
        void repor(Produto &produto, int quantidade) ;
        
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

}