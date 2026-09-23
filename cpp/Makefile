# model graciously provided by geeksforgeeks @ https://www.geeksforgeeks.org/cpp/makefile-in-c-and-its-applications/
# yet I found it quite complex, so I'm explicitly writing the rules...
#I'LL FUCKING DO IT BY HAND THAT'S IT!


# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -g

# Target executable
TARGET = app

# For deleting the target
TARGET_DEL = app

OBJS = ./obj/app.o ./obj/client.o ./obj/item.o ./obj/order.o ./obj/product.o ./obj/discount.o ./obj/calc.o ./obj/stock.o ./obj/stockexc.o ./obj/orderexc.o ./obj/orderservice.o

all: setup app

all_tests: lentos rapidos example apptest

app: obj 
	$(CXX) $(CXXFLAGS) -o app $(OBJS)

setup:
	mkdir -p obj

obj: setup app.o client.o item.o order.o product.o discount.o calc.o stock.o stockexc.o orderexc.o orderservice.o

t_obj: setup client.o item.o order.o product.o discount.o calc.o stock.o stockexc.o orderexc.o orderservice.o


#main object
app.o: setup ./main/App.cpp
	$(CXX) $(CXXFLAGS) -c ./main/App.cpp -o ./obj/app.o

#model objects
client.o: setup ./main/model/Cliente.cpp
	$(CXX) $(CXXFLAGS) -c ./main/model/Cliente.cpp -o ./obj/client.o

item.o: setup ./main/model/ItemPedido.cpp
	$(CXX) $(CXXFLAGS) -c ./main/model/ItemPedido.cpp -o ./obj/item.o

order.o: setup ./main/model/Pedido.cpp
	$(CXX) $(CXXFLAGS) -c ./main/model/Pedido.cpp -o ./obj/order.o

product.o: setup ./main/model/Produto.cpp
	$(CXX) $(CXXFLAGS) -c ./main/model/Produto.cpp -o ./obj/product.o

#service objects
discount.o: setup ./main/service/AplicadorDesconto.cpp
	$(CXX) $(CXXFLAGS) -c ./main/service/AplicadorDesconto.cpp -o ./obj/discount.o

calc.o: setup ./main/service/CalculadoraFrete.cpp
	$(CXX) $(CXXFLAGS) -c ./main/service/CalculadoraFrete.cpp -o ./obj/calc.o

stock.o: setup ./main/service/Estoque.cpp
	$(CXX) $(CXXFLAGS) -c ./main/service/Estoque.cpp -o ./obj/stock.o

stockexc.o: setup ./main/service/EstoqueInsuficienteException.cpp
	$(CXX) $(CXXFLAGS) -c ./main/service/EstoqueInsuficienteException.cpp -o ./obj/stockexc.o

orderexc.o: setup ./main/service/PedidoInvalidoException.cpp
	$(CXX) $(CXXFLAGS) -c ./main/service/PedidoInvalidoException.cpp -o ./obj/orderexc.o

orderservice.o: setup ./main/service/PedidoService.cpp
	$(CXX) $(CXXFLAGS) -c ./main/service/PedidoService.cpp -o ./obj/orderservice.o

# tests
lentos: setup t_obj 
	$(CXX) $(CXXFLAGS) ./test/categorias/TestesLentos.cpp ./obj/* -o ./lentos

rapidos: setup t_obj
	$(CXX) $(CXXFLAGS) ./test/categorias/TestesRapidos.cpp ./obj/* -o ./rapidos

example: setup t_obj
	$(CXX) $(CXXFLAGS) ./test/service/ExemploEstiloTest.cpp ./obj/* -o ./exemplo_teste

apptest:
	$(CXX) $(CXXFLAGS) ./test/AppTest.cpp -o ./apptest

#cleanup
clear: 
	rm -r obj

clean:
	rm app lentos rapidos exemplo_teste apptest



