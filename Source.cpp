#include<iostream>
#include<string>
#include<fstream>
#include<vector>
using namespace std;

#define valMax 10000

class Operator
{
private:
	char op;
public:
	Operator()
	{
		this->op = (char)"";
	}
	Operator(char op) :op(op)
	{

	}
	//metode de acces: get si set
	char getOp()
	{
		return this->op;
	}
	//metode
	bool esteCifra()
	{
		if (op >= '0' && op <= '9')
			return true;
		else return false;
	}
	bool esteOperator()
	{
		if (op == '+' || op == '-' || op == '*' || op == '/' || op == '^' || op == '#')
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool esteParanteza()
	{
		if (op == '(' || op == ')' || op == '[' || op == ']')
			return 1;
		else return 0;
	}
	int Importanta()
	{
		if (op == '^' || op == '#')
			return 3;
		else if (op == '*' || op == '/')
			return 2;
		else if (op == '+' || op == '-')
			return 1;
		else
			return -1;
	}
	int formeazaNumar(string expresie, int index1, int index2, int* stop, int x, int* p)
	{
		int nr = 0;
		int i;
		*p = 0;
		if (index2 < expresie.length() + 1 && index1 >= 0)
			for (i = index1; i < index2; i++)
			{
				Operator op = expresie[i];
				if (op.esteCifra() == true)
					nr = nr * 10 + (expresie[i] - '0');
				else if (op == (char)'x')
					nr = x;
				else if (op == (char)'.')
					(*p)++;
				else
				{
					*stop = i - 1;
					break;
				}
			}
		if (i == index2)//daca am ajuns la sfarsitul ecuatiei
			*stop = index2 - 1;

		return nr;
	}
	int construiesteNumar(string expresie, int index1, int index2, int* stop)
	{
		int nr = 0;
		int i;
		for (i = index1; i < index2; i++)
			nr = nr * 10 + (expresie[i] - '0');
		*stop = i;
		return nr;
	}
	int construiesteNumar(string expresie, int index1, int* stop, int index2)
	{
		int nr = 0;
		int i;
		for (i = index1; i < index2; i++)
			nr = nr * 10 + (expresie[i] - '0');
		*stop = i;
		return nr;
	}
	//operatori
	operator char()		//cast implicit la char
	{
		return this->op;
	}
	bool operator<(Operator op)	//operator < : compara prioritatile a 2 operatori
	{
		if (this->Importanta() > op.Importanta())
			return true;
		else
			return false;
	}

	friend class Calculator;
	friend ostream& operator<<(ostream& out, const Operator& o);
	friend istream& operator>>(istream& in, Operator& o);
};
ostream& operator<<(ostream& out, const Operator& o)
{
	out << "Operatorul este: " << o.op;
	return out;
}
istream& operator>>(istream& in, Operator& o)
{
	cout << "Introduceti operatorul :"; in >> o.op;
	return in;
}

class Ecuatie
{
private:
	string ecuatie;
	static int nrEcuatii;

public:
	Ecuatie() :ecuatie("")
	{
		nrEcuatii++;
	}
	Ecuatie(string ecuatie)
	{
		this->ecuatie = ecuatie;
		nrEcuatii++;
	}
	Ecuatie(const Ecuatie& e)
	{
		this->ecuatie = e.ecuatie;
		nrEcuatii++;
	}
	Ecuatie operator=(const Ecuatie& e)
	{
		if (this == &e)
			return *this;

		this->ecuatie = e.ecuatie;
		return *this;
	}
	//metode de acces: get si set
	string getEcuatie()
	{
		return this->ecuatie;
	}
	void setEcuatie(string ecuatie)
	{
		if (ecuatie != "")
			this->ecuatie = ecuatie;
	}
	static int getNrEcuatii()
	{
		return nrEcuatii;
	}
	//metode
	void calculAparitieOperatori()
	{
		int aparitii[10] = { 0 };
		char sir[] = "+-*/()[]^#";
		if (this->ecuatie != "")
		{
			for (int i = 0; i < ecuatie.length() + 1; i++)
			{
				if (ecuatie[i] == sir[0])
					aparitii[0]++;
				else if (ecuatie[i] == sir[1])
					aparitii[1]++;
				else if (ecuatie[i] == sir[2])
					aparitii[2]++;
				else if (ecuatie[i] == sir[3])
					aparitii[3]++;
				else if (ecuatie[i] == sir[4])
					aparitii[4]++;
				else if (ecuatie[i] == sir[5])
					aparitii[5]++;
				else if (ecuatie[i] == sir[6])
					aparitii[6]++;
				else if (ecuatie[i] == sir[7])
					aparitii[7]++;
				else if (ecuatie[i] == sir[8])
					aparitii[8]++;
				else if (ecuatie[i] == sir[9])
					aparitii[9]++;
			}
		}
		cout << "Aparitia operatorilor:\n";
		cout << "- + * / ( ) [ ] ^ #\n";
		for (int i = 0; i < 10; i++)
			cout << aparitii[i] << " ";
	}
	bool necesitaValidari()//daca avem radical sau impartire trebuie sa ne asiguram ca acestea au sens
	{
		if (this->ecuatie != "")
			for (int i = 0; i < this->ecuatie.length() + 1; i++)
			{
				if (this->ecuatie[i] == '/' || this->ecuatie[i] == '#')
					return 1;
			}
		return 0;
	}
	int validareEcuatie()
	{
		int k1, k2, k3, k4, vb, stop, nr;
		k1 = 0; k2 = 0; k3 = 0; k4 = 0;
		for (int i = 0; i < this->ecuatie.length(); i++)
		{
			Operator op;
			op = this->ecuatie[i];
			if (op.esteCifra() != 1 && op.esteOperator() != 1 && op.esteParanteza() != 1 && this->ecuatie[i] != 'x' && this->ecuatie[i] != ' ' && this->ecuatie[i] != '.')
				return -3;
			if (op.esteCifra() == 1)
			{
				op.formeazaNumar(this->ecuatie, i, this->ecuatie.length(), &stop, -1, &nr);
				if (nr >= 2)
					return -2;//in nr numar de cate ori apare . in numar pt a verifica daca e valid
			}
			if (this->ecuatie[i] == 'x')
				return 0;
			if (this->ecuatie[i] == '[')
				k1++;
			if (this->ecuatie[i] == ']')
				k2++;
			if (this->ecuatie[i] == '(')
				k3++;
			if (this->ecuatie[i] == ')')
				k4++;

		}
		if (k1 != k2 || k3 != k4)
			return -1;
		return 1;
	}
	int nrOperanzi()
	{
		int nrOp = 0;
		int nr;
		int ok = 1, stop;
		for (int i = 0; i < this->ecuatie.length(); i++)
		{
			Operator op = ecuatie[i];
			if (op.esteCifra() == true || op == (char)'x')
			{
				op.formeazaNumar(ecuatie, i, ecuatie.length(), &stop, -1, &nr);
				i = stop;
				nrOp++;
			}
		}
		return nrOp;
	}
	//metode statice
	static int* nrTotalAparitiiOperatori(Ecuatie* ecuatii, int nrEcuatii)
	{
		int* s;
		s = new int[nrEcuatii];
		for (int i = 0; i < nrEcuatii; i++)
			s[i] = 0;
		int aparitii[10] = { 0 };
		char sir[] = "+-*/()[]^#";
		if (ecuatii != NULL && nrEcuatii > 0)
		{
			for (int j = 0; j < nrEcuatii; j++)
			{
				for (int i = 0; i < ecuatii[j].ecuatie.length() + 1; i++)
				{
					if (ecuatii[j].ecuatie[i] == sir[0])
						aparitii[0]++;
					else if (ecuatii[j].ecuatie[i] == sir[1])
						aparitii[1]++;
					else if (ecuatii[j].ecuatie[i] == sir[2])
						aparitii[2]++;
					else if (ecuatii[j].ecuatie[i] == sir[3])
						aparitii[3]++;
					else if (ecuatii[j].ecuatie[i] == sir[4])
						aparitii[4]++;
					else if (ecuatii[j].ecuatie[i] == sir[5])
						aparitii[5]++;
					else if (ecuatii[j].ecuatie[i] == sir[6])
						aparitii[6]++;
					else if (ecuatii[j].ecuatie[i] == sir[7])
						aparitii[7]++;
					else if (ecuatii[j].ecuatie[i] == sir[8])
						aparitii[8]++;
					else if (ecuatii[j].ecuatie[i] == sir[9])
						aparitii[9]++;
				}
				for (int i = 0; i < 10; i++)
					s[j] += aparitii[i];
				for (int i = 0; i < 10; i++)
					aparitii[i] = 0;
			}
		}
		return s;

	}
	static float numarMediuOperatoriInEcuatie(Ecuatie* ecuatii, int nrEcuatii)
	{
		float medie = 0;
		int* s = new int[nrEcuatii];
		s = nrTotalAparitiiOperatori(ecuatii, nrEcuatii);
		for (int i = 0; i < nrEcuatii; i++)
			medie += s[i];
		medie /= nrEcuatii;

		return medie;
	}
	//operatori
	explicit operator string()
	{
		return this->ecuatie;
	}
	Ecuatie& operator+(int x)
	{
		this->ecuatie += "-";
		this->ecuatie += to_string(x);
		return *this;
	}

