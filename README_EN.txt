This project simulates the course of the epidemic using the SIR model. First it accepts the data and then returns the html file.
By clicking on the html file, you will see two graphs. The first graph will show the data from the csv file, and the second graph modeled the data.

To compile the code, please use cmake. Be careful because CMakeLists.txt requires a version of at least 3.20

When you compile the program, you will be able to run it, below is an example of running the program.

./Epidemiological_modeling --real-data <your csv file name>.csv --infectious_days 8 --infections_per_day 0.3 --output index.html

For parameter --real-data please use a csv file
For parameter --infectious_days please use a integer number
For parameter --infections_per_day please use a float number
For parameter --output you can write any name you want but it must be in .html format
