
/**
 * Perfis de cliente atendidos pela cooperativa AgroMart.
 * O tipo de cliente influencia diretamente as regras de desconto
 * aplicadas no fechamento do pedido.
 */

namespace fga0242::model{
    enum TipoCliente {
        COOPERADO,  // produtor associado à cooperativa
        VAREJO,     // pequeno comerciante / consumidor final
        ATACADO     // distribuidor / grande comprador
    };
    
    
}

