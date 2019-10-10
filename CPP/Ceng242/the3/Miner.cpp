#include "Miner.h"
#include <vector>
#include <iostream>
#include <sstream>
#include "Utilizer.h"
#include <iomanip>
/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/

int Miner::getNextAvailableBlockchainID() const
{

  return bilo.size();
}


Miner::Miner(std::string name):namemine(name){}


Miner::~Miner()
{
	for (unsigned int i = 0; i < bilo.size(); ++i)
  {
    if(bilo[i]->bsoft == 1)
    {
      bilo[i]->setsoftheadnull();
    }
  //  bilo[i]->~Blockchain();
  }

   for ( std::vector<Blockchain*>::iterator i = bilo.begin(); i != bilo.end(); ++i )
     delete *i;

  //bilo.~vector<Blockchain *>();
  bilo.clear();
}


void Miner::createNewBlockchain()
{
	int nid = getNextAvailableBlockchainID();
	Blockchain *newbc = new Blockchain(nid);
	bilo.push_back(newbc);
  //newbc->~Blockchain();

}


void Miner::mineUntil(int cycleCount)
{
	int sizebilo = bilo.size();
	for (unsigned int j = 0; j < cycleCount; ++j)
	{

      for (unsigned int i = 0; i < sizebilo; ++i)
      {
        ++(*bilo[i]);
      }

	}

}
void Miner::demineUntil(int cycleCount)
{
	int sizebilo = bilo.size();
	for (unsigned int i = 0; i < sizebilo; ++i)
	{
		for (unsigned int j = 0; j < cycleCount; ++j)
		{

			--(*bilo[i]);
		}
	}

}




double Miner::getTotalValue() const//**********
{
  double totalval = 0;
  for (unsigned int i = 0; i < bilo.size(); ++i)
  {
    if(bilo[i]->bsoft == 0)
    {

      totalval += bilo[i]->getTotalValue();
    }

   // else
      //std::cout<<bilo[i]->getID()<<"\n\n";
  }
  return totalval;
}









long Miner::getBlockchainCount() const
{
  return bilo.size();
}

Blockchain* Miner::operator[](int id) const
{
  if(bilo.size() > id)
    return bilo[id];
  return nullptr;
}

bool Miner::softFork(int blockchainID)
{
  int position = -1;
  for (size_t i = 0; i < bilo.size(); i++) {
    if(bilo[i]->getID() == blockchainID)
    {
      position = i;
      break;
    }
  }


  if(position  == -1)
    return 0;

  else
  {
    Koin *last = bilo[position]->getHead();
    if(last)
    {
      while(last->getNext())
        last = last->getNext();
    }


    int nid = getNextAvailableBlockchainID();
  	Blockchain *newbc = new Blockchain(nid,last);
    if(last)
      last->soft = 1;
    newbc->bsoft = 1;
//burda last koinini isaretlemem gerekli
  	bilo.push_back(newbc);
  }
  return 1;

}

bool Miner::hardFork(int blockchainID)
{
  int position = -1;
  for (size_t i = 0; i < bilo.size(); i++)
  {
    if(bilo[i]->getID() == blockchainID)
    {
      position = i;
      break;
    }
  }


  if(position  == -1)
    return 0;

  else
  {
    Koin *last = bilo[position]->getHead();
    if(last)
    {
      while(last->getNext())
        last = last->getNext();
    }


    int nid = getNextAvailableBlockchainID();
    Koin *hardlast = new Koin(last->getValue());
  	Blockchain *newbc = new Blockchain(nid,hardlast);
  	bilo.push_back(newbc);
  }
  return 1;

}


std::ostream& operator<<(std::ostream& os, const Miner& miner)
{

  os << std::fixed << std::setprecision(Utilizer::koinPrintPrecision());

  os<<"-- BEGIN MINER --\n";
  os<<"Miner name: "<<miner.namemine<<"\n";
  os<<"Blockchain count: "<<miner.getBlockchainCount()<<"\n";
  os<<"Total value: "<<  miner.getTotalValue()<<"\n\n";

  for (size_t i = 0; i < miner.bilo.size(); i++)
  {
    os<< *(miner.bilo[i])<<"\n";
  }
  os<<"\n-- END MINER --\n";
  return os;
}
