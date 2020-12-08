#include <iostream>
#include <algorithm>
#include <map>
#include <random>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

static map<string, double> motion;
static map<string,string> unknown;
bool is_practice = false; // checks if u want to practice or just solve a question
enum class initializeVariables{initialVelocity,acceleration,finalVelocity,timeDuration,length_of_distance};


void calculate(); 
void calculator(string &u,string &v,string &a,string &t,string &s);
void practice();

double chooseValue(int c);
void get_value (const string &a) { cout << "Input your " << a << ":"; }
void evaluate (string a);
double no (char n);
string variable (char n);
bool check (char n);

bool three_var(string a, string b, string c);
bool five_var (string u,string a,string v,string t,string s);
bool invalidoperation(string a,string v,string s);
bool check_u_or_a(string a,string u);

double quadratic1 (double a,double u,double s);
double quadratic2 (double a,double u,double s);

void solve_initial_velocity (string &u,string v,string a,string t,string s);
void solve_acceleration (string u,string v,string &a,string t,string s);
void print_motion();
void print_unknowns();

 


int main()

{
	cout << "Do u want to practice(Y or N)" << std::endl;
	char p;
	cin >> p;
	srand(time(nullptr)); 
	if (p == 'Y' || p == 'y')
	{
		cout << "How many times do u want to practice" << endl;
		int times;cin >> times;
        ::is_practice = true;// sets practice mode to true
		for (int i =0 ; i < times; ++i)
		{
			practice();
			system("pause");
			system("cls");
		}
	}
	
	::is_practice = false; // sets practice mode to false
    cout << "NOTE: Answer may/may not be correct when 4 parameters are given due"
         << " to inconsistency of any of the given parameters";
	cout << "Welcome to my motion calculator."
		 << "\nInput your values and you will get your reults.\n\n\n";
    calculate();
	return 0;
}

bool three_var(string a, string b, string c)
// returns true if values for all corresponding unknowns are known
{
    map<string,double>::iterator a1 = motion.find(a);
    map<string,double>::iterator b1 = motion.find(b);
    map<string,double>::iterator c1 = motion.find(c);
    if (a1 == motion.end() || b1 == motion.end() || c1 == motion.end()) return false; //one of 3  variables is/are not available
    else return true;
}


bool check_u_or_a(string a,string u)
// returns true if acceleration or initial velocity is missing
{
    map<string,double>::iterator a1 = motion.find(a);
    map<string,double>::iterator b1 = motion.find(u);
    if (a1 == motion.end() && b1 == motion.end())   return true;
    return false;
}

void print_motion()
//print out all values in motion
{
    std::cout << "Values:\n ";
	for (const auto &i : motion )
        cout << '\t' << i.first << " = " << i.second << '\n';
}

void print_unknowns()
// prints out all unknowns
{
	for (const auto &i : unknown)
        cout << '\t' << i.first << " => " << i.second << '\n';
}


double no (char n)
// stores parameter in a double
{
    cin.putback(n);
    double num;
    cin >> num;
    return num;
}
string variable (char n)
// stores parameter in a string
{
    cin.putback(n);
    string var;
    getline(cin,var);
    return var;
}

bool check (char n)
// returns true if parameter value is a string(begins with a letter)
{
    if (isalpha(n)) return true;
    else if(isdigit(n))  return false;
}

void evaluate (string a)
// checks if parameter is string or double
{
    char n;
    cin >> n;
    if (check(n) == true)  unknown[a] = variable(n);
    else if (check(n) == false )    motion[a] = no(n);
}

double quadratic1 (double a,double u,double s)
// solves for a value using quadratic formula
{
    //0.5at*t + u*t - s = 0
    double  d = std::sqrt ( (u * u) - (4 * 0.5 * a * s * - 1) ) ;
    d = (-u + d ) / (2 * 0.5 * a);
    return d;
}


double quadratic2 (double a,double u,double s)
// solves for a value using quadratic formula
{
    //0.5at*t + u*t - s = 0
    double  d = std::sqrt ( (u * u) - (4 * 0.5 * a * s * - 1) ) ;
    d = (-u - d ) / (2 * 0.5 * a);
    return d;
}

