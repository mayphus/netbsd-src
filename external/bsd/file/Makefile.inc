#	$NetBSD: Makefile.inc,v 1.8 2024/10/30 18:09:18 christos Exp $

WARNS=4
DIST=${NETBSDSRCDIR}/external/bsd/file/dist

.include <bsd.own.mk>

BINDIR?= /usr/bin
USE_FORT?= yes	# data-driven bugs?

TOOL_MKMAGIC?=	${.OBJDIR}/file

MFILESDIR?=	/usr/share/misc
MFILES?=	magic.mgc
MAGIC?=		${MFILESDIR}/magic

VERSION != ${TOOL_SED} -ne "s/^PACKAGE_VERSION='\([^']*\)'/\1/p" ${DIST}/configure

CPPFLAGS+=	-DMAGIC='"${MAGIC}"' -DHAVE_CONFIG_H -DQUICK -DBUILTIN_ELF \
		-DELFCORE -DVERSION='"${VERSION}"'
CPPFLAGS+=	-I${.CURDIR}/../include -I${DIST}/src

.PATH:		${DIST}/src ${DIST}/doc

DPLIBS+=     lzma    ${NETBSDSRCDIR}/external/public-domain/xz/lib
DPLIBS+=     zstd    ${NETBSDSRCDIR}/external/bsd/zstd/lib
DPLIBS+=     bz2     ${NETBSDSRCDIR}/lib/libbz2
DPLIBS+=     z       ${NETBSDSRCDIR}/lib/libz

