#pragma once


class Timer
{
public:
	Timer( ) = default;
	Timer( float amountTime , int amount);
	Timer( float amountTime );

	void update( float dt_ );
	void reset( );
	void setState( bool in );

	bool checkTime( ) const;

	bool getState( ) const;
	int getAmount( ) const;
	float getTime( ) const;
	float getMaxTime( ) const;

private:
	float time = 0.0f;
	float amountTime = 0.0f;
	int amount = 0;
	bool state = false;


};

