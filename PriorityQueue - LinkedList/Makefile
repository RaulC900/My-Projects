build: tema1.exe

tema1.exe: tema1.obj
        link /out:tema1.exe tema1.obj compare.lib
tema1.obj:
        cl /MD /D_CRT_SECURE_NO_DEPRECATE /Fotema1.obj /c tema1.c /Wall

clean:
        del tema1.exe
        del tema1.obj
