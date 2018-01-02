a.out: cal_client.o cal_impl.o
		gcc cal_client.o cal_impl.o

cal_client.o: cal_client.c cal.h
		gcc -c cal_client.c

cal_impl.o: cal_impl.c cal.h
		gcc -c cal_impl.c