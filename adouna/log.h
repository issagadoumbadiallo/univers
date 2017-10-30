#include "spdlog.h"
//#include "logger.h"
//#include "tweakme.h"
//#include "common.h"
#include <chrono>
#include <ctime>


#include <iostream>
#include <iomanip>
//#include <thread>


class LivingObj {
    std::shared_ptr<spdlog::logger> file;
    size_t q_size = 1048576;//queue size must be power of 2
public:
    LivingObj(){
        spdlog::set_async_mode(q_size);
        file = spdlog::daily_logger_st( "EngineLog", "log.txt");
    };

    ~LivingObj(){
        spdlog::drop_all();
 };

template<typename T> void operator<<( const T* msg)
{
file->info(msg);
}

/*    void i(const char* msg){
        file->info(msg);
    };*/

};

//using namespace std;

/*
class Duree{

private:
    std::clock_t c_start, c_end;
    std::chrono::_V2::system_clock::time_point t_start, t_end; //=std::clock();
    double c_duration=0;
public:
            duree(){
                c_start= std::clock();
                t_start=std::chrono::high_resolution_clock::now();
                //initialisation de la durée
                c_duration=0;
                t_duration=0;
            }

            void restart(){
                this->duree();
            }
            void end(){
                c_end = std::clock();
                t_end = std::chrono::high_resolution_clock::now();
                c_duration= 1000.0 * (c_end-c_start) / CLOCKS_PER_SEC;
                t_duration=std::chrono::duration<double, std::milli>(t_end-t_start).count();
            }

            double duree_Clock(){
                return c_duration;
            }

                double duree_time(){
                return t_duration;
            }

            //void start(){ this.Duree();}
            show_all(){
                std::cout << std::fixed << std::setprecision(2) << "CPU time used: "
                          << c_duration << " ms\n"
                          << "Wall clock time passed: "
                          << t_duration
                          << " ms\n";
            }
};
*/
