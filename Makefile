Compiler=g++ -std=c++20
BUILD_DIRECTORY=build

.PHONY: all clean

all: UTaste

UTaste: $(BUILD_DIRECTORY)/main.o $(BUILD_DIRECTORY)/Utaste.o $(BUILD_DIRECTORY)/reserves.o $(BUILD_DIRECTORY)/helperfunctions.o $(BUILD_DIRECTORY)/Utaste.o $(BUILD_DIRECTORY)/constants.o $(BUILD_DIRECTORY)/exception.o $(BUILD_DIRECTORY)/restaurant.o $(BUILD_DIRECTORY)/command.o $(BUILD_DIRECTORY)/put.o $(BUILD_DIRECTORY)/post.o $(BUILD_DIRECTORY)/get.o $(BUILD_DIRECTORY)/delete.o 
	$(Compiler) $^ -o UTaste

$(BUILD_DIRECTORY):
	mkdir -p $(BUILD_DIRECTORY)

$(BUILD_DIRECTORY)/main.o: main.cpp head.hpp Utaste.hpp | $(BUILD_DIRECTORY)
	$(Compiler) -c main.cpp -o $(BUILD_DIRECTORY)/main.o

$(BUILD_DIRECTORY)/constants.o: constants.cpp constants.hpp| $(BUILD_DIRECTORY)
	$(Compiler) -c constants.cpp -o $(BUILD_DIRECTORY)/constants.o

$(BUILD_DIRECTORY)/reserves.o: reserves.cpp reserves.hpp head.hpp| $(BUILD_DIRECTORY)
	$(Compiler) -c reserves.cpp -o $(BUILD_DIRECTORY)/reserves.o	

$(BUILD_DIRECTORY)/helperfunctions.o: helperfunctions.cpp head.hpp| $(BUILD_DIRECTORY)
	$(Compiler) -c helperfunctions.cpp -o $(BUILD_DIRECTORY)/helperfunctions.o

$(BUILD_DIRECTORY)/exception.o: exception.cpp exception.hpp head.hpp| $(BUILD_DIRECTORY)
	$(Compiler) -c exception.cpp -o $(BUILD_DIRECTORY)/exception.o

$(BUILD_DIRECTORY)/Utaste.o: Utaste.cpp Utaste.hpp put.hpp put.cpp post.hpp post.cpp get.hpp get.cpp delete.hpp delete.cpp head.hpp exception.hpp| $(BUILD_DIRECTORY)
	$(Compiler) -c Utaste.cpp -o $(BUILD_DIRECTORY)/Utaste.o

$(BUILD_DIRECTORY)/command.o: command.cpp command.hpp head.hpp restaurant.hpp| $(BUILD_DIRECTORY)
	$(Compiler) -c command.cpp -o $(BUILD_DIRECTORY)/command.o

$(BUILD_DIRECTORY)/put.o: put.cpp put.hpp command.hpp head.hpp Utaste.hpp| $(BUILD_DIRECTORY)
	$(Compiler) -c put.cpp -o $(BUILD_DIRECTORY)/put.o

$(BUILD_DIRECTORY)/post.o: post.cpp post.hpp command.hpp head.hpp Utaste.hpp| $(BUILD_DIRECTORY)
	$(Compiler) -c post.cpp -o $(BUILD_DIRECTORY)/post.o

$(BUILD_DIRECTORY)/delete.o: delete.cpp delete.hpp command.hpp head.hpp Utaste.hpp| $(BUILD_DIRECTORY)
	$(Compiler) -c delete.cpp -o $(BUILD_DIRECTORY)/delete.o

$(BUILD_DIRECTORY)/get.o: get.cpp get.hpp command.hpp head.hpp Utaste.hpp| $(BUILD_DIRECTORY)
	$(Compiler) -c get.cpp -o $(BUILD_DIRECTORY)/get.o

$(BUILD_DIRECTORY)/restaurant.o: restaurant.cpp restaurant.hpp head.hpp reserves.hpp reserves.cpp| $(BUILD_DIRECTORY)
	$(Compiler) -c restaurant.cpp -o $(BUILD_DIRECTORY)/restaurant.o



clean:
	rm -rf $(BUILD_DIRECTORY) UTaste
