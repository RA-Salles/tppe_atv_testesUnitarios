//#include "TipoCliente.hpp" //unused file kept for parity sake!
#pragma once

#include "../common/imports.hpp"


namespace fga0242::model{

    enum TipoCliente {
        COOPERADO,  // produtor associado à cooperativa
        VAREJO,     // pequeno comerciante / consumidor final
        ATACADO     // distribuidor / grande comprador
    };

    class Cliente {
        private:
            std::string nome;
            TipoCliente tipo;


        public:
            Cliente(): nome{}, tipo{TipoCliente::VAREJO} {}; //beware, this might not be what you want. Make sure to later alter these values...
            Cliente(std::string &nome, TipoCliente tipo);
        
            std::string getNome();
        
            TipoCliente getTipo();

            Cliente& operator=(Cliente &outro);
    };

    

    class Produto {
        private:
            std::string id;
            std::string nome;
            std::string categoria; // "HORTIFRUTI", "GRAOS", "LATICINIOS", "INSUMOS"
            double precoUnitario;
            double pesoKg;
        public:
            Produto();
            Produto(std::string &id, std::string &nome, std::string &categoria, double precoUnitario, double pesoKg);
            std::string getId();
            std::string getNome();
            std::string getCategoria();
            double getPrecoUnitario();
            double getPesoKg();
            Produto& operator=(const Produto &outro);
    };

    class ItemPedido {
        private:
            Produto produto;
            int     quantidade;
        
        public:
            ItemPedido(Produto &produto, int quantidade);

            Produto getProduto();
            int     getQuantidade();
            double  getSubtotal();
            double  getPesoTotal();
    };

    class Pedido {
        private:
            Cliente *cliente;
            std::list<ItemPedido> itens;
            std::string regiaoEntrega; // "DF", "GO", "OUTROS"

        public: 
            Pedido(Cliente &cliente, std::list<ItemPedido> &itens, std::string &regiaoEntrega);

            Cliente *getCliente();

            const std::list<ItemPedido> getItens();

            std::string getRegiaoEntrega();

            double getValorTotalProdutos();

            double getPesoTotal();
    };

};
