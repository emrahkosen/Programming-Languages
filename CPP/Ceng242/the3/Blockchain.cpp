#include "Blockchain.h"
#include "Utilizer.h"
#include <iostream>
#include <iomanip>
/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/

Blockchain::Blockchain(int id):id(id),head(NULL){}

Blockchain::Blockchain(int id, Koin *head):id(id),head(head){}
Blockchain::Blockchain(const Blockchain& rhs):id(id)
{
	if (&rhs == NULL)
		return;
	else
		this->head = new Koin(*(rhs.head));
}





Blockchain& Blockchain::operator=(Blockchain&& rhs) noexcept
{
	if(this->head)
	{
		Koin *tmp = this->head;
		Koin *pre;
		while(tmp)
		{
			pre = tmp;
			tmp = tmp->getNext();
			delete pre;
		}
	}
	this->head = rhs.head;
	rhs.head = NULL;


	return *this;
}









Blockchain::~Blockchain()
{

	Koin *tmp = this->head;
	Koin *pre;
	while(tmp)
	{
		pre = tmp;
		tmp = tmp->getNext();
		delete pre;
	}

}

int Blockchain::getID() const
	{
		return this->id;
	}


Koin* Blockchain::getHead() const
{
	return this->head;
}

double Blockchain::getTotalValue() const
{
	Koin *tmp = head;
	double total = 0;
	while(tmp)
	{
		total += tmp->getValue();
		tmp = tmp->getNext();
	}
	return total;
}

long Blockchain::getChainLength() const
{
	Koin *tmp = head;
	long leng = 0;
	while(tmp)
	{
		leng += 1;
		tmp = tmp->getNext();
	}
	return leng;
}






void Blockchain::operator++()
{

	Koin *Mine = new Koin(Utilizer::fetchRandomValue());


	if(this->head == NULL)
		this->head = Mine;
	else
	{
		Koin *tmp = this->head;
		while(tmp->getNext())
		{
			tmp = tmp->getNext();
		}
		tmp->setNext(Mine);
	}
}


void Blockchain::operator--()
{
	if(this->head)
	{
		if(this->head->getNext() == NULL)
		{
			if(this->head->soft == 0)
			{
				Koin *tmp = this->head;
				this->head = NULL;
				delete tmp;
			}


		}
		else
		{
			Koin *tmp = this->head;
			while(tmp->getNext()->getNext())
			{
				tmp = tmp->getNext();
			}
			if(tmp->getNext()->soft == 0)
			{
				delete tmp->getNext();
				tmp->setNext(NULL);
			}

		}
	}

}


Blockchain& Blockchain::operator*=(int multiplier)
{

	Koin *tmp = this->head;
	while(tmp)
	{
		(*tmp) *= (multiplier);
		tmp = tmp->getNext();
	}

	return *this;
}

Blockchain& Blockchain::operator/=(int divisor)
{
	Koin *tmp = this->head;
	while(tmp)
	{
		(*tmp) /= (divisor);
		tmp = tmp->getNext();
	}

	return *this;
}







std::ostream& operator<<(std::ostream& os, const Blockchain& blockchain)
{
	// os.unsetf ( std::ios::floatfield );
  // os.precision(Utilizer::koinPrintPrecision());
	os << std::fixed << std::setprecision(Utilizer::koinPrintPrecision());
	os<<"Block";
	os<<" ";
	os<<blockchain.id<<": ";
	if(blockchain.head == NULL)
		os<<"Empty.";

	else
	{
		os << *(blockchain.head) ;
		os << "(";
		os<<std::fixed << blockchain.getTotalValue();
		os<<")";
	}
	return os;
}


void Blockchain::setsoftheadnull()
{
	this->head = NULL;
}