	friend ostream& operator<<(ostream& out, const Ecuatie& e);
	friend istream& operator>>(istream& in, Ecuatie& e);
	friend ifstream& operator>>(ifstream& in, Ecuatie& e);
	friend ofstream& operator<<(ofstream& out, Ecuatie& e);
	friend class Calculator;
};
int Ecuatie::nrEcuatii = 0;
ostream& operator<<(ostream& out, const Ecuatie& e)
{
	if (e.ecuatie != "")
		out << "Ecuatia este: " << e.ecuatie;
	else
		out << "Nu se cunoaste ecuatia.";
	out << endl;
	return out;
}
istream& operator>>(istream& in, Ecuatie& e)
{

	cout << "Introduceti ecuatia: \n";
	in >> ws;
	getline(in, e.ecuatie, '\n');

	return in;
}
ifstream& operator>>(ifstream& in, Ecuatie& e)
{
	in >> ws;
	getline(in, e.ecuatie, '\n');
	return in;
}
ofstream& operator<<(ofstream& out, Ecuatie& e)
{
	out << e.ecuatie;
	out << " = ";
	return out;
}

class EcuatieExtinsa : public Ecuatie
{
private:

	char* tipEcuatie;
	int* operanzi;
	int nrOperanzi;
	const string dificultateEcuatie;

public:
	EcuatieExtinsa() : tipEcuatie(NULL), operanzi(NULL), nrOperanzi(0), dificultateEcuatie("")
	{
	}
	EcuatieExtinsa(string ecuatie, char* tipEcuatie, int* operanzi, int nrOperanzi, const string dificultateEcuatie) :Ecuatie(ecuatie), dificultateEcuatie(dificultateEcuatie)
	{
		if (tipEcuatie != NULL)
		{
			this->tipEcuatie = new char[strlen(tipEcuatie) + 1];
			strcpy(this->tipEcuatie, tipEcuatie);
		}
		else
			this->tipEcuatie = NULL;
		if (nrOperanzi > 0 && operanzi != NULL)
		{
			this->nrOperanzi = nrOperanzi;
			this->operanzi = new int[this->nrOperanzi];
			for (int i = 0; i < this->nrOperanzi; i++)
				this->operanzi[i] = operanzi[i];
		}
		else
		{
			this->nrOperanzi = 0;
			this->operanzi = NULL;
		}
	}
	EcuatieExtinsa(const EcuatieExtinsa& e) :Ecuatie(e), dificultateEcuatie(dificultateEcuatie)
	{
		if (tipEcuatie != NULL)
		{
			this->tipEcuatie = new char[strlen(e.tipEcuatie) + 1];
			strcpy(this->tipEcuatie, e.tipEcuatie);
		}
		else
			this->tipEcuatie = NULL;
		if (e.nrOperanzi > 0 && e.operanzi != NULL)
		{
			this->nrOperanzi = e.nrOperanzi;
			this->operanzi = new int[this->nrOperanzi];
			for (int i = 0; i < this->nrOperanzi; i++)
				this->operanzi[i] = e.operanzi[i];
		}
		else
		{
			this->nrOperanzi = 0;
			this->operanzi = NULL;
		}
	}
	EcuatieExtinsa& operator=(const EcuatieExtinsa& e)
	{
		Ecuatie::operator=(e);
		if (this == &e)
			return *this;
		if (this->tipEcuatie != NULL)
			delete[]this->tipEcuatie;
		if (this->operanzi != NULL)
			delete[]this->operanzi;
		if (tipEcuatie != NULL)
		{
			this->tipEcuatie = new char[strlen(e.tipEcuatie) + 1];
			strcpy(this->tipEcuatie, e.tipEcuatie);
		}
		else
			this->tipEcuatie = NULL;
		if (e.nrOperanzi > 0 && e.operanzi != NULL)
		{
			this->nrOperanzi = e.nrOperanzi;
			this->operanzi = new int[this->nrOperanzi];
			for (int i = 0; i < this->nrOperanzi; i++)
				this->operanzi[i] = e.operanzi[i];
		}
		else
		{
			this->nrOperanzi = 0;
			this->operanzi = NULL;
		}
		return *this;
	}
	//metode de acces: get si set
	void setTipEcuatie(char* tipEcuatie)
	{
		if (this->tipEcuatie != NULL)
			delete[]this->tipEcuatie;
		if (tipEcuatie != NULL)
		{
			this->tipEcuatie = new char[strlen(tipEcuatie) + 1];
			strcpy(this->tipEcuatie, tipEcuatie);
		}
		else
			this->tipEcuatie = NULL;
	}
	char* getTipEcuatie()
	{
		if (this->tipEcuatie != NULL)
		{
			char* copie = new char[strlen(this->tipEcuatie) + 1];
			strcpy(copie, this->tipEcuatie);
			return copie;
		}
		else return NULL;
	}
	int getNrOperanzi()
	{
		int nr = Ecuatie::nrOperanzi();
		return nr;
	}
	void setNrOperanzi(int nrOperanzi)
	{
		if (nrOperanzi > 0)
			this->nrOperanzi = nrOperanzi;
		else
			this->nrOperanzi = 0;
	}
	int* getOperanzi()
	{
		if (this->operanzi != NULL)
		{
			int* copie = new int[this->nrOperanzi];
			for (int i = 0; i < this->nrOperanzi; i++)
				copie[i] = this->operanzi[i];
			return copie;
		}
		else return NULL;
	}
	void setOperanzi(int nrOperanzi, int operanzi[])
	{
		if (this->operanzi != NULL)
			delete[]this->operanzi;
		if (nrOperanzi > 0 && operanzi != NULL)
		{
			this->nrOperanzi = nrOperanzi;
			this->operanzi = new int[this->nrOperanzi];
			for (int i = 0; i < this->nrOperanzi; i++)
				this->operanzi[i] = operanzi[i];
		}
		else
		{
			this->nrOperanzi = 0;
			this->operanzi = NULL;
		}
	}
	string getDificultateEcuatie()
	{
		return this->dificultateEcuatie;
	}
	//metode
	int sumaOperanzi()
	{
		int s = 0;
		for (int i = 0; i < this->nrOperanzi; i++)
			s += this->operanzi[i];
		return s;
	}
	int mediaOperanzilor()
	{
		int s;
		s = this->sumaOperanzi();
		return s / this->nrOperanzi;
	}

