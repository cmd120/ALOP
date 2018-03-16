objects=LR_GD.o LR_GD_M.o
cc=g++
run: $(objects)
	$(cc) -o run $(objects) 

LR_GD.o: LR_GD.cpp
	$(cc) -c LR_GD.cpp

LR_GD_M.o: LR_GD_M.cpp
	$(cc) -c LR_GD_M.cpp

clean:
	rm run $(objects)