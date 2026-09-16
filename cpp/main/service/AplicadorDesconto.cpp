
#include "service.hpp"

using namespace fga0242::service;

/**
 * Concentra as regras de desconto comercial da cooperativa AgroMart.
 *
 * Regras de negócio (RN):
 *  RN01 - Produtos da categoria "INSUMOS" nunca recebem desconto,
 *         independentemente do tipo de cliente ou do valor do pedido.
 *  RN02 - Cliente COOPERADO recebe 10% de desconto quando o valor total
 *         do pedido é >= 100.0.
 *  RN03 - Cliente ATACADO recebe 15% de desconto quando o valor total
 *         do pedido é >= 500.0, ou 5% quando está entre 100.0 (inclusive)
 *         e 500.0 (exclusive).
 *  RN04 - Cliente VAREJO recebe 5% de desconto apenas na categoria
 *         "HORTIFRUTI", quando o valor total do pedido é >= 200.0.
 */
double AplicadorDesconto::calcularPercentualDesconto(const fga0242::model::TipoCliente tipoCliente, double valorTotalPedido, const std::string &categoriaProduto) {
    if (!CATEGORIA_INSUMOS.compare(categoriaProduto)) {
        return 0.0;
    }

    switch (tipoCliente) {
        case fga0242::model::COOPERADO:
            return valorTotalPedido >= 100.0 ? 0.10 : 0.0;
        case fga0242::model::ATACADO:
            if (valorTotalPedido >= 500.0) {
                return 0.15;
            }
            return valorTotalPedido >= 100.0 ? 0.05 : 0.0;
        case fga0242::model::VAREJO:
            bool elegivel = !(CATEGORIA_HORTIFRUTI.compare(categoriaProduto)) && valorTotalPedido >= 200.0;
            return elegivel ? 0.05 : 0.0;
        default:
            return 0.0;
    }
}

bool AplicadorDesconto::isElegivelParaDesconto(fga0242::model::TipoCliente tipoCliente, double valorTotalPedido, std::string &categoriaProduto) {
    return calcularPercentualDesconto(tipoCliente, valorTotalPedido, categoriaProduto) > 0.0;
}

double AplicadorDesconto::calcularValorComDesconto( const fga0242::model::TipoCliente tipoCliente, double valorTotalPedido, const std::string &categoriaProduto) {
    double percentual = calcularPercentualDesconto(tipoCliente, valorTotalPedido, categoriaProduto);
    return valorTotalPedido * (1 - percentual);
}