	friend ostream& operator<<(ostream& out, const EcuatieExtinsa& e);
	friend istream& operator>>(istream& in, EcuatieExtinsa& e);
	~EcuatieExtinsa()
	{
		if (this->tipEcuatie != NULL)
			delete[]this->tipEcuatie;
		if (this->operanzi != NULL)
			delete[]this->operanzi;
	}
};
ostream& operator<<(ostream& out, const EcuatieExtinsa& e)
{
	out << (Ecuatie)e;
	out << "Tipul ecuatiei: ";
	if (e.tipEcuatie != NULL)
		out << e.tipEcuatie;
	else
		out << "-";
	out << endl;
	out << "Numarul de operanzi ai ecuatiei: " << e.nrOperanzi;
	out << endl;
	if (e.nrOperanzi != 0)
	{
		out << "Operanzii ecuatiie sunt:";
		for (int i = 0; i < e.nrOperanzi; i++)
			out << e.operanzi[i] << " ";
	}
	out << "\nDificultatea ecuatiei este: " << e.dificultateEcuatie;
	out << endl;
	return out;
}
istream& operator>>(istream& in, EcuatieExtinsa& e)
{
	string buffer;
	in >> (Ecuatie&)e;
	cout << "Introudceti tipul ecuatiei:\n";
	cout << "\tTipul 1: daca ecuatia efectueaza operatii de baza cu +,-,*,/\n";
	cout << "\tTipul 2: daca ecuatia efectueaza operatiile de baza si in schimb efectueaza si ridicare la putere SAU radical(una din cele 2)\n";
	cout << "\tTipul 3: daca ecuatia efectueaza operatiile de baza(cel putin una), ridicare la putere(cel putin una) si radical(cel putin unul)\n";
	in >> buffer;
	if (e.tipEcuatie != NULL)
		delete[]e.tipEcuatie;
	if (buffer == "1" || buffer == "2" || buffer == "3")
	{
		e.tipEcuatie = new char[buffer.length()];
		strcpy(e.tipEcuatie, buffer.c_str());
	}
	else
		strcpy(e.tipEcuatie, "0");
	cout << "Introduceti numarul de operanzi ai ecuatiei: ";
	in >> e.nrOperanzi;
	if (e.operanzi != NULL)
		delete[]e.operanzi;
	if (e.nrOperanzi > 0)
	{
		cout << "Introduceti operanzii ecuatiei: ";
		e.operanzi = new int[e.nrOperanzi];
		for (int i = 0; i < e.nrOperanzi; i++)
			in >> e.operanzi[i];
	}
	else
		cout << "Nu se cunoaste numarul de operanzi, deci nici operanzii ecuatiei";
	return in;
}



class Stiva
{
	int top;
	int s[valMax];
	int dimensiuneStiva; //<valMax
public:
	Stiva() :top(-1)
	{
		this->top = -1;
		this->dimensiuneStiva = 0;
	}
	Stiva(int top, int s[], int dimensiuneStiva)
	{
		this->top = top;
		this->dimensiuneStiva = dimensiuneStiva;
		for (int i = 0; i < this->dimensiuneStiva; i++)
			this->s[i] = s[i];
	}
	//metode de acces: get si set
	int getTop() // nu fac si setter deoarece nu vreau sa las utilizatorul sa modifice varful stivei
	{
		return this->top;
	}
	//metode
	bool push(int x)
	{
		if (top >= (valMax - 1))  //nu mai este loc in stiva
			return false;
		else
		{
			this->s[++top] = x;
			return true;
		}
	}
	bool push(int x, int val)
	{
		if (top >= (valMax - 1))  //nu mai este loc in stiva
			return false;
		else
		{
			this->s[++top] = x;
			return true;
		}
	}
	int pop()
	{
		if (top < 0)
			return 0;
		else
		{
			int x = this->s[top--];
			return x;
		}
	}
	int peek()
	{
		if (top < 0)
			return 0;
		else {
			int x = this->s[top];
			return x;
		}
	}
	bool empty()
	{
		return (top < 0);
	}
	//operatori
	int& operator[](int index)		//operator [] : returneaza valoarea din stiva de pe pozitia index
	{
		if (index >= -1 && index < this->dimensiuneStiva)
			return this->s[index];
	}
	Stiva& operator++()				//operator ++: creste varful stivei
	{
		this->top++;
		return *this;
	}

