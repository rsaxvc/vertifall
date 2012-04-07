#ifndef POSITION_H
#define POSITION_H

struct position
    {
	position();
	position( const position & lhs, const position & rhs );
	position( float init_x, float init_y, float init_z ):x(init_x),y(init_y),z(init_z){};
    float x;
    float y;
    float z;
	float distanceTo( const position & )const;
	position projectTo( const position &, float distance )const;

	private:
	float static inline square( const float input ){return input*input;};
    };

#endif
