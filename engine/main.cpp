#include "GameDirector.hpp"
#include "FileSystem.hpp"

int main(int argc, char** argv)
{
    try {
        ScriptManager scriptManager;
        FileSystem   fileSystem(argv[0]);
        fileSystem.addSearchPath("assets/");
        GameDirector director;
        Application  app(&scriptManager);

        director.timePerFrame(sf::seconds(1.f / 60.f));
        director.setScriptManager(scriptManager);
        director.setFileSystem(fileSystem);
        director.setApp(app);

        director.run();
        //director.DEBUGrun();

    } catch(const Exception& e) {
        std::cout << e.info() << std::endl << e.what() << std::endl;
        std::cin.get();

    } catch(const luabridge::LuaException& e) {
        std::cout << e.what() << std::endl;
        std::cin.get();

    } catch(const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    std::cin.get();
    return 0;
}

/*Дано одновимірний масив з 25 чисел. Знайти суму перших
непарних 11 чисел.*/
/*#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    const int size = 15;

    srand(time(NULL));

    int array[size];
    int i, k = 0, sum = 0;

    for (i = 0; i < size; i++)
    {
        array[i] =  -20 + rand() % 60;
        printf ("array[%i] = %i;\n", i, array[i]);
    }

    for (i = 0; i < size; i++)
    {
        if (array[i] % 2 != 0)
        {
            sum += array[i];
            k++;
        }

        if (k >= 11)
            break;
    }

    printf ("\nsum = %i\n", sum);

    return 0;
}*/
/*
#include <stdio.h>
#include <math.h>

int main()
{
    const int i_size = 4;
    const int j_size = 3;
    double d[i_size][j_size] = { 0 };
    double x[] = { 1.35, 2.6, 1.86, 0.95 };
    double z[] = { 0.60, 1.28, 3.15 };
    int i, j;
    double e = exp(1);

    for (i = 0; i < i_size; i++)
    {
        for (j = 0; j < j_size; j++)
        {
            d[i][j] = (pow (e, x[i] - z[j])) / (sin (1 - x[i] * z[j]));
            printf ("d[%i][%i] = %f\n", i, j, d[i][j]);
        }
    }

    return 0;
}*/
