#include "Utilites.h"
#include "Compressor_station.h"
#include "Pipe.h"
#include "GTS.h"


using namespace std;


// Основной цикл
int main()
{
    setlocale(LC_ALL, "ru");

    GTS GasSystem;

    while (1) {
        ENTER;
        cout << "\n1. Добавить трубу\n" <<
            "2. Добавить КС\n" <<
            "3. Просмотр всех объектов\n" <<
            "4. Редактирование\n" <<
            "5. Удаление\n" <<
            "6. Поиск по фильтру\n" <<
            "7. Сохранить\n" <<
            "8. Загрузить\n" << 
            "0. Выход\n" << endl;
        
       
        switch (GetCorrectNumber(0, 9))
        {

        case 1: 
            {
                GasSystem.CreatePipe();
                break;
            }
        case 2: 
            {
                GasSystem.CreateCS();
                break;
            }
        
        case 3: 
        {
            GasSystem.View();
            break;
        }
        
        case 4: 
        {
            GasSystem.Edit();
            break;
        }

        case 5: {
            GasSystem.Search();
            break;
        }

        case 6: {
            GasSystem.Search();
            break;
        }
        
        case 7: {
            GasSystem.SaveConfiguration();
            break;
        }

        case 8: {
            GasSystem.LoadConfiguration();
            break;
        }
        
        case 0: {
            return 0;

        }
        }
    }

    return 0;
}
