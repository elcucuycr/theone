#this is makefile of 静态链接
main1.out:analysis_order.o main.o
	gcc -o main1.out analysis_order.o main.o
main.o:main.c
	gcc -c main.c -o main.o
analysis_order.o:analysis_order.c
	gcc -c analysis_order.c -o analysis_order.o
clean:
	rm -f *.o main1.out
