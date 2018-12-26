#ifndef _DIRECTOR_H_
#define _DIRECTOR_H_

class Builder;

class Director
{
public:
	Director(Builder* bld):_bld(bld) {}
	~Director() 
	{ 
		if (_bld)  
		{
			delete _bld;
		}
	}

	void Construct()
	{
		_bld->BuildPartA("user-defined");
		_bld->BuildPartB("user-defined");
		_bld->BuildPartC("user-defined");
	}

private:
	Builder* _bld;

};

#endif
