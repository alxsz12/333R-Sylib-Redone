
# ------------------------------------------------- #
# This file is used to take data printed into the   #
# PROS terminal in a CSV file format, and graph it  #
# using plotly and pandas to create an interactive  #
# graph to be able to visualize what is happening   #
# with our motors and to better help debug and tune #
# ------------------------------------------------- #

# ------------------------------------------------- #
# This is a seperate file not intended to be        #
# compiled with the main project. It is intended to #
# be run serperatatly from the main program.        #
# ------------------------------------------------- #

# ------------------------------------------------- #
# In order to use this file there are two things    #
# that you need to do. First is make a file called  #
# data.csv, and then from there you need to         #
# activate the Integrated PROS Brain Terminal,      #
# where the data will be feed into. When you are    #
# done collecting data, simply copy it into the     #
# data.csv file, and then compile and run this      #
# file through the terminal. An alternative would   #
# to send the data directly to the CSV file. To do  #
# this you would open the termianl like this        #
#           pros terminal > data.csv                #
# And if you want to remove the banner at the top,  #
# you would send this to the terminal               #
# ------------------------------------------------- #
# prosv5 terminal --no-banner | tail -n +19 > data.csv #
# ------------------------------------------------- #

import plotly.express as px
import pandas as pd

df = pd.read_csv('data.csv',delimiter=',',names =['time (ms)','target','speed','torque','applied'],
                        skiprows=50,encoding='utf-16',skipfooter=50,engine='python')
plot = px.scatter(df,x='time (ms)',y=['target','speed','torque','applied'],height=800)
plot.show()