void solve_initial_velocity(string &u,string v,string a,string t,string s)
// calculate initial velocity if present in unknowns
{
    map<string,string>::iterator it = unknown.find(u);
    if (it == unknown.end()) return;// initial velocity is not present in unknown,hence it should be in motion
	else if (three_var(s,t,a))
    {
        double d;
        d = ( motion[s] - 0.5 * motion[a] * motion[t] * motion[t] ) / motion[t];
        motion[it->second] = d;
        u = it->second; motion[u] = d;
    }
    else if (three_var(v,a,t))
    {
        double d;
        d = motion[v] - (motion[a] * motion[t]);
        motion[it->second ] = d;
        u = it->second; motion[u] = d;
    }
    else if (three_var(v,a,s))
    {
        double d;
        if ( ( 2 * motion[a] * motion[s] ) > (motion[v] * motion[v]))
        {
            cout << "Cannot find root of negative number because v^2 > 2as;\n";
            return ;
        }
        d = (sqrt( (motion[v] * motion[v]) - (2 * motion[a] * motion[s]) ));
        motion[it->second] = d;
        u = it->second; motion[u] = d;
    }
}

void solve_acceleration(string u,string v,string &a,string t,string s)
// calculates acceleration if present in unknowns
{
   map<string,string>::iterator it = unknown.find(a);
   if (it == unknown.end()) return;  // acceleration is not present in unknown,hence it is should be in motion
   else if (three_var(v,u,t))
    {
        double d;
        d = ( motion[v] - motion[u] ) / motion[t];
        motion[it->second] = d;
        a = it->second; motion[a] = d;
    }
    else if (three_var(v,u,s))
    {
        double d;
        d = ( motion[v] * motion[v] - motion[u] * motion[u]) / ( 2 * motion[s]);
        motion[it->second] = d;
        a = it->second; motion[a] = d;
    }
    else if (three_var(s,u,t))
    {
        double d;
        d =  (motion[s] - motion[u] * motion[t]) / ( 0.5 * motion[t] * motion[t] );
        motion[it->second] = d;
        a = it->second; motion[a] = d;
    }
}

bool five_var (string u,string a,string v,string t,string s)
// returns true if all values are present
{
    map<string,double>::iterator u1 = motion.find(u);
    map<string,double>::iterator a1 = motion.find(a);
    map<string,double>::iterator v1 = motion.find(v);
    map<string,double>::iterator t1 = motion.find(t);
    map<string,double>::iterator s1 = motion.find(s);
    if (u1 == motion.end() || a1 == motion.end() || v1 == motion.end()
        || t1 == motion.end() || s1 == motion.end()) return false; //one of 5  variables is/are not available
    else return true;

}

bool invalidoperation(string a,string v,string s)
// returns true if 2as > v squared
{
    if ( ( 2 * motion[a] * motion[s] ) > (motion[v] * motion[v]))
    {
        cout << "Cannot find root of negative number\n";
        system("pause");
        return true;
    }
    else return false;
}

double chooseValue(initializeVariables c)
// uses random-number generator to get values for unknowns
{
	double value;
	switch(c)
	{
		case initializeVariables::initialVelocity:
			value = rand() % 81; // initial velocity between 1 and 80
			break;
		case initializeVariables::acceleration:
			value = rand() % 31 - 15; // acceleration between -15 and 15
			break;
		case initializeVariables::timeDuration:
			value = rand() % 601; // time between 1 and 600(10 min)
			break;
		case initializeVariables::length_of_distance:
			value = rand() % 5001; // distance between 1 and 5000
			break;
		case initializeVariables::finalVelocity:
			value = rand() % 151; // final velocity between 1 and 150
			break;
		default:
			value = -1;
			break;
	}
	return value;
}

void practice()
// sets random question for u(interface for practicing)
{
	motion.clear();
	unknown.clear();

    string u = "initial velocity(m/s)";
	string v = "final velocity(m/s)";
    string a = "acceleration(m/s^2)"; 
	string t = "time(s)";
	string s = "change in distance(m)";

	string question[] = {u,v,a,t,s};
	initializeVariables nums[6] = {initializeVariables::acceleration,initializeVariables::finalVelocity,
                                   initializeVariables::initialVelocity,initializeVariables::length_of_distance,
                                   initializeVariables::timeDuration,initializeVariables::length_of_distance};
	std::random_shuffle(nums,nums + 5); //random_shuffle doesn't touch last element 
//	for (int i : nums ) cout << i << '\t';cout << endl; 

// generates random values for three random unknows
	double variable1 = chooseValue(nums[0]),variable2 = chooseValue(nums[1]),variable3 = chooseValue(nums[2]);

	cout << question[ (int)nums[0] ] << ':' << variable1 << '\n'; // shows user value of an unknown
    motion[ question[ (int)nums[0] ] ] = variable1;// sets the value of unknown to std::map
	cout << question[ static_cast<int>(nums[1]) ] << ':' << variable2 << '\n';
    motion[ question[ static_cast<int>(nums[1]) ] ]= variable2;
	cout << question[ static_cast<int>(nums[2]) ] << ':' << variable3 << '\n';
    motion[ question[ static_cast<int>(nums[2]) ] ]=  variable3;
	
// shows user the parameters without a given value    
    cout << question[ static_cast<int>(nums[3]) ] << ':' << '\n'
		 << question[ static_cast<int>(nums[4]) ] << ':' << "\nPress Enter to get answer\n\n";

// sets runtime obtained string to unknown values	
    unknown[question[ static_cast<int>(nums[3]) ] ] = question[ static_cast<int>(nums[3]) ];
	unknown[question[ static_cast<int>(nums[4]) ] ] = question[ static_cast<int>(nums[4]) ];
	
    system("pause");
	calculator(u,v,a,t,s);// solves the generated problem
}


