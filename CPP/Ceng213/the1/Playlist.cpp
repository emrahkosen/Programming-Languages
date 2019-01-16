#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Playlist.hpp"
#include "Entry.hpp"

using namespace std;


Playlist::Playlist()
{
    srand(15);
}

int Playlist::getRandomNumber(int i, int n) const
{
    int range=n-i;
    int random = rand() % range + i;
    return random;
}

void Playlist::print()
{
    cout << "[PLAYLIST SIZE=" << entries.getSize() <<"]";
    entries.print();
}
void Playlist::printHistory()
{
    cout<<"[HISTORY]";
    history.print();
}

/* TO-DO: method implementations below */










void Playlist::load(std::string fileName)
{


	string line;
	ifstream file;

	file.open(fileName.c_str());
	while(file.good())
	{


		string line;
		getline(file,line);
		int i=0,j=0;
		int l = line.length(); //strlen(line);
		char tmp[l];
		string t,g,y;

		while(line[i] != ';')
		{

			tmp[j++] = line[i++];
			tmp[j] = '\0';
		}
		i++;
		j =0;
		t = tmp;
		tmp[0] = '\0';








		while(line[i] != ';')
		{

			tmp[j++] = line[i++];
			tmp[j] = '\0';
		}




		i++;
		j =0;
		g = tmp;
		tmp[0] = '\0';

		while(line[i])
		{
			tmp[j++] = line[i++];
			tmp[j] = '\0';
		}
		i++;
		j =0;
		y = tmp;






		Entry newEntry(t,g,y);

    	this->insertEntry(newEntry);









	}
	file.close();







}


















void Playlist::insertEntry(const Entry &e)
{

	entries.insertNode(entries.getTail(), e);

	HistoryRecord ekle(INSERT,e);
	history.push(ekle);


}
























void Playlist::deleteEntry(const std::string &_title)
{


	Node<Entry> *tmp = entries.getHead();


	if(_title == tmp->getData().getTitle())
	{
		Node<Entry> *titlenext = tmp->getNext();
		entries.insertNode(NULL,titlenext->getData());
		entries.deleteNode(entries.getHead());
		entries.deleteNode(entries.getHead());


		/*
		titlenext = titlenext->getNext();


		while(titlenext)
		{	Node<Entry> *titlenext2 = titlenext;
			entries.setTail(titlenext);

			titlenext = titlenext->getNext();
			delete titlenext2;

		}



		*/








	}

	else
	{

		while(tmp->getNext())
		{
			if(_title == tmp->getNext()->getData().getTitle())
			{
				entries.deleteNode(tmp);
				break;
			}

			tmp = tmp->getNext();
		}
	}
	HistoryRecord ekle(DELETE,tmp->getData());
	history.push(ekle);


}



















void Playlist::moveLeft(const std::string &title)
{


	Node<Entry> *tmp = entries.getHead();

	if(title == tmp->getData().getTitle())
	{

	}


	else
	{


		tmp = tmp->getNext();


		if(title == tmp->getData().getTitle())
		{

			entries.insertNode(NULL,tmp->getData());



			entries.deleteNode(entries.getHead()->getNext());




		}






		else
		{


			Node<Entry> *back2 =entries.getHead();
			Node<Entry> *back1 = tmp;
			tmp = tmp->getNext();

			while(tmp)
			{
				if(title == tmp->getData().getTitle())
				{

					if(tmp == entries.getTail())
					{
						Node<Entry> *newtail = new Node<Entry>(back1->getData());
						entries.deleteNode(back2);
						entries.insertNode(entries.getTail(),newtail->getData());
						delete newtail;

					}
					else
					{
					   	back1->setNext(tmp->getNext());
				    	tmp->setNext(back1);
				    	back2->setNext(tmp);

					}



					break;

				}
				back2 = back1;
				back1 = tmp;
				tmp = tmp->getNext();
			}
		}
	}



}




















void Playlist::moveRight(const std::string &title)
{




	Node<Entry> *tmp = entries.getHead();
	Node<Entry> *forvard = tmp->getNext();
	Node<Entry> *back;

    if(title == tmp->getData().getTitle())
    {
		entries.insertNode(NULL,forvard->getData());
		entries.deleteNode(entries.getHead()->getNext());


    }


    else
    {
    	back = tmp;
    	tmp = tmp->getNext();
    	forvard = tmp->getNext();
	while(tmp->getNext())
		{
			if(title == tmp->getData().getTitle())
			{

				if(forvard == entries.getTail())
				{

					Node<Entry> *newtail = new Node<Entry>(tmp->getData());
					entries.deleteNode(back);
					entries.insertNode(entries.getTail(), newtail->getData());
					delete newtail;


				}
				else
				{
					tmp->setNext(forvard->getNext());
					forvard->setNext(tmp);
					back->setNext(forvard);
				}
        break;
			}

			back = tmp;
    		tmp = tmp->getNext();
    		forvard = tmp->getNext();

		}
    }


}






















