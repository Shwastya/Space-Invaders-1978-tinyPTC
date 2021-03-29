
extern "C" {
      #include <tinyPTC/src/tinyptc.h>
   }

#include <cstdint>
#include <sys/render.hpp>



constexpr uint32_t KSCRWIDTH  { 640 };
constexpr uint32_t KSCRHEIGHT { 360 };

void execute(){
   
}
int main() {
   


   try 
   {
      const ECS::RenderSystem_t Render{KSCRWIDTH ,KSCRHEIGHT};
      while (Render.update());

      //while (!ptc_process_events());
   
 
   }
   catch(...) 
   {
      //std::cout << "Capturada: " << s << std::endl;
   }
   return 0;
}