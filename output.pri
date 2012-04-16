isEmpty(DGP_OUTPUTDIR){
	DGP_OUTPUTDIR = $$PWD/../output
}
DGP_BINDIR = $$DGP_OUTPUTDIR/bin
DGP_LIBDIR = $$DGP_OUTPUTDIR/lib

contains(TEMPLATE , app){
    DESTDIR = $$DGP_BINDIR
    
    LIBS += -L$$DGP_LIBDIR
    unix:!mac{
        QMAKE_LFLAGS += -Wl,--rpath=../lib
    }

    CONFIG += link_prl
}

contains(TEMPLATE , lib){
    DESTDIR = $$DGP_LIBDIR
    win32 {
        DLLDESTDIR = $$DGP_BINDIR
    }
    
    # library can also link to library
    LIBS += -L$$DGP_LIBDIR

    CONFIG += create_prl
}