void Playlist::reverse()
{


	Node<Entry> *p = new Node<Entry>(entries.getHead()->getData());
	Node<Entry> *q = new Node<Entry>(entries.getTail()->getData());
	entries.setHead(q);
	entries.setTail(p);




	Node<Entry> *tmp = entries.getHead();
	Node<Entry> *back = entries.getTail();
	Node<Entry> *forvard;

	tmp = tmp->getNext();

	if(tmp)
	{
		forvard = tmp->getNext();
		tmp->setNext(back);




		while(forvard->getNext())
		{
			back = tmp;
			tmp = forvard;
			forvard = forvard->getNext();
			tmp->setNext(back);
		}

		forvard = entries.getHead();
		forvard->setNext(tmp);
	}






	HistoryRecord ekle(REVERSE);
	history.push(ekle);

}
















void Playlist::sort()
{


	if(!entries.isEmpty())
	{

		Node<Entry> *last = entries.getHead();
		Node<Entry> *tmp = last;
		Node<Entry> *smallest = tmp;
		Node<Entry> *pretmp = NULL;
		Node<Entry> *presmall = NULL;
		Node<Entry> *prelast = NULL;



		while(last)
		{


			tmp = last;
			pretmp = prelast;
			smallest = last;
			presmall = prelast;
			while(tmp)  // small ı bulmak için
			{

				if(tmp->getData().getTitle() < smallest->getData().getTitle())
				{




					presmall = pretmp;
					smallest = tmp;
				}
				pretmp = tmp;

				tmp = tmp->getNext();
			}


			if(smallest == last)
			{

				prelast = last;
				last = last->getNext();
			}
			else
			{


				if(prelast == NULL) //burda küçük elemanı başa ekliyoruz
				{

					while(smallest != last->getNext())
					{
						moveLeft(smallest->getData().getTitle());

					}

					this->moveLeft(smallest->getData().getTitle());

					prelast = entries.getHead();


				}


				else
				{



					presmall->setNext(smallest->getNext());
					prelast->setNext(smallest);
					smallest->setNext(last);
					prelast = prelast->getNext();


/*

					while(smallest->getNext() != last)
					{
						moveLeft(smallest->getData().getTitle());

					}


					prelast = prelast->getNext();

*/

				}
			}





		}







	}





/*


		Node<Entry> *tmp = entries.getHead();

		Node<Entry> *forvard =tmp->getNext();
		Node<Entry> *presmallest = tmp;
		Node<Entry> *smallest = tmp;
		Node<Entry> *pretmp;
		while(forvard)
		{

			if(issmaller(forvard->getData().getTitle(),smallest->getData().getTitle()))
			{
				presmallest =smallest;
				smallest = forvard;
			}
			forvard = forvard->getNext();
		}

		if(smallest == tmp)
		{
			if(tmp->getNext())
			{
				pretmp = tmp;
				tmp = tmp->getNext();
			}
		}

		else if(smallest != tmp)
		{
			presmallest->setNext(smallest->getNext());
			smallest->setNext(tmp);
			entries.setHead(smallest);ss

		}


		while(tmp->getNext())
		{
			forvard = tmp->getNext();
			smallest = tmp;

			while(forvard)
			{

				if(issmaller(forvard->getData().getTitle(),smallest->getData().getTitle()))
				{
					presmallest =smallest;
					smallest = forvard;
				}
				forvard = forvard->getNext();
			}


			if(smallest == tmp)
			{
				if(tmp->getNext())
				{
					pretmp = tmp;
					tmp = tmp->getNext();
				}
			}

			else
			{
				presmallest->setNext(smallest->getNext());
				smallest->setNext(tmp);
				pretmp->setNext(smallest);
			}
			tmp = tmp->getNext();







		}

*/




}




