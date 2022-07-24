#include <iostream>
#include <string>
using namespace std;

//function declarations
int gcd(int first, int second);
int lcm(int first, int second);


//Fraction class
class Fraction {

private:

	int numerator;
	int denominator;
	int whole_part;
	bool ismixed;
	void reduce(int *numerator, int *denominator)
	{
		int gcd_n = gcd(*numerator, *denominator);
		*numerator /= gcd_n;
		*denominator /= gcd_n;
	};

public:

	Fraction(int numerator, int denominator, int whole_part = 0)
	{
		if (whole_part != 0) {
			if (numerator < 0 && denominator < 0) {
				numerator *= -1;
				denominator *= -1;
			}
			else if (numerator < 0 || denominator < 0) {
				denominator *= -1;
				if (numerator > 0) numerator *= -1;
			}
			reduce(&numerator, &denominator);
			ismixed = true;
			if (numerator > denominator && denominator != 1 && !(numerator < 0 && denominator < 0))
			{
				whole_part += numerator / denominator;
				this->numerator = numerator % denominator;
				this->denominator = denominator;
				this->whole_part = whole_part;
			}
			else {
				this->numerator = numerator;
				this->denominator = denominator;
				this->whole_part = whole_part;
			}
			
		}
		else {
			if (numerator < 0 && denominator < 0) {
				numerator *= -1;
				denominator *= -1;
			}
			else if (numerator < 0 || denominator < 0) {
				denominator *= -1;
				if (numerator > 0) numerator *= -1;
			}
			reduce(&numerator, &denominator);
			if (numerator > denominator && denominator != 1 && !(numerator < 0 && denominator < 0))
			{
				this->whole_part = numerator / denominator;
				this->numerator = numerator % denominator;
				this->denominator = denominator;
				ismixed = true;
			}
			else {
				this->numerator = numerator;
				this->denominator = denominator;
				ismixed = false;
			}
		}
	};

	void info() {
		if (ismixed)
			cout << " " << whole_part << " " << numerator << "/" << denominator << " ";
		else
			cout << " " << numerator << "/" << denominator << " ";
	}

	bool isGreaterThan(Fraction that)
	{
		if (ismixed && that.ismixed)
			return whole_part > that.whole_part;

		else if (!ismixed && that.ismixed) {
			int new_temporary_numerator_that = that.whole_part * that.denominator + that.numerator;
			int res_1 = numerator * that.denominator;
			int res_2 = new_temporary_numerator_that * denominator;
			return res_1 > res_2;
		}
		else if (ismixed && !that.ismixed) {
			int new_temporary_numerator = whole_part * denominator + numerator;
			int res_1 = new_temporary_numerator * that.denominator;
			int res_2 = that.numerator * denominator;
			return res_1 > res_2;
		}
		else {
			int new_temporary_numerator = numerator;
			int new_temporary_numerator_that = that.numerator;
			int lcm_n = lcm(denominator, that.denominator);
			int additional_multiplier = denominator * lcm_n;
			new_temporary_numerator *= additional_multiplier;
			additional_multiplier = that.denominator * lcm_n;
			new_temporary_numerator_that *= additional_multiplier;
			return new_temporary_numerator > new_temporary_numerator_that;
		}
	};
	bool isLessThan(Fraction that) {  
		if (ismixed && that.ismixed)
			return whole_part < that.whole_part;

		else if (!ismixed && that.ismixed) {
			int new_temporary_numerator_that = that.whole_part * that.denominator + that.numerator;
			int res_1 = numerator * that.denominator;
			int res_2 = new_temporary_numerator_that * denominator;
			return res_1 < res_2;
		}
		else if (ismixed && !that.ismixed) {
			int new_temporary_numerator = whole_part * denominator + numerator;
			int res_1 = new_temporary_numerator * that.denominator;
			int res_2 = that.numerator * denominator;
			return res_1 < res_2;
		}
		else {
			int new_temporary_numerator = numerator;
			int new_temporary_numerator_that = that.numerator;
			int lcm_n = lcm(denominator, that.denominator);
			int additional_multiplier = denominator * lcm_n;
			new_temporary_numerator *= additional_multiplier;
			additional_multiplier = that.denominator * lcm_n;
			new_temporary_numerator_that *= additional_multiplier;
			return new_temporary_numerator < new_temporary_numerator_that;
		}
	};
	bool isEqual(Fraction that)
	{
		if (!isGreaterThan(that) && !isLessThan(that)) return true;
		return false;
	};

};

