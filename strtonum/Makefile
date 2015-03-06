CC=		clang
PREFIX=		/usr/pkg
MANPREFIX=	${PREFIX}/man
SRCS=		strtonum.c
TARGET=		libstrtonum.dylib
CFLAGS=		-Wall -dynamiclib
SHARED_LIB=	-install_name ${PREFIX}/lib/${TARGET}	

all:
	${CC} ${SRCS} ${CFLAGS} ${SHARED_LIB} -o ${TARGET} 

install:
	test -d ${DESTDIR}${PREFIX}/lib || mkdir -p ${DESTDIR}${PREFIX}/lib
	install -pm 755  ${TARGET} ${DESTDIR}${PREFIX}/lib/${TARGET}
	test -d ${DESTDIR}${MANPREFIX}/man3 || mkdir -p ${DESTDIR}${MANPREFIX}/man3
	install -pm 644 strtonum.3 ${DESTDIR}${MANPREFIX}/man3/strtonum.3
	test -d ${DESTDIR}${PREFIX}/include || mkdir -p ${DESTDIR}${PREFIX}/include
	install -pm 755 strtonum.h ${DESTDIR}${PREFIX}/include/strtonum.h

deinstall:
	rm ${DESTDIR}${PREFIX}/include/strtonum.h
	rm ${DESTDIR}${MANPREFIX}/man3/strtonum.3
	rm ${DESTDIR}${PREFIX}/lib/${TARGET}

clean:
	rm ${TARGET}
