#ifndef POSITION_H
#define POSITION_H

struct position
    {
	position();
	position( const position & lhs, const position & rhs );
    float x;
    float y;
    float z;
	float distanceTo( const position & )const;
	position projectTo( const position &, float distance )const;

	private:
	float static inline square( const float input ){return input*input;};
    };

#endif
