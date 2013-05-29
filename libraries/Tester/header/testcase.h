#ifndef TESTER__TESTCASE_H
#define TESTER__TESTCASE_H

#include <iostream>
#include <fstream>


using std::cout;
using std::endl;
using std::string;

namespace Tester
{
	/**
		Ez az oszt�ly �soszt�ja minden modul tesztnek. A k�l�nb�z� el�re defini�lt f�ggv�nyek seg�ts�g�vel lehet vizsg�lni egy k�d reag�l�s�t k�l�nb�z� teszt esetekre.
	  */
    class TestCase
    {
		protected:
			string resultName;		/**< a result f�jl neve*/
			std::ofstream* result;	/**< pointer a result f�jlra*/
			

			bool ok;			/**< igaz ha a teszteset nem bukott meg*/
		public:
		
			/**
			  Defult konstruktor.
			  @simple
			  */
		    TestCase();
			
			/**
			  Egyszer� konstruktor.
			  @simple
			  */
		    TestCase(string result_name);
			
			/**
				Destruktor.
				@simple
			*/
			~TestCase();
			
			/**
				B�rmikor �ll�that� a result f�jl
				@simple
			 */
			void setResultFile(string fileName);
			
			/**
				A teszt v�geredm�ny�t k�rdezhetj�k le
				@return igaz, ha �tment, hamis k�l�nben
			  */
			bool isOk() const;
			
			std::string getResultName() const;
	    
			/**
				A teszteset futtat�sa
				@simple
			*/
		    virtual void run() = 0;
	    
			/**
				megbuktatja a tesztesetet, ha igaz �rt�ket kap
			  */
		    void assertTrue(const bool value, const string comment  = "") const;
			
			/**
				megbuktatja a tesztesetet, ha hamis �rt�ket kap
			  */
		    void assertFalse(const bool value, const string comment  = "") const;
	    
			/**
				megbuktatja a tesztesetet, ha expect egyenl� a value-val
			  */
		    void assertEquale(const string expect, const string value, const string comment  = "") const;

		    /**
			    megbuktatja a tesztesetet, ha expect egyenl a value-val
		      */
		    void assertEquale(const int expect, const int value, const string comment  = "") const;
			
			/**
				megbuktatja a tesztesetet, ha expect egyenl� a value-val
			  */
		    void assertEquale(const double expect, const double value, const string comment  = "") const;
			
			/**
				megbuktatja a tesztesetet, ha expect nem egyenl� a value-val
			  */
		    void assertNotEquale(const string expect, const string value, const string comment  = "") const;

		    /**
			    megbuktatja a tesztesetet, ha expect nem egyenl� a value-val
		      */
		    void assertNotEquale(const int expect, const int value, const string comment  = "") const;
			
			/**
				megbuktatja a tesztesetet, ha expect nem egyenl� a value-val
			*/
		    void assertNotEquale(const double expect, const double value, const string comment  = "") const;
		    
			/**
				megbuktatja a tesztesetet, ha expect nagyobb a value-n�l
			*/
		    void assertHigher(const double expect, const double value, const string comment  = "") const;
			
			/**
				megbuktatja a tesztesetet, ha expect nagyobb vagy egyenl� a value-n�l
			*/
		    void assertHigherEquale(const double expect, const double value, const string comment  = "") const;
			
			/**
				megbuktatja a tesztesetet, ha expect kisebb a value-n�l
			*/
		    void assertLower(const double expect, const double value, const string comment  = "") const;
			
			/**
				megbuktatja a tesztesetet, ha expect kisebb vagy egyenl� a value-n�l
			*/
		    void assertLowerEquale(const double expect, const double value, const string comment  = "") const;
	    
			/**
				megbuktatja a tesztesetet, ha value nincs high �s low k�z�tt
			*/
		    void assertNotBetween(const double low, const double high, const double value, const string comment  = "") const;
			
			/**
				megbuktatja a tesztesetet, ha value �s expect k�l�nbs�ge nagyobb mint different
			*/
		    void assertDifferentHigher(const double expect, const double different, const double value, const string comment  = "") const;
	
    };
}

#endif