	friend ostream& operator<<(ostream& in, Stiva& s);
	friend istream& operator>>(istream& in, Stiva& s);
};
ostream& operator<<(ostream& out, Stiva& s)
{
	out << "Varful stivei are acum valoarea: " << s.top;
	out << "Numar de valori in stiva: " << s.dimensiuneStiva;
	out << endl;
	if (s.dimensiuneStiva > 0)
	{
		out << "Valorile din stiva sunt:";
		for (int i = 0; i < s.dimensiuneStiva; i++)
			out << s.s[i] << " ";
	}
	return out;
}
istream& operator>>(istream& in, Stiva& s)
{
	cout << "Initial indicele pentru varful stivei este implicit -1. Nu puteti modifica aceasta valoare. \n";
	cout << "\nIntroduceti numarul de valori pe care doiriti sa il introduceti in stiva";
	in >> s.dimensiuneStiva;
	cout << "\nIntroduceti valorile in stiva: ";
	for (int i = 0; i < s.dimensiuneStiva; i++)
	{
		int x;
		in >> x;
		s.push(x);
	}
	return in;
}

class IFile
{
	virtual void writeToFile(fstream& f, int) = 0;
	virtual void readFromFile(fstream& f) = 0;
};

class Calculator :public IFile
{
private:
	Ecuatie ecuatie;
	Operator op;
	int nrEcuatiiRezolvate = 0;

public:
	Calculator()
	{

	}
	Calculator(Ecuatie ecuatie, Operator op)
	{
		this->ecuatie = ecuatie;
		this->op = op;
	}
	Calculator(Ecuatie ecuatie)
	{
		this->ecuatie = ecuatie;
	}
	//metode de acces: get si set
	Ecuatie getEcuatie()
	{
		return this->ecuatie;
	}
	void setEcuatie(Ecuatie ecuatie)
	{
		if (ecuatie.ecuatie.length() > 2)
			this->ecuatie = ecuatie;
	}
	void setOperator(Operator op)
	{
		char aux = op;
		int ok = 1;
		while (aux != 0)
		{
			char ch = aux % 10;
			if (!isdigit(ch))
				ok = 0;
			aux = aux / 10;
		}
		if ((aux == 0 && ok == 1) || op == '+' || op == '-' || op == '*' || op == '/' || op == '^' || op == '#')
			this->op = op;
	}
	int getNrEcuatiiRezolvate()
	{
		return this->nrEcuatiiRezolvate;
	}
	Operator getOperator()
	{
		return this->op;
	}
	//metode virtuale
	virtual string formaPoloneza(int* lungimeOperatori, int* k, int x)
	{
		Stiva s;
		string postfix;
		int stop;
		int* lgOp = new int[ecuatie.nrOperanzi()];
		int index = 0;
		int nr = 0;
		for (int i = 0; i < ecuatie.getEcuatie().length(); i++)
		{
			op = ecuatie.getEcuatie()[i];
			if (op.esteCifra() == true)
			{
				lgOp[index++] = (to_string(op.formeazaNumar(ecuatie.getEcuatie(), i, ecuatie.getEcuatie().length(), &stop, -1, &nr))).length();
				postfix += to_string(op.formeazaNumar(ecuatie.getEcuatie(), i, ecuatie.getEcuatie().length(), &stop, -1, &nr));
				i = stop;
			}
			//verific paranteze
			else if (ecuatie.getEcuatie()[i] == '[')  //daca am paranteza [ adaug in stiva
			{
				s.push(ecuatie.getEcuatie()[i]);
			}
			else if (ecuatie.getEcuatie()[i] == '(')  //daca am paranteza ( adaug in stiva
			{
				s.push(ecuatie.getEcuatie()[i]);
			}
			else if (ecuatie.getEcuatie()[i] == ')')
			{
				while ((char)s.peek() != '(' && (!s.empty()))  //verific daca am ceva intre paranteze
				{
					char x = s.peek();
					postfix = postfix + x;
					s.pop();
				}
				if (s.peek() == '(')
				{
					s.pop();
				}
			}
			else if (ecuatie.getEcuatie()[i] == ']')
			{
				while (s.peek() != '[' && (!s.empty()))  //verific daca am ceva intre paranteze
				{
					char x = s.peek();
					postfix = postfix + x;
					s.pop();
				}
				if (s.peek() == '[')
				{
					s.pop();
				}
			}
			else if (op.esteOperator())//verific operator
			{
				if (s.empty())
				{
					s.push(ecuatie.getEcuatie()[i]);
				}
				else
				{
					Operator op2 = s.peek();
					if (op.Importanta() >= op2.Importanta())  //&&(ecuatie.getEcuatie()[i] == '^' || ecuatie.getEcuatie()[i] == '#')
						s.push(ecuatie.getEcuatie()[i]);
					else
					{
						while (!s.empty() && (op.Importanta() <= op2.Importanta()))
						{
							postfix += (char)s.peek();
							s.pop();
							op2 = s.peek();
						}
						s.push(ecuatie.getEcuatie()[i]);
					}
				}
			}
		}
		for (int i = 0; i < ecuatie.nrOperanzi(); i++)
			lungimeOperatori[i] = lgOp[i];
		*k = index;
		while (!s.empty())
		{
			postfix = postfix + (char)(s.peek());
			s.pop();
		}
		return postfix;
	}
	virtual int rezultat(string postfix, int* dimensiune, int nrOperanzi, int* ok)
	{
		Stiva nr;
		int v1, v2;
		int i, x;
		*ok = 1;
		int ret = 0;
		int ind = 0, stop, contor = 0;
		for (i = 0; i < postfix.length(); i++)
		{
			op = postfix[i];
			if (i == 0)
			{
				if (op.esteCifra())
				{
					x = op.construiesteNumar(postfix, ind, i + dimensiune[contor], &stop);
					ind = stop;
					i = ind - 1;
					nr.push(x);
					contor++;
				}
			}
			else if (op.esteCifra())
			{
				x = op.construiesteNumar(postfix, ind, &stop, i + dimensiune[contor]);
				ind = stop;
				i = ind - 1;
				nr.push(x);
				contor++;
			}
			else if (op.esteOperator() == true)
			{
				if (postfix[i] == '+') {
					v1 = nr.peek();
					nr.pop();
					v2 = nr.peek();
					nr.pop();
					ret = (v1 + v2);
				}
				if (postfix[i] == '-') {
					v1 = nr.peek();
					nr.pop();
					v2 = nr.peek();
					nr.pop();
					ret = v2 - v1;
				}
				if (postfix[i] == '*') {
					v1 = nr.peek();
					nr.pop();
					v2 = nr.peek();
					nr.pop();
					ret = (v1 * v2);
				}
				if (postfix[i] == '/') {
					v1 = nr.peek();
					nr.pop();
					v2 = nr.peek();
					nr.pop();
					if (v1 == 0)
					{
						ret = 0;

						*ok = 2;
					}
					else ret = (v2 / v1);
				}
				if (postfix[i] == '^')
				{
					v1 = nr.peek();
					nr.pop();
					v2 = nr.peek();
					nr.pop();
					ret = pow(v2, v1);
				}
				if (postfix[i] == '#')
				{
					v1 = nr.peek();
					nr.pop();
					v2 = nr.peek();
					nr.pop();
					if (v1 % 2 == 0 && v2 < 0)
					{

						*ok = 3;
						break;
					}
					else
						ret = pow(v2, 1.0 / v1);
				}
				nr.push(ret);
				ind++;
			}
		}

		if (*ok == 1)
		{
			ret = nr.peek();
			cout << "Rezultatul obtinut de Calculator este: " << ret << endl;
			this->nrEcuatiiRezolvate++;
		}
		return ret;

	}
	//operatori
	Calculator operator++(int i)	//operator ++ forma preincrementare : creste numarul de ecuatii rezolvate de calculator
	{
		Calculator copie = *this;
		this->nrEcuatiiRezolvate++;
		return copie;
	}
	bool operator>(Calculator& c)	//operator > :compara numarul de ecuatii rezolvate de 2 calculatoare
	{
		if (this->nrEcuatiiRezolvate > c.nrEcuatiiRezolvate)
			return true;
		else return false;
	}

