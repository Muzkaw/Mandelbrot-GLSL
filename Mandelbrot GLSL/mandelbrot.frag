//This file is part of Mandelbrot GLSL (GNU GPL) - https://www.youtube.com/user/Muzkaw.

uniform sampler2D texture;
uniform float X0 ;
uniform float Y0 ;
uniform float zoom ;
uniform float maxIteration ;

float width = 900 ;
float height = 900 ;

int n ;

float a = 0 ;
float a_buf ;
float b = 0 ;

float x = 0 ;
float y = 0 ;


void main()
{
	vec4 p0 = texture2D(texture, gl_TexCoord[0].xy) ;

	x = float(gl_TexCoord[0].x-0.5)/zoom + X0 ;
	y = float(gl_TexCoord[0].y-0.5)/zoom + Y0 ;

	n = 0 ;
	for(n ; n < maxIteration ; n++)
	{
		if(a*a+b*b > 4.f) break ;

		a_buf=a ;
		a=a_buf*a_buf-b*b+x;
		b=2*a_buf*b+y;
	}
	
	if(n < maxIteration) gl_FragColor = vec4(0,sqrt(n/maxIteration),0,1) ;
	else gl_FragColor = vec4(0,0,0,1) ;
}