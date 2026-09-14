export module fga0242.model;

import std;


class Cliente {

    private final String nome;
    private final TipoCliente tipo;



    public Cliente(String nome, TipoCliente tipo) {
        this.nome = nome;
        this.tipo = tipo;
    }

    public String getNome() {
        return nome;
    }

    public TipoCliente getTipo() {
        return tipo;
    }
};