//function which transforms string into integer denominator/integer numerator
//set 1 to get denominator, else to numerator
int toInteger(string something, int setting) {
	if (setting == 1) {
		something.erase(remove(something.begin(), something.end(), ' '), something.end());
		reverse(something.begin(), something.end());
		string intg = something;
		intg.erase(intg.find("/"));
		reverse(intg.begin(), intg.end());
		return stoi(intg);
	}
	else {
		something.erase(remove(something.begin(), something.end(), ' '), something.end());
		string intg = something;
		intg.erase(intg.find("/"));
		reverse(intg.begin(), intg.end());
		return stoi(intg);
	}
}

//function which transforms string into decimal fraction
//set 0 to get whole part, set 1 to get denominator, else to numerator
int toIntegerForD(string text, int setting) {
	string other_part = text;
	reverse(other_part.begin(), other_part.end());
	other_part.erase(other_part.find("."));
	string whole_part = text.erase(text.find("."));
	if (setting == 0) return stoi(whole_part);
	else if (setting == 1) return int(pow(10, other_part.size()));
	else return stoi(other_part);

}

//function which looks for the greatest common divisor for fraction reduce
int gcd(int first, int second) { return second == 0 ? first : gcd(second, first % second); }

//function which looks for the least common multiple for fraction operations
int lcm(int first, int second){ return (first * second) / gcd(first, second); }

//function to check symbol availability in string text
bool isin(string text, char symbol) {
	for (int i = 0; i < text.size(); i++) if (text[i] == symbol) return true;
	return false;
}

//function which check if text is digit
bool STRisdigit(string text) {
	bool minuscheck = false;
	for (int i = 0; i < text.size(); i++) {
		if (isdigit(text[i]) || ((text[i] == '-' && minuscheck == false))) {
			minuscheck = true;
			continue;
		}
		return false;
	}
	return true;
}

//function which check the correctness of the text format for decimals fractions
bool iscorrectForFloat(string text)
{
	if (!isin(text, '.')) return false;
	int check = 0;
	for (int i = 0; i < text.size(); i++)
		if (!isdigit(text[i])) check++;
	if (check == 0) return false;
	string other_part = text;
	reverse(other_part.begin(), other_part.end());
	other_part.erase(other_part.find("."));
	string whole_part = text.erase(text.find("."));
	bool minuscheck = false;
	for (int i = 0; i < whole_part.size(); i++) {
		if (!isdigit(other_part[i]) && ((other_part[i] != '-') || (other_part[i] == '-' && minuscheck == true))) return false;
		if (other_part[i] == '-') minuscheck = true;
	}

	for (int i = 0; i < other_part.size(); i++)
		if (!isdigit(other_part[i])) return false;
}

//function which check the correctness of the text format for default fractions
bool iscorrectForString(string text) 
{
	if (!isin(text, '/')) return false;
	int check = 0;
	for (int i = 0; i < text.size(); i++)
		if (!isdigit(text[i])) check++;
	if (check == 0) return false;
	string other_part = text;
	reverse(other_part.begin(), other_part.end());
	other_part.erase(other_part.find("/"));
	string whole_part = text.erase(text.find("/"));
	bool minuscheck = false;

	for (int i = 0; i < whole_part.size(); i++) {
		if (!isdigit(whole_part[i]) && ((whole_part[i] != '-') || (whole_part[i] == '-' && minuscheck == true))) return false;
		if (whole_part[i] == '-') minuscheck = true;
	}

	minuscheck = false;

	for (int i = 0; i < other_part.size(); i++) {
		if (!isdigit(other_part[i]) && ((other_part[i] != '-') || (other_part[i] == '-' && minuscheck == true))) return false;
		if (other_part[i] == '-') minuscheck = true;
	}
}

