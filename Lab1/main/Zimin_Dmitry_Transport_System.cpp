#include "Utilites.h"
#include "Station.h"
#include "Pipe.h"
#include "GTS.h"
#include <format>
#include <chrono>

using namespace std;
using namespace chrono;


// Основной цикл
int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "ru");


    redirect_stream_wrapper cerr_out(cerr);
    string time = format("{:%d_%m_%Y_%H_%M_%OS}", system_clock::now() + hours(3));
    ofstream logfile("Logs/log_" + time + ".txt");

    if (logfile)
        cerr_out.redirect(logfile);
 

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
        
       
        switch (GetCorrectNumber(cin, 0, 8))
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
            GasSystem.Delete();
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
