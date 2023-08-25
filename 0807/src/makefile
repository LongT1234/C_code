inc=../include
main:main.c libsta.a
	gcc $< -o $@ -lsta -L./ -I$(inc)
libsta.a:add.o sub.o
	ar -rc $@ $^
%.o:%.c	
	gcc -c $< -o $@ -I$(inc)
clean:
	rm main *.o *.a