	friend ostream& operator<<(ostream& out, const Calculator& c);
	friend istream& operator<<(istream& in, Calculator& c);
	friend ofstream& operator<<(ofstream& out, const Calculator& c);
	void writeToFile(fstream& f, int rez)
	{
		//scriere lungime ecuatie
		int lg = this->ecuatie.getEcuatie().length() + 1;
		f.write((char*)&lg, sizeof(int));

		//scriere ecuatie
		f.write(this->ecuatie.ecuatie.data(), lg);

		//scriere caracter =
		char c = '=';
		f.write(&c, sizeof(char));

		//scriere rezultat
		f.write((char*)&rez, sizeof(int));

	}
	void readFromFile(fstream& f)
	{
		//citire lungime ecuatie
		int lg = 0;
		f.read((char*)&lg, sizeof(int));

		//citire ecuatie
		char* buffer = new char[lg];
		f.read(buffer, lg);
		this->ecuatie.ecuatie = buffer;
		delete[]buffer;
		cout << this->ecuatie.ecuatie;

		//citire caracter '='
		char c;
		f.read(&c, sizeof(char));
		cout << c;

		//citire rezultat
		int r;
		f.read((char*)&r, sizeof(int));
		cout << r;
		cout << endl;
	}
};
ostream& operator<<(ostream& out, const Calculator& c)
{
	out << "Ecuatia rezolvata de calculator este: ";
	out << c.ecuatie;
	return out;
}
istream& operator<<(istream& in, Calculator& c)
{
	cout << "Introduceti ecuatia pe care doriti sa o rezolvati: ";
	in >> c.ecuatie;
	return in;
}

class CalculatorInteligent :public Calculator
{
private:
	Operator o;
	Ecuatie e;

public:
	CalculatorInteligent(Ecuatie ecuatie)
	{
		this->e = ecuatie;
	}
	string formaPoloneza(int*, int*, int);
	int rezultat(string, int*, int, int*);
	int nrEcRez()
	{
		this->Calculator::getNrEcuatiiRezolvate();
	}
};
string CalculatorInteligent::formaPoloneza(int* lungimeOperatori, int* k, int x)
{
	Stiva s;
	string postfix;
	int stop;
	int* lgOp = new int[e.nrOperanzi()];
	int index = 0;
	int nr;
	for (int i = 0; i < e.getEcuatie().length(); i++)
	{
		o = e.getEcuatie()[i];
		if (o.esteCifra() == true)
		{
			lgOp[index++] = (to_string(o.formeazaNumar(e.getEcuatie(), i, e.getEcuatie().length(), &stop, -1, &nr))).length();
			postfix += to_string(o.formeazaNumar(e.getEcuatie(), i, e.getEcuatie().length(), &stop, -1, &nr));
			i = stop;
		}
		//verific paranteze
		else if (e.getEcuatie()[i] == '[')  //daca am paranteza [ adaug in stiva
		{
			s.push(e.getEcuatie()[i]);
		}
		else if (e.getEcuatie()[i] == '(')  //daca am paranteza ( adaug in stiva
		{
			s.push(e.getEcuatie()[i]);
		}
		else if (e.getEcuatie()[i] == ')')
		{
			while ((char)s.peek() != '(' && (!s.empty()))  //verific daca am ceva intre paranteze
			{
				char x = s.peek();
				postfix = postfix + x;
				s.pop();
			}
			if (s.peek() == '(')
			{
				s.pop();
			}
		}
		else if (e.getEcuatie()[i] == ']')
		{
			while (s.peek() != '[' && (!s.empty()))  //verific daca am ceva intre paranteze
			{
				char x = s.peek();
				postfix = postfix + x;
				s.pop();
			}
			if (s.peek() == '[')
			{
				s.pop();
			}
		}
		else if (o.esteOperator())//verific operator
		{
			if (s.empty())
			{
				s.push(e.getEcuatie()[i]);
			}
			else
			{
				Operator op2 = s.peek();
				if (o.Importanta() >= op2.Importanta())
					s.push(e.getEcuatie()[i]);
				else
				{
					while (!s.empty() && (o.Importanta() <= op2.Importanta()))
					{
						postfix += (char)s.peek();
						s.pop();
						op2 = s.peek();
					}
					s.push(e.getEcuatie()[i]);
				}
			}
		}
		else if (o == (char)'x')  //verific daca e egal cu x(rezultat al unei ecuatii rezolvate anterior)
		{
			lgOp[index++] = (to_string(o.formeazaNumar(e.getEcuatie(), i, e.getEcuatie().length(), &stop, x, &nr))).length();
			postfix += to_string(o.formeazaNumar(e.getEcuatie(), i, e.getEcuatie().length(), &stop, x, &nr));
			i = stop;
		}
	}
	for (int i = 0; i < e.nrOperanzi(); i++)
		lungimeOperatori[i] = lgOp[i];
	*k = index;
	while (!s.empty())
	{
		postfix = postfix + (char)(s.peek());
		s.pop();
	}

	return postfix;
}
int CalculatorInteligent::rezultat(string postfix, int* dimensiune, int nrOperanzi, int* ok)
{
	Stiva nr;
	int v1, v2;
	int i, x;
	*ok = 1;
	int ret = 0;
	int ind = 0, stop, contor = 0;
	for (i = 0; i < postfix.length(); i++)
	{
		o = postfix[i];
		if (i == 0)
		{
			if (o.esteCifra())
			{
				x = o.construiesteNumar(postfix, ind, i + dimensiune[contor], &stop);
				ind = stop;
				i = ind - 1;
				nr.push(x);
				contor++;
			}
		}
		else if (o.esteCifra())
		{
			x = o.construiesteNumar(postfix, ind, &stop, i + dimensiune[contor]);
			ind = stop;
			i = ind - 1;
			nr.push(x);
			contor++;
		}
		else if (o.esteOperator() == true)
		{
			if (postfix[i] == '+') {
				v1 = nr.peek();
				nr.pop();
				v2 = nr.peek();
				nr.pop();
				ret = (v1 + v2);
			}
			if (postfix[i] == '-') {
				v1 = nr.peek();
				nr.pop();
				v2 = nr.peek();
				nr.pop();
				ret = v2 - v1;
			}
			if (postfix[i] == '*') {
				v1 = nr.peek();
				nr.pop();
				v2 = nr.peek();
				nr.pop();
				ret = (v1 * v2);
			}
			if (postfix[i] == '/') {
				v1 = nr.peek();
				nr.pop();
				v2 = nr.peek();
				nr.pop();
				if (v1 == 0)
				{
					ret = 0;

					*ok = 2;
				}
				else ret = (v2 / v1);
			}
			if (postfix[i] == '^')
			{
				v1 = nr.peek();
				nr.pop();
				v2 = nr.peek();
				nr.pop();
				ret = pow(v2, v1);
			}
			if (postfix[i] == '#')
			{
				v1 = nr.peek();
				nr.pop();
				v2 = nr.peek();
				nr.pop();
				if (v1 % 2 == 0 && v2 < 0)
				{

					*ok = 3;
					break;
				}
				else
					ret = pow(v2, 1.0 / v1);
			}
			nr.push(ret);
			ind++;
		}
	}

	if (*ok == 1)
	{
		ret = nr.peek();
		cout << "Rezultatul obtinut cu Calculatorul Inteligent este: " << ret;
	}
	return ret;
}

void meniu(int* optiunePreluare, int* optiuneRez, int* optiuneSalvareRezultat)
{
	cout << "\n\t\t\t::Meniu de utilizare al aplicatiei::\n";
	cout << "\nOptiuni pentru introducerea datelor:";
	cout << "\n\t1.Introduceti ecuatiile de la tastatura\n\t2.Preluati ecuatiile din fisier text";
	cout << "\nIntroduceti optiunea de preluare a ecuatiilor: ";
	cin >> *optiunePreluare;
	cout << "\nOptiuni pentru afisarea/salvarea rezultatelor:";
	cout << "\n\t1.Afisati rezultatele ecuatiilor la consola\n\t2.Salvati rezultatele ecuatiilor in fisier text\n\t3.Salvati rezultatele ecuatiilor in fisier binar\n";
	cout << "\nIntroduceti optiunea de afisare/stocare a rezultatelor: ";
	cin >> *optiuneRez;
	if (*optiunePreluare == 1)
	{
		cout << "\nDoresti sa salvez rezultatul ultimei ecuatii rezolvate pentru ca mai apoi sa poti folosi acest rezultat? \n\tTasteaza 1 pentru Da, 0 pentru Nu: ";
		cin >> *optiuneSalvareRezultat;
		if (*optiuneSalvareRezultat == 1)
			cout << "Voi salva rezultatele in variabila x. Pentru urmatoarea ecuatie, daca doresti sa folosesti aceasta valoare te rog sa te referi la ea prin a scrie x.\n\n";
	}
}

int main(int argc, char** argv)
{

	Ecuatie eq;
	string expresiePoloneza;
	int rez;
	int* dimensiune;
	int nrOperanzi;
	int optiunePreluare, optiuneRez, optiuneSalvareRezultat, optiuneContinuare = 0;
	int ok;
	int x = -1, k1, k2, k3, k4;
	int var = 1, valid;
	if (argv[1] != NULL)
		eq.setEcuatie(argv[1]);
	optiunePreluare = 0; optiuneRez = 0; optiuneSalvareRezultat = 0;
	if (eq.getEcuatie() == "")
		meniu(&optiunePreluare, &optiuneRez, &optiuneSalvareRezultat);

	vector<int>vectorRezultate;
	vector<Ecuatie>vectorEcuatii;
	vector<int>::iterator itr;
	vector<Ecuatie>::iterator ite;

	if (optiunePreluare == 0)	//rulez in linie de comanda
	{
		cout << "Bine ai venit in aplicatia Calculator!\nAceasta aplicatie este implementata de studenta Carp Ana-Maria, seria C, grupa 1049.";
		cout << "\nAcum rulati aplicatia in CMD\n";

		valid = eq.validareEcuatie();
		if (valid == 1)
		{
			Calculator c1(eq);
			dimensiune = new int[eq.nrOperanzi()];

			expresiePoloneza = c1.formaPoloneza(dimensiune, &nrOperanzi, x);
			rez = c1.rezultat(expresiePoloneza, dimensiune, nrOperanzi, &ok);
			if (ok == 2)
				cout << "Nu are sens impartirea la 0! Nu se poate calcula expresia data.";
			if (ok == 3)
				cout << "Nu putem efectua radical de ordin par din numere negative! Nu se poate calcula expresia data.";

		}
		else if (valid == -3)
			cout << "\nCaractere neconforme: exista caractere ce nu sunt cifre, operatii, paranteze sau caracterul 'x'(solutie anterioara).\n";
		else if (valid == -2)
			cout << "\nNumarul introdus contine prea multe virgule(simbolul .).\n";
		else if (valid == -1)
			cout << "\nParantezele nu corespund.\n";
	}
	else	//daca nu rulez in cmd
	{
		cout << "Bine ai venit in aplicatia Calculator!\nAceasta aplicatie este implementata de studenta Carp Ana-Maria, seria C, grupa 1049.\nCu ajutorul acestei aplicatii poti rezolva expresii matematice cu paranteze rotunde si patrate si suporta operatiile urmatoare: \n\t->adunare\t simbol: +\n\t->scadere\t simbol: -\n\t->inmultire\t simbol: *\n\t->impartire\t simbol: /\n\t->ridicare la putere\t simbol: ^\n\t->radical de ordin n\t simbol: # urmat de ordinul radicalului\n";
		do
		{
			if (optiunePreluare == 1)	//preiau de la consola
			{
				string numeFisierBinar = "rezultateEcuatiiPrecedente.bin";
				fstream fOut(numeFisierBinar, ios::out | ios::binary);

				cin >> eq;
				if (optiuneRez == 1) //afisez la consola
				{
					do
					{

						valid = eq.validareEcuatie();
						if (valid == 1 || valid == 0)
						{
							Calculator c1(eq);
							CalculatorInteligent c2(eq);
							Calculator* pc1 = &c1;
							CalculatorInteligent* pc2 = &c2;

							dimensiune = new int[eq.nrOperanzi()];
							if (valid == 0 && optiuneSalvareRezultat == 1)
							{
								expresiePoloneza = pc2->formaPoloneza(dimensiune, &nrOperanzi, x);

								rez = pc2->rezultat(expresiePoloneza, dimensiune, nrOperanzi, &ok);
								if (ok == 2)
									cout << "Nu are sens impartirea la 0! \nNu se poate calcula expresia data.";
								if (ok == 3)
									cout << "Nu putem efectua radical de ordin par din numere negative!\nNu se poate calcula expresia data.";
								vectorEcuatii.push_back(eq);
								vectorRezultate.push_back(rez);
								x = -1;

								if (optiuneSalvareRezultat == 1)
								{
									x = rez;
									pc2->writeToFile(fOut, rez);
								}

							}
							else if (valid == 0 && optiuneSalvareRezultat == 0)
							{
								cout << "Ati introdus in ecuatie x(ca rezultat al ecuatiei anterioare) dar nu ati introdus optiunea corecta pentru a efectua aceasta operatie.\nNu se poate calcula un rezultat pentru ecuatia introdusa.\n";

							}
							else if (valid == 1)
							{
								expresiePoloneza = pc1->formaPoloneza(dimensiune, &nrOperanzi, x);

								rez = pc1->rezultat(expresiePoloneza, dimensiune, nrOperanzi, &ok);
								if (ok == 2)
									cout << "Nu are sens impartirea la 0! \nNu se poate calcula expresia data.";
								if (ok == 3)
									cout << "Nu putem efectua radical de ordin par din numere negative!\nNu se poate calcula expresia data.";
								vectorEcuatii.push_back(eq);
								vectorRezultate.push_back(rez);
								x = -1;

								if (optiuneSalvareRezultat == 1)
								{
									x = rez;
									pc1->writeToFile(fOut, rez);
								}
							}
						}
						else if (valid == -3)
							cout << "\nCaractere neconforme: exista caractere ce nu sunt cifre, operatii, paranteze sau caracterul 'x'(solutie anterioara).\n";
						else if (valid == -2)
							cout << "\nNumarul introdus contine prea multe virgule(simbolul .).\n";
						else if (valid == -1)
							cout << "\nParantezele nu corespund.\n";
						cout << "\n\nDoresti sa continui? Scrie ecuatia urmatoare!\nDaca nu doresti tasteaza exit!\n";
						cin >> eq;

						if (eq.getEcuatie() == "exit" || eq.getEcuatie() == "Exit" || eq.getEcuatie() == "EXIT")
						{
							cout << "\nAti rezolvat " << vectorEcuatii.capacity() << " ecuatii:\n";
							for (ite = vectorEcuatii.begin(); ite != vectorEcuatii.end(); ite++)
								cout << *ite << endl;
							cout << "Cu urmatoarele rezultate:\n";
							for (itr = vectorRezultate.begin(); itr != vectorRezultate.end(); itr++)
								cout << *itr << " ";
						}

					} while (eq.getEcuatie() != "exit" || eq.getEcuatie() == "Exit" || eq.getEcuatie() == "EXIT");
				}
				else if (optiuneRez == 2) //afisez in fisier text
				{
					string numeFisier;
					cout << "Introduceti numele fisierului in care doriti sa salvati rezultatele: ";
					cin >> numeFisier;
					ofstream g(numeFisier);

					do
					{
						valid = eq.validareEcuatie();
						if (valid == 1 || valid == 0)
						{
							Calculator c1(eq);
							CalculatorInteligent c2(eq);
							Calculator* pc1 = &c1;
							CalculatorInteligent* pc2 = &c2;
							dimensiune = new int[eq.nrOperanzi()];

							if (valid == 0 && optiuneSalvareRezultat == 1)
							{
								expresiePoloneza = pc2->formaPoloneza(dimensiune, &nrOperanzi, x);

								rez = pc2->rezultat(expresiePoloneza, dimensiune, nrOperanzi, &ok);
								if (ok == 2)
									cout << "Nu are sens impartirea la 0! \nNu se poate calcula expresia data.";
								if (ok == 3)
									cout << "Nu putem efectua radical de ordin par din numere negative!\nNu se poate calcula expresia data.";

								g << eq;
								g << rez;
								g << endl;
								if (optiuneSalvareRezultat == 1)
								{
									x = rez;
									pc2->writeToFile(fOut, rez);
								}

							}
							else if (valid == 0 && optiuneSalvareRezultat == 0)
							{
								cout << "Ati introdus in ecuatie x(ca rezultat al ecuatiei anterioare) dar nu ati introdus optiunea corecta pentru a efectua aceasta operatie.\nNu se poate calcula un rezultat pentru ecuatia introdusa.\n";

							}
							else if (valid == 1)
							{
								expresiePoloneza = pc1->formaPoloneza(dimensiune, &nrOperanzi, x);

								rez = pc1->rezultat(expresiePoloneza, dimensiune, nrOperanzi, &ok);
								if (ok == 2)
									g << "Nu are sens impartirea la 0! \nNu se poate calcula expresia data.";
								if (ok == 3)
									g << "Nu putem efectua radical de ordin par din numere negative!\nNu se poate calcula expresia data.";
								g << eq;
								g << rez;
								g << endl;
								x = -1;
								if (optiuneSalvareRezultat == 1)
								{
									x = rez;
									pc1->writeToFile(fOut, rez);
								}
							}
							else if (valid == -3)
							{
								g << eq;
								g << "\tCod eroare -3:";
								g << "Caractere neconforme: exista caractere ce nu sunt cifre, operatii, paranteze sau caracterul 'x'(solutie anterioara).";
								g << endl;
							}
							else if (valid == -2)
							{
								g << eq;
								g << "\tCod eroare -2:";
								g << "Numarul introdus contine prea multe virgule(simbolul .).";
								g << endl;
							}
							else if (valid == -1)
							{
								g << eq;
								g << "\tCod eroare -1:";
								cout << "Parantezele nu corespund.";
								g << endl;
							}
						}
						cout << "\n\nDoresti sa continui? Scrie ecuatia urmatoare!\nDaca nu doresti tasteaza exit!\n";
						cin >> eq;
					} while (eq.getEcuatie() != "exit" || eq.getEcuatie() == "Exit" || eq.getEcuatie() == "EXIT");
					cout << "\nAm rezolvat toate ecuatiile introduse la consola si am afisat rezultatele in fisierul text: " << numeFisier;

				}
				else if (optiuneRez == 3) //afisez in fisier binar
				{
					string numeFisierBinar;
					cout << "Introduceti numele fisierului in care doriti sa salvati rezultatele: ";
					cin >> numeFisierBinar;
					fstream fOut(numeFisierBinar, ios::out | ios::binary);

					do
					{
						valid = eq.validareEcuatie();
						if (valid == 1 || valid == 0)
						{
							Calculator c1(eq);
							CalculatorInteligent c2(eq);
							Calculator* pc1 = &c1;
							CalculatorInteligent* pc2 = &c2;

							dimensiune = new int[eq.nrOperanzi()];
							if (valid == 0 && optiuneSalvareRezultat == 1)
							{
								expresiePoloneza = pc2->formaPoloneza(dimensiune, &nrOperanzi, x);
								rez = pc2->rezultat(expresiePoloneza, dimensiune, nrOperanzi, &ok);
								pc2->writeToFile(fOut, rez);
								x = -1;
								if (optiuneSalvareRezultat == 1)
									x = rez;

							}
							else if (valid == 0 && optiuneSalvareRezultat == 0)
							{
								cout << "Ati introdus in ecuatie x(ca rezultat al ecuatiei anterioare) dar nu ati introdus optiunea corecta pentru a efectua aceasta operatie.\nNu se poate calcula un rezultat pentru ecuatia introdusa.\n";

							}
							else if (valid == 1)
							{
								expresiePoloneza = pc1->formaPoloneza(dimensiune, &nrOperanzi, x);
								rez = pc1->rezultat(expresiePoloneza, dimensiune, nrOperanzi, &ok);
								pc1->writeToFile(fOut, rez);
								x = -1;
								if (optiuneSalvareRezultat == 1)
									x = rez;
							}
							cout << "\n\nDoresti sa continui? Scrie ecuatia urmatoare!\nDaca nu doresti tasteaza exit!\n";
							cin >> eq;
						}
					} while (eq.getEcuatie() != "exit" || eq.getEcuatie() == "Exit" || eq.getEcuatie() == "EXIT");
					fOut.close();
					cout << "\nAm rezolvat toate ecuatiile introduse la consola si am afisat rezultatele in fisierul binar: " << numeFisierBinar;

				}
			}
			else if (optiunePreluare == 2)  //preiau din fisier text
			{
				string numeFisierPreluareEcuatii;
				cout << "\nIntroduceti numele fisierului din care se preiau ecuatiile: ";
				cin >> numeFisierPreluareEcuatii;
				ifstream f(numeFisierPreluareEcuatii);
				if (optiuneRez == 1)	//afisez la consola
				{
					while (f >> eq)
					{
						valid = eq.validareEcuatie();
						if (valid == 1)
						{
							cout << eq;
							Calculator c(eq);
							dimensiune = new int[eq.nrOperanzi()];
							expresiePoloneza = c.formaPoloneza(dimensiune, &nrOperanzi, -1);
							rez = c.rezultat(expresiePoloneza, dimensiune, nrOperanzi, &ok);

							if (ok == 2)
								cout << "Nu are sens impartirea la 0! Nu se poate calcula expresia data.\n";
							if (ok == 3)
								cout << "Nu putem efectua radical de ordin par din numere negative! Nu se poate calcula expresia data.\n";
						}
						else if (valid == -3)
						{
							cout << eq;
							cout << "\tCod eroare -3:";
							cout << "Caractere neconforme: exista caractere ce nu sunt cifre, operatii, paranteze sau caracterul 'x'(solutie anterioara).";
							cout << endl;
						}
						else if (valid == -2)
						{
							cout << eq;
							cout << "\tCod eroare -2:";
							cout << "Numarul introdus contine prea multe virgule(simbolul .).";
							cout << endl;
						}
						else if (valid == -1)
						{
							cout << eq;
							cout << "\tCod eroare -1:";
							cout << "Parantezele nu corespund.";
							cout << endl;
						}
						f >> ws;
					}
					f.close();
					cout << "\nAm rezolvat toate ecuatiile din fisierul " << numeFisierPreluareEcuatii << ".";
				}
				else if (optiuneRez == 2)	//afisez in fisier text
				{
					string numeFisier;
					cout << "Introduceti numele fisierului in care doriti sa salvati rezultatele: ";
					cin >> numeFisier;
					ofstream g(numeFisier);
					while (f >> eq)
					{
						valid = eq.validareEcuatie();
						if (valid == 1)
						{
							Calculator c(eq);
							dimensiune = new int[eq.nrOperanzi()];
							expresiePoloneza = c.formaPoloneza(dimensiune, &nrOperanzi, -1);

							rez = c.rezultat(expresiePoloneza, dimensiune, nrOperanzi, &ok);
							g << eq;
							g << rez;
							g << endl;
						}
						else if (valid == -3)
						{
							g << eq;
							g << "\tCod eroare -3:";
							g << "Caractere neconforme: exista caractere ce nu sunt cifre, operatii, paranteze sau caracterul 'x'(solutie anterioara).";
							g << endl;
						}
						else if (valid == -2)
						{
							g << eq;
							g << "\tCod eroare -2:";
							g << "Numarul introdus contine prea multe virgule(simbolul .).";
							g << endl;
						}
						else if (valid == -1)
						{
							g << eq;
							g << "\tCod eroare -1:";
							cout << "Parantezele nu corespund.";
							g << endl;
						}
					}
					g.close();
					cout << "\nGata, am rezolvat ecuatiile si am salvat rezultatele in fisierul " << numeFisier << ".";
				}
				else if (optiuneRez == 3)	//afisez in fisier binar
				{
					string numeFisierBinar;
					cout << "Introduceti numele fisierului in care doriti sa salvati rezultatele: ";
					cin >> numeFisierBinar;
					fstream fOut(numeFisierBinar, ios::out | ios::binary);

					while (f >> eq)
					{
						valid = eq.validareEcuatie();
						if (valid == 1)
						{
							Calculator c(eq);
							dimensiune = new int[eq.nrOperanzi()];
							expresiePoloneza = c.formaPoloneza(dimensiune, &nrOperanzi, -1);

							rez = c.rezultat(expresiePoloneza, dimensiune, nrOperanzi, &ok);
							c.writeToFile(fOut, rez);
						}
					}
					fOut.close();
					cout << "\nGata, am rezolvat ecuatiile si am salvat rezultatele in fisierul binar: " << numeFisierBinar << ".";
					cout << "\nDoriti sa afisati rezultatele si la consola?(Preluand rezultatele din fisierul binar tocmai creat): 1-Da 0-Nu  ";
					int optiuneConsola;
					cin >> optiuneConsola;
					if (optiuneConsola == 1)
					{
						fstream fIn(numeFisierBinar, ios::in | ios::binary);
						Calculator c2;
						while (!fIn.eof())
							c2.readFromFile(fIn);
					}
				}
			}
			if (optiunePreluare != 0)		//daca rulez in cmd nu mai afisez
			{
				cout << "\n\nDoriti sa testati si alte functionalitati ale aplicatiei?    1-DA, 0-NU: ";
				cin >> optiuneContinuare;
			}
			if (optiuneContinuare == 1)
				meniu(&optiunePreluare, &optiuneRez, &optiuneSalvareRezultat);
			else
				cout << "\nLa revedere!\n\n";
		} while (optiuneContinuare == 1);


	}
}
