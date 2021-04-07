Design Manual

Due to the time constraints of this project, it interacts with the user using a command line interface. 

Command line interface:

To build the project, run the command: make 

This will create an executable file called main

To start the program run: ./main

Commands within the program:

The goal of the program is to build an interface to a memory-based database for data that is sorted using dated timestamps, which would allow the user to insert, select, and delete from that database using a simple interface. It works by the program ingesting a simple CSV file, that contains the primary key as the first column of the database. The only caveat is that for the first implementation, the primary key must be datestamp that is in the format %d/%m/%Y i.e. 12/7/1998. (For an example file, please look at top_chart_data.csv)

Once the data file is read, it will prompt the user to do the following commands:
INSERT - insert a new data point into the database that must contain a primary key value (i.e. date). 
SELECT - select data using the primary key
DELETE - delete a value from the table using the primary key

There are clear instructions on the prompt to how to execute these commands, and they must be written syntactically in the same way as the instructions indicate to be executed correctly. 

Syntactic Command instructions:

COMMANDS: 
 
  1. SELECT <PK>, ..., <columnN> FROM table [WHERE <PK> = x]
  2. INSERT (<PK>, ..., <columnN>) (<PK>, ..., <valueN>)
  3. DELETE WHERE PK = x


If a select query is specified, then it would present a table on the console with the results of the query. 
For example, the following query with the top_chart_data.csv file would result in the following console output:

SELECT date, rank, song, artist FROM table WHERE date = 17/12/1966
 
+----------+----+--------------------+-----------------------+
|date      |rank|song                |artist                 |
+----------+----+--------------------+-----------------------+
|17/12/1966|1   |Winchester Cathedral|The New Vaudeville Band|
+----------+----+--------------------+-----------------------+



Like in SQL, you can use the * command in the select query to take all columns from the table. E.g:

SELECT * FROM table WHERE date = 17/12/1966
 
+-----------------------+----------+---------+---------+----+--------------------+--------------+
|artist                 |date      |last-week|peak-rank|rank|song                |weeks-on-board|
+-----------------------+----------+---------+---------+----+--------------------+--------------+
|The New Vaudeville Band|17/12/1966|3        |1        |1   |Winchester Cathedral|8             |
+-----------------------+----------+---------+---------+----+--------------------+--------------+
 

If you do not specify a where clause, all rows of the table would be presented. For our interface, in order to minimise the amount that is printed on the console, considering the number of rows in the table could be infinite, we only will print the first 50 rows of the table. 
