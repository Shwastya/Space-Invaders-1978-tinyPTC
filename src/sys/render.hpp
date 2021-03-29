#pragma once
#include <cstdint>
#include <memory>
namespace ECS 
{
	struct RenderSystem_t 
	{
		explicit RenderSystem_t(uint32_t w, uint32_t h);
		~RenderSystem_t();

		bool update() const;

		void drawSprite();

		/* constantes */
		static constexpr uint32_t kR = 0x00FF0000;
		static constexpr uint32_t kG = 0x0000FF00;
		static constexpr uint32_t kB = 0x000000FF;

		static constexpr uint32_t sprite[8*8] = 
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

		private:
		const uint32_t _width{0};
		const uint32_t _height{0};
		std::unique_ptr<uint32_t[]> _framebuffer{nullptr}; 
		

	};

	
} // namespace ECS para evitar colisiones con posibles coincidencias en declaracion del nombre del struct

