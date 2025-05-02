
CXXSRCS = eg2_impl.cc eg2_clt.cc eg2_crypto_impl.cc eg2_crypto_clt.cc

DIR_CPPFLAGS = $(CORBA_CPPFLAGS) $(OPEN_SSL_CPPFLAGS)

CORBA_INTERFACES = echo

eg2_impl   	= $(patsubst %,$(BinPattern),eg2_impl)
eg2_clt    	= $(patsubst %,$(BinPattern),eg2_clt)
eg2_crypto_impl = $(patsubst %,$(BinPattern),eg2_crypto_impl)
eg2_crypto_clt  = $(patsubst %,$(BinPattern),eg2_crypto_clt)

all:: $(eg2_impl) $(eg2_clt) $(eg2_crypto_impl) $(eg2_crypto_clt)

clean::
	$(RM) $(eg2_impl) $(eg2_clt) $(eg2_crypto_impl) $(eg2_crypto_clt)

$(eg2_impl): eg2_impl.o $(CORBA_STATIC_STUB_OBJS) $(CORBA_LIB_DEPEND)
	@(libs="$(CORBA_LIB_NODYN) $(OMNIORB_HTTP_LIB)"; $(CXXExecutable))

$(eg2_clt): eg2_clt.o $(CORBA_STATIC_STUB_OBJS) $(CORBA_LIB_DEPEND)
	@(libs="$(CORBA_LIB_NODYN) $(OMNIORB_HTTP_LIB)"; $(CXXExecutable))

$(eg2_crypto_impl): eg2_crypto_impl.o $(CORBA_STATIC_STUB_OBJS) $(CORBA_LIB_DEPEND)
	@(libs="$(CORBA_LIB_NODYN) $(OMNIORB_HTTP_LIB) $(OMNIORB_HTTP_CRYPTO_LIB)"; $(CXXExecutable))

$(eg2_crypto_clt): eg2_crypto_clt.o $(CORBA_STATIC_STUB_OBJS) $(CORBA_LIB_DEPEND)
	@(libs="$(CORBA_LIB_NODYN) $(OMNIORB_HTTP_LIB) $(OMNIORB_HTTP_CRYPTO_LIB)"; $(CXXExecutable))
