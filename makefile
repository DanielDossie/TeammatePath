GITUSERID = daldric
EXE = teams

REPODIR = ../$(COURSE)-$(SEMESTER)-cp$(CP_NUMBER)-$(GITUSERID)
TARFILE = CP$(CP_NUMBER)_$(LASTNAME)_$(USER)_$(GITUSERID).tar

FLAGS = -Wall -Wextra -g
# FLAGS = -Wall -O3
CC = g++
BIN = bin
OBJ = obj

all: $(BIN)/$(EXE)

$(BIN)/$(EXE): $(OBJ)/teams.o $(OBJ)/Vertex.o $(OBJ)/LLNode.o $(OBJ)/LL.o
	$(CC) $(FLAGS) $(OBJ)/teams.o $(OBJ)/Vertex.o $(OBJ)/LLNode.o $(OBJ)/LL.o -o $@

$(OBJ)/teams.o: teams.cpp LLNode.h LL.h Vertex.h
	$(CC) $(FLAGS) -c teams.cpp -o $@

$(OBJ)/Vertex.o: LLNode.h Vertex.cpp Vertex.h LL.h
	$(CC) $(FLAGS) -c Vertex.cpp -o $@

$(OBJ)/LLNode.o: LLNode.cpp LLNode.h
	$(CC) $(FLAGS) -c LLNode.cpp -o $@

$(OBJ)/LL.o: LL.cpp LLNode.h LL.h
	$(CC) $(FLAGS) -c LL.cpp -o $@

tar:	clean
	tar cvvf $(TARFILE) $(REPODIR)
	gzip $(TARFILE)

clean:
	rm -f $(OBJ)/*.o $(BIN)/$(EXE) *.tar.gz

