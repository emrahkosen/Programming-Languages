#include "Koin.h"
#include <iostream>
#include <sstream>
#include "Utilizer.h"
#include <cmath>
#include <iomanip>

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/

Koin::Koin(double value):value(value),next(NULL){}

Koin::Koin(const Koin& rhs):value(rhs.value),next(NULL)
{
	// if(rhs.next == NULL)
	// 	return;

	// else
	// 	this->next = new Koin(*(rhs.next));

}

Koin& Koin::operator=(const Koin& rhs)
{
	if(&rhs != this)
	{
		Koin *tmp = this->next;
		this->next = nullptr;
		Koin *ktmp;
		while(tmp)
		{
			ktmp = tmp->next;

			tmp->~Koin();

			tmp = ktmp;
		}

		this->value = rhs.value;
		this->next = rhs.getNext();
		rhs.~Koin();
	}


	return *this;
}



Koin::~Koin()
{
	Koin *tmp = this->next;;
	Koin *pre;
	while(tmp)
	{
		pre = tmp;
		tmp = tmp->next;
		//	delete pre;
	}
}


double Koin::getValue() const
	{
		return this->value;
	}

Koin* Koin::getNext() const
	{
		return this->next;
	}


void Koin::setNext(Koin *next)
	{
		this->next = next;
	}



bool Koin::operator==(const Koin& rhs) const
{
	if(&rhs == this)
		return 1;
	if(this)
	{
		if( std::abs(rhs.value - this->value) <= Utilizer::doubleSensitivity())
		{
			Koin *tmp = this->next;
			Koin *tmprhs = rhs.next;
			while(tmp && tmprhs)
			{
				if(std::abs(tmprhs->value- tmp->value) >= Utilizer::doubleSensitivity() )
					return 0;
				tmp = tmp->next;
				tmprhs = tmprhs->next;
			}
			if(tmp == NULL && tmprhs == NULL)
				return 1;
		}
	}
	return 0;
}

bool Koin::operator!=(const Koin& rhs) const
{
	if(&rhs != this)
		return 0;
		if(this)
		{
			if( std::abs(rhs.value - this->value) <= Utilizer::doubleSensitivity())
			{
				Koin *tmp = this->next;
				Koin *tmprhs = rhs.next;
				while(tmp && tmprhs)
				{
					if(std::abs(tmprhs->value- tmp->value) >= Utilizer::doubleSensitivity() )
						return 1;
					tmp = tmp->next;
					tmprhs = tmprhs->next;
				}
				if(tmp == NULL && tmprhs == NULL)
					return 0;
			}
		}
		return 1;

}

Koin& Koin::operator*=(int multiplier)
{
	if(this)
		this->value = multiplier*(this->value);
	return *this;
}


Koin& Koin::operator/=(int divisor)
{
	if(this)
		this->value = (this->value)/divisor;
	return *this;
}




std::ostream& operator<<(std::ostream& os, const Koin& koin)
{

	// os.unsetf ( std::ios::floatfield );
  // os.precision(Utilizer::koinPrintPrecision());
	os << std::fixed << std::setprecision(Utilizer::koinPrintPrecision());
	os<<std::fixed << koin.value;


	os<<"--";
	Koin *tmp = koin.next;
	while(tmp)
	{
		os<<std::fixed << tmp->value<<"--";
		tmp = tmp->next;
	}

    os << "|";
    return os;
}
