#include "service.hpp"

using namespace fga0242::service;



/**
 * Responsável pelo cálculo de frete da cooperativa AgroMart.
 */
double CalculadoraFrete::menorDistancia(int origem, std::list<int> &restantes, std::vector<std::vector<double>> &distancias) {
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

/*
    This is  hard in cpp. The easiest way is an if else ladder 
    using strcmp.

    in a beautiful world, switch would work with std::string thingy.
    It does not...
*/


//cool functions! but they'll not solve our problem...
//std::function<bool (std::string&, std::string&)> compare = [](std::string &a, std::string &b){ return std::strcmp(a.c_str(), b.c_str()) < 0;};
//const std::map<std::string, int, decltype(compare) > converter { {"DF", 1} , {"GO", 2} };

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

//implemented as an if else ladder since this is not (ew) Java
double CalculadoraFrete::calcularFrete(double pesoTotalKg, const std::string &regiao) {
    if(!std::strcmp(regiao.c_str(), "DF")){
        return BASE_DF + pesoTotalKg * TAXA_KG_DF;
    } else if(!std::strcmp(regiao.c_str(), "GO")){
        return BASE_GO + pesoTotalKg * TAXA_KG_GO;
    } 
    return BASE_OUTROS + pesoTotalKg * TAXA_KG_OUTROS;
}
        
        
/** DR LANNA GOT SOMETHING NEW TO SAY! ->
Calcula a rota de entrega de menor distância total testando TODAS
as permutações possíveis dos pontos de entrega (força bruta).

ATENÇÃO PEDAGÓGICA: a complexidade deste método é O(n!). Ele é
adequado apenas para pedidos com poucos pontos de entrega (na
prática, cooperativas pequenas raramente entregam mais que 7-8
pontos numa mesma rota). É exatamente esse tipo de método —
correto, porém sensível ao tamanho da entrada — que justifica a
existência de testes com timeout: eles funcionam como uma rede de
segurança contra regressões de desempenho.
*/
double CalculadoraFrete::calcularRotaMaisEconomica(std::list<std::string> pontosDeEntrega, std::vector<std::vector<double>> distancias) {
    std::list<int> indices;
    for (int i = 1; i < pontosDeEntrega.size(); i++) {
        indices.emplace_back(i);
    }
    return menorDistancia(0, indices, distancias);
}

