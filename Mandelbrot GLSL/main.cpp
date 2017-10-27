/*********************************************************************

This file is part of Mandelbrot GLSL (GNU GPL) - https://www.youtube.com/user/Muzkaw.

Mandelbrot GLSL is free software : you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Mandelbrot GLSL is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Mandelbrot GLSL. If not, see <http://www.gnu.org/licenses/>.

Mandelbrot GLSL codded by Muzkaw : https://www.youtube.com/user/Muzkaw
You need to link SFML 2.0 or above to run the program

********************************************************************/

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std ;
using namespace sf ;

int main()
{
	int width = 900 ;
	int height = 900 ;

	RenderWindow window(VideoMode(width,height,32),"GLSL Mandelbrot set plotter");

	Shader fragment_shader ;
	if(!fragment_shader.loadFromFile("mandelbrot.frag",Shader::Fragment)) cout<<"Frag shader error :("<<endl;

	Texture texture ; texture.create(width,height) ;
	Sprite sprite ; sprite.setTexture(texture) ;
	float X0 = 0 ;
	float Y0 = 0 ;
	float zoom = 1 ;
	float maxIteration = 1000 ;

	fragment_shader.setUniform("texture",texture) ;
	fragment_shader.setUniform("X0",X0) ;
	fragment_shader.setUniform("Y0",Y0) ;
	fragment_shader.setUniform("zoom",zoom) ;
	fragment_shader.setUniform("maxIteration",maxIteration) ;

	Clock deltaTime ;
	float dt = 0.01 ;

	while(window.isOpen())
	{
		if(Keyboard::isKeyPressed(Keyboard::Z))
			zoom+=(1*zoom)*dt;
		if(Keyboard::isKeyPressed(Keyboard::S))
			zoom-=(1*zoom)*dt;
		if(Keyboard::isKeyPressed(Keyboard::Left))
			X0-=(1/zoom)*dt;
		if(Keyboard::isKeyPressed(Keyboard::Right))
			X0+=(1/zoom)*dt ;
		if(Keyboard::isKeyPressed(Keyboard::Up))
			Y0-=(1/zoom)*dt ;
		if(Keyboard::isKeyPressed(Keyboard::Down))
			Y0+=(1/zoom)*dt ;
		if(Keyboard::isKeyPressed(Keyboard::Q))
			maxIteration -= 500*dt ;
		if(Keyboard::isKeyPressed(Keyboard::D))
			maxIteration += 500*dt ;
		fragment_shader.setUniform("texture",texture) ;
		fragment_shader.setUniform("X0",X0) ;
		fragment_shader.setUniform("Y0",Y0) ;
		fragment_shader.setUniform("zoom",zoom) ;
		fragment_shader.setUniform("maxIteration",maxIteration) ;
		window.clear() ;
		window.draw(sprite, &fragment_shader) ;
		window.display() ;

		dt = deltaTime.restart().asSeconds() ;
	}
}