PIDGIN_TOP=../../..
AM_CFLAGS=	@LIBGCRYPT_CFLAGS@ @LIBOTR_CFLAGS@ @LIBOTRNG_CFLAGS@ @EXTRA_CFLAGS@ @LIBXML_CFLAGS@
AM_CFLAGS+=	-DUSING_GTK -DPURPLE_PLUGINS \
		-I$(PIDGIN_TOP)/libpurple \
		-I$(PIDGIN_TOP)/pidgin \
		-DPIDGIN_OTR_VERSION=\"@VERSION@\" \
		-DLOCALEDIR=\"$(datadir)/locale\"

SUBDIRS=	po test

plugindir=		${libdir}/pidgin

plugin_LTLIBRARIES=	pidgin-otrng.la

pidgin_otrng_la_SOURCES 	= otrng-plugin.c \
				  prekey-plugin.c \
				  prekey-discovery.c \
				  prekey-discovery-jabber.c \
				  plugin-all.c \
				  ui.c \
				  dialogs.c \
				  gtk-ui.c \
				  gtk-dialog.c \
				  tooltipmenu.c \
				  otrng-client.c

pidgin_otrng_la_LDFLAGS=	-module -avoid-version
pidgin_otrng_la_LDFLAGS+=	@LIBGCRYPT_LIBS@ @LIBOTR_LIBS@ @LIBOTRNG_LIBS@

#TODO: Make sure windows packaging works
EXTRA_DIST=		dialogs.h gtk-dialog.h gtk-ui.h otr-plugin.h ui.h \
			otr-icons.h tooltipmenu.h prekey-discovery.h prekey-discovery-jabber.h \
			Makefile.mingw packaging/windows/pidgin-otr.nsi \
			packaging/fedora/pidgin-otr.spec po/Makefile.mingw \
			po/README intltool-extract.in intltool-merge.in \
			intltool-update.in Makefile.static INSTALL.mingw

DISTCLEANFILES=		intltool-extract intltool-merge intltool-update

code-style:
	clang-format -style=file -i config.h *.h *.c

test: check
	test/test
