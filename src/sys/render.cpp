extern "C" 
{  
	#include <tinyPTC/src/tinyptc.h>  
}
#include <sys/render.hpp>
// #include <iostream>


namespace ECS {

	RenderSystem_t::RenderSystem_t(uint32_t w, uint32_t h) 
	: _width{w}, _height{h}, _framebuffer {std::make_unique<uint32_t[]>(_width*_height)}
	{
		ptc_open("window", w, h);		
	}	

	RenderSystem_t::~RenderSystem_t()
	{
		ptc_close();
	}
	void RenderSystem_t::drawSprite() 
	{
		   uint32_t* pscr = _framebuffer.get();  
			const uint32_t* psp  = sprite;  
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
	}
	bool RenderSystem_t::update() const { 
   
   	auto* screen = _framebuffer.get();
		
		for (uint32_t i=0; i < _width*_height; ++i) screen[i] = kR;
		
		ptc_update(screen);      
		
		return !ptc_process_events();
	}

	

}