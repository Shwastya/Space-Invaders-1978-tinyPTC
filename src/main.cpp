
extern "C" {
      #include <tinyPTC/src/tinyptc.h>
   }

#include <cstdint>
#include <iostream>
///#include <exception>
#include <memory>

uint32_t* screen = nullptr; // los pixeles en RGBA ocupan un entero 32 bits

constexpr uint32_t KSCRWIDTH  { 640 };
constexpr uint32_t KSCRHEIGHT { 360 };

constexpr uint32_t kR = 0x00FF0000;
constexpr uint32_t kG = 0x0000FF00;
constexpr uint32_t kB = 0x000000FF;

constexpr uint32_t sprite[8*8] = 
{
   kG, kG, kG, kG, kG, kG, kG, kG,
   kG, kB, kR, kR, kR, kR, kB, kG,
   kG, kB, kR, kG, kG, kG, kB, kG,
   kG, kB, kB, kR, kG, kG, kB, kG,
   kG, kB, kB, kB, kR, kG, kB, kG,
   kG, kB, kB, kB, kB, kR, kB, kG,
   kG, kB, kR, kR, kR, kR, kB, kG,
   kG, kG, kG, kG, kG, kG, kG, kG
};
/* struct Screen_t
{
   //Screen_t() = default;
   Screen_t(uint32_t w, uint32_t h)   : screen(new uint32_t[w*h])
   {}

   ~Screen_t() 
   {
      delete[] screen; 
   } 

   uint32_t* screen { nullptr };
}; */
void execute(){
   ptc_open("window",KSCRWIDTH ,KSCRHEIGHT);
 
   // Screen_t scr(KSCRWIDTH, KSCRHEIGHT);
   // std::unique_ptr<uint32_t[]> screen(new uint32_t[KSCRWIDTH*KSCRHEIGHT]);
   // std::unique_ptr<uint32_t[]> screen = std::make_unique<uint32_t[]>(KSCRWIDTH*KSCRHEIGHT);
   auto screen = std::make_unique<uint32_t[]>(KSCRWIDTH*KSCRHEIGHT);

   while (!ptc_process_events())
   {
      for (uint32_t i=0; i < KSCRWIDTH * KSCRHEIGHT; ++i) screen[i] = kR;

      uint32_t* pscr = screen.get();  // puntero a screen
      const uint32_t* psp  = sprite;  // puntero a sprite

      for (uint32_t i=0; i < 8; ++i) 
      {
         for (uint32_t j=0; j < 8; ++j) 
         {
            *pscr = *psp;
            ++pscr;
            ++psp;
         }
         pscr += 640 - 8;
      }
         
      //throw "Exception";
      ptc_update(screen.get());      
   };

   ptc_close();
}
int main() {
   
   try 
   {
      execute();
   }
   catch(const char* s) 
   {
      std::cout << "Capturada: " << s << std::endl;
   }
   return 0;
}