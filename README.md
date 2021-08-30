# Pass-malloc-secure_malloc
Ceci est un exemple de passe llvm qui consiste à remplacer tous les appels de fonction malloc dans un programme c par des appels secure_malloc 

compilation:
            $ cd Pass-malloc-secure_malloc
            $ mkdir build
            $ cd build
            $ cmake ..
            $ make
            $ cd ..

exécution:
        $ clang -Xclang -load -Xclang build/Pass-malloc-secure_malloc/libMalloc_to_secure_mallocPass.* exemple.c