void calculator(string &u,string &v,string &a,string &t,string &s)
// solves the problem
{
	while(true)
	{
        // searches for initial velocity or acceleration if possible
        solve_initial_velocity(u,v,a,t,s);
        solve_acceleration(u,v,a,t,s);

         if ( check_u_or_a(a,u) )
        //acceleration or initial velocity must be present to solve
        {
            cout << "\nabsent acceleration and initial velocity\n";
            cout << "acceleration or initial velocity needed."
                 << "\nYou have " << unknown.size() << " variables"
                 << ".\nVariables:\n";
            print_unknowns();
            unknown.clear();
            motion.clear();
            system("pause");
            system("cls");
			if (!is_practice) calculate(); // if not in practice mode,try again
			else practice();// if in practice mode,retry 
        }
        else if (three_var(v,a,s) && invalidoperation(a,v,s))
        // checks for the invalid case where 2as > v squared
        {
        //    print_motion();
            unknown.clear();
            motion.clear();
            system("cls");
 		    if (!is_practice) calculate();
			else practice();

        }

        else if (five_var(u,a,v,t,s))
        // if all values are present
        {
            system("cls");
            print_motion();
			return;//  break;
        }

        else if (motion.size() < 3)
        // at least 3 known values are need for calculating
        {
            cout << "\ni need at least 3 known values\n";
            cout << "Insufficient variables"
                 << "\nYou have " << unknown.size() << " variables"
                 << ".\nVariables:\n";
            print_unknowns();
            unknown.clear();
            motion.clear();
            system("pause");
            system("cls");
   			if (!is_practice) calculate();
			else practice();

        }
        else
        {
            for (map<string,string>::iterator it = unknown.begin() ; it != unknown.end(); ++it)
            // solves for distance(s),time(t) and final velocity(v)
            {
                if (it->first == s)
                //if distance is unknown
                {
                    if (three_var(a,u,t))
                    {
                        double d;
                        d = motion[u] * motion[t] + 0.5 * motion[a] * motion[t] * motion[t];
                        motion[it->second] = d;
                    }
                    else if (three_var(a,u,v))
                    {
                        double d;
                        d =  (motion[v] * motion[v] - motion[u] * motion[u]) / (2 * motion[a]);
                        motion[it->second] = d;
                    }
                }
                else if (it->first == t)
                // if time is unknown
                {
                    if (three_var(s,u,a))
                    {
                       double d1,d2;
                        d1 = quadratic1(motion[a],motion[u],motion[s]);
                        d2 = quadratic2(motion[a],motion[u],motion[s]);
                        motion[it->second] = d1;
                        motion["2nd " + it->second] = d2;
                    }
                    else if (three_var(v,u,a))
                    {
                        double d;
                        d = ( motion[v] - motion[u] ) /motion[a];
                        motion[it->second] = d;
                    }
                }
                else if (it->first == v)
                //if v is unknown
                {
                    if (three_var(u,a,t))
                    {
                        double d;
                        d = motion[u] + motion[a] * motion[t];
                        motion[it->second] = d;
                    }
                   else if (three_var(u,a,s))
                    {
                        double d;
                        d = std::sqrt(( motion[u] * motion[u] ) + ( 2 * motion[a] * motion[s] )  );
                        motion[it->second] = d;
                    }
                }
            }
            system("cls");
            print_motion();
            return;
        }
	}
}

void calculate()
// interface for calculation for user
{
	motion.clear();
	unknown.clear();
    string u = "initial velocity(m/s)";
    get_value(u);
    evaluate(u);

    string a = "acceleration(m/s^2)";
    get_value(a);
    evaluate(a);

    string v = "final velocity(m/s)";
    get_value(v);
    evaluate(v);

    string t = "time(s)";
    get_value(t);
    evaluate(t);

    string s = "change in distance(m)";
    get_value(s);
    evaluate(s);
	
	calculator(u,v,a,t,s);
}

