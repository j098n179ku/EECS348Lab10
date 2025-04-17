#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <cctype>
#include <sstream>

/*
    code authored by me, but i did have to reference outside sources to
    figure out how to use substring.
    this functions cleans up the string. the first thing to look for
    is any signs. if it has a sign, then the index should skip the first index so it can
    get to the leading or trailing zeroes. but it also needs to check if theres a
    negative sign. if there is a negative sign, have a boolean to make sure that sign is saved
    now loop through from back to front and front to back in order to create a substring
    that removes any of the leading or trailing zeroes. i used this link to figure out how to
    use the substring command and type casting command to turn an unsigned to an int
    https://stackoverflow.com/questions/22184403/how-to-cast-the-size-t-to-double-or-int-c
    https://www.geeksforgeeks.org/substring-in-cpp/

*/
std::string clean_string(std::string data)
{
    int i = 0; //counter for going forward in the string to look for leading zeroes
    int j = data.length() - 1; //j is the counter that will go backwards in the string using the index length-1 since the index always starts at 0 and the maximum index is 1 less than the length
    bool has_neg = false;

    if (data[i] == '-' || data[i] == '+') //at the start of the string if there is a + or - at index 0, then the index is incremented by 1 so it can keep the sign while removing any leading zeroes
    {
        if(data[i] == '-') //if the data at the 0th index has a negative sign in it, then
        {
            has_neg = true; //lets the program know that there is a negative that needs to be accounted for and passed through at the
        }
        i += 1; //increments the index by 1 to pass over the sign
    }
    while (i < static_cast<int>(data.length()) && data[i] == '0') //while the index i is less than the length of the data, and the data at the index is '0', this is a leading 0 and will be counted so it wont be kept in the substring. this while loop keeps going until it hits a non zero
    {
        i += 1; //increments the i index counter by 1 to check the next index
    }
    while (j > 0 && data[j] == '0') //this for loop goes backwards in the index  looking for any trailing zeroes. it keeps going backwards until it finds a non zero number
    {
        j -= 1; //subtract j since the index should be going backwards in the index to find the trailing zeroes
    }
    if (data[j] == '.') //if the nummbers after the decimal place were all zero, theres no reason to keep that decimal point since its not really doing anything, so no point in
    {
        j -= 1; //subtract j since the index should be going backwards in the index to find the decimal places
    }

    if (has_neg == true)//if there was a negative sign in the string
    {
        return "-" + data.substr(i, j - i + 1); //returns a negative sign concatonated with the substring.substr basically will start at index i, and then take however many indeces of j there is +1 to account for grabbing the last non zero before it subtracted
    }
    else//otherwise, theres no need to add a positive sign since thats kind of what it will default to
    {
        return data.substr(i, j + 1); //.substr basically will start at index i, and then take however many indeces of j there is +1 to account for grabbing the last non zero before it subtracted
    }
}
/*
    the declaration of the function was made from the EECS348 lab template
    code is mostly authored by me, but one thing i did need chatgpt for was
    i needed to add an extra variable to keep track of the index in case
    there was a sign. that is what j is for because otherwise it was
    throwing errors since it was going to the index with the sign in it. i
    also needed to reference this to parse the character as a number and to do static cast
    https://stackoverflow.com/questions/22184403/how-to-cast-the-size-t-to-double-or-int-c
    https://stackoverflow.com/questions/5029840/convert-char-to-int-in-c-and-c

    The number parsing function first checks for a negative sign. if there is,
    then it delimits the start of the number index by 1. then it checks for a decimal
    place. if theres a decimal, that index is saved. if theres no decimal
    then it can go right to creating the number. from the left side of the 
    decimal place it loops backwards and the multiplier gets multiplied by 10
    for each place, the ones place, tens place, and so on. the same applies to
    the numbers to the right of the decimal place, where it multiplies the divisor
    by 10 each time for the tenths, hundreths, thousanth, each time it adds it
    to a total sum in the form of a double
*/
double parse_number(const std::string& expression)//inititalizes the number parsing function to turn the string to a double. it takes the line as a parameter
{
    double sum = 0; //double varaible that will hold the sum of each placement of the string
    bool has_neg = false; //boolean to check to see if the sign is negative so a negative value can be returned
    bool has_dec = false; //boolean to check to see if there is a decimal place in the string
    int decimal_index = -1; //this will hold the index of the decimal place in case there is one
    int j = 0; //this k varaible is used to store the minimum index in the event of a sign
    double multiplier = 1;
    double divisor = 10;
    if (expression[0] == '-')//if the first index of the string has a negative sign
    {
        has_neg = true;//has_neg will be true so it can be returned as a negative number
        j +=1; //adds 1 to j so it can be set as the new index for i to reset to
    }
    for (int i = 0; i < static_cast<int>(expression.length()); i++) //for each index inside of the string, iterate through it to look for any decimal in the indeces
    {
        if (expression[i] == '.')//if a decimal point is found, then that will flag for using the if statement that does work with a decimal point
        {
            has_dec = true; //set has_dec to true so that way the decimal calculating loop can be active
            decimal_index = i;//set the decimal index so that way the loops can start at that index and work backwards for the whole numbers and forwards for the decimals
        }
    }

    if (has_dec == false) //if there is no decimal point in the string
    {
        for (int i = expression.length() - 1; i >= j; i--) //starting at the end of the index,  it loops backwards all the way to j, which will be 0 or 1 depending on if there is a negative sign in the string
        {
            sum += (expression[i] - '0') * multiplier; //changes the character at the index of the expression to be a number, then it multiplies it with the multiplier which varies depending on what place the index is
            multiplier *= 10; // multiplies the multiplier by 10 in order to properly multiply the next place in the index
        }
    }
    else if(has_dec == true)//otherwise, if there are decimals in the string
    {
        for (int i = decimal_index - 1; i >= j; i--) //starting at the index just before the decimal point,  it loops backwards all the way to j, which will be 0 or 1 depending on if there is a negative sign in the string
        {
            sum += (expression[i] - '0') * multiplier; //changes the character at the index of the expression to be a number, then it multiplies it with the multiplier which varies depending on what place the index is
            multiplier *= 10; // multiplies the multiplier by 10 in order to properly multiply the next place in the index
        }
        for (int i = decimal_index + 1; i < static_cast<int>(expression.length()); i++) //starting at the index after the decimal point, it loops forward to the index until it reaches the end, for each loop the dividor gets multiplied by 10 for each place in the decimal
        {
            sum += (expression[i] - '0') / divisor; //changes the character at the index of the expression to be a number, then it divides it with the divisor which varies depending on what place the index is
            divisor *= 10; //multiplies the divisor by 10 to account for the change in place of the next decimal place
        }
    }
    if (has_neg == true)
    {
        sum *= -1; //multiply the sum of the parts by -1 so it can get a negative
    }
    return sum; //return the sum so it can be added with -123.456 in main
}
/*
    code written by me
    the is_valid function grabs the data of the line that was passed through as a string parameter
    this will check to make sure there are no letters in the line, make sure that there are no trailing
    decimal points at the end, and also makes sure there arent more than one instance of a sign. 
    i used this as a reference for the for loop of iterating characters of a string: https://www.geeksforgeeks.org/iterate-over-characters-of-a-string-in-c/
*/
bool is_valid(std::string data) //initializes the is_valid function and passes the line data as a parameter from main
{
    int sign_count = 0; //this counter will be used to make sure there is 1 or less sign in the string
    int decimal_count = 0; //this counter will be used to make sure there is 1 or less decimal in the string
    for(char c: data) //for loop that goes through each character in the data of the string
    {
        if(std::isalpha(c)) //if the character c is any letter, then it will return false
        {
            return false; //returns false to let the program skip over this line
        }
        if(c == '+' || c == '-') //if the character is a + or -, then that means there is a sign that has to be accounted for later
        {
            sign_count += 1; //adds to the sign count to keep track of how many signs are inside of the line
            if(sign_count > 1)//if the sign count is greater than 1, then the format of the string is not valid
            {
                return false; //returns false to let the program skip over this line
            }
        }
        if(c == '.') //if the character equals a period or decimal point
        {
            decimal_count +=1;//increments the decimal counter by 1 to ensure only 1 or 0 decimal points is in the string
            if(decimal_count > 1)//if the decimal count is greater than 1, then the input is not valid
            {
                return false; //returns false so the program can skip the line
            }
        }
    }
    if(data.back() == '.') //if the very end of the string is a deimal place, then it is not a valid format since theres nothing past the decimal
    {
        return false; //returns false to let the program skip over this line
    }
    return true; //if all of these criteria are met to make sure the format is valid, then it is returned true so the program can keep going
}
/*
    Code authored by me
    The main function takes in the file name and tries searching for
    the file. if it finds the file, the number on the line will first
    be checked to make sure it is valid, then if it is, will be cleaned up
    by removing any unecessary decimals and zeroes, and then it gets turned
    into a double. this double will then be added to -123.456 and the result will
    be printed out
*/
int main() //initializes the main function. this grabs the file, uses a loop to grab the numbers in the test file and the pass them through to check validity and then converts the string to a double
{
    std::string file_name; //stores the file name that the user will enter so the program can look for the file
    std::string data; //stores the data on the line. there should only be 1 number on each line that the program needs to check

    std::cout << "Please enter a valid txt file and each number will be added to -123.456: "; //lets the user know to enter a file name and that the program will subtract the double -123.456 to the new double
    std::cin >> file_name; //user input saves to file_name so the program can look for the file in the directory
    std::ifstream file(file_name);  //ifstream command to let the program look for the file
    if (!file) //if the file was not found, then the program will let the user know and end the program
    {
        std::cout << "File not found, exitting "; //let the user know that the program could not be found
        return 0;//returns and ends the program so it can be started again
    }
    while (std::getline(file, data))//this while loops goes through the data line by line until it gets to the last line. while loop is used to parse through a dynamic amount of lines in a text file
    {
        if(is_valid(data)) //calls the is_valid boolean function to check the line to make sure it is valid. if it is valid, then it continues, if its not valid, it tells the user and skips the line
        {
            std::string cleaned_string = clean_string(data); //parses the data through the clean_string function to get rid of any leading or trailing zeroes to clean it up so it can be converted to a double
            double conv_string = parse_number(cleaned_string);//passes the cleaned string to the parse number to convert it into a double, saving it as a conversion from string to double
            double sum = conv_string - 123.456; //saves the sum of the newly made double with -123.456 and saves it as a new variable so it can be outputted to the user to show the result
            std::cout << "\n" << sum << "\n"; //prints out the sum of the two numbers for the user to look at
        }
        else //otherwise, if the string was not in a valid format
        {
            std::cout << "\nLine not valid\n"; //let the user know that the string was not a valid format and will be skipped
        }
    }
    return 0;//returns to end the program when the loop finishes
}