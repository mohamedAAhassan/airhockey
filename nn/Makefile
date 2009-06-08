CC = g++
CFLAGS = -Wall
OBJS = nevronske_mreze2.cpp LearnNeuralNetwork.cpp Matrix.cpp NeuralNetwork.cpp Neuron.cpp NeuronLayer.cpp NNParser.cpp Error.cpp DeltaError.cpp

all: ${OBJS}
	${CC} ${CFLAGS} -o nn ${OBJS}
	
tests:
	${CC} ${CFLAGS} -o tests unit_test.cpp Neuron.cpp -lcppunit
	
clean:
	rm -rf nn
	rm -rf tests
