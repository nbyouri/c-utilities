CC=		clang
PREFIX=		/usr/pkg
CFLAGS=		-Weverything -dynamiclib
LDFLAGS=	
SRCS=		xmalloc.c
TARGET=		xmalloc.dylib
SHARED_LIB=	-install_name ${PREFIX}/lib/${TARGET}	

all:
	${CC} ${CFLAGS} ${LDFLAGS} ${SRCS} ${SHARED_LIB} -o ${TARGET}

install:
	test -f ${DESTDIR}${PREFIX}/lib || mkdir -p ${DESTDIR}${PREFIX}/lib
	test -f ${DESTDIR}${PREFIX}/include || mkdir -p ${DESTDIR}${PREFIX}/include
	install -pm 755 xmalloc.dylib ${DESTDIR}${PREFIX}/lib/libxmalloc.dylib
	install -pm 755 xmalloc.h ${DESTDIR}${PREFIX}/include/xmalloc.h

clean:
	rm ${TARGET}
	