//formalization and realization
int main()
{
	bool isdecimal = false, ismixed_1st = false, ismixed_2nd = false;
	cout << "choose your fractions format:\n<0> - default;\n<1> - decimal;\n-> ";
	int choose;
	cin >> choose;
	while (choose != 1 && choose != 0) {
		cout << "\nerror! try again\n-> "; cin >> choose;
	}
	isdecimal = choose;
	string _1st, _2nd, wp_1st = "0", wp_2nd = "0";
	if (!isdecimal) {
		cout << "does your first fraction have a whole part?\n<1> - yes;\n<0> - no;\n-> ";
		cin >> choose;
		while (choose != 1 && choose != 0) {
			cout << "\nerror! try again\n-> "; cin >> choose;
		}
		ismixed_1st = choose;
		if (ismixed_1st) {
			cout << "input whole part'\n-> ";
			cin >> wp_1st;
			while (!STRisdigit(wp_1st) && wp_1st[0]) {
				cout << "\nerror! try again\n-> "; cin >> wp_1st;
			}
		}
		cout << "input your first fraction in format like that'\n(n / d)\n-> ";
		cin >> _1st;
		while (!iscorrectForString(_1st)) {
			cout << "\nerror! try again\n-> "; cin >> _1st;
		}
		choose = 0;
		cout << "does your second fraction have a whole part?\n<1> - yes;\n<0> - no;\n-> ";
		cin >> choose;
		while (choose != 1 && choose != 0) {
			cout << "\nerror! try again\n-> "; cin >> choose;
		}
		ismixed_2nd = choose;
		if (ismixed_2nd) {
			cout << "input whole part'\n-> ";
			cin >> wp_2nd;
			while (!STRisdigit(wp_2nd)) {
				cout << "\nerror! try again\n-> "; cin >> wp_1st;
			}
		}
		cout << "input your second fraction in format like that'\n(n / d)\n-> ";
		cin >> _2nd;
		while (!iscorrectForString(_2nd)) {
			cout << "\nerror! try again\n-> "; cin >> _2nd;
		}
		Fraction one(toInteger(_1st, 0), toInteger(_1st, 1), stoi(wp_1st));
		Fraction two(toInteger(_2nd, 0), toInteger(_2nd, 1), stoi(wp_2nd));
		cout << endl;
		if (one.isGreaterThan(two)) {
			one.info();
			cout << ">";
			two.info();
		}
		else if (one.isLessThan(two)) {
			one.info();
			cout << "<";
			two.info();
		}
		else {
			one.info();
			cout << "=";
			two.info();
		}
	}
	else {
		cout << "input your first decimal fraction\n-> "; 
		cin >> _1st;
		while (!iscorrectForFloat(_1st)) {
			cout << "\nerror! try again\n-> "; cin >> _1st;
		}
		cout << "input your second decimal fraction\n-> ";
		cin >> _2nd;
		while (!iscorrectForFloat(_2nd)) {
			cout << "\nerror! try again\n-> "; cin >> _2nd;
		}
		Fraction one(toIntegerForD(_1st, 2), toIntegerForD(_1st, 1), toIntegerForD(_1st, 0));
		Fraction two(toIntegerForD(_2nd, 2), toIntegerForD(_2nd, 1), toIntegerForD(_2nd, 0));
		cout << endl;
		if (one.isGreaterThan(two)) {
			one.info();
			cout << ">";
			two.info();
		}
		else if (one.isLessThan(two)) {
			one.info();
			cout << "<";
			two.info();
		}
		else {
			one.info();
			cout << "=";
			two.info();
		}
	}
}