void Playlist::merge(const Playlist & pl)
{




	Node<Entry> *tmppl = pl.entries.getHead();
	Node<Entry> *tmpthis = this->entries.getHead();
	Node<Entry> *p = new Node<Entry>(tmpthis->getData());
	p->setNext(tmpthis->getNext());
	tmpthis->setNext(NULL);
	Node<Entry> *ptp = p;


	if(tmppl->getData().getTitle() < p->getData().getTitle())
	{
		Node<Entry> *newnode = new Node<Entry>(tmppl->getData());
		entries.setHead(newnode);
		tmppl = tmppl->getNext();
		tmpthis = this->entries.getHead();


	}
	else
	{

		p = p->getNext();
		delete ptp;

	}


	while(p || tmppl)
	{


		while(p && tmppl)
		{
			if(tmppl->getData().getTitle() < p->getData().getTitle())
			{



				entries.insertNode(tmpthis,tmppl->getData());
				tmppl = tmppl->getNext();
				tmpthis = tmpthis->getNext();
				tmpthis->setNext(NULL);

			}
			else
			{

				Node<Entry> *newnode = p;

				entries.insertNode(tmpthis,p->getData());
				p = p->getNext();
				tmpthis = tmpthis->getNext();
				tmpthis->setNext(NULL);
				delete newnode;

			}
		}
		if(!tmppl)
		{

			while(p)
			{
					Node<Entry> *newnode = p;

					entries.insertNode(tmpthis,p->getData());
					p = p->getNext();
					tmpthis = tmpthis->getNext();
					tmpthis->setNext(NULL);
					delete newnode;
			}



				break;

		}
		if(!p)
		{

			while(tmppl)
			{


				entries.insertNode(tmpthis,tmppl->getData());
				tmppl = tmppl->getNext();
				tmpthis = tmpthis->getNext();
				tmpthis->setNext(NULL);

			}
			break;
		}


	}



	/*
cout<<"******************\n";

	Node<Entry> *tmppl = pl.entries.getHead(); //pl nin entries ine ulaşamadım

	Node<Entry> *tmp = this->entries.getHead();

	if(tmppl)
	{
		if(tmppl->getData().getTitle() < tmp->getData().getTitle());
		{
			Node<Entry> *newnode = new Node<Entry>(tmppl->getData());

			entries.insertNode(NULL,newnode->getData());
			tmppl = tmppl->getNext();
			delete  newnode;
		}


		Node<Entry> *pretmp = entries.getHead();
		tmp = pretmp->getNext();
		while(tmppl)
		{
cout<<"******************\n";
			if(tmp)
			{
				if(tmppl->getData().getTitle() < tmp->getData().getTitle())
				{
					entries.insertNode(pretmp,tmppl->getData());
					tmppl = tmppl->getNext();
					pretmp = pretmp->getNext();

				}
				else
				{
					while(tmppl->getData().getTitle() > tmp->getData().getTitle() && tmp)
					{
						pretmp = tmp;
						tmp = tmp->getNext();
					}
					entries.insertNode(pretmp,tmppl->getData());
					tmppl = tmppl->getNext();
					pretmp = tmp;
					tmp = tmp->getNext();

				}

			}

			else
			{
				entries.insertNode(entries.getTail(),tmppl->getData());
				tmppl = tmppl->getNext();

			}


		}

	}


*/

}




void Playlist::shuffle()
{

	Node<Entry> *tmp = entries.getHead();
	int n = 0;
	while(tmp)
	{

		n++;
		tmp = tmp->getNext();
	}

	for (int i = 0; i < n-2; ++i)
	{
		int j = this->getRandomNumber(i,n);




		Node<Entry> *tmpi = entries.getHead();
		Node<Entry> *tmpipre;
		Node<Entry> *tmpj = entries.getHead();
		Node<Entry> *tmpjpre;

		int ii = i;
		int jj = j;
		while(ii)
		{

			tmpipre = tmpi;
			tmpi = tmpi->getNext();
			ii--;
		}
		while(jj)
		{


			tmpjpre = tmpj;
			tmpj = tmpj->getNext();
			jj--;
		}


		if(i != j)
		{

			if(i == j+1)
			{





				this->moveLeft(tmpi->getData().getTitle());

			}
			else if(j == i+1)
			{

				this->moveLeft(tmpj->getData().getTitle());

			}

			else
			{

				if(i == 0)
				{



					entries.insertNode(NULL,tmpj->getData());

					Node<Entry> *ptr = tmpi;
					Node<Entry> *ptr2 = entries.getHead();
					ptr2->setNext(ptr->getNext());

					ptr->setNext(tmpj->getNext());
					tmpj->setNext(ptr);
					entries.deleteNode(tmpjpre);

				}

				else if (j == 0)
				{



					entries.insertNode(NULL,tmpi->getData());
					Node<Entry> *ptr = tmpj;
					Node<Entry> *ptr2 = entries.getHead();
					ptr2->setNext(ptr->getNext());

					ptr->setNext(tmpi->getNext());
					tmpi->setNext(ptr);
					entries.deleteNode(tmpipre);


				}

				else
				{

					tmpipre->setNext(tmpj);



					Node<Entry> *tmpjnext = tmpj->getNext();




					tmpj->setNext(tmpi->getNext());

					tmpjpre->setNext(tmpi);

					tmpi->setNext(tmpjnext);
				}



			}

		}


	}








}



void Playlist::undo()
{

	Node<HistoryRecord> *histNode = history.Top();
	HistoryRecord hist = histNode->getData();


	if(hist.getOperation() == INSERT)
	{
		history.pop();
		this->deleteEntry(hist.getEntry().getTitle());
		history.pop();

	}


	else if(hist.getOperation() == DELETE)
	{
		history.pop();
		this->insertEntry(hist.getEntry());
		history.pop();
	}


	else if(hist.getOperation() == REVERSE)
	{
		history.pop();
		this->reverse();
		history.pop();

	}



}









/*




int Playlist::issmaller(string &title1,string &title2)
{
	if(title1 < title2)
	{
		return 1;

	}

	return 0;

}





int Playlist::isequal(string first,string second)
{
	int i = 0;
	while(first[i])
	{
		if(first[i] != second[i])
			return 0;
		i++;

	}
	return 1;
}







*/
