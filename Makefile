all: compiler

OBJS = grammar.o \
		token.o  \
		codegen.o \
		main.o	 \
		objgen.o \
		typesystem.o \

LLVMCONFIG = llvm-config
CPPFLAGS = `$(LLVMCONFIG) --cppflags` -std=c++17
LDFLAGS = `$(LLVMCONFIG) --ldflags` -lpthread -ldl -lz -lncurses -rdynamic -L/usr/local/lib -ljsoncpp
LIBS = `$(LLVMCONFIG) --libs`

clean:
	$(RM) -rf grammar.cpp grammar.hpp test compiler tokens.cpp *.output $(OBJS)

objgen.cpp: objgen.h

codegen.cpp: codegen.h ast.h

grammar.cpp: grammar.y
	bison -d -o $@ $<

grammar.hpp: grammar.cpp

token.cpp: token.l grammar.hpp
	flex -o $@ $<

%.o: %.cpp
	g++ -c $(CPPFLAGS) -o $@ $<

compiler: $(OBJS)
	g++ $(CPPFLAGS) -o $@ $(OBJS) $(LIBS) $(LDFLAGS)

test: compiler test.input
	cat test.input | ./compiler

testlink: output.o testmain.cpp
	clang output.o testmain.cpp -o test
	./test
