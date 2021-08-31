# Pass-malloc-secure_malloc
Ceci est un exemple de passe llvm qui consiste à remplacer tous les appels de fonction malloc dans un programme c par des appels secure_malloc 
 
 
 Le fichier #Sujet-approche_solution.pdf contient la description du projet et une approche solution.


 le fichier fichier_1.txt represent le fichier f1 et  exemple.c represente notre programme c (f2)


 notre pass se trouve dans pass-malloc-secure_malloc/pass.cpp 


compilation : 

            $ cd Pass-malloc-secure_malloc

            $ mkdir build

            $ cd build

            $ cmake ..

            $ make

            $ cd ..

exécution:

        $ clang -Xclang -load -Xclang build/Pass-malloc-secure_malloc/libMalloc_to_secure_mallocPass.* exemple.c
