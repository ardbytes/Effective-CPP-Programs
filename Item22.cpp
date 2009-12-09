// Declare data members private

class NightDanceBarCustomer
{
 // Big mistake!!
 public:
 	int age;
	
};

int main()
{
 NightDanceBarCustomer a;
 //A 10 year kid is a night dance bar customer!
 a.age = 10;
}

/*
Notes:

Making data members private:

	-> will allow you to control class invariants,
	-> define access schemes to the data members,
	-> encapsulate data. ( You could compute age from date of birth )
*/	  

