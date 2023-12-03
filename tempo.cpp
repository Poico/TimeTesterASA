#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <utility>
#include <regex>

using namespace std;

int main()
{
  ifstream inputFile("tempo.txt");
  list<pair<int, double>> times;
  string line;
  string out;
  pair<int, double> time;
  int extractedNumber;
  while (getline(inputFile, line))
  {
    // if (time.first != 0 && time.second != 0)
    // {
    //   times.push_back(time);
    //   pair<int, int> time;
    // }

    istringstream iss(line);
    if (line.find("teste") != string::npos)
    {
      stringstream number;

      for (char ch : line)
      {
        if (isdigit(ch))
        {
          number << ch;
        }
      }

      int extractedNumber;
      number >> extractedNumber;
      time.first = stoi(number.str());
    }
    else if (line.find("real") != string::npos)
    {
      std::regex number_regex("[0-9]+[.]?[0-9]*"); // Matches decimal numbers

      std::sregex_iterator it(line.begin(), line.end(), number_regex);
      std::sregex_iterator end;
      int i = 0;
      double sum = 0;
      while (it != end)
      {
        std::smatch match = *it;
        if (i == 0)
        {
          sum += (stod(match.str()) * 60);
        }
        else
        {
          sum += (stod(match.str()));
        }
        ++it;
        i++;
      }
      time.second = sum;
      times.push_back(time);
      time.first = 0;
      time.second = 0;
    }
    // string label;
    // double value;

    // if (iss >> label >> value)
    // {
    //   times.push_back(make_pair(label, value));
    // }
  }
  times.sort();
  inputFile.close(); // Close the file
                     // Create a file to store data
  std::ofstream dataFile("plot_data.txt");
  if (!dataFile.is_open())
  {
    std::cerr << "Error creating data file!" << std::endl;
    return 1;
  }

  // Write data from the list to the file
  for (const auto &pair : times)
  {
    dataFile << pair.first << " " << pair.second << "\n";
  }
  dataFile.close();

  // Open a pipe to gnuplot
  FILE *gnuplotPipe = popen("gnuplot -persistent", "w");
  if (!gnuplotPipe)
  {
    std::cerr << "Error opening gnuplot pipe!" << std::endl;
    return 1;
  }

  // Send commands to gnuplot
  fprintf(gnuplotPipe, "set title 'Plot from std::list'\n");
  fprintf(gnuplotPipe, "plot 'plot_data.txt' with linespoints\n");

  // Close gnuplot pipe
  pclose(gnuplotPipe);
}
