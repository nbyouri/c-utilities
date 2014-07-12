CC=		clang
PREFIX=		/usr/pkg
CFLAGS=		-Weverything -dynamiclib
LDFLAGS=	
SRCS=		progressmeter.c
TARGET=		libprogressmeter.dylib
SHARED_LIB=	-install_name ${PREFIX}/lib/${TARGET}	

all:
	${CC} ${CFLAGS} ${LDFLAGS} ${SRCS} ${SHARED_LIB} -o ${TARGET}

install:
	test -f ${DESTDIR}${PREFIX}/lib || mkdir -p ${DESTDIR}${PREFIX}/lib
	test -f ${DESTDIR}${PREFIX}/include || mkdir -p ${DESTDIR}${PREFIX}/include
	install -pm 755 ${TARGET} ${DESTDIR}${PREFIX}/lib/${TARGET}
	install -pm 755 progressmeter.h ${DESTDIR}${PREFIX}/include/progressmeter.h

uninstall:
	rm ${DESTDIR}${PREFIX}/lib/${TARGET}
	rm ${DESTDIR}${PREFIX}/include/progressmeter.h
	
clean:
	rm ${TARGET}
	
