CC=		clang
PREFIX=		/usr/pkg
MANPREFIX=	${PREFIX}/man
SRCS=		humanize_number.c dehumanize_number.c
TARGET=		libhn.dylib
CFLAGS=		-Wall -dynamiclib
SHARED_LIB=	-install_name ${PREFIX}/lib/${TARGET}	

all:
	${CC} ${SRCS} ${CFLAGS} ${SHARED_LIB} -o ${TARGET} 

install:
	test -d ${DESTDIR}${PREFIX}/lib || mkdir -p ${DESTDIR}${PREFIX}/lib
	install -pm 755  ${TARGET} ${DESTDIR}${PREFIX}/lib/${TARGET}
	test -d ${DESTDIR}${MANPREFIX}/man3 || mkdir -p ${DESTDIR}${MANPREFIX}/man3
	install -pm 644 humanize_number.3 ${DESTDIR}${MANPREFIX}/man3/humanize_number.3
	test -d ${DESTDIR}${PREFIX}/include || mkdir -p ${DESTDIR}${PREFIX}/include
	install -pm 755 humanize_number.h ${DESTDIR}${PREFIX}/include/humanize_number.h

deinstall:
	rm ${DESTDIR}${PREFIX}/include/humanize_number.h
	rm ${DESTDIR}${MANPREFIX}/man3/humanize_number.3
	rm ${DESTDIR}${PREFIX}/lib/${TARGET}

clean:
	rm ${TARGET}
