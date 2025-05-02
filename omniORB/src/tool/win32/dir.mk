all:: clwrapper.exe libwrapper.exe linkwrapper.exe oidlwrapper.exe

define CompileWrapper
CL.EXE $< advapi32.lib
endef

clwrapper.exe: clwrapper.c pathmapping.h
	$(CompileWrapper)

libwrapper.exe: libwrapper.c pathmapping.h
	$(CompileWrapper)

linkwrapper.exe: linkwrapper.c pathmapping.h
	$(CompileWrapper)

oidlwrapper.exe: oidlwrapper.c pathmapping.h
	$(CompileWrapper)

export:: clwrapper.exe libwrapper.exe linkwrapper.exe oidlwrapper.exe
	@$(ExportExecutable)
